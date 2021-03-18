import QtQuick 2.6
import QtQuick.Window 2.2
import Lcd 1.0
import "."

Window {
    id: mainWindow;
    visible: true;
    title: qsTr("WindEmu")
    width: 1404;
    height: 1872;

    Rectangle {
        rotation: 90;
        width: 1872;
        height: 702;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        border.color: "black"
        border.width: 1

        Lcd {
            id: lcd;
            objectName: "lcd"
            width: 1872;
            height: 702;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter: parent.verticalCenter;
        }

    }

    Rectangle {
        id: bmenubox;
        width: 80
        height: 80
        color: "white"
        border.color: "black"
        border.width: 3
        radius: 10
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        Text {
            id: bsc;
            text: "<font size='+1' face='Noto Emoji'>📶</font>";
            textFormat: Text.RichText;
            anchors {horizontalCenter: parent.horizontalCenter;}
        }
        MouseArea {
            id: bdownMouseArea
            anchors.fill: parent
            onPressed: {
                lcd.menuButtonPressed();
            }
            onReleased: {
                lcd.menuButtonReleased();
            }
        }
    }

}
