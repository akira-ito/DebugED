#ifndef EDITOR_H
#define EDITOR_H

#include "codeed.h"
#include <QPlainTextEdit>
#include <QObject>
#include <QMap>

class QCompleter;
class QAbstractItemModel;


class Editor : public QPlainTextEdit{
    Q_OBJECT

public:
    Editor(CodeED *codeED, QWidget *parent = 0);
    enum Implementation { CreateNO, PointNO, ReceivePoint, SetValueNO};
    void lineNumberAreaPaintEvent(QPaintEvent *event);

protected:
    void resizeEvent(QResizeEvent *event);
    void focusOutEvent(QFocusEvent *e);
    void focusInEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
    void createCompleter();
    QAbstractItemModel *createImplementation();
    bool processLine(QTextBlock block, bool next);
    QStringList readSample(CodeED::Sample sample);

    QWidget *lineNumberArea;
    CodeED *_codeED;
    QCompleter *_completer;
    int lineWeigth;
    QMap<QString, QString> *_mapImplement;
    QStringList *_implement;

private slots:
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void passAction(CodeED::Pass);
    void selectSample(CodeED::Sample sample);
    void insertCompletion(const QString &completion);

signals:
    void blockNext();
    void blockPrevious();
    void createStruct(Struct::StructType type, QString var);
    void createArrow(QString varA, QString varB);
    void removeStruct(Struct::StructType type, QString var);
    void removeArrow(QString varA, QString varB);
    void createReceivePoint(QString varA, QString varB);
    void removeReceivePoint(QString varA, QString varB);
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(Editor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    Editor *codeEditor;
};


#endif // EDITOR_H
