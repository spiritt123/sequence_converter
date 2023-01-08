#include "normal_markov_algorithm_view.h"
#include "ui_nma.h"
#include <QDebug>

NMAView::NMAView(QWidget *parent)
    : QWidget(parent)
    , _nma_view(new Ui::NMAView)
{
    _nma_view->setupUi(this);

    _validREX = QRegExp(".*\\|{0,1}->.*");
    
    _worker_timer = new QTimer();

    _worker_timer->setInterval(500);
    connect(_worker_timer, SIGNAL(timeout()), this,  SLOT(calc()));
}

void NMAView::on_button_start_clicked()
{
    _nma_view->tape->setReadOnly(true);
    _worker_timer->start();
}

void NMAView::on_button_stop_clicked()
{
    _worker_timer->stop();
    _nma_view->tape->setReadOnly(false);
}

void NMAView::on_button_add_rule_clicked()
{
    QString str = _nma_view->line_for_rule->text();
    if (_validREX.exactMatch(str))
    {
        _nma.addRule(_nma_view->number_of_rule->value(), str.toStdString());
        updateRuleBox();
    }
}

void NMAView::on_button_remove_rule_clicked()
{
    _nma.removeRule(_nma_view->number_of_rule->value());
    updateRuleBox();
}

void NMAView::calc()
{
    std::string tape = _nma_view->tape->text().toStdString();
    int status = _nma.calculate(tape);
    if (status != nma::STATUS::Wait)
    {
        on_button_stop_clicked();
    }
    _nma_view->tape->setText(tape.c_str());
    switch (status)
    {
    case nma::STATUS::Wait :
        _nma_view->status_line->setText("Wait");
        _nma_view->status_line->setStyleSheet("QLineEdit { background: #fdd835;}");
        break;
    case nma::STATUS::Success :
        _nma_view->status_line->setText("Success");
        _nma_view->status_line->setStyleSheet("QLineEdit { background: #2e7d32;}");
        break;
    case nma::STATUS::Error :
        _nma_view->status_line->setText("Error");
        _nma_view->status_line->setStyleSheet("QLineEdit { background: #d50000;}");
        break;
    }
}
 
void NMAView::updateRuleBox()
{
    _nma_view->rules_textbox->clear();
    int i = 0;
    for (const auto& rule : _nma.getRules())
    {
        ++i;
        if (rule == " ") continue;

        _nma_view->rules_textbox->appendPlainText(QString::number(i) + "> " + QString(rule.c_str()));
    }
    QTextCursor cursor = _nma_view->rules_textbox->textCursor();
    cursor.movePosition(QTextCursor::Start);
    _nma_view->rules_textbox->setTextCursor(cursor);
}

NMAView::~NMAView()
{
    delete _nma_view;
}

