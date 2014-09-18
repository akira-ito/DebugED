#ifndef STRUCT_H
#define STRUCT_H

#include "arrow.h"
#include "variable.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QMainWindow>
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
class Variable;
class QMainWindow;
class QObject;
QT_END_NAMESPACE


class Struct : public QGraphicsPolygonItem, QObject{

public:
    enum StructType{ Cell };
    enum {Type = UserType + 1};

    Struct(StructType structType);
    void setValues(QList<QString> values);
    StructType structType() const { return _structType; }
    QPolygonF structItem() { return _structItem; }
    QPolygonF structHead() { return _structHead; }
    QGraphicsPolygonItem* head() { return _head; }
    QList<QString> values() const { return _values; }
    qreal width() const { return _width; }
    qreal height() const { return _height; }
    Variable *variable() const { return _variable; }
    QList<Arrow *> arrows(){ return _arrows; }
    int addres() { return _address; }
    int type() const { return Type;}

    void setVariable(Variable *variable);
    void addArrow(Arrow *arrow);
    void removeArrow(Arrow *arrow);
    void pointAddress(int address);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    StructType _structType;
    QPolygonF _structItem;
    QPolygonF _structHead;
    QGraphicsPolygonItem* _head;
    QList<QString> _values;
    QList<Arrow *> _arrows;
    Variable *_variable;
    QGraphicsTextItem *_pointAddress;
    int _address;
    qreal _width;
    qreal _height;

};



#endif // STRUCT_H
