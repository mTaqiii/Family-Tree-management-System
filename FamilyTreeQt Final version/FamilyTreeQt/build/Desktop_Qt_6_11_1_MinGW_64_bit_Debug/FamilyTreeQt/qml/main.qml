import QtQuick
import QtQuick.Controls
import FamilyTreeQt

ApplicationWindow {
    id: window
    width: 1200
    height: 760
    visible: true
    title: "Family Tree Management System"

    property var currentTreeRoot: null
    property var infoPerson: null
    property bool showSplash: true

    function openTree(rootPerson) {
        FamilyTreeController.loadTree(rootPerson)
        currentTreeRoot = rootPerson
    }

    Item {
        anchors.fill: parent
        visible: !window.showSplash

        Dashboard {
            id: dashboard
            anchors.fill: parent
            visible: opacity > 0
            opacity: window.currentTreeRoot === null ? 1 : 0
            Behavior on opacity { NumberAnimation { duration: Theme.sceneDuration; easing.type: Easing.InOutQuad } }

            onOpenTree: (rootPerson) => window.openTree(rootPerson)
            onPersonSelected: (person) => window.infoPerson = person
        }

        TreeView {
            id: treeView
            anchors.fill: parent
            visible: opacity > 0
            opacity: window.currentTreeRoot !== null ? 1 : 0
            Behavior on opacity { NumberAnimation { duration: Theme.sceneDuration; easing.type: Easing.InOutQuad } }

            onPersonSelected: (person) => window.infoPerson = person
            onCloseRequested: {
                window.currentTreeRoot = null
                window.infoPerson = null
            }
        }

        InfoPanel {
            id: infoPanel
            person: window.infoPerson

            onClosed: window.infoPerson = null
            onNavigateTo: (person) => {
                window.infoPerson = person
                treeView.selectedPerson = person
            }
        }
    }

    SplashScreen {
        anchors.fill: parent
        visible: window.showSplash
        onFinished: window.showSplash = false
    }

    ToastHost {
        anchors.fill: parent
    }
}
