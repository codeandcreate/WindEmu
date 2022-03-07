import QtQuick 2.6
import QtQuick.Window 2.2
import Lcd 1.0
import "."

Window {
    id: mainWindow;
    visible: true;
	color: "dimgrey"
    title: qsTr("WindEmu")
	flags: Qt.Window 
    width: 1440;
    height: 800;
    onClosing: lcd.saveButtonPressed()

    Rectangle {
        rotation: 0;
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

}
