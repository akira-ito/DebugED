#ifndef CODEED_H
#define CODEED_H

#include "structed.h"
#include <QMainWindow>
#include <QActionGroup>

class StructED;
class QActionGroup;

class CodeED : public QMainWindow{
    Q_OBJECT

public:
    CodeED(StructED *structED, QWidget *parent = 0);
    enum Pass{Play, Next, Previous, Stop, Replay};
    enum Sample{Point, Remove};

    StructED *structED() const { return _structED; }

signals:
    void passAction(CodeED::Pass pass);
    void selectSample(CodeED::Sample sample);

private slots:
    void play();
    void next();
    void previous();
    void stop();
    void replay();
    void blockNext();
    void blockPrevious();
    void triggerSample(QAction *action);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createDockWidgets();
    void createStatusBar();

    QMenu *_menuFile;
    QMenu *_menuEdit;
    QMenu *_menuDebug;
    QMenu *_menuView;
    QMenu *_menuSample;

    QAction *_actionPlay;
    QAction *_actionNext;
    QAction *_actionPrevious;
    QAction *_actionStop;
    QAction *_actionReplay;
    QActionGroup *_actionSample;

    QToolBar *_toolBarCode;

    StructED *_structED;
};

#endif // CODEED_H
