#include "debuged.h"
#include "codeed.h"
#include "structed.h"

#include <QApplication>
#include <QMainWindow>
#include <QSplitter>
#include <QFile>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(arquivos);
    QSplitter page;

    QFile file(":/estilo/estilo.qss");
    file.open(QFile::ReadOnly);
    qApp->setStyleSheet(file.readAll());

    StructED *view = new StructED();
    CodeED *code = new CodeED(view);

    page.addWidget(code);
    page.addWidget(view);


    page.setWindowTitle(QMainWindow::tr("DebugED - Debugador de Estrutura de Dados"));
    page.setWindowIcon(QIcon(":/images/new.png"));
    page.setMinimumSize(QSize(1000, 500));
    page.show();
    return a.exec();
}
