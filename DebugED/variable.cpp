#include "variable.h"
#include <math.h>
#include <QPen>
#include <QPainter>
#include <QGraphicsLineItem>

const qreal Pi = 3.14;

Variable::Variable(Struct *structItem, QString &var) {
    _structItem.push(structItem);
    setVariable(var);
}

QRectF Variable::boundingRect() const{
    qreal extra = (pen().width() + 20) / 2.0;

     return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                       line().p2().y() - line().p1().y()))
         .normalized()
         .adjusted(-extra, -extra, extra, extra);

}

void Variable::setVariable(QString &var){
    _variable = new QGraphicsTextItem(this);
    _variable->setPlainText(var);
    _variable->setFlag(GraphicsItemFlag::ItemIsSelectable, true);
    _variable->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    _variable->setFlag(QGraphicsItem::ItemIsMovable, true);
    QPointF posStruct = _structItem.last()->pos();
    _variable->setPos(posStruct + QPointF(-10, -10));
}

void Variable::pointStruct(Struct *structItem){
    _structItem.push(structItem);
}

void Variable::removeStruct(Struct *){
    _structItem.pop();
}

QPainterPath Variable::shape() const{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void Variable::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    if (_variable->collidesWithItem(_structItem.last()))
        return;

    QPen myPen = pen();
    myPen.setColor(Qt::black);
    myPen.setStyle(Qt::DotLine);
    qreal arrowSize = 10;
    painter->setPen(myPen);
    painter->setBrush(Qt::black);

    QLineF centerLine(_variable->pos(), _structItem.last()->pos());
    QPolygonF endPolygon = _structItem.last()->polygon();
    QPointF p1 = endPolygon.first() + _structItem.last()->pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); ++i) {
    p2 = endPolygon.at(i) + _structItem.last()->pos();
    polyLine = QLineF(p1, p2);
    QLineF::IntersectType intersectType =
        polyLine.intersect(centerLine, &intersectPoint);
    if (intersectType == QLineF::BoundedIntersection)
        break;
        p1 = p2;
    }

    setLine(QLineF(intersectPoint, _variable->pos()));

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

}


void Variable::updatePosition(){
    QLineF line(mapFromItem(_variable, 0, 0), mapFromItem(_structItem.last(), 0, 0));
    setLine(line);
}
