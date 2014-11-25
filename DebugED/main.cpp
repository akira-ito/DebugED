#include "debuged.h"
#include "codeed.h"
#include "structed.h"

#include <QApplication>
#include <QMainWindow>
#include <QSplitter>
#include <QTime>
#include <QFile>
#include <QList>

int main(int argc, char *argv[]){

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    QApplication a(argc, argv);
    Q_INIT_RESOURCE(arquivos);
    QSplitter page;

    QFile file(":/estilo/estilo.qss");
    file.open(QFile::ReadOnly);
    qApp->setStyleSheet(file.readAll());

    StructED *view = new StructED(&page);
    CodeED *code = new CodeED(view);

    page.addWidget(code);
    page.addWidget(view);
    int width = page.size().width();
    page.setSizes(QList<int>() << width/5*2 << width/5*3);
    page.setWindowTitle(QMainWindow::tr("Ferramenta para visualizar Estrutura de Dados"));
    page.setWindowIcon(QIcon(":/images/struct.ico"));
    page.setMinimumSize(QSize(1000, 500));
    page.show();
    return a.exec();
}
