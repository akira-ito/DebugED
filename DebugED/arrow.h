#ifndef ARROW_H
#define ARROW_H

#include "struct.h"
#include <QGraphicsLineItem>

class Struct;


class Arrow : public QGraphicsLineItem{

public:
    enum {Type = UserType + 2};
    Arrow(Struct *a, Struct *b);
    Struct *a() const { return _a; }
    Struct *b() const { return _b; }
    QString name() { return _name; }
    QRectF boundingRect() const;
    QPainterPath Arrow::shape() const;
    void updatePosition();
    int type() const { return Type; }
    void remove();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);


private:
    Struct *_a;
    Struct *_b;
    QString _name;

    QPolygonF arrowHead;
};

#endif // ARROW_H
