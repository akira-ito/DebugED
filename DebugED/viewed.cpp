#include "viewed.h"

#include <QKeyEvent>

ViewED::ViewED(SceneED *scene) : QGraphicsView(scene){
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

void ViewED::zoomIn(){
    scaleView(qreal(1.2));
}

void ViewED::zoomOut(){
    scaleView(1 / qreal(1.2));
}

void ViewED::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
