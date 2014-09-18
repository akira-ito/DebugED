#ifndef VARIABLE_H
#define VARIABLE_H

#include "struct.h"
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QStack>


class Struct;

class Variable : public QGraphicsLineItem{

public:
    Variable(Struct *structItem, QString &var);
    enum {Type = UserType + 3};
    int type() const { return Type; }
    Struct *structItem(){ return _structItem.last(); }
    QString variable() { return _variable->toPlainText(); }
    QRectF boundingRect() const;
    QPainterPath Variable::shape() const;
    void setVariable(QString &var);
    void pointStruct(Struct *structItem);
    void removeStruct(Struct *structItem);
    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    QStack<Struct *> _structItem;
    QGraphicsTextItem *_variable;
    QPolygonF arrowHead;

signals:

public slots:

};

#endif // VARIABLE_H
