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

    setBrush(QBrush(Qt::white));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    _head = new QGraphicsPolygonItem(this);
    _head->setPolygon(_structHead);



   /* QGraphicsRectItem *b = new QGraphicsRectItem(this);
    b->setRect(0, 0, 20, 50);

    QGraphicsTextItem *a = new QGraphicsTextItem();
    a->setParentItem(this);
    a->setPlainText("akira");
    qDebug() << childItems();*/

    //setPolygon(structItem);
    setPolygon( _structItem);
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
