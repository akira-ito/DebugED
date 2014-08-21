#include "editor.h"
#include <QtWidgets>

Editor::Editor(QWidget *parent) : QPlainTextEdit(parent), lineWeigth(0){

    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    highlightCurrentLine();
    setViewportMargins(20, 0, 0, 0);
    setFont(QFont("courier", 10));
    setTabStopWidth(40);
    setTabChangesFocus(false);
    setAutoFillBackground(true);
    setTextInteractionFlags(Qt::TextInteractionFlag::TextEditorInteraction);
}

void Editor::updateLineNumberArea(const QRect &rect, int dy)
{

    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

}

void Editor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), 20, cr.height()));
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
                painter.setFont(QFont("Courier", 11, QFont::Black));
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