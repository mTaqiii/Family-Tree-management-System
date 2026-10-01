pragma Singleton
import QtQuick

// Lightweight singleton so any QML file, no matter how deeply
// nested (a PersonCard delegate, an InfoPanel field, ...), can call
// Toast.show("message") without needing a reference threaded down
// to it. The actual visual popup lives in ToastHost.qml, which
// listens for the `requested` signal -- this object holds no visual
// state of its own.
QtObject {
    signal requested(string message, bool isError)

    function show(message, isError) {
        requested(message, !!isError)
    }
}
