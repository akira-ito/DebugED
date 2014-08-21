#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>
#include <QObject>


class Editor : public QPlainTextEdit{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0);
    void lineNumberAreaPaintEvent(QPaintEvent *event);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QWidget *lineNumberArea;
    int lineWeigth;

private slots:
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

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
