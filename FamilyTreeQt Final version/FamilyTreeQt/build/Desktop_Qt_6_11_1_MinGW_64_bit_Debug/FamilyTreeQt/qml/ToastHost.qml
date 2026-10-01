import FamilyTreeQt
import QtQuick

// Visual toast stack, anchored bottom-center. Instantiated exactly
// once (in main.qml, above everything else in z-order) and driven
// entirely by the Toast singleton's `requested` signal -- nothing
// else needs a reference to this component directly.
Item {
    id: root
    anchors.fill: parent
    z: 1000

    Connections {
        target: Toast
        function onRequested(message, isError) {
            toastModel.append({ text: message, error: isError, uid: Date.now() + Math.random() })
        }
    }

    ListModel { id: toastModel }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 28
        spacing: 8

        Repeater {
            model: toastModel
            delegate: Rectangle {
                id: toastItem
                width: Math.min(420, label.implicitWidth + 48)
                height: 44
                radius: 10
                color: model.error ? "#5C2430" : "#204A38"
                border.width: 1
                border.color: model.error ? "#E0667A" : Theme.forestGreen

                opacity: 0
                y: 20

                Component.onCompleted: appear.start()

                Text {
                    id: label
                    anchors.centerIn: parent
                    text: (model.error ? "⚠ " : "✓ ") + model.text
                    color: Theme.textPrimary
                    font.pixelSize: 13
                    font.bold: true
                }

                ParallelAnimation {
                    id: appear
                    NumberAnimation { target: toastItem; property: "opacity"; to: 1; duration: Theme.fastDuration }
                    NumberAnimation { target: toastItem; property: "y"; to: 0; duration: Theme.fastDuration; easing.type: Easing.OutCubic }
                }

                Timer {
                    interval: 3200
                    running: true
                    onTriggered: dismiss.start()
                }

                SequentialAnimation {
                    id: dismiss
                    NumberAnimation { target: toastItem; property: "opacity"; to: 0; duration: Theme.fastDuration }
                    ScriptAction {
                        script: {
                            for (var i = 0; i < toastModel.count; i++) {
                                if (toastModel.get(i).uid === model.uid) {
                                    toastModel.remove(i)
                                    break
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
