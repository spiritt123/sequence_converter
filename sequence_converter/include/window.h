#pragma once

#include <QMainWindow>
#include <QString>
#include <QTimer>

#include <unordered_map>

#include "loadStyle.h"
#include "rule.h"

namespace Ui
{
    class Window;
} // namespace

class Window : public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QMainWindow *parent = 0);
    virtual ~Window();

public slots:
    void on_button_add_rule_clicked();
    void on_button_remove_rule_clicked();
    void on_button_right_tape_clicked();
    void on_button_right_pointer_clicked();
    void on_button_left_pointer_clicked();
    void on_button_left_tape_clicked();
    void on_button_save_tape_clicked();
 
    void calc();

private:
    std::unordered_map<std::string, Rule> _rules;
    std::string _tape, _pointer;
    int _tape_offset, _pointer_offset;

    QTimer *_worker_timer;

    void updateRuleBox();
    void updateTape();
    void updatePointer();

private:
    Ui::Window *ui;
};

