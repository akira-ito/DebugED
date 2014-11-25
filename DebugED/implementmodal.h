#ifndef IMPLEMENTMODAL_H
#define IMPLEMENTMODAL_H

#include "editor.h"
#include <QMessageBox>
#include <QHBoxLayout>

class ImplementModal : public QDialog{
    Q_OBJECT

public:
    ImplementModal(QPair<QString, QStringList> *interpret, Editor::Implementation implementation, QWidget *parent = 0);
    enum Button{Cancel, Confirm, Delet};
    Button button(){ return _button; }
    QString impl();

private slots:
    void buttonClicked(int button);

private:
    Editor::Implementation _implementation;
    QString _impl;
    Button _button;
    QList<QLineEdit *> _texts;

    QHBoxLayout *createButton();
};

#endif // IMPLEMENTMODAL_H
