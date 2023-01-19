#pragma once

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QRegExpValidator>
#include <QRegExp>

#include "turing_machine.h"

namespace Ui
{
    class TuringMachineView;
} // namespace

class TuringMachineView : public QWidget
{
    Q_OBJECT
public:
    explicit TuringMachineView(QWidget *parent = 0);
    virtual ~TuringMachineView();

public slots:
    void on_button_add_rule_clicked();
    void on_button_remove_rule_clicked();
    void on_button_right_tape_clicked();
    void on_button_right_pointer_clicked();
    void on_button_left_pointer_clicked();
    void on_button_left_tape_clicked();
    void on_button_start_clicked();
    void on_button_stop_clicked();
    
    void calc();

private:
    void updateRuleBox();
    void updateTape();
    void updatePointer();

private:
    QTimer *_worker_timer;

    Ui::TuringMachineView *_turing_machine_view;
    TuringMachine _turing_machine;
    QRegExp _validREX;

    int _tape_offset;
    int _pointer_offset;
};

