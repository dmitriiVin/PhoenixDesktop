import QtQuick
import Phoenix 1.0


Item {
    id: desktop
    property var manager

    Rectangle {
        anchors.fill: parent
        color: PhoenixTheme.background
    }

    Repeater {
        model: manager.files

        DesktopIcon {
            fileName: modelData.name
            folder: modelData.folder
            x: 50 + (index % 8) * 120
            y: 90 + Math.floor(index / 8) * 120
        }
    }
}