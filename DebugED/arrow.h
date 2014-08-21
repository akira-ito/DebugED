#ifndef ARROW_H
#define ARROW_H

#include "struct.h"
#include <QGraphicsLineItem>


class Arrow : public QGraphicsLineItem{

public:
    Arrow(Struct *a, Struct *b);
    Struct *a() const { return _a; }
    Struct *b() const { return _b; }
    QRectF boundingRect() const;
    QPainterPath Arrow::shape() const;
    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);


private:
    Struct *_a;
    Struct *_b;

    QPolygonF arrowHead;
};

#endif // ARROW_H
