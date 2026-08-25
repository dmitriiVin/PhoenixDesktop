import QtQuick
import Phoenix 1.0

Item {
    id: desktop

    property var manager

    IconThemeManager {
        id: iconManager
    }

    Rectangle {
        anchors.fill: parent
        color: PhoenixTheme.background
    }

    Component.onCompleted: {
        manager.setDesktopSize(
            width,
            height
        )
    }

    onWidthChanged: {
        manager.setDesktopSize(
            width,
            height
        )
    }

    onHeightChanged: {
        manager.setDesktopSize(
            width,
            height
        )
    }

    Repeater {
        model: manager.files

        delegate: DesktopIcon {
            fileName: modelData.name
            filePath: modelData.path

            iconPath: iconManager.iconForFile(
                modelData.path
            )

            desktopItem: modelData
            desktopManager: manager

            desktopWidth: desktop.width
            desktopHeight: desktop.height

            x: modelData.x
            y: modelData.y
        }
    }
}