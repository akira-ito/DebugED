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
    enum Implementation { CreateNO, CreateNOVar, PointNOCreate,PointNO, PointNONext, PointNextNONext, ReceivePoint, Free, SetValueNO};
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    QMap<QString, QString> *mapImplement(){ return _mapImplement; }

protected:
    void resizeEvent(QResizeEvent *event);
    void focusOutEvent(QFocusEvent *e);
    void focusInEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
    void createCompleter();
    void deleteCurrentLine();
    QAbstractItemModel *createImplementation();
    QPair<QString, QStringList> *interpretLine(QString textLine);
    void processLine(QTextBlock block, bool next);
    QStringList readSample(CodeED::Sample sample);

    QWidget *lineNumberArea;
    CodeED *_codeED;
    QCompleter *_completer;
    int lineWeigth;
    QMap<QString, QString> *_mapImplement;
    QStringList *_implement;
    QStringList *_args;
    bool _endLine;
    QString _fileName;

private slots:
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void passAction(CodeED::Pass);
    void selectSample(CodeED::Sample sample);
    bool insertCompletion(const QString &completion, QStringList list = QStringList());
    void highlighted(const QString &text);
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void exit();

signals:
    void blockNext();
    void blockPrevious();
    void createVarPointStruct(Struct::StructType, QString var, QString varStruct);
    void removeVarPointStruct(Struct::StructType, QString var, QString varStruct);
    void createStruct(Struct::StructType type, QString var);
    void removeStruct(Struct::StructType type, QString var);
    void createNextNoCreate(Struct::StructType, QString var);
    void removeNextNoCreate(Struct::StructType, QString var);
    void createArrow(QString varA, QString varB);
    void removeArrow(QString varA, QString varB);
    void createReceivePoint(QString varA, QString varB);
    void removeReceivePoint(QString varA, QString varB);
    void createReceivePointNext(QString var, QString varStruct);
    void removeReceivePointNext(QString var, QString varStruct);
    void createReceiveNextPointNext(QString varStructA, QString varStructB);
    void removeReceiveNextPointNext(QString varStructA, QString varStructB);
    void createFree(QString var);
    void removeFree(QString var);
    void setValueNo(QString var, QString val);
    void clearStructed();

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
