import FamilyTreeQt
import QtQuick

Item {
    id: splash

    signal finished()

    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: Theme.darkBlue }
            GradientStop { position: 1.0; color: Theme.black }
        }
    }

    // Simple growing tree -- a static glyph that scales and fades
    // in, rather than a per-frame Canvas repaint. Lighter weight,
    // and avoids repeatedly re-entering the 2D canvas painter every
    // animation frame.
    Text {
        id: treeGlyph
        text: "🌳"
        font.pixelSize: 110
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -60
        scale: 0.4
        opacity: 0

        SequentialAnimation {
            running: true
            PauseAnimation { duration: 150 }
            ParallelAnimation {
                NumberAnimation { target: treeGlyph; property: "scale"; to: 1.0; duration: 900; easing.type: Easing.OutBack }
                NumberAnimation { target: treeGlyph; property: "opacity"; to: 1.0; duration: 700 }
            }
        }
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: treeGlyph.bottom
        anchors.topMargin: 12
        spacing: 4

        Text {
            text: "FAMILY TREE"
            color: Theme.textPrimary
            font.pixelSize: 26
            font.bold: true
            font.letterSpacing: 3
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            text: "MANAGEMENT SYSTEM"
            color: Theme.gold
            font.pixelSize: 12
            font.letterSpacing: 5
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            text: "Presented by Taqi"
            color: Theme.textSecondary
            font.pixelSize: 11
            anchors.horizontalCenter: parent.horizontalCenter
            topPadding: 10
        }
    }

    // Loading bar.
    Rectangle {
        id: loadingTrack
        width: 240
        height: 4
        radius: 2
        color: "#2A3F5F"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 70

        Rectangle {
            id: loadingFill
            height: parent.height
            radius: parent.radius
            color: Theme.gold
            width: 0

            NumberAnimation on width {
                from: 0; to: loadingTrack.width
                duration: 2000
                easing.type: Easing.InOutQuad
                running: true
                onFinished: exitTimer.start()
            }
        }
    }

    Text {
        text: "Initializing..."
        color: Theme.textSecondary
        font.pixelSize: 11
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: loadingTrack.bottom
        anchors.topMargin: 8
    }

    Timer {
        id: exitTimer
        interval: 200
        onTriggered: fadeOut.start()
    }

    NumberAnimation {
        id: fadeOut
        target: splash
        property: "opacity"
        from: 1; to: 0
        duration: Theme.sceneDuration
        onFinished: splash.finished()
    }
}
