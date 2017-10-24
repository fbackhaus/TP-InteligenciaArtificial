#include <QApplication>
#include "scene.h"

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Scene *scene = new Scene(NULL);
    scene->show();

    return app.exec();
}
