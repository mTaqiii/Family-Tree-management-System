import FamilyTreeQt
import QtQuick
import QtQuick.Layouts

Item {
    id: root

    property string label: ""
    property bool active: false
    signal clicked()

    Layout.fillWidth: true
    height: 46

    scale: (hover.hovered && enabled) ? 1.03 : 1.0
    Behavior on scale { NumberAnimation { duration: Theme.fastDuration } }

    HoverHandler { id: hover; enabled: root.enabled }
    TapHandler { enabled: root.enabled; onTapped: root.clicked() }

    Rectangle {
        anchors.fill: parent
        radius: 10
        color: {
            if (root.active) return Theme.surfaceActive
            if (hover.hovered && root.enabled) return Theme.surfaceHover
            return Theme.surfaceNormal
        }
        opacity: root.enabled ? 1.0 : 0.45
        border.width: (root.active || (hover.hovered && root.enabled)) ? 1 : 0
        border.color: Theme.gold

        Behavior on color { ColorAnimation { duration: Theme.fastDuration } }

        // Active-page indicator bar on the left edge.
        Rectangle {
            visible: root.active
            width: 3
            radius: 2
            color: Theme.gold
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 6
        }

        Text {
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            text: (hover.hovered && root.enabled ? "▶ " : "") + root.label
            color: Theme.textPrimary
            font.pixelSize: 14
            font.bold: root.active
        }
    }
}
