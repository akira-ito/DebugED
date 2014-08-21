#ifndef CODEED_H
#define CODEED_H

#include <QMainWindow>

class CodeED : public QMainWindow{
    Q_OBJECT
public:
    explicit CodeED(QWidget *parent = 0);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createDockWidgets();
    void createStatusBar();

    QMenu *arquivo;
    QMenu *visualizar;

    QAction *_actionPlay;
    QAction *_actionNext;
    QAction *_actionPrevious;
    QAction *_actionStop;

    QToolBar *_toolBarCode;

private slots:
   void novos();
};

#endif // CODEED_H
