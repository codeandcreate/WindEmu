#include "lcd.h"
#include <QDebug>
#include <QTimer>
#include <QImage>
#include<QPixmap>
#include<QPainter>
#include<QFile>
#include <QBitmap>
#include <QCoreApplication>

#include "../WindCore/decoder.h"
#include "clps7111.h"

#define SCALE_F 2
#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 1440
#define ORIGIN_X (((SCREEN_WIDTH-1391)/2)/* + 91*/)
#define ORIGIN_Y (((SCREEN_HEIGHT-611)/2)/* + 12*/)
#define LCD_IMAGE_FORMAT QImage::Format_Indexed8

Lcd::Lcd(QQuickItem *parent) {

}

void Lcd::start(EmuBase* emu) {
    this->emu = emu;
    qDebug() << "Lcd::start()";
    img = new QImage(emu->getLCDWidth(), emu->getLCDHeight(), LCD_IMAGE_FORMAT);
    for (int y = 0; y < img->height(); y++)
        lines[y] = img->scanLine(y);
            
    elapsedTimer.start();
	emu->setLogger([&](const char *str) {
		QString fullStr = QStringLiteral("[%1] %2").arg(elapsedTimer.elapsed()).arg(str);
		qDebug() << fullStr;
	});

    emuThread = new LcdWorkerThread(this->emu);
    
    paintTimer = new QTimer(NULL);
    paintTimer->setInterval(1);
    qDebug() << "connecting Timer";

    connect(paintTimer, SIGNAL(timeout()), SLOT(execPaintTimer()));
    paintTimer->start();

    emuThread->start();
}

void Lcd::paint(QPainter *painter) {
    #ifdef FRAME_DEBUG
    QElapsedTimer pt;
    pt.start();
    #endif

	emu->readLCDIntoBuffer(lines, false);

    QRectF target(0.0, 0.0, 640.0, 240.0);
    QRectF source(0.0, 0.0, 640.0, 240.0);

    painter->scale(SCALE_F, SCALE_F);
    painter->drawPixmap(target, QPixmap::fromImage(*img), source);

    #ifdef FRAME_DEBUG
    qDebug() << "Paint operation took" << pt.elapsed() << "milliseconds";
    #endif
}

void Lcd::dumpDisassembly() {
    const int context = 8 * 4;
	uint32_t pc = emu->getGPR(15) - 8;
    uint32_t minCode = pc - context;
	if (minCode >= (UINT32_MAX - context))
        minCode = 0;
    uint32_t maxCode = pc + context;
	if (maxCode < context)
        maxCode = UINT32_MAX;

	for (uint32_t addr = minCode; addr >= minCode && addr <= maxCode; addr += 4) {
		const char *prefix = (addr == pc) ? (emu->instructionReady() ? "==>" : "...") : "   ";
        struct ARMInstructionInfo info;
        char buffer[512];

		auto result = emu->readVirtual(addr, ARM710::V32);
		if (result.first.has_value()) {
			uint32_t opcode = result.first.value();
			ARMDecodeARM(opcode, &info);
			ARMDisassemble(&info, addr, buffer, sizeof(buffer));
			qDebug() << QString("%1 %2 | %3 | %4").arg(prefix).arg(addr, 8, 16).arg(opcode, 8, 16).arg(buffer);
		}
    }
}

void Lcd::saveButtonPressed() {
    emuThread->terminate();
    emuThread->wait();
    qDebug() << "Saving state to psion.out";
    QFile f("psion.out");
	f.open(QFile::WriteOnly);
    emu->saveState(&f);
	f.close();
    qDebug() << "State written.";
    QCoreApplication::quit();
}

void Lcd::digitizerDown(QPointF pos) {
    // We rotate the display 90 degrees so x and y get flipped.
    int32_t px = (pos.y() - ORIGIN_X) / SCALE_F;
    int32_t py = ((SCREEN_HEIGHT - pos.x()) - ORIGIN_Y) / SCALE_F;

    emu->updateTouchInput(px, py, true);
}

void Lcd::digitizerUp(QPointF pos) {
    // We rotate the display 90 degrees so x and y get flipped.
    int32_t px = (pos.y() - ORIGIN_X) / SCALE_F;
    int32_t py = ((SCREEN_HEIGHT - pos.x()) - ORIGIN_Y) / SCALE_F;

    emu->updateTouchInput(px, py, false);
}

void Lcd::digitizerPos(QPointF pos) {
    digitizerDown(pos);
}

void Lcd::fingerPos(QPointF pos) {
    fingerDown(pos);
}

void Lcd::fingerDown(QPointF pos) {
    emu->updateTouchInput((int32_t)(pos.x()/SCALE_F), (int32_t)(pos.y()/SCALE_F), true);
}
void Lcd::fingerUp(QPointF pos) {
    emu->updateTouchInput((int32_t)(pos.x()/SCALE_F), (int32_t)(pos.y()/SCALE_F), false);
}

void Lcd::execPaintTimer() {
    update();
}

void Lcd::execTimer() {
    #ifdef FRAME_DEBUG
    qDebug() << "Inter-exec time:" << frameTimer.elapsed() << "milliseconds";
    frameTimer.start();
    #endif

	if (emu) {
        QElapsedTimer pt;
        pt.start();

		emu->executeUntil(emu->currentCycles() + (emu->getClockSpeed() / 64));

        frame++;
    #ifdef FRAME_DEBUG
        if (pt.nsecsElapsed() > 15625000) {
            qDebug() << "Exec+draw took" << pt.nsecsElapsed() << "nanoseconds [should be < 15,625,000]";
        }
    #endif
    }
}

static EpocKey resolveKey(int key, int vk) {
	switch (key) {
		case Qt::Key_Apostrophe: return EStdKeySingleQuote;
		case Qt::Key_Backspace: return EStdKeyBackspace;
		case Qt::Key_Escape: return EStdKeyEscape;
		case Qt::Key_Enter: return EStdKeyEnter;
		case Qt::Key_Return: return EStdKeyEnter;
		case Qt::Key_Alt: return EStdKeyMenu;
		case Qt::Key_Tab: return EStdKeyTab;
	#ifdef Q_OS_MAC
		case Qt::Key_Meta: return EStdKeyLeftCtrl;
	#else
		case Qt::Key_Control: return EStdKeyLeftCtrl;
	#endif
		case Qt::Key_Down: return EStdKeyDownArrow;
		case Qt::Key_Period: return EStdKeyFullStop;
	#ifdef Q_OS_MAC
		case Qt::Key_Control: return EStdKeyLeftFunc;
	#else
		case Qt::Key_Meta: return EStdKeyLeftFunc;
	#endif
		case Qt::Key_Shift: return EStdKeyLeftShift;
		case Qt::Key_Right: return EStdKeyRightArrow;
		case Qt::Key_Left: return EStdKeyLeftArrow;
		case Qt::Key_Comma: return EStdKeyComma;
		case Qt::Key_Up: return EStdKeyUpArrow;
		case Qt::Key_Space: return EStdKeySpace;
	}

	if (key >= '0' && key <= '9') return (EpocKey)key;
	if (key >= 'A' && key <= 'Z') return (EpocKey)key;

	return (EpocKey)key;
}

void Lcd::keyPressEvent(QKeyEvent *event)
{
	emu->log("KeyPress: QtKey=%d nativeVirtualKey=%x nativeModifiers=%x", event->key(), event->nativeVirtualKey(), event->nativeModifiers());
	EpocKey k = resolveKey(event->key(), event->nativeVirtualKey());
	if (k != EStdKeyNull)
		emu->setKeyboardKey(k, true);
}

void Lcd::keyReleaseEvent(QKeyEvent *event)
{
	EpocKey k = resolveKey(event->key(), event->nativeVirtualKey());
	if (k != EStdKeyNull)
		emu->setKeyboardKey(k, false);
}
