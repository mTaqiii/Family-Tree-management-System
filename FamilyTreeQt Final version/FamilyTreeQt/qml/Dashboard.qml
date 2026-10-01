import FamilyTreeQt
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Item {
    id: root

    signal openTree(var rootPerson)
    signal personSelected(var person)

    property string activePanel: "" // "", "create", "search", "trees", "export", "settings"

    ConfirmDialog { id: confirmDialog }

    FileDialog {
        id: exportDialog
        property var exportRoot: null
        fileMode: FileDialog.SaveFile
        nameFilters: ["XML files (*.xml)"]
        defaultSuffix: "xml"
        onAccepted: {
            var r = FamilyTreeController.exportTree(exportRoot, selectedFile)
            Toast.show(r.message, !r.success)
        }
    }

    FileDialog {
        id: importDialog
        fileMode: FileDialog.OpenFile
        nameFilters: ["XML files (*.xml)", "All files (*)"]
        onAccepted: {
            var r = FamilyTreeController.importTree(selectedFile)
            Toast.show(r.message, !r.success)
            if (r.success) {
                root.activePanel = ""
                root.openTree(r.person)
            }
        }
    }

    // Background: gradient standing in for the countryside/garden
    // illustration from the design brief until real artwork exists.
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: Theme.forestGreen }
            GradientStop { position: 0.55; color: Theme.darkBlue }
            GradientStop { position: 1.0; color: Theme.black }
        }
        opacity: 0.9
    }

    // Ambient falling leaves -- "leaves occasionally fall" from the
    // hidden-interactions list. Deliberately minimal (one animation
    // per item, few items) so it costs almost nothing to leave
    // running behind the dashboard.
    Repeater {
        model: AppSettings.reducedMotion ? 0 : 4
        delegate: Rectangle {
            width: 8; height: 5
            radius: 2
            color: Theme.gold
            opacity: 0.5
            x: (index + 1) * (root.width / 5)
            y: -20

            SequentialAnimation on y {
                loops: Animation.Infinite
                running: true
                PauseAnimation { duration: index * 2000 }
                NumberAnimation {
                    to: root.height + 20
                    duration: 11000
                    easing.type: Easing.InOutSine
                }
                NumberAnimation { to: -20; duration: 0 }
            }
        }
    }

    // --- Welcome / stats section -----------------------------------------
    Column {
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -40
        spacing: 6
        visible: activePanel === ""

        Text {
            text: "FAMILY TREE"
            color: Theme.textPrimary
            font.pixelSize: 38
            font.bold: true
            font.letterSpacing: 4
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            text: "MANAGEMENT SYSTEM"
            color: Theme.gold
            font.pixelSize: 16
            font.letterSpacing: 6
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            text: "Build, Explore, and Preserve Your Family History"
            color: Theme.textSecondary
            font.pixelSize: 13
            font.italic: true
            anchors.horizontalCenter: parent.horizontalCenter
            topPadding: 10
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            topPadding: 34
            spacing: 18

            Repeater {
                model: [
                    { label: "Family Trees", value: FamilyTreeController.trees.count },
                    { label: "People Recorded", value: FamilyTreeController.totalPeople }
                ]
                delegate: Rectangle {
                    width: 160
                    height: 84
                    radius: 14
                    color: Theme.panelBgElevated
                    opacity: 0.85
                    border.width: 1
                    border.color: Theme.panelBorder

                    Column {
                        anchors.centerIn: parent
                        spacing: 2
                        Text {
                            text: modelData.value
                            color: Theme.gold
                            font.pixelSize: 26
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Text {
                            text: modelData.label
                            color: Theme.textSecondary
                            font.pixelSize: 11
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }
            }
        }
    }

    // --- Glass navigation panel ----------------------------------------
    Rectangle {
        id: glassPanel
        width: 340
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 20
        radius: 18
        color: Theme.panelBgElevated
        opacity: 0.88
        border.width: 1
        border.color: Theme.panelBorder

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 10

            Text {
                text: "🌳 Family Tree"
                color: Theme.textPrimary
                font.pixelSize: 19
                font.bold: true
                Layout.bottomMargin: 8
            }

            NavButton {
                label: "🏡 Create Family"
                active: root.activePanel === "create"
                onClicked: root.activePanel = (root.activePanel === "create") ? "" : "create"
            }
            NavButton {
                label: "🔍 Search Person"
                active: root.activePanel === "search"
                onClicked: root.activePanel = (root.activePanel === "search") ? "" : "search"
            }
            NavButton {
                label: "📜 Family Trees (" + FamilyTreeController.trees.count + ")"
                active: root.activePanel === "trees"
                onClicked: root.activePanel = (root.activePanel === "trees") ? "" : "trees"
            }
            NavButton {
                label: "📄 Export XML"
                active: root.activePanel === "export"
                onClicked: root.activePanel = (root.activePanel === "export") ? "" : "export"
            }
            NavButton {
                label: "📂 Import XML"
                onClicked: importDialog.open()
            }
            NavButton {
                label: "⚙ Settings"
                active: root.activePanel === "settings"
                onClicked: root.activePanel = (root.activePanel === "settings") ? "" : "settings"
            }
            NavButton {
                label: "🚪 Exit"
                onClicked: {
                    confirmDialog.ask(
                        "Exit Application",
                        "Any family data not exported to XML will be lost when you exit. Continue?",
                        function() { Qt.quit() },
                        "Exit"
                    )
                }
            }

            Item { Layout.fillHeight: true }
        }
    }

    // --- Inline panels ----------------------------------------------------
    Rectangle {
        id: inlinePanel
        visible: root.activePanel !== ""
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 20
        width: 360
        radius: 18
        color: Theme.panelBgElevated
        opacity: 0.95
        border.width: 1
        border.color: Theme.panelBorder

        // --- Create Family ------------------------------------------
        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 20
            visible: root.activePanel === "create"
            spacing: 8

            Text { text: "Create Family"; color: Theme.textPrimary; font.pixelSize: 18; font.bold: true }
            TextField {
                id: createName
                Layout.fillWidth: true
                placeholderText: "Root person's name"
            }
            RowLayout {
                RadioButton { id: createMale; text: "♂ Male"; checked: true }
                RadioButton { id: createFemale; text: "♀ Female" }
            }
            Button {
                text: "Create Tree"
                Layout.fillWidth: true
                onClicked: {
                    var g = createMale.checked ? "male" : "female"
                    var r = FamilyTreeController.registerRootPerson(createName.text, g)
                    Toast.show(r.message, !r.success)
                    if (r.success) {
                        createName.text = ""
                        root.openTree(r.person)
                        root.activePanel = ""
                    }
                }
            }
        }

        // --- Search --------------------------------------------------
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            visible: root.activePanel === "search"
            spacing: 8

            Text { text: "Search Person"; color: Theme.textPrimary; font.pixelSize: 18; font.bold: true }
            RowLayout {
                Layout.fillWidth: true
                TextField {
                    id: searchField
                    Layout.fillWidth: true
                    placeholderText: "Type a name (any case)..."
                    onAccepted: searchButton.clicked()
                }
                Button {
                    id: searchButton
                    text: "Go"
                    onClicked: {
                        var count = FamilyTreeController.searchByName(searchField.text)
                        if (count === 0)
                            Toast.show("No matches for \"" + searchField.text + "\".", true)
                    }
                }
            }
            ListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                model: FamilyTreeController.searchResults
                delegate: ItemDelegate {
                    width: ListView.view.width
                    text: model.person.name + "  (ID " + model.person.id + ")"
                    onClicked: root.personSelected(model.person)
                }
            }
        }

        // --- Trees list ------------------------------------------------
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            visible: root.activePanel === "trees"
            spacing: 8

            Text { text: "Family Trees"; color: Theme.textPrimary; font.pixelSize: 18; font.bold: true }
            ListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                model: FamilyTreeController.trees
                delegate: ItemDelegate {
                    width: ListView.view.width
                    text: "🌳 " + model.person.name + "  (ID " + model.person.id + ")"
                    onClicked: root.openTree(model.person)
                }
            }
        }

        // --- Export XML ------------------------------------------------
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            visible: root.activePanel === "export"
            spacing: 8

            Text { text: "Export XML"; color: Theme.textPrimary; font.pixelSize: 18; font.bold: true }
            Text {
                text: "Choose a family tree to export. You'll be asked where to save the file."
                color: Theme.textSecondary
                font.pixelSize: 12
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }
            ListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                model: FamilyTreeController.trees
                delegate: ItemDelegate {
                    width: ListView.view.width
                    text: "📄 " + model.person.name + "  (ID " + model.person.id + ")"
                    onClicked: {
                        exportDialog.exportRoot = model.person
                        exportDialog.currentFile = "file:///" + model.person.name.replace(/\s+/g, "_") + "_family_tree.xml"
                        exportDialog.open()
                    }
                }
            }
        }

        // --- Settings ------------------------------------------------
        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 20
            visible: root.activePanel === "settings"
            spacing: 12

            Text { text: "Settings"; color: Theme.textPrimary; font.pixelSize: 18; font.bold: true }

            RowLayout {
                Layout.fillWidth: true
                Text {
                    text: "Reduced Motion"
                    color: Theme.textPrimary
                    font.pixelSize: 13
                    Layout.fillWidth: true
                }
                Switch {
                    checked: AppSettings.reducedMotion
                    onToggled: AppSettings.reducedMotion = checked
                }
            }
            Text {
                text: "Shortens or removes scene transitions, camera pans, and card animations -- useful during a long editing session, or if motion is distracting."
                color: Theme.textSecondary
                font.pixelSize: 11
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }

            RowLayout {
                Layout.fillWidth: true
                Text {
                    text: Theme.isNight ? "🌙 Night Mode" : "☀ Day Mode"
                    color: Theme.textPrimary
                    font.pixelSize: 13
                    Layout.fillWidth: true
                }
                Switch {
                    checked: AppSettings.nightMode
                    onToggled: AppSettings.nightMode = checked
                }
            }
        }
    }
}
