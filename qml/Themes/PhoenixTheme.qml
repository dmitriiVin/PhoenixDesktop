pragma Singleton

import QtQuick

QtObject {
    // Основной фон рабочего стола
    readonly property color background: "#1B1D29"
    // Основной фон панелей
    readonly property color panel: "#181824"
    // Более тёмные панели / TopBar
    readonly property color panelDark: "#0E101F"
    // Phoenix Island
    readonly property color island: "#050509"
    // Карточки
    readonly property color card: "#1B1D29"
    // Карточка при наведении
    readonly property color cardHover: "#272636"
    // Границы
    readonly property color border: "#353346"
    // Основной текст
    readonly property color text: "#F5F3F7"
    // Вторичный текст
    readonly property color textSecondary: "#A9A5B2"
    // Приглушённый текст
    readonly property color textMuted: "#716D7C"
    // Главный акцент Phoenix
    readonly property color accent: "#A855F7"
    // Более светлый вариант акцента
    readonly property color accentLight: "#C084FC"
    // Тёмный вариант акцента
    readonly property color accentDark: "#7E22CE"
    // Фон выделенного элемента
    readonly property color accentBackground: "#2A1D3F"
    // Успешное состояние
    readonly property color success: "#4ADE80"
    // Предупреждение
    readonly property color warning: "#FACC15"
    // Ошибка
    readonly property color error: "#F87171"


    readonly property real panelOpacity: 0.80
    readonly property real islandOpacity: 0.90
    readonly property real cardOpacity: 0.75
    readonly property real desktopOpacity: 1.0

    function withOpacity(color, opacity) {
        return Qt.rgba(
            color.r,
            color.g,
            color.b,
            opacity
        )
    }
}