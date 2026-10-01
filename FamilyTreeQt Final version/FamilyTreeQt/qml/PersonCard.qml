import FamilyTreeQt
import QtQuick

// A single person's card, as described in the design brief:
// blue border for male, pink for female, gray when deceased, gold
// when selected. Hover gives a slight scale + glow.
Item {
    id: card

    property var person: null
    property bool selected: false
    property bool hasChildren: false
    property bool collapsed: false
    property bool dimmed: false
    property bool timelineDeceased: false

    signal clicked()
    signal toggleCollapse()

    width: Theme.cardWidth
    height: Theme.cardHeight

    readonly property bool isFemale: person !== null && person.gender === 1
    readonly property bool isDeceased: (person !== null && person.status === 1) || timelineDeceased

    readonly property color borderColor: {
        if (selected) return Theme.gold
        if (isDeceased) return Theme.deceased
        return isFemale ? Theme.female : Theme.male
    }

    opacity: dimmed ? 0.28 : 1.0
    Behavior on opacity { NumberAnimation { duration: Theme.normalDuration } }

    scale: hoverHandler.hovered ? 1.06 : 1.0
    Behavior on scale { NumberAnimation { duration: Theme.fastDuration; easing.type: Easing.OutBack } }

    Behavior on x { NumberAnimation { duration: Theme.slowDuration; easing.type: Easing.InOutQuad } }
    Behavior on y { NumberAnimation { duration: Theme.slowDuration; easing.type: Easing.InOutQuad } }

    HoverHandler { id: hoverHandler }
    TapHandler { onTapped: card.clicked() }

    Rectangle {
        id: shadow
        anchors.fill: body
        anchors.topMargin: 4
        radius: body.radius
        color: "#40000000"
        visible: hoverHandler.hovered || selected
    }

    Rectangle {
        id: body
        anchors.fill: parent
        radius: 12
        color: isDeceased ? Theme.deceasedCardBg : Theme.panelBg
        border.width: selected ? 3 : 2
        border.color: card.borderColor

        Behavior on border.color { ColorAnimation { duration: Theme.normalDuration } }

        Column {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 3

            Row {
                spacing: 6
                Rectangle {
                    width: 10; height: 10; radius: 5
                    anchors.verticalCenter: parent.verticalCenter
                    color: isDeceased ? Theme.deceased : "#4CD964"
                }
                Text {
                    text: person ? person.name : ""
                    color: Theme.textPrimary
                    font.pixelSize: 15
                    font.bold: true
                    elide: Text.ElideRight
                    width: Theme.cardWidth - 40
                }
            }

            Text {
                text: person ? ("ID " + person.id) : ""
                color: Theme.textSecondary
                font.pixelSize: 11
            }

            Text {
                text: {
                    if (!person) return ""
                    var g = isFemale ? "♀ Female" : "♂ Male"
                    var s = isDeceased ? "Deceased" : "Alive"
                    return g + " • " + s
                }
                color: Theme.textSecondary
                font.pixelSize: 11
            }
        }
    }

    // Expand/collapse badge -- only shown for a node that actually
    // has children. Sits on the card's bottom edge so it reads as
    // "toggle what's below me". A separate TapHandler keeps this
    // from also selecting the card underneath it.
    Rectangle {
        id: collapseBadge
        visible: card.hasChildren
        width: 22
        height: 22
        radius: 11
        anchors.horizontalCenter: body.horizontalCenter
        anchors.top: body.bottom
        anchors.topMargin: -11
        color: Theme.panelBg
        border.width: 2
        border.color: Theme.gold
        z: 2

        HoverHandler { id: badgeHover }
        TapHandler { onTapped: card.toggleCollapse() }

        scale: badgeHover.hovered ? 1.15 : 1.0
        Behavior on scale { NumberAnimation { duration: Theme.fastDuration } }

        Text {
            anchors.centerIn: parent
            text: card.collapsed ? "+" : "−"
            color: Theme.gold
            font.pixelSize: 14
            font.bold: true
        }
    }
}
