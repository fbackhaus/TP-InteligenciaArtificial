#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

// qt includes
#include <QMainWindow>

// project includes
#include "exampler.hpp"
#include "gesturerecognizer.hpp"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Ui::MainWindow *ui;
    bool logging;

public:

    explicit MainWindow( QWidget *parent = NULL );
    ~MainWindow();

    bool getLogging() const;
    void setLogging( bool value );

private slots:

    void log();
};

#endif // MAINWINDOW_HPP
