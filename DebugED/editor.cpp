#include "editor.h"
#include "codeed.h"
#include "struct.h"
#include <QtWidgets>
#include <QDebug>
#include <QIODevice>

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
    setFont(QFont("courier", 10));
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

}

QAbstractItemModel *Editor::createImplementation(){
    _implement = new QStringList();
    _implement->insert(CreateNO, "Criar nó");
    _implement->insert(PointNO, "Apontar nó");
    _implement->insert(ReceivePoint, "Receber ponteiro de nó");

    _mapImplement = new QMap<QString, QString>();
    _mapImplement->insert(_implement->at(CreateNO), "NO *%1 = malloc(sizeof(NO *));");
    _mapImplement->insert(_implement->at(PointNO), "%1->next = %2;");
    _mapImplement->insert(_implement->at(ReceivePoint), "%1 = %2;");

    return new QStringListModel(_mapImplement->keys(), _completer);
}

bool Editor::processLine(QTextBlock block, bool next){
    QString textLine = block.text();
    QStringList res = QStringList();
    Implementation implementation;

    foreach(QString code, _mapImplement->values()){
        QRegExp regex = QRegExp(QRegExp::escape(code).replace(QRegExp("%[1-9]"), "([A-z0-9]*)"), Qt::CaseInsensitive);
        if (regex.exactMatch(textLine)){
            implementation = (Implementation) _implement->indexOf(_mapImplement->key(code));
            res = regex.capturedTexts();
            break;
        }
    }

    switch(implementation){
    case CreateNO:
        if (next)
            emit createStruct(Struct::Cell, res[1]);
        else{
            emit removeStruct(Struct::Cell, res[1]);
            return false;
        }
        break;
    case PointNO:
        if (next)
            emit createArrow(res[1], res[2]);
        else{
            emit removeArrow(res[1], res[2]);
            return false;
        }
        break;
    case ReceivePoint:
        if (next){
            emit createReceivePoint(res[1], res[2]);
        }else{
            emit removeReceivePoint(res[1], res[2]);
        }
        break;
    }
    return true;
}

QStringList Editor::readSample(CodeED::Sample sample){
    QString fileName = "";
    switch(sample){
    case CodeED::Sample::Point:
        fileName = "apontarNo";
        break;
    case CodeED::Sample::Remove:
        fileName = "removerNo";
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

void Editor::insertCompletion(const QString &completion){
    if (_completer->widget() != this)
        return;

    QString impl = _mapImplement->value(completion);
    while (!textCursor().block().text().isEmpty()){
        textCursor().deletePreviousChar();
    }

    if (completion == _implement->at(CreateNO)){
        QString var = QInputDialog::getText(this, completion, tr("Digite a variavel"));
        if (!var.trimmed().isEmpty()){
            insertPlainText(impl.arg(var.trimmed()));
        }
    }else if (completion == _implement->at(PointNO)){
        QString varA = QInputDialog::getText(this, completion, tr("Digite a variavel"));
        QString varB = QInputDialog::getText(this, completion, tr("Digite a variavel"));
        insertPlainText(impl.arg(varA).arg(varB));
    }else if (completion == _implement->at(ReceivePoint)){
        QString varA = QInputDialog::getText(this, completion, tr("Digite a variavel"));
        QString varB = QInputDialog::getText(this, completion, tr("Digite a variavel"));
        insertPlainText(impl.arg(varA).arg(varB));
    }

}

void Editor::updateLineNumberArea(const QRect &rect, int dy){
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

}

void Editor::passAction(CodeED::Pass pass){
    bool executeLine = true;
    switch(pass){
    case CodeED::Pass::Play:
        moveCursor(QTextCursor::Start);
        break;
    case CodeED::Pass::Next:
        moveCursor(QTextCursor::NextBlock);

        if (!textCursor().movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor)){
            emit blockNext();
        }
        break;
    case CodeED::Pass::Previous:
        executeLine = processLine(textCursor().block(), false);
        moveCursor(QTextCursor::PreviousBlock);

        if (!textCursor().movePosition(QTextCursor::PreviousBlock, QTextCursor::KeepAnchor)){
            emit blockPrevious();
        }
        break;
    case CodeED::Pass::Stop:
        return;
        break;
    }

    if (executeLine)
        processLine(textCursor().block(), true);
    highlightCurrentLine();
}

void Editor::selectSample(CodeED::Sample sample){
    document()->clear();
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
    if (_completer && _completer->popup()->isVisible()) {
        // The following keys are forwarded by the completer to the widget
       switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
       default:
           break;
       }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Space); // CTRL+E
    if (!_completer || !isShortcut) // do not process the shortcut when we have a completer
        QPlainTextEdit::keyPressEvent(e);
    //! [7]

    //! [8]
    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!_completer || (ctrlOrShift && e->text().isEmpty()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;

    QTextCursor tc = textCursor();
    tc.select(QTextCursor::LineUnderCursor);
    QString completionPrefix = tc.selectedText();

    if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 10
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
            if (lineWeigth == blockNumber){
                painter.setFont(QFont("Courier", 10, QFont::Black));
            }else{
                painter.setFont(QFont("courier", 10));
            }
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
