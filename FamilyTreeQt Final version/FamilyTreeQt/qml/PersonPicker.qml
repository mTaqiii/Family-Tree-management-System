import FamilyTreeQt
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// "Choose Existing Person" search dialog. Instantiate once per
// screen and call personPicker.pick("Choose Existing Father", function(person) { ... }).
// The callback only runs when the user actually selects someone;
// closing/cancelling the dialog does nothing.
Dialog {
    id: root

    property var onPicked: null

    modal: true
    anchors.centerIn: parent
    width: 420
    height: 420
    closePolicy: Popup.CloseOnEscape

    function pick(dialogTitle, callback) {
        titleLabel.text = dialogTitle
        onPicked = callback
        searchField.text = ""
        resultsList.model = null
        root.open()
        searchField.forceActiveFocus()
    }

    background: Rectangle {
        color: Theme.panelBg
        radius: 14
        border.width: 1
        border.color: Theme.panelBorder
    }

    contentItem: ColumnLayout {
        spacing: 10

        Text {
            id: titleLabel
            color: Theme.textPrimary
            font.pixelSize: 17
            font.bold: true
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: searchField
                Layout.fillWidth: true
                placeholderText: "Type a name (any case)..."
                onTextChanged: {
                    if (text.length > 0) {
                        var count = FamilyTreeController.searchByName(text)
                        resultsList.model = FamilyTreeController.searchResults
                        emptyLabel.visible = count === 0
                    } else {
                        resultsList.model = null
                        emptyLabel.visible = false
                    }
                }
            }
        }

        Text {
            id: emptyLabel
            text: "No matches."
            color: Theme.textSecondary
            font.pixelSize: 12
            visible: false
        }

        ListView {
            id: resultsList
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 4

            delegate: Rectangle {
                width: resultsList.width
                height: 48
                radius: 8
                color: hoverArea.containsMouse ? Theme.surfaceHover : "transparent"

                Column {
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    Text {
                        text: model.person.name
                        color: Theme.textPrimary
                        font.pixelSize: 13
                        font.bold: true
                    }
                    Text {
                        text: "ID " + model.person.id + " • " + (model.person.gender === 1 ? "♀ Female" : "♂ Male")
                        color: Theme.textSecondary
                        font.pixelSize: 11
                    }
                }

                MouseArea {
                    id: hoverArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        if (root.onPicked !== null)
                            root.onPicked(model.person)
                        root.close()
                    }
                }
            }
        }
    }

    footer: DialogButtonBox {
        background: Rectangle { color: "transparent" }
        Button {
            text: "Cancel"
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
        }
    }
}
