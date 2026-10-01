import FamilyTreeQt
import QtQuick
import QtQuick.Controls

// Reusable "are you sure?" dialog. Instantiate once per screen and
// call confirmDialog.ask("Title", "Message", function() { ... }) --
// the callback only runs if the user taps Confirm.
Dialog {
    id: root

    property var onConfirmed: null
    property string dangerLabel: "Confirm"

    modal: true
    anchors.centerIn: parent
    width: 360
    closePolicy: Popup.CloseOnEscape

    function ask(dialogTitle, message, callback, confirmLabel) {
        titleLabel.text = dialogTitle
        messageLabel.text = message
        onConfirmed = callback
        dangerLabel = confirmLabel || "Confirm"
        root.open()
    }

    background: Rectangle {
        color: Theme.panelBg
        radius: 14
        border.width: 1
        border.color: Theme.panelBorder
    }

    contentItem: Column {
        spacing: 14
        padding: 20

        Text {
            id: titleLabel
            color: Theme.textPrimary
            font.pixelSize: 17
            font.bold: true
            width: root.width - 40
            wrapMode: Text.WordWrap
        }
        Text {
            id: messageLabel
            color: Theme.textSecondary
            font.pixelSize: 13
            width: root.width - 40
            wrapMode: Text.WordWrap
        }
    }

    footer: DialogButtonBox {
        background: Rectangle { color: "transparent" }

        Button {
            text: "Cancel"
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
        }
        Button {
            text: root.dangerLabel
            DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole

            background: Rectangle {
                radius: 6
                color: "#B23B48"
            }
            contentItem: Text {
                text: parent.text
                color: "white"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    onAccepted: {
        if (onConfirmed !== null)
            onConfirmed()
    }
}
