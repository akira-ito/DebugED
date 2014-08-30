#include "structed.h"
#include "sceneed.h"
#include "struct.h"
#include "arrow.h"
#include "viewed.h"

#include "math.h"
#include <QtWidgets>

StructED::StructED(QWidget *parent) : QMainWindow(parent){
    createActions();
    createToolBar();

    _scene = new SceneED;
    _view = new ViewED(_scene);

    Struct *a = new Struct(Struct::Cell);
    Struct *b = new Struct(Struct::Cell);
    a->setPos(-250, 0);
    _scene->addItem(a);
    _scene->addItem(b);

    Arrow *c = new Arrow(a,b);
    c->setZValue(-1000.0);
    _scene->addItem(c);
    //c->updatePosition();

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
