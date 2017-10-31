#include "scene.hpp"

Scene::Scene( QWidget *parent ) :
    QGLWidget( parent )
{
    this->setSceneTimer( new QTimer( this ) );
    this->setCameraTexture( new Texture( "camera" ) );

    connect( this->getSceneTimer(), SIGNAL( timeout() ), this, SLOT( update() ) );
    this->getSceneTimer()->setInterval( 10 );
    this->getSceneTimer()->start();
}

Scene::~Scene()
{
    delete this->getSceneTimer();
    delete this->getCameraTexture();
}

void Scene::initializeGL()
{
    glClearColor( 0, 0, 0, 0 );
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
}

void Scene::resizeGL( int width, int height )
{
    glViewport( 0, 0, width, height );
}

void Scene::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho( 0, RESOLUTION_WIDTH, 0, RESOLUTION_HEIGHT, 1, 1000 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glEnable( GL_TEXTURE_2D );
    glColor3f( 1, 1, 1 );
    glBindTexture( GL_TEXTURE_2D, *this->getCameraTexture()->getId() );
    glBegin( GL_QUADS );

        glTexCoord2f( 0, 0 ); glVertex3f( 0, RESOLUTION_HEIGHT, -999 );
        glTexCoord2f( 1, 0 ); glVertex3f( RESOLUTION_WIDTH, RESOLUTION_HEIGHT, -999 );
        glTexCoord2f( 1, 1 ); glVertex3f( RESOLUTION_WIDTH, 0, -999 );
        glTexCoord2f( 0, 1 ); glVertex3f( 0, 0, -999 );

    glEnd();
    glDisable( GL_TEXTURE_2D );
}

Texture *Scene::getCameraTexture() const
{
    return cameraTexture;
}

void Scene::setCameraTexture(Texture *value)
{
    cameraTexture = value;
}

QTimer *Scene::getSceneTimer() const
{
    return sceneTimer;
}

void Scene::setSceneTimer(QTimer *value)
{
    sceneTimer = value;
}

void Scene::update()
{
    this->getCameraTexture()->setMat( CameraProcessor::getInstance()->getCurrentFrame() );
    this->getCameraTexture()->generateFromMat();
    this->updateGL();
}
