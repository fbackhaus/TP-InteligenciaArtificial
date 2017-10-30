#include <QApplication>
#include <QStyleFactory>
#include "mainwindow.h"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );
    qApp->setStyle( QStyleFactory::create( "Fusion" ) );

    MainWindow *augmentedReality = new MainWindow;
    augmentedReality->showMaximized();

    return app.exec();
}
