#include "brainfuck_view.h"
#include "brainfuck.h"
#include "ui_brainfuck.h"
#include <QDebug>

BrainfuckView::BrainfuckView(QWidget *parent)
    : QWidget(parent)
    , _brainfuck_view(new Ui::BrainfuckView)
{
    _brainfuck_view->setupUi(this);

    _validREX = QRegExp("[+|\\-|>|<|.|,|\\[|\\]]*");
    
    _worker_timer = new QTimer();
    //_brainfuck_view->code->setValidator(new QRegExpValidator(_validREX, this));

    _worker_timer->setInterval(10);
    connect(_worker_timer, SIGNAL(timeout()), this,  SLOT(calc()));
}

void BrainfuckView::on_start_button_clicked()
{
    QString str = _brainfuck_view->code->toPlainText().remove('\n').remove(' ');
    if (!_validREX.exactMatch(str))
    {
        _brainfuck_view->status->setText("Error code: \"Incorrect chars\"");
        _brainfuck_view->status->setStyleSheet("QLineEdit { background: #d50000;}");
        return ;
    }

    bf::STATUS_CODE status = _brainfuck.setCode(str.toStdString());

    if (status == bf::STATUS_CODE::OpenBracketNestingError)
    {
        _brainfuck_view->status->setText("Error code: \"Expect [\"");
        _brainfuck_view->status->setStyleSheet("QLineEdit { background: #d50000;}");
        return ;
    } 
    else if (status == bf::STATUS_CODE::CloseBracketNestingError)
    {
        _brainfuck_view->status->setText("Error code: \"Expect ]\"");
        _brainfuck_view->status->setStyleSheet("QLineEdit { background: #d50000;}");
        return ;
    }
    _worker_timer->start();
}

void BrainfuckView::on_stop_button_clicked()
{
    _worker_timer->stop();
}

void BrainfuckView::on_restart_button_clicked()
{
    _worker_timer->stop();
    _brainfuck.setPointer(0);
    _brainfuck.clearMemory();
    _brainfuck_view->output_line->setText("");
    on_start_button_clicked();
}

void BrainfuckView::calc()
{
    bf::STATUS status = _brainfuck.calculate();
    switch (status)
    {
    case bf::STATUS::Success:
        _brainfuck_view->status->setText("Success");
        _brainfuck_view->status->setStyleSheet("QLineEdit { background: #2e7d32;}");
        on_stop_button_clicked();
        break;
    case bf::STATUS::InputChar:
        //if line.size == 0 -> error
        _brainfuck_view->status->setText("Input char");
        _brainfuck_view->status->setStyleSheet("QLineEdit { background: #fdd835;}");
        _brainfuck.setChar(_brainfuck_view->input_line->text().front().toLatin1());
        _brainfuck_view->input_line->setText(_brainfuck_view->input_line->text().mid(1));

        break;
    case bf::STATUS::OutputChar:
        _brainfuck_view->status->setText("Output char");
        _brainfuck_view->status->setStyleSheet("QLineEdit { background: #fdd835;}");
        _brainfuck_view->output_line->setText(
                _brainfuck_view->output_line->text() + _brainfuck.getChar()
                );
        break;
    case bf::STATUS::Wait:
        _brainfuck_view->status->setText("Wait");
        _brainfuck_view->status->setStyleSheet("QLineEdit { background: #fdd835;}");
        break;
    }
        //_worker_timer->stop();
    updateMemory();
}
 
QString convertMemoryToView(const char* memory, uint32_t size_memory)
{
    QString str = "";
    char buffer[4];

    for (int i = 0; i < size_memory; ++i)
    {
        sprintf(buffer, "%2x ", memory[i]);
        str += buffer;
    }

    return str.remove(0, 1);
}

void BrainfuckView::updateMemory()
{
    _brainfuck_view->memory->clear();
    QString memory = convertMemoryToView(_brainfuck.getMemory(), _brainfuck.getMemorySize());
    _brainfuck_view->memory->setText(memory);
}

BrainfuckView::~BrainfuckView()
{
    delete _worker_timer;
    delete _brainfuck_view;
}

