#include "struct.h"

#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMenu>
#include <QDebug>

Struct::Struct(StructType structType): _width(70), _height(30){
    _structType = structType;

    switch (_structType){
        case Cell:
            _structItem << QPointF(-_width, -_height) << QPointF(_width, -_height)
                        << QPointF(_width, _height) << QPointF(-_width, _height)
                        << QPointF(-_width, -_height);

            _structHead << QPointF(50, -_height) << QPointF(_width, -_height)
                        << QPointF(_width, _height) << QPointF(50, _height)
                        << QPointF(50, -_height);
         break;

        default:
            break;
    }

    _head = new QGraphicsPolygonItem(this);
    _head->setPolygon(_structHead);

    _pointAddress = new QGraphicsTextItem(_head);
    _pointAddress->setPos(75 ,-30);
    _pointAddress->setFont(QFont("Timer new roma", 12, QFont::Bold, true));
    _pointAddress->setToolTip(tr("Endereço da celula apontada."));
    _pointAddress->setDefaultTextColor(QColor(255, 0, 250, 100));
    _pointAddress->setRotation(90);

    _address = (qrand() % (4294967295));
    QGraphicsTextItem *address = new QGraphicsTextItem(this);
    address->setPlainText(QString::number(_address));
    address->setPos(-20, -50);
    address->setFont(QFont("Timer new roma", 13, QFont::Bold, true));
    address->setToolTip(tr("Endereço de memoria."));
    address->setDefaultTextColor(QColor(255, 0, 150, 200));


    setPolygon( _structItem);
    setBrush(QBrush(Qt::white));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void Struct::setValues(QList<QString> values){
    switch(_structType){
    case Cell:
        QGraphicsSimpleTextItem *a = new QGraphicsSimpleTextItem(this);
        a->setText(QStringList(values).join("\n"));
        break;
    }
}

void Struct::setVariable(Variable *variable){
    _variable = variable;
}

void Struct::addArrow(Arrow *arrow){
    _arrows.push_back(arrow);
}

void Struct::removeArrow(Arrow *arrow){
    int index = _arrows.indexOf(arrow);
    if (index != -1)
        _arrows.removeAt(index);
}

void Struct::pointAddress(int address){
    _pointAddress->setPlainText(QString::number(address));
}

void Struct::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    QMenu *a = new QMenu("llll");
    QAction *v = new QAction("lll", a);
    a->addAction(v);
    a->exec(event->screenPos());
}

QVariant Struct::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value){

    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (Arrow *arrow, _arrows) {
            arrow->updatePosition();
        }
    }

    return value;
}
