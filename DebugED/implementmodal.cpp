#include "implementmodal.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QToolBar>
#include <QPushButton>
#include <QGroupBox>
#include <QDebug>

ImplementModal::ImplementModal(QPair<QString, QStringList> *interpret, Editor::Implementation implementation, QWidget *parent) : QDialog(parent){
    _implementation = implementation;
    _impl = ((Editor *)parent)->mapImplement()->value(interpret->first);
    _texts = QList<QLineEdit *>();
    _button = Cancel;

    QGroupBox *group;
    QHBoxLayout *lytVar;
    QVBoxLayout *res = new QVBoxLayout();
    QLineEdit *txtVar;

    switch(implementation){
    case Editor::CreateNO:
        setWindowTitle(tr("Criar variavel e apontar para nova Célula"));
        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(0):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite o nome da variavel:");
        group->setLayout(lytVar);
        res->addWidget(group);
         break;
    case Editor::CreateNOVar:
        setWindowTitle(tr("Criar variavel e apontar para Célula existente"));
        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(0):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite o nome da variavel:");
        group->setLayout(lytVar);
        res->addWidget(group);

        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(1):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite a variavel da Célula:");
        group->setLayout(lytVar);
        res->addWidget(group);
        break;
    case Editor::PointNOCreate:
        setWindowTitle(tr("Apontar Célula para uma nova Célula"));
        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(0):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite a variavel da Célula de origem:");
        group->setLayout(lytVar);
        res->addWidget(group);
        break;
    case Editor::PointNO:
        setWindowTitle(tr("Apontar Célula para uma Célula existente"));
        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(0):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite a variavel da Célula de origem:");
        group->setLayout(lytVar);
        res->addWidget(group);

        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(1):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite a variavel da Célula de destino:");
        group->setLayout(lytVar);
        res->addWidget(group);
        break;
    case Editor::PointNONext:
        setWindowTitle(tr("Apontar Variavel para proxima Célula"));
        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(0):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite a variavel:");
        group->setLayout(lytVar);
        res->addWidget(group);

        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(1):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite a variavel da Célula:");
        group->setLayout(lytVar);
        res->addWidget(group);

        break;
    case Editor::PointNextNONext:
        setWindowTitle(tr("Apontar Célula para proxima Célula"));
        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(0):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite a variavel da célula:");
        group->setLayout(lytVar);
        res->addWidget(group);

        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(1):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite outra variavel da Célula:");
        group->setLayout(lytVar);
        res->addWidget(group);

        break;
    case Editor::ReceivePoint:
        setWindowTitle(tr("Apontar Váriavel para uma Célula existente"));
        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(0):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite a variavel:");
        group->setLayout(lytVar);
        res->addWidget(group);

        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(1):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite a variavel da Célula:");
        group->setLayout(lytVar);
        res->addWidget(group);
        break;
    case Editor::Free:
        setWindowTitle(tr("Desacolar endereço memória da Célula."));
        txtVar = new QLineEdit();
        txtVar->setValidator(new QRegExpValidator(QRegExp("^[A-z][a-zA-Z_]*$")));
        txtVar->setText(interpret->second.size()>0?interpret->second.at(0):"");
        _texts.append(txtVar);
        lytVar = new QHBoxLayout();
        lytVar->addWidget(txtVar);
        lytVar->addSpacerItem( new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group = new QGroupBox();
        group->setTitle("Digite a variavel:");
        group->setLayout(lytVar);
        res->addWidget(group);
        break;
    }


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(res);
    layout->addSpacerItem(new QSpacerItem(0, 0,QSizePolicy::Minimum, QSizePolicy::Expanding));
    layout->addLayout(createButton());
    setLayout(layout);
}

QString ImplementModal::impl(){
    return _impl;
}

void ImplementModal::buttonClicked(int button){
    _button = (Button) button;

    if (_button == Button::Confirm){
        foreach(QLineEdit *text, _texts){
            _impl = _impl.arg(text->text());
        }
    }

    hide();
}

QHBoxLayout *ImplementModal::createButton(){
    QPushButton *cancel = new QPushButton();
    cancel->setText(tr("Cancelar"));
    cancel->setIcon(QIcon(":/images/cancel.ico"));
    QPushButton *confirm = new QPushButton();
    confirm->setText(tr("Confirmar"));
    confirm->setDefault(true);
    confirm->setIcon(QIcon(":/images/confirm.ico"));
    QPushButton *delet = new QPushButton();
    delet->setText(tr("Deletar"));
    delet->setAutoDefault(true);
    delet->setIcon(QIcon(":/images/delet.ico"));
    QButtonGroup *group = new QButtonGroup();
    group->addButton(cancel, Button::Cancel);
    group->addButton(confirm, Button::Confirm);
    group->addButton(delet, Button::Delet);

    QHBoxLayout *bottom = new QHBoxLayout();
    bottom->addSpacerItem(new QSpacerItem(0, 0,QSizePolicy::Expanding, QSizePolicy::Minimum));
    bottom->addWidget(cancel);
    bottom->addWidget(confirm);
    bottom->addWidget(delet);
    bottom->addSpacerItem(new QSpacerItem(0, 0,QSizePolicy::Expanding, QSizePolicy::Minimum));

    connect(group, SIGNAL(buttonClicked(int)), this, SLOT(buttonClicked(int)));

    return bottom;
}
