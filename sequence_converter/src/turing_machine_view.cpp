#include "turing_machine_view.h"
#include "ui_tm.h"
#include <QDebug>

TuringMachineView::TuringMachineView(QWidget *parent)
    : QWidget(parent)
    , _turing_machine_view(new Ui::TuringMachineView)
{
    _turing_machine_view->setupUi(this);

    _validREX = QRegExp(".q\\d{1,3}->.q\\d{1,3}[L|S|R]");
    //_turing_machine_view->line_for_rule->setValidator(new QRegExpValidator(_validREX, this));
    
    _tape_offset = 0;
    _pointer_offset = 0;

    _worker_timer = new QTimer();

    _worker_timer->setInterval(500);
    connect(_worker_timer, SIGNAL(timeout()), this,  SLOT(calc()));

    _turing_machine_view->
        line_pointer->setText( 
                (std::string(_pointer_offset, ' ') + "^q" + std::to_string(_turing_machine.getState()) ).c_str());
}

void TuringMachineView::on_button_start_clicked()
{
    _turing_machine.setTape(_turing_machine_view->line_tape->text().toStdString());
    _turing_machine.setPointer(std::abs(_tape_offset) + _pointer_offset);
    _pointer_offset = 0;
    // disable all
    _worker_timer->start();
}

void TuringMachineView::on_button_stop_clicked()
{
    _pointer_offset = _turing_machine.getPointer();
    _turing_machine.setPointer(0);
    _worker_timer->stop();
}

void TuringMachineView::on_button_add_rule_clicked()
{
    QString str = _turing_machine_view->line_for_rule->text();
    if (_validREX.exactMatch(str))
    {
        _turing_machine.addRule(str.toStdString());
        updateRuleBox();
    }
}

void TuringMachineView::on_button_remove_rule_clicked()
{
    _turing_machine.removeRule(_turing_machine_view->line_for_rule->text().toStdString());
    updateRuleBox();
}

void TuringMachineView::calc()
{
    if (!_turing_machine.calculate())
    {
        on_button_stop_clicked();
        //_worker_timer->stop();
    }
    updateTape();
    updatePointer();
}
 
void TuringMachineView::on_button_right_tape_clicked()
{
    if (_tape_offset > 0)
    {
        _tape_offset = 0;
        return;
    }

    ++_tape_offset;
    updateTape();
}

void TuringMachineView::on_button_left_tape_clicked()
{
    if (_tape_offset + _turing_machine.getTape().length() < 2)
    {
        _tape_offset = -_turing_machine.getTape().length();
        return ;
    }
    
    --_tape_offset;
    updateTape();
} 
 
void TuringMachineView::updateTape()
{
    std::string buffer = _turing_machine.getTape();
    if (buffer.length() == 0)
    {
        _turing_machine_view->line_for_rule->setText("Please input the tape");
        _tape_offset = 0;
        return;
    }

    if (_tape_offset > 0)
    {
        _tape_offset = 0;
        return;
    }

    buffer = buffer.substr(std::abs(_tape_offset), buffer.length());
    _turing_machine_view->line_tape->setText(buffer.c_str());
}  

void TuringMachineView::on_button_right_pointer_clicked()
{
    ++_pointer_offset;
    
    std::string tape = _turing_machine.getTape();
    int overflow = tape.length() - (std::abs(_tape_offset) + _pointer_offset);
    if (overflow <= 0)
    {
        _turing_machine.setTape(tape + std::string(std::abs(overflow) + 1, '0'));
        updateTape();
    }
    
    updatePointer();
}
    
void TuringMachineView::on_button_left_pointer_clicked()
{
    if (_pointer_offset < 1)
        return;

    --_pointer_offset;
    updatePointer();
}

void TuringMachineView::updatePointer()
{
    _turing_machine_view->
        line_pointer->setText( 
                (std::string(_pointer_offset + _turing_machine.getPointer(), ' ') + "^q" + std::to_string(_turing_machine.getState()) ).c_str());
}

void TuringMachineView::updateRuleBox()
{
    _turing_machine_view->rules_textbox->clear();
    for (const auto& rule : _turing_machine.getRules())
    {
        _turing_machine_view->rules_textbox->appendPlainText("> " + QString(rule.c_str()));
    }
}

TuringMachineView::~TuringMachineView()
{
    delete _turing_machine_view;
}

