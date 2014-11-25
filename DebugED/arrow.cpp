#include "arrow.h"
#include <math.h>
#include <QPen>
#include <QPainter>
#include <QDebug>


const qreal Pi = 3.14;

Arrow::Arrow(Struct *a, Struct *b){
    _a = a;
    _b = b;

    if (!_a->arrows().isEmpty())
        _a->arrows().last()->setOpacity(0);

    //_b->addArrow(this);
    _a->addArrow(this);
    _a->pointAddress(_b->addres());
    _name = _a->addres()+":"+_b->addres();

    setFlag(GraphicsItemFlag::ItemIsSelectable, true);
    setFlag(GraphicsItemFlag::ItemIsFocusable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setZValue(-1000.0);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    if (_a->collidesWithItem(_b))
        return;

    QPen myPen = pen();
    myPen.setColor(Qt::black);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(Qt::black);
//! [4] //! [5]

    QLineF centerLine(_a->pos(), _b->pos());
    QPolygonF endPolygon = _b->polygon();
    QPointF p1 = endPolygon.first() + _b->pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); ++i) {
    p2 = endPolygon.at(i) + _b->pos();
    polyLine = QLineF(p1, p2);
    QLineF::IntersectType intersectType =
        polyLine.intersect(centerLine, &intersectPoint);
    if (intersectType == QLineF::BoundedIntersection)
        break;
        p1 = p2;
    }

    setLine(QLineF(intersectPoint, _a->pos()+QPointF(70,0)));

//! [5] //! [6]

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                    cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                    cos(angle + Pi - Pi / 3) * arrowSize);


    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;
//! [6] //! [7]
    painter->drawLine(line());
    painter->drawPolygon(arrowHead);
    if (isSelected()) {
        painter->setPen(QPen(Qt::red, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
}
QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void Arrow::updatePosition(){
    QLineF line(mapFromItem(_a, 0, 0), mapFromItem(_b, 0, 0));
    setLine(line);
}

void Arrow::remove(){
    _a->removeArrow(this);
    if (!_a->arrows().isEmpty()){
        _a->arrows().last()->setOpacity(1);
        _a->pointAddress(_a->arrows().first()->b()->addres());
    }else{
        _a->removePointAddress();
    }
    //_b->removeArrow(this);
}

bool Arrow::receivePoint(Struct *structB){
    return structB->addres() == _b->addres() && _a->pointAddress() == structB->addres() && _a->opacity() == 1;
}

