#ifndef STRUCTED_H
#define STRUCTED_H

#include "sceneed.h"
#include "viewed.h"

#include <QMainWindow>

class QGraphicsView;

class StructED : public QMainWindow{

public:
    StructED(QWidget *parent = 0);

private:
    ViewED *_view;
    SceneED *_scene;
    QToolBar *_toolBarView;

    void createToolBar();

};

#endif // STRUCTED_H
