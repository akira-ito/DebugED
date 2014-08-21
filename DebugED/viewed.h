#ifndef VIEWED_H
#define VIEWED_H

#include "sceneed.h"
#include <QGraphicsView>

class ViewED : public QGraphicsView{

public:
    ViewED(SceneED *scene);

protected:
    void keyPressEvent(QKeyEvent *event);
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event);
#endif

private:
    void zoomIn();
    void zoomOut();
    void scaleView(qreal scaleFactor);

    SceneED *_scene;
};

#endif // VIEWED_H
