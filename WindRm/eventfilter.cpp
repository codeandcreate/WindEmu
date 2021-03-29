// (c) Nathaniel van Diepen 2019 and used with permission.
// https://github.com/Eeems/oxide/blob/master/LICENSE.md
#include "eventfilter.h"
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>
#include <QTabletEvent>
#include <QScreen>

#define DISPLAYWIDTH 1404
#define DISPLAYHEIGHT 1872.0
#define WACOM_X_SCALAR (float(DISPLAYWIDTH) / float(DISPLAYHEIGHT))
#define WACOM_Y_SCALAR (float(DISPLAYHEIGHT) / float(DISPLAYWIDTH))
#define DEBUG_EVENTS 1

EventFilter::EventFilter(QObject *parent) : QObject(parent), root(nullptr) {}

QPointF swap(QPointF pointF){
    return QPointF(pointF.y(), pointF.x());
}

QPointF transpose(QPointF pointF){
    //qDebug() << "transpose " << pointF;
    pointF = swap(pointF);
    // Handle scaling from wacom to screensize
    pointF.setX(pointF.x() * WACOM_X_SCALAR);
    pointF.setY((DISPLAYWIDTH - pointF.y()) * WACOM_Y_SCALAR);
    //qDebug() << "-transpose " << pointF;
    return pointF;
}
QPointF globalPos(QQuickItem* obj){
    qreal x = obj->x();
    qreal y = obj->y();
    while(obj->parentItem() != nullptr){
        obj = obj->parentItem();
        x += obj->x();
        y += obj->y();
    }
    return QPointF(x, y);
}
QMouseEvent* toMouseEvent(QEvent::Type type, QEvent* ev){
    auto tabletEvent = (QTabletEvent*)ev;
    auto button = tabletEvent->pressure() > 0 || type == QMouseEvent::MouseButtonRelease ? Qt::LeftButton : Qt::NoButton;
    return new QMouseEvent(
        type,
        transpose(tabletEvent->posF()),
        transpose(tabletEvent->globalPosF()),
        transpose(tabletEvent->globalPosF()),
        button,
        button,
        tabletEvent->modifiers()
    );
}


bool EventFilter::eventFilter(QObject* obj, QEvent* ev){
    auto type = ev->type();
    bool filtered = QObject::eventFilter(obj, ev);
    if(!filtered){
        if (type == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(ev);
            if (lcd) {
                lcd->keyPressEvent(keyEvent);
            }
        }
        if (type == QEvent::KeyRelease) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(ev);
            if (lcd) {
                lcd->keyReleaseEvent(keyEvent);
            }
        }
        if(type == QEvent::TabletPress){
            auto mouseEvent = toMouseEvent(type, ev);
            auto pos = mouseEvent->globalPos();
            lcd->digitizerDown(pos);
        } else if(type == QEvent::TabletRelease){
            auto mouseEvent = toMouseEvent(type, ev);
            auto pos = mouseEvent->globalPos();
            lcd->digitizerUp(pos);
        } else if(type == QEvent::TabletMove){
            auto mouseEvent = toMouseEvent(type, ev);
            auto pos = mouseEvent->globalPos();
            lcd->digitizerPos(pos);
        }
    }
    return filtered;
}