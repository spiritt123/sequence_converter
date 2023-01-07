#pragma once

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QRegExpValidator>
#include <QRegExp>

#include "normal_markov_algorithm.h"

namespace Ui
{
    class NMAView;
} // namespace

class NMAView : public QWidget
{
    Q_OBJECT
public:
    explicit NMAView(QWidget *parent = 0);
    virtual ~NMAView();

public slots:
    void on_button_add_rule_clicked();
    void on_button_remove_rule_clicked();
    void on_button_start_clicked();
    void on_button_stop_clicked();
    
    void calc();

private:
    void updateRuleBox();

private:
    QTimer *_worker_timer;

    Ui::NMAView *_nma_view;
    NMA _nma;
    QRegExp _validREX;
};

