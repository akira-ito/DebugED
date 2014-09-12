#include "structed.h"
#include "sceneed.h"
#include "struct.h"
#include "arrow.h"
#include "viewed.h"

#include "math.h"
#include <QtWidgets>

class Struct;

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
        if (item->type() == Struct::Type && qgraphicsitem_cast<Struct *>(item)->var() == var){
            return qgraphicsitem_cast<Struct *>(item);
        }
    }
    return NULL;
}

Arrow *StructED::searchArrow(QString varA, QString varB){
    foreach (QGraphicsItem *item, _scene->items()){
        if (item->type() == Arrow::Type && qgraphicsitem_cast<Arrow *>(item)->var() == varA+":"+varB){
            return qgraphicsitem_cast<Arrow *>(item);
        }
    }
    return NULL;
}

void StructED::createStruct(Struct::StructType type, QString var){
    Struct *a = new Struct(type, var);
    _scene->addItem(a);

    qreal pos = _scene->itemsBoundingRect().width();
    a->setPos(pos+30, 0);
}

void StructED::createArrow(QString varA, QString varB){
    Struct *structA = searchStruct(varA);
    Struct *structB = searchStruct(varB);
    Arrow *c = new Arrow(structA,structB);
    c->setZValue(-1000.0);
    _scene->addItem(c);
}

void StructED::removeStruct(Struct::StructType type, QString var){
    Struct *structed = searchStruct(var);
    _scene->removeItem(structed);
}

void StructED::removeArrow(QString varA, QString varB){
    Arrow *arrow = searchArrow(varA, varB);
    arrow->remove();
    _scene->removeItem(arrow);
}
