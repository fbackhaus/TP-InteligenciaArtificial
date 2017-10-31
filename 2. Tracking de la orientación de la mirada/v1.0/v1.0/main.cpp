#include <QApplication>

#include "test.hpp"

int main( int argc, char **argv )
{
    QApplication application( argc, argv );

    Test test;
    test.show();

    return application.exec();
}
