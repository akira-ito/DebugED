#include "codeed.h"
#include "structed.h"
#include "sceneed.h"
#include "struct.h"
#include "arrow.h"
#include "viewed.h"
#include "variable.h"

#include "math.h"
#include <QtWidgets>
#include <QSizePolicy>
#include <QtAlgorithms>
#include <QSplitter>

class Struct;
class Variable;
class CodeED;

StructED::StructED(QSplitter *page, QWidget *parent) : QMainWindow(parent){
    createActions();
    createToolBar();
    createTableView();

    _scene = new SceneED;
    _view = new ViewED(_scene);
    _column = new QMap<QString, int>();
    _columns = new QMap<QString, QList<QStandardItem*>>();
    _page = page;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(_view);
    layout->addWidget(_tableView);
    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    setCentralWidget(widget);

    connect(this, SIGNAL(zoom()), _view, SLOT(zoom()));
    connect(this, SIGNAL(zoomIn()), _view, SLOT(zoomIn()));
    connect(this, SIGNAL(zoomOut()), _view, SLOT(zoomOut()));
    connect(_view, SIGNAL(selectedVar(Variable*)), this, SLOT(selectedVar(Variable*)));
}

void StructED::selectedVar(Variable *var){
    int column = _column->value(var->address());
    _tableView->selectColumn(column);
}

void StructED::createActions(){
    QActionGroup *group = new QActionGroup(this);
    _actionZoomIn = new QAction(QIcon(":/images/zoomIn.ico"), tr("Zoom In"), this);
    _actionZoomIn->setToolTip(tr("Zoom mais."));
    _actionZoomIn->setStatusTip(tr("Zoom Mais."));
    _actionZoomIn->setShortcut(QKeySequence("+"));
    _actionZoomIn->setData(ZoomIn);
    group->addAction(_actionZoomIn);

    _actionZoom = new QAction(QIcon(":/images/zoom.ico"), tr("Zoom In"), this);
    _actionZoom->setToolTip(tr("Zoom padrão."));
    _actionZoom->setStatusTip(tr("Zoom padrão."));
    _actionZoom->setShortcut(QKeySequence("*"));
    _actionZoom->setData(Zoom);
    group->addAction(_actionZoom);

    _actionZoomOut = new QAction(QIcon(":/images/zoomOut.ico"), tr("Zoom In"), this);
    _actionZoomOut->setToolTip(tr("Zoom menos."));
    _actionZoomOut->setStatusTip(tr("Zoom menos."));
    _actionZoomOut->setShortcut(QKeySequence("-"));
    _actionZoomOut->setData(ZoomOut);
    group->addAction(_actionZoomOut);

    _actionFull = new QAction(QIcon(":/images/fullScreen.ico"), tr("Full screen"), this);
    _actionFull->setToolTip(tr("Full screen."));
    _actionFull->setStatusTip(tr("Full screen."));
    _actionFull->setCheckable(true);

    connect(_actionFull, SIGNAL(triggered()), this, SLOT(fullScreen()));
    connect(group, SIGNAL(triggered(QAction*)), this, SLOT(actionToolBar(QAction*)));
}

void StructED::createToolBar(){
    _toolBarView = addToolBar("Barra de ferramenta visualização do código");
    _toolBarView->setAllowedAreas(Qt::ToolBarArea::TopToolBarArea | Qt::ToolBarArea::BottomToolBarArea);
    _toolBarView->setFloatable(false);
    _toolBarView->setOrientation(Qt::Horizontal);
    _toolBarView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    _toolBarView->addAction(_actionZoomIn);
    _toolBarView->addAction(_actionZoom);
    _toolBarView->addAction(_actionZoomOut);
    _toolBarView->addAction(_actionFull);
}

void StructED::createTableView(){
    _tableView = new QTableView;
    _tableView->setAlternatingRowColors(true);
    _tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _tableView->setSelectionBehavior(QAbstractItemView::SelectColumns);
    _tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    _tableView->setFocusPolicy(Qt::NoFocus);
    _tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    _tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    _tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    _tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _tableView->horizontalHeader()->setHidden(true);
    _tableView->setFixedHeight(115);

    createHeaderTable(new QStandardItemModel());
}

void StructED::createHeaderTable(QStandardItemModel *model){
    QStandardItem *var =new QStandardItem("Variável");
    var->setToolTip(tr("Nome da variavel"));
    QStandardItem *add = new QStandardItem("Endereço");
    add->setToolTip(tr("Endereço de memória"));
    QStandardItem *val = new QStandardItem("Valor");
    val->setToolTip(tr("Valor"));
    /*QStandardItem *pon = new QStandardItem("Ponteiro(*)");
    pon->setToolTip(tr("Valor"));*/
    model->setVerticalHeaderItem(0, var);
    model->setVerticalHeaderItem(1, add);
    model->setVerticalHeaderItem(2, val);
//    model->setVerticalHeaderItem(3, pon);

    _tableView->setModel(model);
}

Struct *StructED::searchStruct(QString var){
    foreach (QGraphicsItem *item, _scene->items()){
        if (item->type() == Struct::Type && qgraphicsitem_cast<Struct *>(item)->matchVariable(var)){
            return qgraphicsitem_cast<Struct *>(item);
        }
    }
    return NULL;
}

Arrow *StructED::searchArrow(Struct *structA, Struct *structB){
    foreach (QGraphicsItem *item, _scene->items()){
        if (item->type() == Arrow::Type && qgraphicsitem_cast<Arrow *>(item)->name() == structA->addres()+":"+structB->addres()){
            return qgraphicsitem_cast<Arrow *>(item);
        }
    }
    return NULL;
}

QList<Arrow *> StructED::searchArrowB(Struct *structB){
    QList<Arrow *> arrows;
    foreach (QGraphicsItem *item, _scene->items()){
        if (item->type() == Arrow::Type && qgraphicsitem_cast<Arrow *>(item)->receivePoint(structB)){
            arrows.push_back(qgraphicsitem_cast<Arrow *>(item));
        }
    }
    return arrows;
}

Variable *StructED::searchVariable(QString varA, bool opacity){
    foreach (QGraphicsItem *item, _scene->items()){
        if (item->type() == Variable::Type && qgraphicsitem_cast<Variable *>(item)->variable() == varA && (item->opacity() || opacity)){
            return qgraphicsitem_cast<Variable *>(item);
        }
    }
    return NULL;
}

void StructED::clearStructed(){
    ((QStandardItemModel *)_tableView->model())->clear();
    _scene->clear();
    createHeaderTable((QStandardItemModel *)_tableView->model());
}

void StructED::createStruct(Struct::StructType type, QString var){
    Struct *structItem = new Struct(type);
    _scene->addItem(structItem);

    qreal pos = _scene->itemsBoundingRect().width();
    structItem->setPos(pos+30, 0);

    Variable *variable = new Variable(structItem, var);
    _scene->addItem(variable);

    structItem->addVariable(variable);
    variable->updatePosition();

    QStandardItemModel *model = (QStandardItemModel *) _tableView->model();
    QList<QStandardItem *> s;
    s << new QStandardItem(var) << new QStandardItem(variable->address()) << new QStandardItem(structItem->addres());
    _column->insert(variable->address(), _tableView->horizontalHeader()->count());
    model->appendColumn(s);
}

void StructED::createVarPointStruct(Struct::StructType, QString var, QString varStruct){
    Struct *structItem = searchStruct(varStruct);
    if (errorNull(structItem)) return;

    Variable *variable = new Variable(structItem, var);
    variable->updatePosition();

    structItem->addVariable(variable);
    _scene->addItem(variable);

    QStandardItemModel *model = (QStandardItemModel *) _tableView->model();
    QList<QStandardItem *> s;
    s << new QStandardItem(var) << new QStandardItem(variable->address()) << new QStandardItem(structItem->addres());
    _column->insert(variable->address(), _tableView->horizontalHeader()->count());
    model->appendColumn(s);
}

void StructED::createArrow(QString varA, QString varB){
    Variable *variableA = searchVariable(varA);
    if (errorNull(variableA)) return;
    Struct *structA = variableA->structItem();
    Struct *structB = searchStruct(varB);
    if (errorNull(structB) || errorNull(structA)) return;

    Arrow *arrow = new Arrow(structA,structB);
    arrow->updatePosition();
    _scene->addItem(arrow);
}

void StructED::createReceivePoint(QString varA, QString varB){
    Variable *variableA = searchVariable(varA);
    Variable *variableB = searchVariable(varB);
    if (errorNull(variableA) || errorNull(variableB)) return;

    variableA->pointStruct(variableB->structItem());
    variableA->updatePosition();
}

void StructED::createReceivePointNext(QString var, QString varStruct){
    Variable *variableA = searchVariable(varStruct);
    Variable *variable = searchVariable(var);
    if (errorNull(variableA) || errorNull(variable)) return;
    Struct *structed = variableA->structItem();
    if (errorNull(structed)) return;

    Arrow *arrow = structed->arrows().last();
    variable->pointStruct(arrow->b());
    variable->updatePosition();
    arrow->b()->addVariable(variable);

    QStandardItemModel *model = (QStandardItemModel *) _tableView->model();
    int column = _column->value(variable->address());
    QStandardItem *s = model->item(2, column);
    s->setText(arrow->b()->addres());
}

void StructED::createFree(QString var){
    Variable *variableA = searchVariable(var);
    if (errorNull(variableA)) return;
    Struct *structA = variableA ->structItem();
    if (errorNull(structA)) return;

    QStandardItemModel *model = (QStandardItemModel *) _tableView->model();
    foreach(Variable *var, structA->variables()){
        var->setOpacity(0);
        _columns->insert(var->address(), model->takeColumn(_column->value(var->address())));
    }
    foreach(Arrow *arrow, structA->arrows()){
        arrow->setOpacity(0);
    }
    foreach(Arrow *arrow, searchArrowB(structA)){
        arrow->setOpacity(0);
    }

    structA->setOpacity(0);
}

void StructED::createNextNoCreate(Struct::StructType type, QString var){
    Variable *variableA = searchVariable(var);
    if (errorNull(variableA)) return;
    Struct *structA = variableA ->structItem();
    if (errorNull(structA)) return;

    Struct *structB = new Struct(type);
    _scene->addItem(structB);
    qreal pos = _scene->itemsBoundingRect().width();
    structB->setPos(pos+30, 0);

    Arrow *arrow = new Arrow(structA,structB);
    arrow->updatePosition();
    _scene->addItem(arrow);
}

void StructED::createReceiveNextPointNext(QString varStructA, QString varStructB){
    Variable *variableA = searchVariable(varStructA);
    Variable *variableB = searchVariable(varStructB);
    if (errorNull(variableA) || errorNull(variableB)) return;
    Struct *structA = variableA ->structItem();
    Struct *structB = variableB ->structItem();
    if (errorNull(structA) || errorNull(structB)) return;

    Arrow *arrow = new Arrow(structA, structB->arrows().last()->b());
    arrow->updatePosition();
    _scene->addItem(arrow);
}

void StructED::removeStruct(Struct::StructType, QString var){
    Struct *structed = searchStruct(var);
    if (errorNull(structed)) return;

    QStandardItemModel *model = (QStandardItemModel *) _tableView->model();
    foreach (Variable *variable, structed->variables()){
        model->removeColumn(_column->value(variable->address()));
        _scene->removeItem(variable);
    }
    _scene->removeItem(structed);
}

void StructED::removeVarPointStruct(Struct::StructType, QString var, QString varStruct){
    Variable *variable = searchVariable(var);
    Struct *structA = searchStruct(varStruct);
    if (errorNull(variable) || errorNull(structA)) return;

    structA->removeVariable(variable);
    _scene->removeItem(variable);

    QStandardItemModel *model = (QStandardItemModel *) _tableView->model();
    model->removeColumn(_column->value(variable->address()));
}

void StructED::removeArrow(QString varA, QString varB){
    Variable *variableA = searchVariable(varA);
    Variable *variableB = searchVariable(varB);
    if (errorNull(variableA) || errorNull(variableB)) return;

    Arrow *arrow = searchArrow(variableA->structItem(), variableB->structItem());
    arrow->remove();
    _scene->removeItem(arrow);
}

void StructED::removeReceivePoint(QString varA, QString varB){
    Variable *variableA = searchVariable(varA);
    Variable *variableB = searchVariable(varB);
    if (errorNull(variableA) || errorNull(variableB)) return;


    variableA->removeStruct(variableB->structItem());
    variableA->updatePosition();
}

void StructED::removeReceivePointNext(QString var, QString varStruct){
    Variable *variable = searchVariable(var);
    Variable *variableB = searchVariable(varStruct);
    if (errorNull(variable) || errorNull(variableB)) return;
    Struct *structA = variableB->structItem();
    if (errorNull(structA)) return;

    variable->removeStruct(structA);
    variable->updatePosition();
    structA->removeVariable(variable);

    QStandardItemModel *model = (QStandardItemModel *) _tableView->model();
    int column = _column->value(variable->address());
    QStandardItem *s = model->item(2, column);
    s->setText(variable->structItem()->addres());
}

void StructED::removeFree(QString var){
    Variable *variable = searchVariable(var, true);
    if (errorNull(variable)) return;
    Struct *structA = variable->structItem();
    if (errorNull(structA)) return;

    QStandardItemModel *model = (QStandardItemModel *) _tableView->model();
    QMap<int, Variable *> lst;
    foreach(Variable *var, structA->variables()){
        lst.insert(_column->value(var->address()), var);
    }

    foreach(Variable *var, lst.values()){
        var->setOpacity(1);
        model->insertColumn(_column->value(var->address()), _columns->value(var->address()));
    }
    foreach(Arrow *arrow, structA->arrows()){
        arrow->setOpacity(1);
    }
    foreach(Arrow *arrow, searchArrowB(structA)){
        arrow->setOpacity(1);
    }

    structA->setOpacity(1);
}

void StructED::removeNextNoCreate(Struct::StructType, QString var){
    Variable *variable = searchVariable(var);
    if (errorNull(variable)) return;
    Struct *structA = variable->structItem();
    if (errorNull(structA)) return;

    Arrow *arrow = structA->arrows().last();
    arrow->remove();
    _scene->removeItem(arrow->b());
    _scene->removeItem(arrow);
}

void StructED::removeReceiveNextPointNext(QString varStructA, QString varStructB){
    Variable *variableA = searchVariable(varStructA);
    Variable *variableB = searchVariable(varStructB);
    if (errorNull(variableA) || errorNull(variableB)) return;
    Struct *structA = variableA->structItem();
    Struct *structB = variableB->structItem();
    if (errorNull(structA) || errorNull(structB)) return;

    Arrow *arrow = structA->arrows().last();
    arrow->remove();
    _scene->removeItem(arrow);
}

void StructED::actionToolBar(QAction *action){
    Action act = static_cast<Action>(action->data().toInt());
    switch(act){
    case Zoom:
        emit zoom();
        break;
    case ZoomIn:
        emit zoomIn();
        break;
    case ZoomOut:
        emit zoomOut();
        break;
    }
}

void StructED::fullScreen(){
    int width = _page->size().width();
    if (_actionFull->isChecked()){
        _page->setSizes(QList<int>() << 0 << width);
    }else{
        _page->setSizes(QList<int>() << width/5*2 << width/5*3);
    }
}
