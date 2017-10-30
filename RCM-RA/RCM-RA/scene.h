#ifndef SCENE_H
#define SCENE_H

#define RESOLUTION_WIDTH  1280
#define RESOLUTION_HEIGHT 720

#include <QDir>
#include <QFile>
#include <QTimer>
#include <QVector>
#include <QGLWidget>
#include <QGLFunctions>

#include "texture.h"

#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Scene : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT

private:

    VideoCapture *videoCapture;
    QTimer *sceneTimer;

    QVector< Texture * > *textures;

    void loadTextures();

    void process( Mat &frame );

    void drawCamera( int percentage = 100 );
    void drawCameraBox( int percentage = 100 );
    void drawSheet( QString textureName, int percentage = 100 );
    void drawBox( QString textureName, int percentage = 100 );

public:

    Scene( QWidget *parent = 0 );

protected:

    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();

private slots:

    void slot_updateScene();
};

#endif // SCENE_H
