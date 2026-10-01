import FamilyTreeQt
import QtQuick
import QtQuick.Controls

Item {
    id: root

    signal personSelected(var person)
    signal closeRequested()

    property var selectedPerson: null
    property rect bounds: FamilyTreeController.treeBounds
    property bool focusMode: false
    property var pendingCenterTarget: null

    // Centers the viewport on `person`'s card, animating both pan
    // and (if needed) zoom back to a comfortable level. Used for
    // "View Parents/Children/Spouse" navigation from the info panel,
    // and for breadcrumb / search jumps -- the camera moves instead
    // of the screen simply changing, per the design brief.
    function centerOnPerson(person) {
        if (person === null)
            return

        nodeRepeater.centerOn(person)
    }

    // Re-centering after a collapse/expand toggle has to wait a
    // tick for the layout to update, and by then the PersonCard
    // delegate that triggered it may already be gone (the model
    // reset destroys and recreates delegates). Routing the deferred
    // call through a root-level property instead of a closure over
    // the delegate keeps it alive regardless.
    onPendingCenterTargetChanged: {
        if (pendingCenterTarget !== null) {
            var target = pendingCenterTarget
            Qt.callLater(function() { centerOnPerson(target) })
        }
    }

    function isRelevant(p) {
        if (selectedPerson === null || p === null)
            return true
        if (p === selectedPerson) return true
        if (selectedPerson.father === p) return true
        if (selectedPerson.mother === p) return true
        if (selectedPerson.spouse === p) return true
        for (var i = 0; i < selectedPerson.children.length; i++)
            if (selectedPerson.children[i] === p) return true
        return false
    }

    onSelectedPersonChanged: {
        if (selectedPerson !== null)
            centerOnPerson(selectedPerson)
    }

    focus: true
    Keys.onPressed: (event) => {
        if (event.key === Qt.Key_F) { focusMode = true; event.accepted = true }
        else if (event.key === Qt.Key_A) { focusMode = false; event.accepted = true }
    }

    // Background: subtle dark gradient rather than a full illustrated
    // scene for now -- see roadmap Phase 3 for the countryside artwork.
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: Theme.darkBlue }
            GradientStop { position: 1.0; color: Theme.black }
        }
    }

    Flickable {
        id: flick
        anchors.fill: parent
        clip: true
        boundsBehavior: Flickable.StopAtBounds

        property real zoom: 1.0
        readonly property real minZoom: 0.35
        readonly property real maxZoom: 2.2

        Behavior on contentX { NumberAnimation { duration: Theme.slowDuration; easing.type: Easing.InOutQuad } }
        Behavior on contentY { NumberAnimation { duration: Theme.slowDuration; easing.type: Easing.InOutQuad } }

        contentWidth: Math.max(width, world.width * zoom)
        contentHeight: Math.max(height, world.height * zoom)

        Item {
            id: world
            width: Math.max(root.bounds.width, 1)
            height: Math.max(root.bounds.height, 1)
            scale: flick.zoom
            transformOrigin: Item.TopLeft

            Canvas {
                id: edgeCanvas
                anchors.fill: parent
                z: 0

                property var edges: FamilyTreeController.treeEdges
                onEdgesChanged: requestPaint()
                Component.onCompleted: requestPaint()

                onPaint: {
                    var ctx = getContext("2d")
                    ctx.reset()

                    for (var i = 0; i < edges.length; i++) {
                        var e = edges[i]
                        var x1 = e.x1 - root.bounds.x
                        var y1 = e.y1 - root.bounds.y
                        var x2 = e.x2 - root.bounds.x
                        var y2 = e.y2 - root.bounds.y

                        if (e.type === "marriage") {
                            ctx.strokeStyle = Theme.gold
                            ctx.lineWidth = 2
                            var dx = y2 - y1, dy = x1 - x2
                            var len = Math.sqrt(dx * dx + dy * dy) || 1
                            var ox = (dx / len) * 3, oy = (dy / len) * 3

                            ctx.beginPath()
                            ctx.moveTo(x1 + ox, y1 + oy)
                            ctx.lineTo(x2 + ox, y2 + oy)
                            ctx.stroke()

                            ctx.beginPath()
                            ctx.moveTo(x1 - ox, y1 - oy)
                            ctx.lineTo(x2 - ox, y2 - oy)
                            ctx.stroke()
                        } else {
                            ctx.strokeStyle = "#5A6B85"
                            ctx.lineWidth = 2
                            var midY = (y1 + y2) / 2
                            ctx.beginPath()
                            ctx.moveTo(x1, y1)
                            ctx.lineTo(x1, midY)
                            ctx.lineTo(x2, midY)
                            ctx.lineTo(x2, y2)
                            ctx.stroke()
                        }
                    }
                }
            }

            Repeater {
                id: nodeRepeater
                model: FamilyTreeController.treeLayout

                function centerOn(person) {
                    for (var i = 0; i < count; i++) {
                        var item = itemAt(i)
                        if (item && item.person === person) {
                            var targetX = item.x + Theme.cardWidth / 2
                            var targetY = item.y + Theme.cardHeight / 2
                            flick.contentX = (targetX * flick.zoom) - flick.width / 2
                            flick.contentY = (targetY * flick.zoom) - flick.height / 2
                            return
                        }
                    }
                }

                delegate: PersonCard {
                    x: nodeX - root.bounds.x - Theme.cardWidth / 2
                    y: nodeY - root.bounds.y - Theme.cardHeight / 2
                    person: model.person
                    selected: root.selectedPerson === model.person
                    hasChildren: model.hasChildren
                    collapsed: model.collapsed
                    dimmed: root.focusMode && !root.isRelevant(model.person)
                    timelineDeceased: FamilyTreeController.timelineEnabled &&
                                       model.person.deathYear > 0 &&
                                       model.person.deathYear <= FamilyTreeController.timelineYear
                    z: selected ? 3 : 1

                    onClicked: {
                        root.selectedPerson = model.person
                        root.personSelected(model.person)
                    }
                    onToggleCollapse: {
                        root.pendingCenterTarget = null
                        root.pendingCenterTarget = model.person
                        FamilyTreeController.toggleCollapsed(model.person)
                    }
                }
            }
        }

        WheelHandler {
            acceptedModifiers: Qt.NoModifier
            onWheel: (event) => {
                var factor = event.angleDelta.y > 0 ? 1.1 : (1 / 1.1)
                flick.zoom = Math.max(flick.minZoom, Math.min(flick.maxZoom, flick.zoom * factor))
            }
        }
    }

    // --- Top bar: title + zoom controls + close -----------------------
    Rectangle {
        id: topBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 56
        color: Theme.panelBgLight

        Row {
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10

            Text {
                text: "🌳"
                font.pixelSize: 20
            }
            Text {
                text: FamilyTreeController.activeRoot ? (FamilyTreeController.activeRoot.name + "'s Family Tree") : "Family Tree"
                color: Theme.textPrimary
                font.pixelSize: 16
                font.bold: true
            }
        }

        Row {
            anchors.right: parent.right
            anchors.rightMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            spacing: 8

            Button {
                text: FamilyTreeController.timelineEnabled ? "Timeline: On" : "Timeline"
                onClicked: FamilyTreeController.timelineEnabled = !FamilyTreeController.timelineEnabled
            }
            Button {
                text: root.focusMode ? "Full Family (A)" : "Focus (F)"
                onClicked: root.focusMode = !root.focusMode
            }
            Button {
                text: "−"
                onClicked: flick.zoom = Math.max(flick.minZoom, flick.zoom / 1.2)
            }
            Button {
                text: "Reset"
                onClicked: flick.zoom = 1.0
            }
            Button {
                text: "+"
                onClicked: flick.zoom = Math.min(flick.maxZoom, flick.zoom * 1.2)
            }
            Button {
                text: "Close"
                onClicked: root.closeRequested()
            }
        }
    }

    // --- Breadcrumb bar: path from tree root to the selected person ---
    Rectangle {
        id: breadcrumbBar
        visible: root.selectedPerson !== null
        anchors.top: topBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 34
        color: Theme.panelBgLight
        opacity: 0.85

        readonly property var path: root.selectedPerson ? FamilyTreeController.ancestryPath(root.selectedPerson) : []

        Row {
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            spacing: 6

            Repeater {
                model: breadcrumbBar.path
                delegate: Row {
                    spacing: 6
                    readonly property bool isLast: index === breadcrumbBar.path.length - 1

                    Text {
                        text: modelData.name
                        color: isLast ? Theme.gold : Theme.softCyan
                        font.pixelSize: 12
                        font.bold: isLast

                        TapHandler {
                            onTapped: {
                                root.selectedPerson = modelData.person
                                root.personSelected(modelData.person)
                            }
                        }
                    }
                    Text {
                        text: isLast ? "" : "›"
                        color: Theme.textSecondary
                        font.pixelSize: 12
                    }
                }
            }
        }
    }

    // --- Timeline slider: only visible in Timeline Mode -----------------
    Rectangle {
        id: timelineBar
        visible: FamilyTreeController.timelineEnabled
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 16
        width: 420
        height: 60
        radius: 10
        color: Theme.panelBgLight
        opacity: 0.92

        Column {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 4

            Row {
                width: parent.width
                Text {
                    text: "Timeline: " + timelineSlider.value.toFixed(0)
                    color: Theme.gold
                    font.pixelSize: 13
                    font.bold: true
                }
            }
            Slider {
                id: timelineSlider
                width: parent.width
                from: 1900
                to: 2026
                stepSize: 1
                value: FamilyTreeController.timelineYear
                onMoved: FamilyTreeController.timelineYear = value
            }
        }
    }

    // --- Minimap: bottom-right overview with viewport indicator --------
    Rectangle {
        id: minimap
        width: 190
        height: 130
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 16
        radius: 8
        color: Theme.panelBgElevated
        opacity: 0.85
        border.width: 1
        border.color: Theme.panelBorder
        clip: true

        readonly property real scaleX: root.bounds.width > 0 ? (width - 12) / root.bounds.width : 1
        readonly property real scaleY: root.bounds.height > 0 ? (height - 12) / root.bounds.height : 1
        readonly property real mapScale: Math.min(scaleX, scaleY)

        Repeater {
            model: FamilyTreeController.treeLayout
            delegate: Rectangle {
                width: 6
                height: 6
                radius: 3
                color: root.selectedPerson === model.person ? Theme.gold : Theme.softCyan
                x: 6 + (nodeX - root.bounds.x) * minimap.mapScale
                y: 6 + (nodeY - root.bounds.y) * minimap.mapScale
            }
        }

        // Viewport indicator rectangle.
        Rectangle {
            border.width: 1
            border.color: Theme.gold
            color: "#20D4AF37"
            x: 6 + (flick.contentX / flick.zoom) * minimap.mapScale
            y: 6 + (flick.contentY / flick.zoom) * minimap.mapScale
            width: Math.min(minimap.width - 12, (flick.width / flick.zoom) * minimap.mapScale)
            height: Math.min(minimap.height - 12, (flick.height / flick.zoom) * minimap.mapScale)
        }

        TapHandler {
            onTapped: (eventPoint) => {
                var localX = (eventPoint.position.x - 6) / minimap.mapScale
                var localY = (eventPoint.position.y - 6) / minimap.mapScale
                flick.contentX = (localX * flick.zoom) - flick.width / 2
                flick.contentY = (localY * flick.zoom) - flick.height / 2
            }
        }
    }
}
