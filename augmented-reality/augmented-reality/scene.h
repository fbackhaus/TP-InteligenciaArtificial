#ifndef SCENE_H
#define SCENE_H

#define RESOLUTION_WIDTH  640
#define RESOLUTION_HEIGHT 480

#include <QDir>
#include <QFile>
#include <QTimer>
#include <QVector>
#include <QGLWidget>
#include <QGLFunctions>

#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "texture.h"

using namespace cv;

class Scene : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT

private:

    VideoCapture *videoCapture;
    QTimer *sceneTimer;
    Texture *cameraTexture;

    void process( Mat &frame );

public:

    Scene( QWidget *parent = 0 );

protected:

    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();

private slots:

    void updateScene();
};

#endif // SCENE_H
