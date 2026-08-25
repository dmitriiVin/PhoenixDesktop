import QtQuick
import Phoenix 1.0

Item {
    DesktopManager {
        id: desktopManager
    }
    Desktop {
        anchors.fill: parent
        manager: desktopManager
    }
    TopBar {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }
    Island {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 8
    }
}
