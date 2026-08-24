import QtQuick
import Phoenix 1.0

Item {
    width: 90
    height: 100
    property string fileName
    property bool folder

    Column {
        anchors.centerIn: parent
        spacing: 0
        Rectangle {
            width: 64
            height: 64
            radius: 14
            color: PhoenixTheme.card
            Text {
                anchors.centerIn: parent
                text: folder ? "📁" : "📄"
                font.pixelSize: 34
            }
        }
        Text {
            width: 90
            text: fileName
            color: PhoenixTheme.text
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
        }
    }
}