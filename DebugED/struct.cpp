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
    _pointAddress->setPos(70 ,-30);
    _pointAddress->setFont(QFont("Timer new roma", 9, QFont::Bold, true));
    _pointAddress->setToolTip(tr("Endereço da celula apontada."));
    _pointAddress->setDefaultTextColor(QColor(255, 0, 250, 100));
    _pointAddress->setRotation(90);

    _address = QString::number(qrand() % (4294967295), 16).toUpper();

    QGraphicsTextItem *address = new QGraphicsTextItem(this);
    address->setPlainText(_address);
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

void Struct::addVariable(Variable *variable){
    _variables.push_back(variable);
}

void Struct::removeVariable(Variable *variable){
    int index = _variables.indexOf(variable);
    if (index != -1)
        _variables.removeAt(index);
}

bool Struct::matchVariable(QString variable){
    foreach(Variable *var,  _variables){
        if (var->variable() == variable){
            return true;
        }
    }
    return false;
}

void Struct::addArrow(Arrow *arrow){
    _arrows.push_back(arrow);
}

void Struct::removeArrow(Arrow *arrow){
    int index = _arrows.indexOf(arrow);
    if (index != -1)
        _arrows.removeAt(index);
}

void Struct::pointAddress(QString address){
    _pointAddress->setPlainText(address);
}

void Struct::removePointAddress(){
    _pointAddress->setPlainText("");
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
