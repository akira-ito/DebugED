#include "viewed.h"
#include "variable.h"
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QDebug>

ViewED::ViewED(SceneED *scene) : QGraphicsView(scene), _zoom(0){
    _scene = scene;

    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setInteractive(true);
    setAcceptDrops(true);
}

void ViewED::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Plus:
            zoomIn();
            break;
        case Qt::Key_Minus:
            zoomOut();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}

void ViewED::wheelEvent(QWheelEvent *event){
    scaleView(pow((double)2, event->delta() / 240.0));
}

void ViewED::mousePressEvent(QMouseEvent *event){
    QGraphicsView::mousePressEvent(event);
    foreach(QGraphicsItem *item, _scene->selectedItems()){
        if (item->parentItem() != NULL && item->parentItem()->type() == Variable::Type){
            emit selectedVar(static_cast<Variable *>(item->parentItem()));
        }
    }
}

void ViewED::zoomIn(){
    scaleView(qreal(1.4));
}

void ViewED::zoomOut(){
    scaleView(qreal(0.7));
}

void ViewED::zoom(){
    while (_zoom){
        _zoom < 0 ? zoomOut() : zoomIn();
    }
}

void ViewED::scaleView(qreal scaleFactor){
    scaleFactor = ((int)(scaleFactor*10))/10.0;
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;
    _zoom += scaleFactor > 1 ? -1 : 1;
    scale(scaleFactor, scaleFactor);
}
