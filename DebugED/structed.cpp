#include "structed.h"
#include "sceneed.h"
#include "struct.h"
#include "arrow.h"
#include "viewed.h"
#include "variable.h"

#include "math.h"
#include <QtWidgets>

class Struct;
class Variable;

StructED::StructED(QWidget *parent) : QMainWindow(parent){
    createActions();
    createToolBar();

    _scene = new SceneED;
    _view = new ViewED(_scene);

    setCentralWidget(_view);
}

void StructED::createActions(){
    _actionZoomIn = new QAction(QIcon(":/images/zoomIn.ico"), tr("Zoom In"), this);
    _actionZoomIn->setToolTip(tr("Zoom mais."));
    _actionZoomIn->setStatusTip(tr("Iniciar execução do codigo."));
    _actionZoomIn->setShortcuts(QKeySequence::New);

    _actionZoom = new QAction(QIcon(":/images/zoom.ico"), tr("Zoom In"), this);
    _actionZoom->setToolTip(tr("Zoom padrão."));
    _actionZoom->setStatusTip(tr("Iniciar execução do codigo."));
    _actionZoom->setShortcuts(QKeySequence::New);

    _actionZoomOut = new QAction(QIcon(":/images/zoomOut.ico"), tr("Zoom In"), this);
    _actionZoomOut->setToolTip(tr("Zoom menos."));
    _actionZoomOut->setStatusTip(tr("Iniciar execução do codigo."));
    _actionZoomOut->setShortcuts(QKeySequence::New);
}

void StructED::createToolBar(){
    _toolBarView = addToolBar("Kkk");
    _toolBarView->setAllowedAreas(Qt::ToolBarArea::TopToolBarArea | Qt::ToolBarArea::BottomToolBarArea);
    _toolBarView->setFloatable(false);
    _toolBarView->setOrientation(Qt::Horizontal);
    _toolBarView->setLayoutDirection(Qt::LayoutDirectionAuto);

    _toolBarView->addAction(_actionZoomIn);
    _toolBarView->addAction(_actionZoom);
    _toolBarView->addAction(_actionZoomOut);
}

Struct *StructED::searchStruct(QString var){
    foreach (QGraphicsItem *item, _scene->items()){
        if (item->type() == Struct::Type && qgraphicsitem_cast<Struct *>(item)->variable()->variable() == var){
            return qgraphicsitem_cast<Struct *>(item);
        }
    }
    return NULL;
}

Arrow *StructED::searchArrow(Struct *structA, Struct *structB){
    foreach (QGraphicsItem *item, _scene->items()){
        if (item->type() == Arrow::Type && qgraphicsitem_cast<Arrow *>(item)->name() == structA->addres()+":"+structB->addres()){
            return qgraphicsitem_cast<Arrow *>(item);
        }
    }
    return NULL;
}

Variable *StructED::searchVariable(QString varA){
    foreach (QGraphicsItem *item, _scene->items()){
        if (item->type() == Variable::Type && qgraphicsitem_cast<Variable *>(item)->variable() == varA){
            return qgraphicsitem_cast<Variable *>(item);
        }
    }
    return NULL;
}

void StructED::createStruct(Struct::StructType type, QString var){
    Struct *structItem = new Struct(type);
    _scene->addItem(structItem);

    qreal pos = _scene->itemsBoundingRect().width();
    structItem->setPos(pos+30, 0);

    Variable *variable = new Variable(structItem, var);
    _scene->addItem(variable);

    structItem->setVariable(variable);
    variable->updatePosition();
}

void StructED::createArrow(QString varA, QString varB){
    Struct *structA = searchStruct(varA);
    Struct *structB = searchStruct(varB);

    Arrow *c = new Arrow(structA,structB);
    c->setZValue(-1000.0);
    _scene->addItem(c);
    c->updatePosition();
}

void StructED::createReceivePoint(QString varA, QString varB){
    Variable *variableA = searchVariable(varA);
    Variable *variableB = searchVariable(varB);

    variableA->pointStruct(variableB->structItem());
    variableA->updatePosition();
}

void StructED::removeStruct(Struct::StructType type, QString var){
    Struct *structed = searchStruct(var);
    _scene->removeItem(structed->variable());
    _scene->removeItem(structed);
}

void StructED::removeArrow(QString varA, QString varB){
    Variable *variableA = searchVariable(varA);
    Variable *variableB = searchVariable(varB);

    Arrow *arrow = searchArrow(variableA->structItem(), variableB->structItem());
    qDebug() << arrow;
    arrow->remove();
    _scene->removeItem(arrow);
}

void StructED::removeReceivePoint(QString varA, QString varB){
    Variable *variableA = searchVariable(varA);
    Variable *variableB = searchVariable(varB);

    variableA->removeStruct(variableB->structItem());

}
