// (c) Nathaniel van Diepen 2019 and used with permission.
// https://github.com/Eeems/oxide/blob/master/LICENSE.md
#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>
#include <QEvent>
#include <QGuiApplication>
#include <QQuickItem>
#include "lcd.h"

class EventFilter : public QObject
{
    Q_OBJECT
public:
    QQuickItem* root;
    explicit EventFilter(QObject* parent = nullptr);
    void setLcd(Lcd* listener) {lcd = listener;}
signals:
    void suspend();
protected:
  bool eventFilter(QObject* obj, QEvent* ev);
  Lcd* lcd;
};


#endif // EVENTFILTER_H