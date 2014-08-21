#ifndef DEBUGED_H
#define DEBUGED_H

#include <QMainWindow>

class DebugED : public QMainWindow{
    Q_OBJECT

public:
    DebugED(QWidget *parent = 0);
    ~DebugED();


private:
   void criarMenu();
   void criarToolBar();
   void criarJanelas();

   QMenu *arquivo;
   QMenu *visualizar;

   QAction *novo;
   QAction *sobre;

   QToolBar *arquivoTool;

private slots:
   void novos();

};

#endif // DEBUGED_H
