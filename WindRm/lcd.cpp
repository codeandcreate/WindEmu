#include "lcd.h"
#include <QDebug>
#include <QTimer>
#include <QImage>
#include<QPixmap>
#include<QPainter>

#include "../WindCore/decoder.h"
#include "clps7111.h"

Lcd::Lcd(QQuickItem *parent) {

}

void Lcd::start(EmuBase* emu) {
    this->emu = emu;
    qDebug() << "Lcd::start()";
    elapsedTimer.start();
	emu->setLogger([&](const char *str) {
		QString fullStr = QStringLiteral("[%1] %2").arg(elapsedTimer.elapsed()).arg(str);
		qDebug() << fullStr;
	});

    timer = new QTimer(this);
    timer->setInterval(1000/64);
    qDebug() << "connecting Timer";

    connect(timer, SIGNAL(timeout()), SLOT(execTimer()));
    timer->start();
}

void Lcd::paint(QPainter *painter) {
	uint8_t *lines[1024];
	QImage img(emu->getLCDWidth(), emu->getLCDHeight(), QImage::Format_Grayscale8);
	for (int y = 0; y < img.height(); y++)
		lines[y] = img.scanLine(y);
	emu->readLCDIntoBuffer(lines, false);

    QRectF target(0.0, 0.0, 640.0, 240.0);
    QRectF source(0.0, 0.0, 640.0, 240.0);

    painter->scale(2.925, 2.925);
    painter->drawPixmap(target, QPixmap::fromImage(std::move(img)), source);
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

void Lcd::menuButtonPressed() {
    qDebug() << "menuPressed " << emu->currentCycles();
    emu->setKeyboardKey(EStdKeyMenu, true);
}
void Lcd::menuButtonReleased() {
    emu->setKeyboardKey(EStdKeyMenu, false);
}


void Lcd::execTimer() {
    //qDebug() << "execTimer";
	if (emu) {
		emu->executeUntil(emu->currentCycles() + (emu->getClockSpeed() / 64));
		//updateScreen();
        //qDebug() << QString("Cycles: %1").arg(emu->currentCycles());
        //dumpDisassembly();

        if (emu->currentCycles() >= 72000008 && emu->currentCycles() <= 73000008) {
            // splash screen ready
            update();
        }

        if (emu->currentCycles() > 1047744048) {
            update();
        }
	}
}
