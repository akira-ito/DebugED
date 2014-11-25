#include "editor.h"
#include "codeed.h"
#include "struct.h"
#include "implementmodal.h"

#include <QtWidgets>
#include <QDebug>
#include <QIODevice>
#include <QImage>
#include <QDebug>
#include <QPair>
#include <QToolTip>

class Struct;
class QTextBlockUserData;

Editor::Editor(CodeED *codeED, QWidget *parent) : QPlainTextEdit(parent), lineWeigth(0){
    _codeED = codeED;
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    if (codeED != NULL){
        connect(_codeED, SIGNAL(passAction(CodeED::Pass)), this, SLOT(passAction(CodeED::Pass)));
        connect(_codeED, SIGNAL(selectSample(CodeED::Sample)), this, SLOT(selectSample(CodeED::Sample)));
    }

    createCompleter();
    highlightCurrentLine();
    setViewportMargins(20, 0, 0, 0);
    setFont(QFont("Courier New", 10));
    setTabStopWidth(40);
    setTabChangesFocus(false);
    setAutoFillBackground(true);
    setTextInteractionFlags(Qt::TextInteractionFlag::TextEditorInteraction);
}

void Editor::createCompleter(){
    _completer = new QCompleter(this);
    _completer->setModel(createImplementation());
    _completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    _completer->setCaseSensitivity(Qt::CaseInsensitive);
    _completer->setWrapAround(false);
    _completer->setWidget(this);
    _completer->setCompletionMode(QCompleter::PopupCompletion);
    _completer->setMaxVisibleItems(10);

    connect(_completer, SIGNAL(activated(QString)),this, SLOT(insertCompletion(QString)));
    connect(_completer, SIGNAL(highlighted(QString)), this, SLOT(highlighted(QString)));
}

void Editor::deleteCurrentLine(){
    moveCursor(QTextCursor::EndOfBlock, QTextCursor::MoveAnchor);
    while (!textCursor().block().text().isEmpty()){
        textCursor().deletePreviousChar();
    }
}

QAbstractItemModel *Editor::createImplementation(){
    _implement = new QStringList();
    _implement->insert(CreateNO, tr("Criar Variavel e apontar nova Célula"));
    _implement->insert(CreateNOVar, tr("Criar Variavel e apontar a Célula"));
    _implement->insert(PointNOCreate, tr("Apontar Célula para outra Célula nova"));
    _implement->insert(PointNO, tr("Apontar Célula para outra Célula criada"));
    _implement->insert(PointNONext, tr("Apontar Variavel para proxima Célula"));
    _implement->insert(PointNextNONext, tr("Apontar Célula para proxima Célula"));
    _implement->insert(ReceivePoint, tr("Apontar Várivel para Célula"));
    _implement->insert(Free, tr("Desalocar Célula"));
    //_implement->insert(SetValueNO, tr("Setar valor nó"));

    _mapImplement = new QMap<QString, QString>();
    _mapImplement->insert(_implement->at(CreateNO), "NO *%1 = (NO *)malloc(sizeof(NO));");
    _mapImplement->insert(_implement->at(CreateNOVar), "NO *%1 = %2;");
    _mapImplement->insert(_implement->at(PointNOCreate), "%1->next = (NO *)malloc(sizeof(NO));");
    _mapImplement->insert(_implement->at(PointNO), "%1->next = %2;");
    _mapImplement->insert(_implement->at(PointNONext), "%1 = %2->next;");
    _mapImplement->insert(_implement->at(PointNextNONext), "%1->next = %2->next;");
    _mapImplement->insert(_implement->at(ReceivePoint), "%1 = %2;");
    _mapImplement->insert(_implement->at(Free), "free(%1);");
    //_mapImplement->insert(_implement->at(SetValueNO), "%1->value = %2;");

    _args = new QStringList();
    _args->insert(CreateNO,"variável");
    _args->insert(CreateNOVar,"variável,variável");
    _args->insert(PointNOCreate,"variável");
    _args->insert(PointNO,"variável,variável");
    _args->insert(PointNONext,"variável,célula");
    _args->insert(PointNextNONext,"variável,variável");
    _args->insert(ReceivePoint,"variável,célula");
    _args->insert(Free,"célula");

    int row = 0;
    QStandardItemModel *model = new QStandardItemModel(_completer);
    foreach(QString impl, _mapImplement->keys()){
        QStandardItem* item = new QStandardItem(impl);
        item->setIcon(QIcon(":/images/command.ico"));
        QString tooTip = _mapImplement->value(impl);
        foreach(QString arg, _args->at(_implement->indexOf(impl)).split(",")){
            tooTip = tooTip.arg("<font size='4' color='blue'><strong>"+arg+"</strong></font>");
        }
        item->setToolTip("<pre>"+tooTip+"</pre>");
        model->setItem(row, 0, item);
        row++;
    }

    return model;
}

QPair<QString, QStringList> *Editor::interpretLine(QString textLine){
    QStringList res = QStringList();
    QString impl;

    foreach(QString code, _mapImplement->values()){
        QRegExp regex = QRegExp(QRegExp::escape(code).replace(QRegExp("%[1-9]"), "([A-z0-9]*)"), Qt::CaseInsensitive);
        if (regex.exactMatch(textLine)){
            impl = _mapImplement->key(code);
            res = regex.capturedTexts();
            res.removeAt(0);
            break;
        }
    }
    return new QPair<QString, QStringList>(impl, res);
}

void Editor::processLine(QTextBlock block, bool next){
    QString textLine = block.text();
    QPair<QString, QStringList> *interpret = interpretLine(textLine);
    Implementation implementation = (Implementation) _implement->indexOf(interpret->first);
    QStringList res = interpret->second;

    switch(implementation){
    case CreateNO:
        if (next)
            emit createStruct(Struct::Cell, res[0]);
        else{
            emit removeStruct(Struct::Cell, res[0]);
        }
        break;
    case CreateNOVar:
        if (next)
            emit createVarPointStruct(Struct::Cell, res[0], res[1]);
        else{
            emit removeVarPointStruct(Struct::Cell, res[0], res[1]);
        }
        break;
    case PointNOCreate:
        if (next)
            emit createNextNoCreate(Struct::Cell, res[0]);
        else{
            emit removeNextNoCreate(Struct::Cell, res[0]);
        }
        break;
    case PointNO:
        if (next)
            emit createArrow(res[0], res[1]);
        else{
            emit removeArrow(res[0], res[1]);
        }
        break;
    case ReceivePoint:
        if (next){
            emit createReceivePoint(res[0], res[1]);
        }else{
            emit removeReceivePoint(res[0], res[1]);
        }
        break;
    case PointNONext:
        if (next){
            emit createReceivePointNext(res[0], res[1]);
        }else{
            emit removeReceivePointNext(res[0], res[1]);
        }
        break;
    case PointNextNONext:
        if (next){
            emit createReceiveNextPointNext(res[0], res[1]);
        }else{
            emit removeReceiveNextPointNext(res[0], res[1]);
        }
        break;
    case Free:
        if (next){
            emit createFree(res[0]);
        }else{
            emit removeFree(res[0]);
        }
        break;
    case SetValueNO:
        if (next){
            emit setValueNo(res[0], res[1]);
        }else{

        }
        break;
    }
}

QStringList Editor::readSample(CodeED::Sample sample){
    QString fileName = "";
    switch(sample){
    case CodeED::Sample::List:
        fileName = "List";
        break;
    case CodeED::Sample::UnList:
        fileName = "UnList";
        break;
    case CodeED::Sample::Stack:
        fileName = "Stack";
        break;
    case CodeED::Sample::UnStack:
        fileName = "UnStack";
        break;
    }

    QStringList lines;
    QFile file(":/exemplos/"+fileName+".txt");
    if(!file.open(QFile::ReadOnly | QFile::Text))
        qDebug() << " Could not open file for writing";
    else
        while (!file.atEnd())
            lines << file.readLine();

    return lines;
}


bool Editor::insertCompletion(const QString &completion, QStringList list){
    QString complete = completion;
    QPair<QString, QStringList> *interpret = new QPair<QString, QStringList>(completion, list);
    ImplementModal *a = new ImplementModal(interpret, (Implementation)_implement->indexOf(complete), this);
    a->exec();
    if (a->button() == ImplementModal::Confirm){
        deleteCurrentLine();
        insertPlainText(a->impl());
    }else if(a->button() == ImplementModal::Delet){
        deleteCurrentLine();
        return true;
    }
    return false;
}

void Editor::highlighted(const QString &text){
    QModelIndex index =_completer->popup()->currentIndex();
    int heigthRow = _completer->popup()->sizeHintForRow(index.row());
    QPoint a = _completer->popup()->pos() - QPoint(0,heigthRow);
    QPoint b = QPoint(_completer->popup()->sizeHintForColumn(0)+ _completer->popup()->verticalScrollBar()->sizeHint().width(), index.row()*heigthRow);
    QString toolTip = ((QStandardItemModel *)_completer->model())->findItems(text).at(0)->toolTip();
    QToolTip::showText( a+b, toolTip, _completer->popup(),QRect(QPoint(20,20), QSize(400,90)));
}

void Editor::fileSave(){
    if (_fileName.isEmpty())
            return fileSaveAs();

    QTextDocumentWriter writer(_fileName);
    bool success = writer.write(document());
    if (success)
        document()->setModified(false);
}

void Editor::fileOpen(){
    QString fn = QFileDialog::getOpenFileName(this, tr("Abrir arquivo..."), QString(), tr("C (*.c);; C++ (*.cpp)"));
    if (fn.isEmpty())
        return;

    QStringList lines;
    QFile file(fn);
    if(!file.open(QFile::ReadOnly | QFile::Text))
        qDebug() << " Could not open file for writing";
    else
        while (!file.atEnd())
            lines << file.readLine();

    clear();
    foreach (QString line, lines){
        insertPlainText(line);
    }
    moveCursor(QTextCursor::Start);
    highlightCurrentLine();
}

void Editor::fileNew(){
    clear();
    _fileName = QString();
}

void Editor::fileSaveAs(){
    QString fn = QFileDialog::getSaveFileName(this, tr("Salvar como..."), QString(), tr("C (*.c);; C++ (*.cpp)"));
    if (fn.isEmpty())
        return;

    if (!(fn.endsWith(".c", Qt::CaseInsensitive) || fn.endsWith(".cpp", Qt::CaseInsensitive)) )
        fn += ".c";
    _fileName = fn;
    fileSave();
}

void Editor::exit(){
    qApp->quit();
}

void Editor::updateLineNumberArea(const QRect &rect, int dy){
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

}

void Editor::passAction(CodeED::Pass pass){
    switch(pass){
    case CodeED::Play:
        document()->setPlainText(document()->toPlainText().trimmed());
        moveCursor(QTextCursor::Start);
        setDisabled(true);
        _endLine = false;
        emit clearStructed();
        break;
    case CodeED::Next:
        processLine(textCursor().block(), true);
        if (!_endLine && !textCursor().movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor)){
            moveCursor(QTextCursor::EndOfBlock);
            insertPlainText("\n");
            _endLine = true;
            emit blockNext();
        }else
            moveCursor(QTextCursor::NextBlock);
        break;
    case CodeED::Previous:
        if (_endLine){
            textCursor().deletePreviousChar();
            _endLine = false;
        }else
            moveCursor(QTextCursor::PreviousBlock);
        processLine(textCursor().block(), false);
        if (!textCursor().movePosition(QTextCursor::PreviousBlock, QTextCursor::KeepAnchor))
            emit blockPrevious();
        break;
    case CodeED::Stop:
        setEnabled(true);
        document()->setPlainText(document()->toPlainText().trimmed());
        moveCursor(QTextCursor::EndOfBlock, QTextCursor::MoveAnchor);
        return;
    }
    highlightCurrentLine();
}

void Editor::selectSample(CodeED::Sample sample){
    clear();
    QStringList lines = readSample(sample);
    foreach (QString line, lines){
        insertPlainText(line);
    }
    moveCursor(QTextCursor::Start);
    highlightCurrentLine();
}

void Editor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), 20, cr.height()));
}

void Editor::focusOutEvent(QFocusEvent *e){
    QPlainTextEdit::focusOutEvent(e);
    setExtraSelections(QList<QTextEdit::ExtraSelection>());
}

void Editor::focusInEvent(QFocusEvent *e){
    highlightCurrentLine();

    if (_completer)
        _completer->setWidget(this);

    QPlainTextEdit::focusInEvent(e);
}

void Editor::keyPressEvent(QKeyEvent *e){
    if (_completer->popup()->isVisible()) {
       switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            e->ignore();
            return;
       default:
           break;
       }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Space); // CTRL+SPACE
    if (!isShortcut && e->key() != Qt::Key_Backspace && e->key() != Qt::Key_Return)
        QPlainTextEdit::keyPressEvent(e);

    bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-=");
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;

    QString completionPrefix = textCursor().selectedText();
    if (completionPrefix.isEmpty()){
        QTextCursor tc = textCursor();
        tc.select(QTextCursor::LineUnderCursor);
        completionPrefix = tc.selectedText();
    }

    if (e->key() == Qt::Key_Backspace){
        QPair<QString, QStringList> *interpret = interpretLine(completionPrefix);
        QString impl = interpret->first;
        if (!impl.isEmpty()){
            if (insertCompletion(interpret->first, interpret->second)){
                QPlainTextEdit::keyPressEvent(e);
            }
        }else{
            QPlainTextEdit::keyPressEvent(e);
        }

        if (completionPrefix.isEmpty()){
            _completer->popup()->hide();
            return;
        }
    }

    if(e->key() ==  Qt::Key_Return){
        QString impl = interpretLine(completionPrefix)->first;
        if (impl.isEmpty()){
            return;
        }
        moveCursor(QTextCursor::EndOfBlock);
        QPlainTextEdit::keyPressEvent(e);
    }

    if (!isShortcut && (hasModifier || e->text().isEmpty()
                      || eow.contains(e->text().right(1)))) {
        _completer->popup()->hide();
        return;
    }

    if (completionPrefix != _completer->completionPrefix()) {
        _completer->setCompletionPrefix(completionPrefix);
        _completer->popup()->setCurrentIndex(_completer->completionModel()->index(0, 0));
    }

    QRect cr = cursorRect();
    cr.setWidth(_completer->popup()->sizeHintForColumn(0)
                + _completer->popup()->verticalScrollBar()->sizeHint().width());
    _completer->complete(cr); // popup it up!
}

void Editor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();

        lineWeigth = selection.cursor.blockNumber();
        extraSelections.append(selection);


    }

    setExtraSelections(extraSelections);
}

void Editor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor(Qt::lightGray).lighter(120));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {

            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(Qt::darkCyan).light(150));
            if (!isEnabled() && lineWeigth == blockNumber){
                painter.drawPixmap(5,top,lineNumberArea->width()-5, fontMetrics().height(), QPixmap(":/images/currentLine.ico"));
            }else if (lineWeigth == blockNumber){
                painter.setFont(QFont("Courier", 10, QFont::Black));
                painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
            }else{
                painter.setFont(QFont("courier", 10));
                painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
            }
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
