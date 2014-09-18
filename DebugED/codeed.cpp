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
    createMenus();
    createToolBars();
    createDockWidgets();
    createStatusBar();
}

void CodeED::createActions(){
    _actionPlay = new QAction(QIcon(":/images/play.ico"), tr("Iniciar"), this);
    _actionPlay->setToolTip(tr("Iniciar a execução."));
    _actionPlay->setStatusTip(tr("Iniciar execução do codigo."));
    _actionPlay->setShortcuts(QKeySequence::New);

    _actionNext = new QAction(QIcon(":/images/next.ico"), tr("Próximo"), this);
    _actionNext->setToolTip(tr("Próximo passo"));
    _actionNext->setStatusTip(tr("Próximo passo do código"));
    _actionNext->setShortcuts(QKeySequence::New);

    _actionPrevious = new QAction(QIcon(":/images/previous.ico"), tr("Anterior"), this);
    _actionPrevious->setToolTip(tr("Próximo passo"));
    _actionPrevious->setStatusTip(tr("Próximo passo do código"));
    _actionPrevious->setShortcuts(QKeySequence::New);

    _actionStop = new QAction(QIcon(":/images/stop.ico"), tr("Parar"), this);
    _actionStop->setToolTip(tr("Parar execução"));
    _actionStop->setStatusTip(tr("Parar a execução do código"));
    _actionStop->setShortcuts(QKeySequence::New);

    _actionReplay = new QAction(QIcon(":/images/replay.ico"), tr("Reiniciar"), this);
    _actionReplay->setToolTip(tr("Reiniciar execução"));
    _actionReplay->setStatusTip(tr("Reiniciar a execução do código"));
    _actionReplay->setShortcuts(QKeySequence::New);

    _actionNext->setEnabled(false);
    _actionPrevious->setEnabled(false);
    _actionStop->setEnabled(false);
    _actionReplay->setEnabled(false);

    connect(_actionPlay, SIGNAL(triggered()), this, SLOT(play()));
    connect(_actionNext, SIGNAL(triggered()), this, SLOT(next()));
    connect(_actionPrevious, SIGNAL(triggered()), this, SLOT(previous()));
    connect(_actionStop, SIGNAL(triggered()), this, SLOT(stop()));
    connect(_actionReplay, SIGNAL(triggered()), this, SLOT(replay()));

    QAction *action = new QAction(QIcon(":/images/replay.ico"), tr("Apontar Nó"), this);
    action->setToolTip(tr("Apontar"));
    action->setStatusTip(tr("Apontar nó"));
    action->setShortcuts(QKeySequence::New);
    action->setData(CodeED::Point);
    _actionSample = new QActionGroup(this);
    _actionSample->addAction(action);

    action = new QAction(QIcon(":/images/replay.ico"), tr("Remover Nó"), this);
    action->setToolTip(tr("Remover"));
    action->setStatusTip(tr("Remover nó"));
    action->setShortcuts(QKeySequence::New);
    action->setData(CodeED::Remove);
    _actionSample->addAction(action);

    connect(_actionSample, SIGNAL(triggered(QAction*)), this, SLOT(triggerSample(QAction*)));

}

void CodeED::createMenus(){
    _menuFile = menuBar()->addMenu(tr("&Arquivo"));

    _menuEdit = menuBar()->addMenu(tr("&Editar"));
    _menuEdit->addSeparator();

    _menuDebug = menuBar()->addMenu(tr("&Depurar"));
    _menuDebug->addAction(_actionPlay);
    _menuDebug->addAction(_actionNext);
    _menuDebug->addAction(_actionPrevious);
    _menuDebug->addAction(_actionStop);
    _menuDebug->addAction(_actionReplay);

    _menuView = menuBar()->addMenu(tr("&Visualizar"));

    _menuSample = menuBar()->addMenu(tr("Soluções Simples"));
    _menuSample->addActions(_actionSample->actions());

}

void CodeED::createToolBars(){
    _toolBarCode = addToolBar(tr("DebugED - Barra de ferramenta"));
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

    /*visualizar->addAction(arquivoTool->toggleViewAction());*/
}

void CodeED::createDockWidgets(){
    QDockWidget *dockStruct = new QDockWidget(tr("Estrutura"), this);
    Editor *editorStruct = new Editor(NULL, dockStruct);
    dockStruct->setFeatures(QDockWidget::DockWidgetMovable);
    dockStruct->setWidget(editorStruct);
    dockStruct->setFloating(false);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dockStruct);
    dockStruct->setMaximumHeight(120);

    editorStruct->setPlainText("struct cel{\n\tint valor;\n\tstruct cel *next;\n}\ntypedef struct cel no;");

    QDockWidget *dockImplement = new QDockWidget(tr("Implementação"), this);
    Editor *editorImplement = new Editor(this, dockImplement);
    dockImplement->setFeatures(QDockWidget::DockWidgetMovable);
    dockImplement->setWidget(editorImplement);
    dockImplement->setFloating(false);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dockImplement);
    connect(editorImplement, SIGNAL(blockNext()), this, SLOT(blockNext()));
    connect(editorImplement, SIGNAL(blockPrevious()), this, SLOT(blockPrevious()));

    connect(editorImplement, SIGNAL(createStruct(Struct::StructType,QString)), _structED, SLOT(createStruct(Struct::StructType,QString)));
    connect(editorImplement, SIGNAL(createArrow(QString,QString)), _structED, SLOT(createArrow(QString,QString)));
    connect(editorImplement, SIGNAL(createReceivePoint(QString,QString)), _structED, SLOT(createReceivePoint(QString,QString)));
    connect(editorImplement, SIGNAL(removeStruct(Struct::StructType,QString)), _structED, SLOT(removeStruct(Struct::StructType,QString)));
    connect(editorImplement, SIGNAL(removeArrow(QString,QString)), _structED, SLOT(removeArrow(QString,QString)));
    connect(editorImplement, SIGNAL(removeReceivePoint(QString,QString)), _structED, SLOT(removeReceivePoint(QString,QString)));
}

void CodeED::createStatusBar(){
    statusBar()->addWidget(new QLabel(tr("DebugED - Debugador de Estrutura de Dados")));
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


