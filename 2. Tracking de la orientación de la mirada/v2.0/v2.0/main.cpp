#include <QApplication>

#include "mainwindow.hpp"

int main( int argc, char **argv )
{
    QApplication application( argc, argv );

    MainWindow *mainWindow = new MainWindow( NULL );
    mainWindow->showMaximized();

    return application.exec();
}
