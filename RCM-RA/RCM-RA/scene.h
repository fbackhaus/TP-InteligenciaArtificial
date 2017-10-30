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

#include "texture.h"
#include "model.h"
#include "video.h"

#include <aruco/aruco.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace aruco;

class Scene : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT

private:

    VideoCapture *videoCapture;
    QTimer *sceneTimer;
    bool videoActive;
    bool localMusicActive;
    bool musicActive;

    QVector< Texture * > *textures;
    QVector< Model * > *models;
    QVector< Video * > *videos;
    GLuint webImageTextureId;
    GLuint webMusicImageTextureId;
    QMediaPlayer *webMusicPlayer;

    CameraParameters *cameraParameters;
    MarkerDetector *markerDetector;
    QVector< Marker > detectedMarkers;

    void loadTextures();
    void loadModels();
    void prepareModels();
    void loadTexturesForModels();
    void loadVideos();

    void process( Mat &frame );

    void drawCamera( int percentage = 100 );
    void drawCameraBox( int percentage = 100 );
    void drawSheet( QString textureName, int percentage = 100 );
    void drawBox( QString textureName, int percentage = 100 );
    void drawModel( QString modelName, int percentage = 100 );
    void drawVideo( QString videoName, int volume = 100, int percentage = 100 );
    void decreaseVideoVolume( QString videoName );
    void drawWebImage( int percentage = 100 );
    void drawWebMusicImage( int percentage = 100 );
    void listenWebMusic();

public:

    Scene( QWidget *parent = 0 );

    void setWebImageTextureId( GLuint textureId );
    void setWebMusicImageTextureId( GLuint textureId );
    void setWebMusicPlayerMedia( QString musicUri );

    bool detectMarkersOption;
    bool rotateOption;
    int rotationVelocityOption;
    bool descriptionOption;
    int scaleOption;
    double xTranslationOption;
    double yTranslationOption;
    double zTranslationOption;
    int xRotationOption;
    int yRotationOption;
    int zRotationOption;

protected:

    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();

private slots:

    void slot_updateScene();
    void slot_webMusicPlayerBufferChanged( int percentageLoaded );

signals:

    void message( QString text );
};

#endif // SCENE_H
