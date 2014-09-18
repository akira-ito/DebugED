#ifndef STRUCTED_H
#define STRUCTED_H

#include "sceneed.h"
#include "viewed.h"
#include "struct.h"

#include <QMainWindow>

class Struct;
class QGraphicsView;

class StructED : public QMainWindow{
    Q_OBJECT

public:
    StructED(QWidget *parent = 0);
    void clear() { _scene->clear(); }

private:
    ViewED *_view;
    SceneED *_scene;
    QToolBar *_toolBarView;
    QAction *_actionZoomIn;
    QAction *_actionZoom;
    QAction *_actionZoomOut;

    void createActions();
    void createToolBar();

    Struct *searchStruct(QString var);
    Arrow *searchArrow(Struct *structA, Struct *structB);
    Variable *searchVariable(QString varA);

private slots:
    void createStruct(Struct::StructType type, QString var);
    void createArrow(QString varA, QString varB);
    void createReceivePoint(QString varA, QString varB);
    void removeStruct(Struct::StructType type, QString var);
    void removeArrow(QString varA, QString varB);
    void removeReceivePoint(QString varA, QString varB);

};

#endif // STRUCTED_H
