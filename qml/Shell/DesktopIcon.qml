import QtQuick
import Phoenix 1.0

Item {
    id: root

    width: 90
    height: 110

    property string fileName
    property string filePath
    property string iconPath

    property var desktopItem
    property var desktopManager

    property real desktopWidth: 0
    property real desktopHeight: 0

    Column {
        width: root.width

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        spacing: 6

        Image {
            width: 64
            height: 64

            anchors.horizontalCenter: parent.horizontalCenter

            source: root.iconPath

            fillMode: Image.PreserveAspectFit
            smooth: true
        }

        Text {
            width: parent.width

            text: root.fileName
            color: PhoenixTheme.text

            font.pixelSize: 12

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop

            wrapMode: Text.Wrap
        }
    }

    MouseArea {
        anchors.fill: parent

        cursorShape: pressed
                     ? Qt.ClosedHandCursor
                     : Qt.OpenHandCursor

        drag.target: root
        drag.axis: Drag.XAndYAxis

        onReleased: {
            if (!desktopManager)
                return

            var margin = 10

            root.x = Math.max(
                margin,
                Math.min(
                    root.x,
                    root.desktopWidth - root.width - margin
                )
            )

            root.y = Math.max(
                margin,
                Math.min(
                    root.y,
                    root.desktopHeight - root.height - margin
                )
            )

            desktopManager.setItemPosition(
                root.filePath,
                root.x,
                root.y
            )
        }
    }
}