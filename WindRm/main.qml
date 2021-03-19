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
        id: digitizer;
        rotation: 90;
        width: 1872;
        height: 882;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;

        MouseArea {
            id: lcdMouseArea;
            anchors.fill: parent;
            onPositionChanged: {
                var positionInDigitizer = mapToItem(digitizer, mouse.x, mouse.y);
                console.log("pos ", positionInDigitizer);
                lcd.digitizerPos(positionInDigitizer);
            }
            onPressed: {
                var positionInDigitizer = mapToItem(digitizer, mouse.x, mouse.y);
                console.log("pressed ", positionInDigitizer);
                lcd.digitizerDown(positionInDigitizer);
            }
            onReleased: {
                var positionInDigitizer = mapToItem(digitizer, mouse.x, mouse.y);
                console.log("rel ", positionInDigitizer);
                lcd.digitizerUp(positionInDigitizer);
            }
        }

        Image {
            source: "imgs/cover.png"
        }

        Lcd {
            id: lcd;
            objectName: "lcd";
            y:14;
            x:122;
            width: 1723;
            height: 646;
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
            text: "<font size='+1' face='Noto Emoji'>💾</font>";
            textFormat: Text.RichText;
            anchors {horizontalCenter: parent.horizontalCenter;}
        }
        MouseArea {
            id: bdownMouseArea
            anchors.fill: parent
            onClicked: {
                lcd.saveButtonPressed();
            }
        }
    }

}
