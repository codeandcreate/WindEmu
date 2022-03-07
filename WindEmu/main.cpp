#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
// Added for reMarkable support
#include <QtPlugin>
#ifdef __arm__
Q_IMPORT_PLUGIN(QsgEpaperPlugin)
#endif
// end reMarkable additions
#include <QtDBus>
#include <QTimer>

#include "eventfilter.h"
#include "lcd.h"

using namespace std;

#include "../WindCore/clps7111.h"
#include "../WindCore/windermere.h"



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // Added for reMarkable support
#ifdef __arm__
    qputenv("QMLSCENE_DEVICE", "epaper");
    qputenv("QT_QPA_PLATFORM", "epaper:enable_fonts");
    qputenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS", "rotate=180");
    qputenv("QT_QPA_GENERIC_PLUGINS", "evdevtablet");
#endif
    // end reMarkable additions

    qDebug() << "Starting";

    QGuiApplication app(argc, argv);
    qmlRegisterType<Lcd>("Lcd",1,0,"Lcd");

	auto args = app.arguments();

	QString romFile;
	if (args.length() > 1)
		romFile = args.last();
	if (romFile.isNull()) return 0;

	// what do we have?
	QFile f(romFile);
	f.open(QFile::ReadOnly);
	auto buffer = f.readAll();
	f.close();

	if (buffer.size() < 0x400000) {
		//QMessageBox::critical(nullptr, "WindEmu", "Invalid ROM file!");
        printf("Invalid ROM file!");
		return 0;
	}

	EmuBase *emu = nullptr;
	uint8_t *romData = (uint8_t *)buffer.data();

	// parse this ROM to learn what hardware it's for
	int variantFile = *((uint32_t *)&romData[0x80 + 0x4C]) & 0xFFFFFFF;
	if (variantFile < (buffer.size() - 8)) {
		int variantImg = *((uint32_t *)&romData[variantFile + 4]) & 0xFFFFFFF;
		if (variantImg < (buffer.size() - 0x70)) {
			int variant = *((uint32_t *)&romData[variantImg + 0x60]);

			if (variant == 0x7060001) {
				// 5mx ROM
				emu = new Windermere::Emulator;
			} else if (variant == 0x5040001) {
				// Osaris ROM
				emu = new CLPS7111::Emulator;
			} else {
				//QMessageBox::critical(nullptr, "WindEmu", "Unrecognised ROM file!");
                printf("Unrecognised ROM file!");
				return 0;
			}
		}
	}

    // Look into QQuickPaintedItem

	emu->loadROM(romData, buffer.size());
    qDebug() << "ROM loaded";

    QFile stateFile("psion.out");
	if (stateFile.open(QFile::ReadOnly)) {
        qDebug() << "State found, loading";
        emu->restoreState(&stateFile);
        qDebug() << "State loaded";
    }
    stateFile.close();

    auto filter = new EventFilter(&app);
    app.setApplicationDisplayName("Desktop");
    app.installEventFilter(filter);

    qDebug() << "Event filter installed";

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    QObject* root = engine.rootObjects().first();
    filter->root = (QQuickItem*)root;
    qDebug() << "Root";
    Lcd* lcd = (Lcd*)root->findChild<QObject*>("lcd");
    filter->setLcd(lcd);

    qDebug() << "Lcd found " << lcd;
    lcd->start(emu);


    return app.exec();
}