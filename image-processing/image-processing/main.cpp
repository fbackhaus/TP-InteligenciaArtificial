#include <QApplication>

#include "scene.h"


int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    Scene scene;
    scene.show();

    return app.exec();
}
