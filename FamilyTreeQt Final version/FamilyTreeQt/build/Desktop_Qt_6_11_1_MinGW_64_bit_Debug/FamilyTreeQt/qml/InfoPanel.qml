import FamilyTreeQt
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    property var person: null
    readonly property bool open: person !== null

    signal closed()
    signal navigateTo(var person)

    width: 320
    clip: false

    x: open ? (parent.width - width - 16) : parent.width
    y: 72
    height: parent.height - 88

    Behavior on x { NumberAnimation { duration: Theme.normalDuration; easing.type: Easing.OutCubic } }

    function describe(p) {
        if (!p) return ""
        var g = p.gender === 1 ? "♀ Female" : "♂ Male"
        var s = p.status === 1 ? "Deceased" : "Alive"
        return g + " • " + s
    }

    ConfirmDialog { id: confirmDialog }
    PersonPicker { id: personPicker }

    Rectangle {
        anchors.fill: parent
        radius: 14
        color: Theme.panelBg
        border.width: 1
        border.color: Theme.panelBorder
        opacity: 0.97
    }

    ScrollView {
        anchors.fill: parent
        anchors.margins: 16
        clip: true
        background: Rectangle { color: "transparent" }

        ColumnLayout {
            width: root.width - 32
            spacing: 14

            // --- Header -----------------------------------------------
            RowLayout {
                Layout.fillWidth: true
                Text {
                    text: root.person ? root.person.name : ""
                    color: Theme.textPrimary
                    font.pixelSize: 20
                    font.bold: true
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                }
                Button {
                    text: "✕"
                    flat: true
                    onClicked: root.closed()
                }
            }

            Text {
                text: root.person ? ("ID " + root.person.id + "  •  " + root.describe(root.person)) : ""
                color: Theme.textSecondary
                font.pixelSize: 12
            }

            Rectangle { Layout.fillWidth: true; height: 1; color: Theme.divider }

            // --- Relationships -----------------------------------------
            GridLayout {
                columns: 3
                Layout.fillWidth: true
                rowSpacing: 6
                columnSpacing: 8

                Text { text: "Father"; color: Theme.textSecondary; font.pixelSize: 12 }
                Text {
                    text: root.person && root.person.father ? root.person.father.name : "—"
                    color: Theme.textPrimary
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    MouseArea {
                        anchors.fill: parent
                        enabled: root.person && root.person.father
                        onClicked: root.navigateTo(root.person.father)
                        cursorShape: enabled ? Qt.PointingHandCursor : Qt.ArrowCursor
                    }
                }
                Button {
                    text: "✕"
                    flat: true
                    visible: root.person && root.person.father
                    implicitWidth: 28; implicitHeight: 24
                    onClicked: {
                        confirmDialog.ask(
                            "Remove Father Link",
                            "This removes the father relationship for " + root.person.name + ". " + root.person.father.name + " themselves is not deleted.",
                            function() {
                                var r = FamilyTreeController.unlinkFather(root.person)
                                Toast.show(r.message, !r.success)
                            },
                            "Remove"
                        )
                    }
                }

                Text { text: "Mother"; color: Theme.textSecondary; font.pixelSize: 12 }
                Text {
                    text: root.person && root.person.mother ? root.person.mother.name : "—"
                    color: Theme.textPrimary
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    MouseArea {
                        anchors.fill: parent
                        enabled: root.person && root.person.mother
                        onClicked: root.navigateTo(root.person.mother)
                        cursorShape: enabled ? Qt.PointingHandCursor : Qt.ArrowCursor
                    }
                }
                Button {
                    text: "✕"
                    flat: true
                    visible: root.person && root.person.mother
                    implicitWidth: 28; implicitHeight: 24
                    onClicked: {
                        confirmDialog.ask(
                            "Remove Mother Link",
                            "This removes the mother relationship for " + root.person.name + ". " + root.person.mother.name + " themselves is not deleted.",
                            function() {
                                var r = FamilyTreeController.unlinkMother(root.person)
                                Toast.show(r.message, !r.success)
                            },
                            "Remove"
                        )
                    }
                }

                Text { text: "Spouse"; color: Theme.textSecondary; font.pixelSize: 12 }
                Text {
                    text: root.person && root.person.spouse ? root.person.spouse.name : "—"
                    color: Theme.textPrimary
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    MouseArea {
                        anchors.fill: parent
                        enabled: root.person && root.person.spouse
                        onClicked: root.navigateTo(root.person.spouse)
                        cursorShape: enabled ? Qt.PointingHandCursor : Qt.ArrowCursor
                    }
                }
                Item { width: 1; height: 1 }

                Text { text: "Children"; color: Theme.textSecondary; font.pixelSize: 12 }
                Text {
                    text: root.person ? root.person.children.length : "0"
                    color: Theme.textPrimary
                    font.pixelSize: 12
                }
                Item { width: 1; height: 1 }
            }

            Rectangle { Layout.fillWidth: true; height: 1; color: Theme.divider }

            // --- Timeline years (optional, powers Timeline Mode) --------
            Text { text: "Timeline Years (optional)"; color: Theme.gold; font.pixelSize: 12; font.bold: true }
            RowLayout {
                Layout.fillWidth: true
                Text { text: "Born"; color: Theme.textSecondary; font.pixelSize: 12 }
                TextField {
                    id: birthYearField
                    Layout.preferredWidth: 70
                    placeholderText: "e.g. 1975"
                    validator: IntValidator { bottom: 1800; top: 2100 }
                    text: root.person && root.person.birthYear > 0 ? String(root.person.birthYear) : ""
                }
                Text { text: "Died"; color: Theme.textSecondary; font.pixelSize: 12 }
                TextField {
                    id: deathYearField
                    Layout.preferredWidth: 70
                    placeholderText: "optional"
                    validator: IntValidator { bottom: 1800; top: 2100 }
                    text: root.person && root.person.deathYear > 0 ? String(root.person.deathYear) : ""
                }
                Button {
                    text: "Save"
                    onClicked: {
                        if (birthYearField.text && deathYearField.text &&
                            parseInt(deathYearField.text) < parseInt(birthYearField.text)) {
                            Toast.show("Death year can't be before birth year.", true)
                            return
                        }
                        var by = birthYearField.text ? parseInt(birthYearField.text) : 0
                        var dy = deathYearField.text ? parseInt(deathYearField.text) : 0
                        var r = FamilyTreeController.setYears(root.person, by, dy)
                        Toast.show(r.message, !r.success)
                    }
                }
            }

            Rectangle { Layout.fillWidth: true; height: 1; color: Theme.divider }

            // --- Add relationships ---------------------------------------
            Text { text: "Father"; color: Theme.gold; font.pixelSize: 12; font.bold: true; visible: root.person && !root.person.father }
            RowLayout {
                Layout.fillWidth: true
                visible: root.person && !root.person.father
                TextField { id: fatherField; Layout.fillWidth: true; placeholderText: "New person's name" }
                Button {
                    text: "Add New"
                    onClicked: {
                        var r = FamilyTreeController.registerNewFather(root.person, fatherField.text)
                        Toast.show(r.message, !r.success)
                        if (r.success) fatherField.text = ""
                    }
                }
                Button {
                    text: "Choose Existing"
                    onClicked: {
                        personPicker.pick("Choose Existing Father", function(picked) {
                            var r = FamilyTreeController.linkExistingFather(root.person, picked)
                            Toast.show(r.message, !r.success)
                        })
                    }
                }
            }

            Text { text: "Mother"; color: Theme.gold; font.pixelSize: 12; font.bold: true; visible: root.person && !root.person.mother }
            RowLayout {
                Layout.fillWidth: true
                visible: root.person && !root.person.mother
                TextField { id: motherField; Layout.fillWidth: true; placeholderText: "New person's name" }
                Button {
                    text: "Add New"
                    onClicked: {
                        var r = FamilyTreeController.registerNewMother(root.person, motherField.text)
                        Toast.show(r.message, !r.success)
                        if (r.success) motherField.text = ""
                    }
                }
                Button {
                    text: "Choose Existing"
                    onClicked: {
                        personPicker.pick("Choose Existing Mother", function(picked) {
                            var r = FamilyTreeController.linkExistingMother(root.person, picked)
                            Toast.show(r.message, !r.success)
                        })
                    }
                }
            }

            Text { text: "Spouse"; color: Theme.gold; font.pixelSize: 12; font.bold: true; visible: root.person && !root.person.spouse }
            RowLayout {
                Layout.fillWidth: true
                visible: root.person && !root.person.spouse
                TextField { id: spouseField; Layout.fillWidth: true; placeholderText: "New person's name" }
                Button {
                    text: "Add New"
                    onClicked: {
                        var r = FamilyTreeController.registerNewSpouse(root.person, spouseField.text)
                        Toast.show(r.message, !r.success)
                        if (r.success) spouseField.text = ""
                    }
                }
                Button {
                    text: "Choose Existing"
                    onClicked: {
                        personPicker.pick("Choose Existing Spouse", function(picked) {
                            var r = FamilyTreeController.linkExistingSpouse(root.person, picked)
                            Toast.show(r.message, !r.success)
                        })
                    }
                }
            }

            Text { text: "Add Child"; color: Theme.gold; font.pixelSize: 12; font.bold: true; visible: root.person !== null }
            RowLayout {
                Layout.fillWidth: true
                visible: root.person !== null
                TextField {
                    id: childField
                    Layout.fillWidth: true
                    placeholderText: "New person's name"
                }
                RadioButton { id: childMale; text: "♂"; checked: true }
                RadioButton { id: childFemale; text: "♀" }
                Button {
                    text: "Add"
                    onClicked: {
                        var g = childMale.checked ? "male" : "female"
                        var r = FamilyTreeController.registerNewChild(root.person, childField.text, g)
                        Toast.show(r.message, !r.success)
                        if (r.success) childField.text = ""
                    }
                }
            }
            Button {
                text: "Choose Existing Child"
                Layout.fillWidth: true
                visible: root.person !== null
                onClicked: {
                    personPicker.pick("Choose Existing Child", function(picked) {
                        var r = FamilyTreeController.linkExistingChild(root.person, picked)
                        Toast.show(r.message, !r.success)
                    })
                }
            }

            Rectangle { Layout.fillWidth: true; height: 1; color: Theme.divider }

            // --- Lifecycle actions --------------------------------------
            RowLayout {
                Layout.fillWidth: true
                spacing: 8

                Button {
                    text: "Mark Deceased"
                    enabled: root.person && root.person.status === 0
                    onClicked: {
                        confirmDialog.ask(
                            "Mark as Deceased",
                            "Are you sure? " + root.person.name + " will be marked as deceased. This does not remove any relationships.",
                            function() {
                                var r = FamilyTreeController.markDeceased(root.person)
                                Toast.show(r.message, !r.success)
                            },
                            "Mark Deceased"
                        )
                    }
                }
                Button {
                    text: "Divorce"
                    enabled: root.person && root.person.spouse
                    onClicked: {
                        confirmDialog.ask(
                            "End Marriage",
                            "Are you sure you want to remove the spouse relationship between " + root.person.name + " and " + root.person.spouse.name + "?",
                            function() {
                                var r = FamilyTreeController.divorcePerson(root.person)
                                Toast.show(r.message, !r.success)
                            },
                            "Divorce"
                        )
                    }
                }
            }
        }
    }
}
