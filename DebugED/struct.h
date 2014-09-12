#ifndef STRUCT_H
#define STRUCT_H

#include "arrow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QList>



QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
class Arrow;
QT_END_NAMESPACE


class Struct : public QGraphicsPolygonItem{

public:
    enum StructType{ Cell };
    enum {Type = UserType + 1};

    Struct(StructType structType, QString var);
    void setValues(QList<QString> values);
    StructType structType() const { return _structType; }
    QPolygonF structItem() { return _structItem; }
    QPolygonF structHead() { return _structHead; }
    QGraphicsPolygonItem* head() { return _head; }
    QList<QString> values() const { return _values; }
    qreal width() const { return _width; }
    qreal height() const { return _height; }
    QString var() const { return _var; }
    QList<Arrow *> arrows(){ return _arrows; }
    int type() const { return Type;}

    void addArrow(Arrow *arrow);
    void removeArrow(Arrow *arrow);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    StructType _structType;
    QPolygonF _structItem;
    QPolygonF _structHead;
    QGraphicsPolygonItem* _head;
    QList<QString> _values;
    QList<Arrow *> _arrows;
    QString _var;
    qreal _width;
    qreal _height;

};



#endif // STRUCT_H
