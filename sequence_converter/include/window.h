#pragma once

#include <QMainWindow>

#include "turing_machine_view.h"
#include "normal_markov_algorithm_view.h"

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

private:
    Ui::Window *_ui;
    TuringMachineView *_turing_machine_view;
    NMAView *_nma_view;
};

