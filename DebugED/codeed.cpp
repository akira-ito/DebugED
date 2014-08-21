#include "codeed.h"
#include "editor.h"
#include <QtWidgets>

CodeED::CodeED(QWidget *parent) :
    QMainWindow(parent){
    createActions();
    createMenus();
    createToolBars();
    createDockWidgets();
    createStatusBar();
}

void CodeED::createActions(){
    _actionPlay = new QAction(QIcon(":/images/new.png"), tr("Executar"), this);
    _actionPlay->setToolTip(tr("Executar o codigo."));
    _actionPlay->setStatusTip(tr("Executar o codigo."));
    _actionPlay->setShortcuts(QKeySequence::New);

    _actionNext = new QAction(QIcon(":/images/new.png"), tr("Próximo passo"), this);
    _actionNext->setToolTip(tr("Próximo passo"));
    _actionNext->setStatusTip(tr("Próximo passo do código"));
    _actionNext->setShortcuts(QKeySequence::New);

    _actionPrevious = new QAction(QIcon(":/images/new.png"), tr("Passo anterior"), this);
    _actionPrevious->setToolTip(tr("Próximo passo"));
    _actionPrevious->setStatusTip(tr("Próximo passo do código"));
    _actionPrevious->setShortcuts(QKeySequence::New);

    _actionStop = new QAction(QIcon(":/images/new.png"), tr("Parar"), this);
    _actionStop->setToolTip(tr("Parar execução"));
    _actionStop->setStatusTip(tr("Parar a execução do código"));
    _actionStop->setShortcuts(QKeySequence::New);




    connect(_actionPlay, SIGNAL(triggered()), this, SLOT(novos()));

}

void CodeED::createMenus(){



    arquivo = menuBar()->addMenu(tr("&Arquivo"));
    arquivo->addAction(_actionPlay);

    menuBar()->addSeparator();

    visualizar = menuBar()->addMenu(tr("visualizar"));

    arquivo->addMenu(visualizar);
}

void CodeED::createToolBars(){
    _toolBarCode = addToolBar(tr("DebugED - Barra de ferramenta"));
    _toolBarCode->setAllowedAreas(Qt::ToolBarArea::LeftToolBarArea | Qt::ToolBarArea::TopToolBarArea);
    _toolBarCode->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    _toolBarCode->setFloatable(false);
    _toolBarCode->setParent(this);

    _toolBarCode->addAction(_actionPlay);
    _toolBarCode->addAction(_actionNext);
    _toolBarCode->addAction(_actionPrevious);
    _toolBarCode->addAction(_actionStop);

    /*visualizar->addAction(arquivoTool->toggleViewAction());*/
}

void CodeED::createDockWidgets(){
    QDockWidget *a = new QDockWidget(tr("Estrutura"), this);
    a->setFeatures(QDockWidget::DockWidgetMovable);
    QListWidget *customerList = new QListWidget(a);
    customerList->addItems(QStringList()
            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
            << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
            << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
            << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
            << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
            << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    a->setWidget(customerList);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, a);
    //a->setAllowedAreas(Qt::DockWidgetArea::LeftDockWidgetArea | Qt::DockWidgetArea::RightDockWidgetArea);
    a->setFloating(false);

    visualizar->addAction(a->toggleViewAction());

    QDockWidget *b = new QDockWidget(tr("Implementação"), this);

    Editor *editor = new Editor(b);
    b->setFeatures(QDockWidget::DockWidgetMovable);
    b->setWidget(editor);
    b->setFloating(false);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, b);
    //b->setAllowedAreas(Qt::DockWidgetArea::LeftDockWidgetArea | Qt::DockWidgetArea::RightDockWidgetArea);
    //splitDockWidget(a, b, Qt::Orientation::Vertical);
    visualizar->addAction(b->toggleViewAction());

}

void CodeED::createStatusBar(){
    statusBar()->addWidget(new QPushButton("Bem vindo"), 0);
}

/////SLOTS
void CodeED::novos(){

}



