#pragma once

#include <QString>
#include <QWidget>
#include <QTimer>
#include <QRegExpValidator>
#include <QRegExp>

#include "brainfuck.h"

namespace Ui
{
    class BrainfuckView;
} // namespace

class BrainfuckView : public QWidget
{
    Q_OBJECT
public:
    explicit BrainfuckView(QWidget *parent = 0);
    virtual ~BrainfuckView();

public slots:
    void on_start_button_clicked();
    void on_stop_button_clicked();
    void on_restart_button_clicked();
    
    void calc();

private:
    void updateMemory();

private:
    QTimer *_worker_timer;

    Ui::BrainfuckView *_brainfuck_view;
    Brainfuck _brainfuck;
    QRegExp _validREX;
};

