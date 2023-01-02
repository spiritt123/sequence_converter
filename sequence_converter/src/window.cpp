#include "window.h"
#include "ui_mainwindow.h"
#include <QDebug>


Window::Window(QMainWindow *parent) : 
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    
    _tape_offset = 0;
    _pointer_offset = 0;
    _pointer = "^q0";
    ui->line_pointer->insert(_pointer.c_str());

    _worker_timer = new QTimer();

    connect(ui->button_start, SIGNAL(clicked()), _worker_timer, SLOT(start()));
    connect(ui->button_stop, SIGNAL(clicked()), _worker_timer, SLOT(stop()));

    _worker_timer->setInterval(500);
    connect(_worker_timer, SIGNAL(timeout()), this,  SLOT(calc()));
}

void Window::on_button_add_rule_clicked()
{
    try
    {
        Rule rule(ui->line_for_rule->text().toStdString());
        std::string key = "";
                    key += rule.getCurrentSymbol();
                    key += "q" + std::to_string(rule.getCurrentState());
        _rules.insert({key, rule});
    }
    catch(const char* msg) 
    {
        qDebug() << msg;
    }
    
    updateRuleBox();
}

void Window::on_button_remove_rule_clicked()
{
    std::string key = ui->line_for_rule->text().toStdString();
    _rules.erase(key.substr(0, key.find("->")));
    updateRuleBox();
}

bool isContains(const std::unordered_map<std::string, Rule> &r, const std::string &str)
{
    for (const auto &k : r)
    {
        if (k.first == str)
        {
            return true;
        }
    }
    return false;
}

void Window::calc()
{
    std::string buffer = _pointer;
    buffer[0] = _tape[_tape_offset + _pointer_offset];

    if (!isContains(_rules, buffer))
    {
        _worker_timer->stop();
        qDebug() << "Error (stop)";
        return;
    }
    Rule out = _rules.find(buffer)->second;
    
    _tape[_tape_offset + _pointer_offset] = out.getNextSymbol();
    _pointer = "^q" + std::to_string(out.getNextState());
    
    if (out.getMove() == 'L')
    {
        on_button_left_pointer_clicked();
    }
    else if (out.getMove() == 'R')
    {
        on_button_right_pointer_clicked();
    }
    updateTape();
}

void Window::updateTape()
{
    if (_tape.length() == 0)
    {
        ui->line_for_rule->setText("Please save the tape");
        _tape_offset = 0;
        return;
    }

    if (_tape_offset <= 0)
    {
        std::string buffer = _tape.substr(-1 * _tape_offset, _tape.length());
        ui->line_tape->setText(buffer.c_str());
    }
    else
    {
        --_tape_offset;
    }
}

void Window::updatePointer()
{
    if (_pointer_offset >= 0)
    {
        ui->line_pointer->setText( (std::string(_pointer_offset, ' ') + _pointer) .c_str());
    }
    else
    {
        ++_pointer_offset;
    }
}
    
void Window::on_button_right_tape_clicked()
{
    ++_tape_offset;
    updateTape();
}
    
void Window::on_button_right_pointer_clicked()
{
    ++_pointer_offset;
    updatePointer();
}
    
void Window::on_button_left_pointer_clicked()
{
    --_pointer_offset;
    updatePointer();
}

void Window::on_button_left_tape_clicked()
{
    --_tape_offset;
    updateTape();
} 

void Window::on_button_save_tape_clicked()
{
    _tape = ui->line_tape->text().toStdString();
}

void Window::updateRuleBox()
{
    ui->rules_textbox->clear();
    for (const auto& l : _rules)
    {
        ui->rules_textbox->appendPlainText("> " + QString(l.second.getLine().c_str()));
    }
}

Window::~Window()
{
    delete ui;
}

