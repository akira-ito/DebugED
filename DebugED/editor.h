#ifndef EDITOR_H
#define EDITOR_H

#include "codeed.h"
#include <QPlainTextEdit>
#include <QObject>

class QCompleter;
class QAbstractItemModel;


class Editor : public QPlainTextEdit{
    Q_OBJECT

public:
    Editor(CodeED *codeED, QWidget *parent = 0);
    void lineNumberAreaPaintEvent(QPaintEvent *event);

protected:
    void resizeEvent(QResizeEvent *event);
    void focusOutEvent(QFocusEvent *e);
    void focusInEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
    void createCompleter();
    QAbstractItemModel *modelFromFile(const QString& fileName);

    QWidget *lineNumberArea;
    CodeED *_codeED;
    QCompleter *_completer;
    int lineWeigth;

private slots:
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void passAction(CodeED::Pass);

    void insertCompletion(const QString &completion);

signals:
    void blockNext();
    void blockPrevious();
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
