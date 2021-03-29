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
        id: digitizer;
        width:1391;
        height:611;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;

        MouseArea {
            id: lcdMouseArea;
            anchors.fill: parent;
            onPositionChanged: {
                var positionInDigitizer = mapToItem(digitizer, mouse.x, mouse.y);
                lcd.fingerPos(positionInDigitizer);
            }
            onPressed: {
                var positionInDigitizer = mapToItem(digitizer, mouse.x, mouse.y);
                lcd.fingerDown(positionInDigitizer);
            }
            onReleased: {
                var positionInDigitizer = mapToItem(digitizer, mouse.x, mouse.y);
                lcd.fingerUp(positionInDigitizer);
            }
        }

        Image {
            source: "imgs/cover.png"
        }

        Lcd {
            id: lcd;
            objectName: "lcd";
            y:12;
            x:91;
            width: 1280;
            height: 480;
        }



    }

    // Keyboard {
    //         id: keyboard;
    //         visible: true;
    //         function onChar(ch) {
    //             console.log(ch);
    //             lcd.keyPressEvent(ch.toUpperCase());
    //         }
    //         function onCharRelease(ch) {
    //             console.log("release:" + ch);
    //             lcd.keyReleaseEvent(ch.toUpperCase());
    //         }
    //         anchors.bottom: parent.bottom
    // }

    Rectangle {
        id: bmenubox;
        rotation: 90;
        width: 80
        height: 80
        color: "white"
        border.color: "black"
        border.width: 3
        radius: 10
        anchors.left: parent.left;
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
