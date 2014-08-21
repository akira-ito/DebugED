#include "debuged.h"


DebugED::DebugED(QWidget *parent)
    : QMainWindow(parent)
{
    QFile file(":/estilo/estilo.qss");
    file.open(QFile::ReadOnly);
    qApp->setStyleSheet(file.readAll());

    setWindowTitle(tr("DebugED - Debugador de Estrutura de Dados"));
    setWindowIcon(QIcon(":/images/new.png"));
    //setMinimumSize(QSize(500,500));
    //setMaximumSize(QSize(800,800));
    //setFixedSize(QSize(300,300));

    QLabel *a = new QLabel();
    setCentralWidget(a);

    criarMenu();
    criarToolBar();
    criarJanelas();


    statusBar()->addWidget(new QPushButton("Bem vindo"), 0);
}

DebugED::~DebugED()
{

}

void DebugED::criarMenu()
{
    novo = new QAction(QIcon(":/images/new.png"), tr("Novo"), this);
    novo->setShortcuts(QKeySequence::New);
    novo->setStatusTip(tr("Começar de novo."));
    novo->setToolTip("HHHHHHHHHH");
    connect(novo, SIGNAL(triggered()), this, SLOT(novo()));

    sobre = new QAction(QIcon(":/images/print.png"), tr("So bre"), this);
    sobre->setStatusTip(tr("kkkkk"));
    sobre->setShortcuts(QList<QKeySequence>()<< QKeySequence::Close << QKeySequence::Find);

    arquivo = menuBar()->addMenu(tr("&Arquivo"));
    arquivo->addAction(novo);
    arquivo->addAction(sobre);

    menuBar()->addSeparator();

    visualizar = menuBar()->addMenu(tr("visualizar"));
    visualizar->addAction(sobre);

    arquivo->addMenu(visualizar);
}

void DebugED::criarToolBar(){
    arquivoTool = addToolBar("hhhh");
    arquivoTool->setAllowedAreas(Qt::ToolBarArea::LeftToolBarArea | Qt::ToolBarArea::TopToolBarArea);
    arquivoTool->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    arquivoTool->setFloatable(false);
    arquivoTool->setMouseTracking(true);
    arquivoTool->setMovable(true);
    arquivoTool->setParent(this);
    arquivoTool->setWindowTitle("Kkjhhhhhhhhhhhhhh");

    arquivoTool->addAction(novo);

    visualizar->addAction(arquivoTool->toggleViewAction());

}

void DebugED::criarJanelas()
{
    QDockWidget *a = new QDockWidget(tr("Codigo"), this);
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
    visualizar->addAction(a->toggleViewAction());


    QDockWidget *b = new QDockWidget(tr("Desenho"), this);
    QListWidget *teste = new QListWidget(b);
    teste->addItems(QStringList()
            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
            << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
            << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
            << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
            << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
            << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    b->setWidget(teste);
    b->setFloating(false);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, b);
    visualizar->addAction(b->toggleViewAction());

    repaint();

}

void DebugED::novos(){

}
