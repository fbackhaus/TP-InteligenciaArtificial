#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#define CCW_WIDTH 960
#define CCW_HEIGHT 540

// qt includes
#include <QMainWindow>

// project includes
#include "exampler.hpp"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Ui::MainWindow *ui;

public:

    explicit MainWindow( QWidget *parent = NULL );
    ~MainWindow();
};

#endif // MAINWINDOW_HPP
