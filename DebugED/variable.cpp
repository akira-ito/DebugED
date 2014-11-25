#include "variable.h"
#include <math.h>
#include <QPen>
#include <QPainter>
#include <QGraphicsLineItem>
#include <QTextCursor>
#include <QTextBlock>
#include <QDebug>

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
    _variable->setFont(QFont("Timer new roma", 15));
    _variable->setFlag(GraphicsItemFlag::ItemIsSelectable, true);
    _variable->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    _variable->setFlag(QGraphicsItem::ItemIsMovable, true);

    QPointF posStruct = _structItem.last()->pos();
    _variable->setPos(posStruct + QPointF(0, 80));

    _address = QString::number(qrand() % (4294967295), 16).toUpper();
    QGraphicsTextItem *addressText = new QGraphicsTextItem(_variable);
    addressText->setPlainText(_address);

    int size = _variable->boundingRect().width();
    int length = _address.length()*10;
    int posx = size < length ? -(length-size)/2 : size/3;
    addressText->setPos(posx, 25);
    addressText->setFont(QFont("Timer new roma", 10, QFont::Bold, true));
    addressText->setToolTip(tr("Endereço de memoria."));
    addressText->setDefaultTextColor(QColor(0, 0, 0, 200));
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

    /*painter->setFont(QFont("Timer new roma", 11, -1, true) );
    painter->drawText(_variable->pos()+QPointF(0,40),QString::number(_address,16).toUpper() ,Qt::AlignCenter, 0);
*/

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

    setLine(QLineF(intersectPoint+QPointF(_variable->textCursor().block().length(),0), _variable->pos()+QPointF(_variable->textCursor().block().length()*5,12)));

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                    cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                    cos(angle + Pi - Pi / 3) * arrowSize);


    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;
    painter->drawLine(line());
    painter->drawPolygon(arrowHead);

    prepareGeometryChange();

}

void Variable::updatePosition(){
    QLineF line(mapFromItem(_variable, 0, 0), mapFromItem(_structItem.last(), 0, 0));
    setLine(line);
    prepareGeometryChange();
}
