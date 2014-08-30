#ifndef CODEED_H
#define CODEED_H

#include <QMainWindow>

class CodeED : public QMainWindow{
    Q_OBJECT

public:
    explicit CodeED(QWidget *parent = 0);
    enum Pass{Play, Next, Previous, Stop, Replay};

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

    QAction *_actionPlay;
    QAction *_actionNext;
    QAction *_actionPrevious;
    QAction *_actionStop;
    QAction *_actionReplay;

    QToolBar *_toolBarCode;

signals:
    void passAction(CodeED::Pass pass);

private slots:
    void play();
    void next();
    void previous();
    void stop();
    void replay();
    void blockNext();
    void blockPrevious();
};

#endif // CODEED_H
