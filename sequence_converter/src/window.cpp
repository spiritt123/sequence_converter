#include "window.h"
#include "ui_mainwindow.h"


Window::Window(QMainWindow *parent) 
    : QMainWindow(parent)
    , _ui(new Ui::Window)
{
    _ui->setupUi(this);
    
    _turing_machine_view = new TuringMachineView(this);
    _ui->layoutTuringMachine->addWidget(_turing_machine_view);
    _turing_machine_view->show();
    
    _nma_view = new NMAView(this);
    _ui->layoutNMA->addWidget(_nma_view);
    _nma_view->show();
}

Window::~Window()
{
    delete _turing_machine_view;
    delete _nma_view;
    delete _ui;
}

