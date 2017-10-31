#ifndef SCENE_HPP
#define SCENE_HPP

#define RESOLUTION_WIDTH  640
#define RESOLUTION_HEIGHT 480

#include <QTimer>
#include <QGLWidget>
#include <QKeyEvent>

#include "texture.hpp"
#include "cameraprocessor.hpp"

using namespace std;
using namespace cv;

class Scene : public QGLWidget
{
    Q_OBJECT

private:

    QTimer *sceneTimer;
    Texture *cameraTexture;

public:

    Scene( QWidget *parent = 0 );
    ~Scene();

    Texture *getCameraTexture() const;
    void setCameraTexture( Texture *value );

    QTimer *getSceneTimer() const;
    void setSceneTimer( QTimer *value );

protected:

    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();

private slots:

    void update();
};

#endif // SCENE_HPP
