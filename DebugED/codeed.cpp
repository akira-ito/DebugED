#include "codeed.h"
#include "editor.h"
#include "struct.h"
#include "structed.h"

#include <QtWidgets>
#include <QDebug>
#include <QActionGroup>

class Struct;
class StructED;
class QActionGroup;


CodeED::CodeED(StructED *structED, QWidget *parent) : QMainWindow(parent){
    _structED = structED;

    createActions();
    createToolBars();
    createMenus();
    createDockWidgets();
    createStatusBar();

    connect(_structED, SIGNAL(error()), this, SLOT(stop()));
    //connect(this, SIGNAL(passAction(CodeED::Pass)), _structED, SLOT(passAction(CodeED::Pass)));
}

void CodeED::createActions(){
    /// **********Action CODE******* ///
    _actionPlay = new QAction(QIcon(":/images/play.ico"), tr("Iniciar"), this);
    _actionPlay->setToolTip(tr("Iniciar a execução."));
    _actionPlay->setStatusTip(tr("Iniciar execução do codigo."));
    _actionPlay->setShortcut(QKeySequence("F5"));

    _actionNext = new QAction(QIcon(":/images/next.ico"), tr("Próximo"), this);
    _actionNext->setToolTip(tr("Próximo passo"));
    _actionNext->setStatusTip(tr("Próximo passo do código"));
    _actionNext->setShortcut(QKeySequence("F6"));

    _actionPrevious = new QAction(QIcon(":/images/previous.ico"), tr("Anterior"), this);
    _actionPrevious->setToolTip(tr("Próximo passo"));
    _actionPrevious->setStatusTip(tr("Próximo passo do código"));
    _actionPrevious->setShortcut(QKeySequence("F7"));

    _actionStop = new QAction(QIcon(":/images/stop.ico"), tr("Parar"), this);
    _actionStop->setToolTip(tr("Parar execução"));
    _actionStop->setStatusTip(tr("Parar a execução do código"));
    _actionStop->setShortcut(QKeySequence("F8"));

    _actionReplay = new QAction(QIcon(":/images/replay.ico"), tr("Reiniciar"), this);
    _actionReplay->setToolTip(tr("Reiniciar execução"));
    _actionReplay->setStatusTip(tr("Reiniciar a execução do código"));
    _actionReplay->setShortcut(QKeySequence("F9"));

    _actionNext->setEnabled(false);
    _actionPrevious->setEnabled(false);
    _actionStop->setEnabled(false);
    _actionReplay->setEnabled(false);

    connect(_actionPlay, SIGNAL(triggered()), this, SLOT(play()));
    connect(_actionNext, SIGNAL(triggered()), this, SLOT(next()));
    connect(_actionPrevious, SIGNAL(triggered()), this, SLOT(previous()));
    connect(_actionStop, SIGNAL(triggered()), this, SLOT(stop()));
    connect(_actionReplay, SIGNAL(triggered()), this, SLOT(replay()));

    ////***************Examples CODE*******************////
    _actionSample = new QActionGroup(this);
    QAction *action = new QAction(QIcon(":/images/example.ico"), tr("Fila encadeada"), this);
    action->setToolTip(tr("Exemplo de criação fila encadeada"));
    action->setStatusTip(tr("Exemplo de criação fila encadeada"));
    action->setData(CodeED::List);
    _actionSample->addAction(action);

    action = new QAction(QIcon(":/images/example.ico"), tr("Remover fila encadeada"), this);
    action->setToolTip(tr("Exemplo de remoção da célula fila encadeada"));
    action->setStatusTip(tr("Exemplo de remoção da célula fila encadeada"));
    action->setData(CodeED::UnList);
    _actionSample->addAction(action);

    action = new QAction(QIcon(":/images/example.ico"), tr("Pilha encadeada"), this);
    action->setToolTip(tr("Exemplo de criação pilha encadeada"));
    action->setStatusTip(tr("Exemplo de criação pilha encadeada"));
    action->setData(CodeED::Stack);
    _actionSample->addAction(action);

    action = new QAction(QIcon(":/images/example.ico"), tr("Remover pilha encadeada"), this);
    action->setToolTip(tr("Exemplo de remoção da célula pilha encadeada"));
    action->setStatusTip(tr("Exemplo de remoção da célula pilha encadeada"));
    action->setData(CodeED::UnStack);
    _actionSample->addAction(action);

    connect(_actionSample, SIGNAL(triggered(QAction*)), this, SLOT(triggerSample(QAction*)));

    ////***************Menu ARQUIVO*******************////
    _actionNew = new QAction(QIcon(":/images/new.ico"), tr("Novo"), this);
    _actionNew->setToolTip(tr("Novo código "));
    _actionNew->setStatusTip(tr("Novo código"));
    _actionNew->setShortcut(QKeySequence("Ctrl+N"));

    _actionOpen = new QAction(QIcon(":/images/open.ico"), tr("Abrir"), this);
    _actionOpen->setToolTip(tr("Abrir código "));
    _actionOpen->setStatusTip(tr("Abrir código"));
    _actionOpen->setShortcut(QKeySequence("Ctrl+O"));

    _actionSave = new QAction(QIcon(":/images/save.ico"), tr("Salvar"), this);
    _actionSave->setToolTip(tr("Salvar código "));
    _actionSave->setStatusTip(tr("Salvar código"));
    _actionSave->setShortcut(QKeySequence("Ctrl+S"));

    _actionSaveAs = new QAction(QIcon(":/images/saveAs.ico"), tr("Salvar como..."), this);
    _actionSaveAs->setToolTip(tr("Salvar código como..."));
    _actionSaveAs->setStatusTip(tr("Salvar código como..."));
    _actionSaveAs->setShortcut(QKeySequence("Ctrl+Shift+S"));

    _actionExit = new QAction(QIcon(":/images/exit.ico"), tr("Sair"), this);
    _actionExit->setToolTip(tr("Sair"));
    _actionExit->setStatusTip(tr("Sair"));
    _actionExit->setShortcut(QKeySequence("Alt+F4"));

    ////***************Menu Sobre*******************////
    _actionAbout = new QAction(tr("Sobre"), this);
    _actionAbout->setToolTip(tr("Sobre a ferramenta"));
    _actionAbout->setStatusTip(tr("Sobre a ferramenta"));
    connect(_actionAbout, SIGNAL(triggered()), this, SLOT(about()));
}

void CodeED::createMenus(){
    _menuFile = menuBar()->addMenu( tr("&Arquivo") );
    _menuFile->addAction(_actionNew);
    _menuFile->addAction(_actionOpen);
    _menuFile->addAction(_actionSave);
    _menuFile->addAction(_actionSaveAs);
    _menuFile->addSeparator();
    _menuFile->addAction(_actionExit);

    _menuEdit = menuBar()->addMenu(tr("&Editar"));

    _menuDebug = menuBar()->addMenu(tr("&Ações"));;
    _menuDebug->addAction(_actionPlay);
    _menuDebug->addAction(_actionNext);
    _menuDebug->addAction(_actionPrevious);
    _menuDebug->addAction(_actionStop);
    _menuDebug->addAction(_actionReplay);

    _menuView = menuBar()->addMenu(tr("&Visualizar"));
    _menuView->addAction(_structED->toolBarView()->toggleViewAction());
    _menuView->addAction(_toolBarCode->toggleViewAction());
    _menuView->addSeparator();
    _menuView->addAction(_structED->actionZoom());
    _menuView->addAction(_structED->actionZoomIn());
    _menuView->addAction(_structED->actionZoomOut());
    _menuView->addAction(_structED->actionFull());

    _menuSample = menuBar()->addMenu(tr("Exemplos"));
    _menuSample->addActions(_actionSample->actions());

    menuBar()->addAction(_actionAbout);
}

void CodeED::createToolBars(){
    _toolBarCode = addToolBar(tr("Barra de ferramenta ações do código"));
    _toolBarCode->setObjectName("toolBarCode");
    _toolBarCode->setAllowedAreas(Qt::ToolBarArea::LeftToolBarArea | Qt::ToolBarArea::TopToolBarArea);
    _toolBarCode->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    _toolBarCode->setFloatable(false);
    _toolBarCode->setParent(this);

    _toolBarCode->addAction(_actionPlay);
    _toolBarCode->addAction(_actionNext);
    _toolBarCode->addAction(_actionPrevious);
    _toolBarCode->addAction(_actionStop);
    _toolBarCode->addAction(_actionReplay);
}

void CodeED::createDockWidgets(){
    /*QDockWidget *dockStruct = new QDockWidget(tr("Estrutura"), this);
    Editor *editorStruct = new Editor(NULL, dockStruct);
    dockStruct->setFeatures(QDockWidget::DockWidgetMovable);
    dockStruct->setWidget(editorStruct);
    dockStruct->setFloating(false);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dockStruct);
    dockStruct->setMaximumHeight(120);

    editorStruct->setPlainText("struct cel{\n\tint valor;\n\tstruct cel *next;\n}\ntypedef struct cel no;");*/

    QDockWidget *dockImplement = new QDockWidget(tr("Implementação"), this);
    Editor *editorImplement = new Editor(this, dockImplement);
    dockImplement->setFeatures(QDockWidget::DockWidgetMovable);
    dockImplement->setWidget(editorImplement);
    dockImplement->setFloating(false);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dockImplement);
    connect(editorImplement, SIGNAL(blockNext()), this, SLOT(blockNext()));
    connect(editorImplement, SIGNAL(blockPrevious()), this, SLOT(blockPrevious()));

    connect(editorImplement, SIGNAL(clearStructed()), _structED, SLOT(clearStructed()));
    connect(editorImplement, SIGNAL(createStruct(Struct::StructType,QString)), _structED, SLOT(createStruct(Struct::StructType,QString)));
    connect(editorImplement, SIGNAL(createVarPointStruct(Struct::StructType,QString,QString)), _structED, SLOT(createVarPointStruct(Struct::StructType,QString,QString)));
    connect(editorImplement, SIGNAL(createArrow(QString,QString)), _structED, SLOT(createArrow(QString,QString)));
    connect(editorImplement, SIGNAL(createReceivePoint(QString,QString)), _structED, SLOT(createReceivePoint(QString,QString)));
    connect(editorImplement, SIGNAL(createReceivePointNext(QString,QString)), _structED, SLOT(createReceivePointNext(QString,QString)));
    connect(editorImplement, SIGNAL(createFree(QString)), _structED, SLOT(createFree(QString)));
    connect(editorImplement, SIGNAL(createNextNoCreate(Struct::StructType,QString)), _structED, SLOT(createNextNoCreate(Struct::StructType,QString)));
    connect(editorImplement, SIGNAL(createReceiveNextPointNext(QString,QString)), _structED, SLOT(createReceiveNextPointNext(QString,QString)));
    connect(editorImplement, SIGNAL(removeStruct(Struct::StructType,QString)), _structED, SLOT(removeStruct(Struct::StructType,QString)));
    connect(editorImplement, SIGNAL(removeVarPointStruct(Struct::StructType,QString,QString)), _structED, SLOT(removeVarPointStruct(Struct::StructType,QString,QString)));
    connect(editorImplement, SIGNAL(removeArrow(QString,QString)), _structED, SLOT(removeArrow(QString,QString)));
    connect(editorImplement, SIGNAL(removeReceivePoint(QString,QString)), _structED, SLOT(removeReceivePoint(QString,QString)));
    connect(editorImplement, SIGNAL(removeReceivePointNext(QString,QString)), _structED, SLOT(removeReceivePointNext(QString,QString)));
    connect(editorImplement, SIGNAL(removeFree(QString)), _structED, SLOT(removeFree(QString)));
    connect(editorImplement, SIGNAL(removeNextNoCreate(Struct::StructType,QString)), _structED, SLOT(removeNextNoCreate(Struct::StructType,QString)));
    connect(editorImplement, SIGNAL(removeReceiveNextPointNext(QString,QString)), _structED, SLOT(removeReceiveNextPointNext(QString,QString)));

    _menuEdit->addActions(editorImplement->createStandardContextMenu()->actions());

    connect(_actionNew, SIGNAL(triggered()), editorImplement, SLOT(fileNew()));
    connect(_actionOpen, SIGNAL(triggered()), editorImplement, SLOT(fileOpen()));
    connect(_actionSave, SIGNAL(triggered()), editorImplement, SLOT(fileSave()));
    connect(_actionSaveAs, SIGNAL(triggered()), editorImplement, SLOT(fileSaveAs()));
    connect(_actionExit, SIGNAL(triggered()), editorImplement, SLOT(exit()));
}

void CodeED::createStatusBar(){
    statusBar()->showMessage(tr("Bem vindo a ferramenta!"));
}

void CodeED::play(){
    _actionPlay->setEnabled(false);
    _actionNext->setEnabled(true);
    _actionPrevious->setEnabled(false);
    _actionStop->setEnabled(true);
    _actionReplay->setEnabled(true);
    _structED->clear();

    emit passAction(Pass::Play);
}

void CodeED::next(){
    _actionPrevious->setEnabled(true);

    emit passAction(Pass::Next);
}

void CodeED::previous(){
    _actionNext->setEnabled(true);

    emit passAction(Pass::Previous);
}

void CodeED::stop(){
    _actionPlay->setEnabled(true);
    _actionNext->setEnabled(false);
    _actionPrevious->setEnabled(false);
    _actionStop->setEnabled(false);
    _actionReplay->setEnabled(false);

    emit passAction(Pass::Stop);
}

void CodeED::replay(){
    play();
}

void CodeED::blockNext(){
    _actionNext->setEnabled(false);
}

void CodeED::blockPrevious(){
    _actionPrevious->setEnabled(false);
}

void CodeED::triggerSample(QAction *action){
    emit selectSample(static_cast<Sample>(action->data().toInt()));
}

void CodeED::about(){

}
