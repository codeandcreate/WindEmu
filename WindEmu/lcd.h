#ifndef LCD_H
#define LCD_H

#include <QQuickPaintedItem>
#include <QElapsedTimer>
#include <QThread>
#include "../WindCore/emubase.h"

// #define FRAME_DEBUG
#define TICKS_PER_SECOND 64
#define DRIFT_MILLIS_ADJUST_PER_TICK 10
#define NANO_PER_MILLI 1000000
#define SECOND_IN_NANOS 1000000000

class LcdWorkerThread : public QThread {
    Q_OBJECT
public:
    LcdWorkerThread(EmuBase* emuBase) : emu(emuBase) {}
    void run() override {
        QElapsedTimer t;
        int driftMs = 0;
        for (;;) {
            t.start();
            emu->executeUntil(emu->currentCycles() + (emu->getClockSpeed() / TICKS_PER_SECOND));
            int sleepNs = (SECOND_IN_NANOS/TICKS_PER_SECOND) - t.nsecsElapsed();
            if (driftMs > DRIFT_MILLIS_ADJUST_PER_TICK && sleepNs > DRIFT_MILLIS_ADJUST_PER_TICK * NANO_PER_MILLI) {
                sleepNs -= DRIFT_MILLIS_ADJUST_PER_TICK * NANO_PER_MILLI;
                driftMs = driftMs - DRIFT_MILLIS_ADJUST_PER_TICK;
            }
            if (sleepNs > 0) {
                struct timespec ts = { 0, sleepNs };
                nanosleep(&ts, NULL);
            } else {
                // sleepNs always negative here, adding to drift.
                driftMs -= sleepNs / NANO_PER_MILLI;
                #ifdef FRAME_DEBUG
                qDebug() << "Drift is now: " << driftMs << "ms (" << t.nsecsElapsed() << ") last exec.";
                #endif
            }
        }
    }
private:
    EmuBase* emu;
};

class Lcd : public QQuickPaintedItem {
    Q_OBJECT
 
public:
    Lcd(QQuickItem *parent = 0);
 
    void paint(QPainter *painter) override;
    void start(EmuBase* emu);

    Q_INVOKABLE void saveButtonPressed();
    Q_INVOKABLE void digitizerDown(QPointF pos);
    Q_INVOKABLE void digitizerUp(QPointF pos);
    Q_INVOKABLE void digitizerPos(QPointF pos);
    
    Q_INVOKABLE void fingerDown(QPointF pos);
    Q_INVOKABLE void fingerUp(QPointF pos);
    Q_INVOKABLE void fingerPos(QPointF pos);

    Q_INVOKABLE void keyPressEvent(QKeyEvent* event);
    Q_INVOKABLE void keyReleaseEvent(QKeyEvent* event);


public slots:
    void execTimer();
    void execPaintTimer();

private:
    void dumpDisassembly();

private:
	QElapsedTimer elapsedTimer;
#ifdef FRAME_DEBUG
    QElapsedTimer frameTimer;
#endif
	EmuBase *emu;
    QTimer *paintTimer;
    int frame;
    QThread* emuThread;
    QThread* lcdThread;
    uint8_t* lines[1024];
	QImage* img;

};
#endif