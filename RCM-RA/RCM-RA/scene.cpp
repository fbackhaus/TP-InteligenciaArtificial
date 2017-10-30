#include "scene.h"
#include <QDebug>
Scene::Scene( QWidget *parent ) : QGLWidget( parent ),
                                  videoCapture ( new cv::VideoCapture( 0 ) ),
                                  sceneTimer ( new QTimer ),
                                  textures( new QVector< Texture * > )
{
    this->setMinimumSize( videoCapture->get( CV_CAP_PROP_FRAME_WIDTH ), videoCapture->get( CV_CAP_PROP_FRAME_HEIGHT ) );
    sceneTimer->start( 10 );

    connect( sceneTimer, SIGNAL( timeout() ), SLOT( slot_updateScene() ) );
}

void Scene::loadTextures()
{
    QDir directory( "../Textures" );
    QStringList fileFilter;
    fileFilter << "*.jpg" << "*.png" << "*.bmp" << "*.gif";
    QStringList imageFiles = directory.entryList( fileFilter );

    for ( int i = 0; i < imageFiles.size(); i++ )
    {
        textures->append( new Texture( imageFiles.at( i ) ) );
        QString textureUri = "../Textures/" + imageFiles.at( i );

        Mat textureMat = imread( textureUri.toStdString() );
        flip( textureMat, textureMat, 0 );
        textures->last()->mat = textureMat;
        textures->last()->generateFromMat();
    }
}

void Scene::initializeGL()
{
    initializeGLFunctions();

    glClearColor( 0, 0, 0, 0 );
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );

    GLfloat lightAmbient[4]; lightAmbient[0] = 0.5f;  lightAmbient[1] = 0.5f;  lightAmbient[2] = 0.5f;  lightAmbient[3] = 1.0f;
    GLfloat lightDiffuse[4]; lightDiffuse[0] = 1.0f;  lightDiffuse[1] = 1.0f;  lightDiffuse[2] = 1.0f;  lightDiffuse[3] = 1.0f;
    GLfloat lightPosition[4];lightPosition[0]= 0.0f;  lightPosition[1]= 0.0f;  lightPosition[2]= 2.0f;  lightPosition[3]= 1.0f;

    glLightfv( GL_LIGHT1, GL_AMBIENT, lightAmbient );  glLightfv( GL_LIGHT1, GL_DIFFUSE, lightDiffuse );
    glLightfv( GL_LIGHT1, GL_POSITION,lightPosition ); glEnable( GL_LIGHT1 );

    textures->append( new Texture( "CameraTexture" ) );
    loadTextures();
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

    // Inicio: Gráfico de cámara

    glEnable( GL_TEXTURE_2D );
    glColor3f( 1, 1, 1 );
    glBindTexture( GL_TEXTURE_2D, textures->at( 0 )->id );
    glBegin( GL_QUADS );

        glTexCoord2f( 0, 0 ); glVertex3f( 0, RESOLUTION_HEIGHT, -999 );
        glTexCoord2f( 1, 0 ); glVertex3f( RESOLUTION_WIDTH, RESOLUTION_HEIGHT, -999 );
        glTexCoord2f( 1, 1 ); glVertex3f( RESOLUTION_WIDTH, 0, -999 );
        glTexCoord2f( 0, 1 ); glVertex3f( 0, 0, -999 );

    glEnd();
    glDisable( GL_TEXTURE_2D );

    // Fin: Gráfico de cámara

    glFlush();
}

void Scene::process( Mat &frame )
{
    Mat grayscaleMat; cvtColor( frame, grayscaleMat, CV_BGR2GRAY );
    Mat binaryMat; threshold( grayscaleMat, binaryMat, 128, 255, cv::THRESH_BINARY );
}

void Scene::drawCamera( int percentage )
{
    drawSheet( "CameraTexture", percentage );
}

void Scene::drawCameraBox( int percentage )
{
    drawBox( "CameraTexture", percentage );
}

void Scene::drawSheet( QString textureName, int percentage )
{
    for( int i = 0; i < textures->size(); i++ )
        if( textures->at( i )->name == textureName )
        {
            float sideLength = percentage / ( float )2300;
            glEnable( GL_TEXTURE_2D );
            glBindTexture( GL_TEXTURE_2D, textures->at( i )->id );
            glColor3f( 1, 1, 1 );
            glRotated( 90, 1, 0, 0 );
            glTranslatef( 0, 0, sideLength );
            glBegin( GL_QUADS );

                glNormal3f( 0.0f, 0.0f,-1.0f);
                glTexCoord2f( 1.0f, 0.0f ); glVertex3f(-sideLength, -sideLength, -sideLength );
                glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-sideLength,  sideLength, -sideLength );
                glTexCoord2f( 0.0f, 1.0f ); glVertex3f( sideLength,  sideLength, -sideLength );
                glTexCoord2f( 0.0f, 0.0f ); glVertex3f( sideLength, -sideLength, -sideLength );

            glEnd();
            glDisable( GL_TEXTURE_2D);
        }
}

void Scene::drawBox( QString textureName, int percentage )
{
    for( int i = 0; i < textures->size(); i++ )
        if( textures->at( i )->name == textureName )
        {
            float sideLength = percentage / ( float )2300;

            glEnable( GL_TEXTURE_2D );
            glBindTexture( GL_TEXTURE_2D, textures->at( i )->id );
            glColor3f( 1, 1, 1 );
            glRotated( 90, 1, 0, 0 );
            glTranslatef( 0, 0, -sideLength );
            glEnable( GL_LIGHTING );
            glBegin( GL_QUADS );

                glNormal3f( 0.0f, 0.0f, 1.0f ); // Frontal
                glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-sideLength, -sideLength,  sideLength );
                glTexCoord2f( 1.0f, 0.0f ); glVertex3f( sideLength, -sideLength,  sideLength );
                glTexCoord2f( 1.0f, 1.0f ); glVertex3f( sideLength,  sideLength,  sideLength );
                glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-sideLength,  sideLength,  sideLength );

                glNormal3f( 0.0f, 0.0f,-1.0f ); // Anterior
                glTexCoord2f( 1.0f, 0.0f ); glVertex3f(-sideLength, -sideLength, -sideLength );
                glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-sideLength,  sideLength, -sideLength );
                glTexCoord2f( 0.0f, 1.0f ); glVertex3f( sideLength,  sideLength, -sideLength );
                glTexCoord2f( 0.0f, 0.0f ); glVertex3f( sideLength, -sideLength, -sideLength );

                glNormal3f( 0.0f, 1.0f, 0.0f ); // Superior
                glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-sideLength,  sideLength, -sideLength );
                glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-sideLength,  sideLength,  sideLength );
                glTexCoord2f( 1.0f, 0.0f ); glVertex3f( sideLength,  sideLength,  sideLength );
                glTexCoord2f( 1.0f, 1.0f ); glVertex3f( sideLength,  sideLength, -sideLength );

                glNormal3f( 0.0f,-1.0f, 0.0f ); // Inferior
                glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-sideLength, -sideLength, -sideLength );
                glTexCoord2f( 0.0f, 1.0f ); glVertex3f( sideLength, -sideLength, -sideLength );
                glTexCoord2f( 0.0f, 0.0f ); glVertex3f( sideLength, -sideLength,  sideLength );
                glTexCoord2f( 1.0f, 0.0f ); glVertex3f(-sideLength, -sideLength,  sideLength );

                glNormal3f( 1.0f, 0.0f, 0.0f ); // Derecha
                glTexCoord2f( 1.0f, 0.0f ); glVertex3f( sideLength, -sideLength, -sideLength );
                glTexCoord2f( 1.0f, 1.0f ); glVertex3f( sideLength,  sideLength, -sideLength );
                glTexCoord2f( 0.0f, 1.0f ); glVertex3f( sideLength,  sideLength,  sideLength );
                glTexCoord2f( 0.0f, 0.0f ); glVertex3f( sideLength, -sideLength,  sideLength );

                glNormal3f( -1.0f, 0.0f, 0.0f ); // Izquierda
                glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-sideLength, -sideLength, -sideLength );
                glTexCoord2f( 1.0f, 0.0f ); glVertex3f(-sideLength, -sideLength,  sideLength );
                glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-sideLength,  sideLength,  sideLength );
                glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-sideLength,  sideLength, -sideLength );

            glEnd();
            glDisable( GL_LIGHTING );
            glDisable( GL_TEXTURE_2D );
        }
}

void Scene::slot_updateScene()
{
    videoCapture->operator >>( textures->operator []( 0 )->mat );
    process( textures->operator []( 0 )->mat );
    textures->operator []( 0 )->generateFromMat();
    this->updateGL();
}
