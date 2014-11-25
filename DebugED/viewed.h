#ifndef VIEWED_H
#define VIEWED_H

#include "sceneed.h"
#include "variable.h"
#include <QGraphicsView>

class ViewED : public QGraphicsView{
    Q_OBJECT
public:
    ViewED(SceneED *scene);

protected:
    void keyPressEvent(QKeyEvent *event);
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event);
#endif
    void mousePressEvent(QMouseEvent *event);

signals:
    void selectedVar(Variable *var);

private:
    void scaleView(qreal scaleFactor);
    SceneED *_scene;
    int _zoom;

private slots:
    void zoomIn();
    void zoomOut();
    void zoom();

};

#endif // VIEWED_H
