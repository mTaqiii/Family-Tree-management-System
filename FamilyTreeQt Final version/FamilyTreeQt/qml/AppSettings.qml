pragma Singleton
import QtQuick
import Qt.labs.settings

// App-wide persisted preferences.
QtObject {
    property alias reducedMotion: settingsStore.reducedMotion
    property alias nightMode: settingsStore.nightMode

    property Settings settingsStore: Settings {
        id: settingsStore
        category: "FamilyTreeQt"
        property bool reducedMotion: false
        property bool nightMode: true
    }
}
