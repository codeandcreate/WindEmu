#ifndef LCD_H
#define LCD_H

#include <QQuickPaintedItem>
#include <QElapsedTimer>
#include "../WindCore/emubase.h"

class Lcd : public QQuickPaintedItem {
    Q_OBJECT
 
public:
    Lcd(QQuickItem *parent = 0);
 
    void paint(QPainter *painter) override;
    void start(EmuBase* emu);

    Q_INVOKABLE void menuButtonPressed();
    Q_INVOKABLE void menuButtonReleased();
    Q_INVOKABLE void saveButtonPressed();
    Q_INVOKABLE void digitizerDown(QPointF pos);
    Q_INVOKABLE void digitizerUp(QPointF pos);
    Q_INVOKABLE void digitizerPos(QPointF pos);


public slots:
    void execTimer();

private:
    void dumpDisassembly();

private:
	QElapsedTimer elapsedTimer;
	EmuBase *emu;
    QTimer *timer;
};
#endif