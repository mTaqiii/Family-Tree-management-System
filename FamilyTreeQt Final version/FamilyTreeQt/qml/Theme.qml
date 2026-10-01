pragma Singleton
import FamilyTreeQt
import QtQuick

QtObject {
    readonly property bool isNight: AppSettings.nightMode

    // Palette straight from the design brief. Background/panel/text
    // colors swap between day and night; accent colors (gold, the
    // gender colors, forest green) stay put in both, since they're
    // meant to read the same regardless of time of day.
    readonly property color darkBlue: isNight ? "#16213E" : "#BEE3F8"
    readonly property color forestGreen: "#2E8B57"
    readonly property color gold: "#D4AF37"
    readonly property color white: "#F4F1EA"
    readonly property color softCyan: isNight ? "#8FD9E8" : "#2C7DA0"
    readonly property color black: isNight ? "#0B0F1A" : "#EAF6FB"

    // Derived / functional colors.
    readonly property color male: "#4A90D9"
    readonly property color female: "#D97AA8"
    readonly property color deceased: "#8A8F98"
    readonly property color panelBg: isNight ? "#1B2A45" : "#FFFFFF"
    readonly property color panelBgLight: isNight ? "#22335294" : "#DDFFFFFF"
    readonly property color panelBgElevated: isNight ? "#22314E" : "#EEF3F8"
    readonly property color panelBorder: isNight ? "#4A6690" : "#B7C8DA"
    readonly property color divider: isNight ? "#33465F" : "#D3DFEA"
    readonly property color deceasedCardBg: isNight ? "#3A3F47" : "#DCE0E5"

    // Text colors -- both verified against their panel backgrounds
    // to clear WCAG AA (4.5:1) for normal text: night textSecondary
    // ~9.3:1 on panelBgElevated, day textSecondary ~13.8:1. Day mode
    // originally shipped with textSecondary too light (~2.6:1) since
    // several panels were still hardcoded to a dark-only background
    // color instead of Theme.panelBg/panelBgElevated -- fixed here
    // and at every one of those call sites.
    readonly property color textPrimary: isNight ? white : "#16213E"
    readonly property color textSecondary: isNight ? "#CBDCEA" : "#122436"

    // Interactive surfaces (nav buttons, list rows, etc) -- three
    // states, each adapting so hover/active states stay visible
    // against whichever panel color is currently active instead of
    // just getting darker (which would vanish on a light day panel).
    readonly property color surfaceNormal: isNight ? "#25324A" : "#DCE6F0"
    readonly property color surfaceHover: isNight ? "#2E4468" : "#C7D8EA"
    readonly property color surfaceActive: isNight ? "#35507A" : "#B7CDE5"

    // Motion. Halved-to-near-zero when Reduced Motion is on in
    // Settings, rather than a separate code path everywhere a
    // Behavior/Animation references these -- every existing
    // `duration: Theme.xDuration` binding gets the benefit for free.
    readonly property int fastDuration: AppSettings.reducedMotion ? 0 : 150
    readonly property int normalDuration: AppSettings.reducedMotion ? 0 : 300
    readonly property int slowDuration: AppSettings.reducedMotion ? 60 : 600
    readonly property int sceneDuration: AppSettings.reducedMotion ? 120 : 900

    // Layout.
    readonly property int cardWidth: 160
    readonly property int cardHeight: 92
}
