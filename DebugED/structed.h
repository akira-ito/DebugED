#ifndef STRUCTED_H
#define STRUCTED_H

#include "sceneed.h"
#include "viewed.h"
#include "struct.h"
#include "codeed.h"
#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QGraphicsItem>
#include <QSplitter>

class Struct;
class QGraphicsView;
class CodeED;

class StructED : public QMainWindow{
    Q_OBJECT

public:
    StructED(QSplitter *page, QWidget *parent = 0);
    enum Action{ZoomIn, ZoomOut, Zoom};
    void clear() { _scene->clear(); }
    QToolBar *toolBarView() { return _toolBarView; }
    QAction *actionZoomIn(){ return _actionZoomIn; }
    QAction *actionZoom(){ return _actionZoom; }
    QAction *actionZoomOut(){ return _actionZoomOut; }
    QAction *actionFull(){ return _actionFull; }
    bool errorNull(QGraphicsItem *item){
        if (item == NULL){
            QMessageBox::critical(this, tr("Erro durante a execução."), tr("Verifique se a sintaxe está correta!"));
            emit error();
            return true;
        }
        return false;
    }

signals:
    void zoom();
    void zoomIn();
    void zoomOut();
    void error();

private slots:
    void selectedVar(Variable *var);
    void clearStructed();
    void createStruct(Struct::StructType type, QString var);
    void createVarPointStruct(Struct::StructType, QString var, QString varStruct);
    void createArrow(QString varA, QString varB);
    void createReceivePoint(QString varA, QString varB);
    void createReceivePointNext(QString var, QString varStruct);
    void createFree(QString var);
    void createNextNoCreate(Struct::StructType type, QString var);
    void createReceiveNextPointNext(QString varStructA, QString varStructB);
    void removeStruct(Struct::StructType, QString var);
    void removeVarPointStruct(Struct::StructType, QString var, QString varStruct);
    void removeArrow(QString varA, QString varB);
    void removeReceivePoint(QString varA, QString varB);
    void removeReceivePointNext(QString var, QString varStruct);
    void removeFree(QString var);
    void removeNextNoCreate(Struct::StructType, QString var);
    void removeReceiveNextPointNext(QString varStructA, QString varStructB);
    void actionToolBar(QAction *action);
    void fullScreen();

private:
    ViewED *_view;
    SceneED *_scene;
    QToolBar *_toolBarView;
    QAction *_actionZoomIn;
    QAction *_actionZoom;
    QAction *_actionZoomOut;
    QAction *_actionFull;
    QTableView *_tableView;
    QMap<QString, int> *_column;
    QMap<QString, QList<QStandardItem*>> *_columns;
    QSplitter *_page;

    void createActions();
    void createToolBar();
    void createTableView();
    void createHeaderTable(QStandardItemModel *model);

    Struct *searchStruct(QString var);
    Arrow *searchArrow(Struct *structA, Struct *structB);
    QList<Arrow *> searchArrowB(Struct *structB);
    Variable *searchVariable(QString varA, bool opacity = false);
};

#endif // STRUCTED_H
