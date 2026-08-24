import QtQuick
import Phoenix 1.0

Item {
    id: island

    width: 360
    height: 40

    Rectangle {
        anchors.fill: parent

        radius: height / 2

        color: PhoenixTheme.withOpacity(
            PhoenixTheme.island,
            PhoenixTheme.islandOpacity
        )

        Text {
            anchors.centerIn: parent

            text: "Phoenix Island"
            color: PhoenixTheme.text
            font.pixelSize: 13
        }
    }
}