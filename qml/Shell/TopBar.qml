import QtQuick
import Phoenix 1.0

Item {
    id: topBar

    height: 58

    Rectangle {
        anchors.fill: parent
        color: PhoenixTheme.withOpacity(
            PhoenixTheme.panelDark,
            PhoenixTheme.panelOpacity
        )
    }

    Text {
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.verticalCenter: parent.verticalCenter

        text: "Phoenix"
        color: PhoenixTheme.text
        font.pixelSize: 16
        font.bold: true
    }
}