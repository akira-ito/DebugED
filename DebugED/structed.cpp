#include "structed.h"
#include "sceneed.h"
#include "struct.h"
#include "arrow.h"
#include "viewed.h"

#include "math.h"
#include <QtWidgets>

StructED::StructED(QWidget *parent) : QMainWindow(parent){
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

void StructED::createToolBar(){
    _toolBarView = addToolBar("Kkk");
    _toolBarView->setAllowedAreas(Qt::ToolBarArea::TopToolBarArea | Qt::ToolBarArea::BottomToolBarArea);
    _toolBarView->setFloatable(false);
}
