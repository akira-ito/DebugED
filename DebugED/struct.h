#ifndef STRUCT_H
#define STRUCT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>



QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE


class Struct : public QGraphicsPolygonItem{

public:
    enum StructType{ Cell };

    Struct(StructType structType);
    StructType structType() const { return _structType; }
    QPolygonF structItem() { return _structItem; }
    QPolygonF structHead() { return _structHead; }
    QGraphicsPolygonItem* head() { return _head; }
    qreal width() const { return _width; }
    qreal height() const { return _height; }

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    StructType _structType;
    QPolygonF _structItem;
    QPolygonF _structHead;
    QGraphicsPolygonItem* _head;
    qreal _width;
    qreal _height;

};



#endif // STRUCT_H
