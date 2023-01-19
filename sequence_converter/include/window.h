#pragma once

#include <QMainWindow>

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
};

