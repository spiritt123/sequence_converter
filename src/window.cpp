#include "window.h"
#include "ui_mainwindow.h"

#include "brainfuck_view.h"
#include "turing_machine_view.h"
#include "normal_markov_algorithm_view.h"

Window::Window(QMainWindow *parent) 
    : QMainWindow(parent)
    , _ui(new Ui::Window)
{
    _ui->setupUi(this);
    
    _ui->tabWidget->addTab(new TuringMachineView(this), "Turing Machine");
    _ui->tabWidget->addTab(new NMAView(this), "Normal Markov algorithm");
    _ui->tabWidget->addTab(new BrainfuckView(this), "Brainfuck");
    
}

Window::~Window()
{
    delete _ui;
}

