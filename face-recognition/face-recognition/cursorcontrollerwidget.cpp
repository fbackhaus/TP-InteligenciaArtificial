#include "cursorcontrollerwidget.hpp"

CursorControllerWidget::CursorControllerWidget( QWidget *parent ) :
    QGLWidget( parent )
{
    this->setController( new CursorController( this ) );
    this->setControllerTexture( new Texture( "controller_texture" ) );
    this->setWidgetUpdater( new QTimer( this ) );

    this->connect( this->getWidgetUpdater(), SIGNAL( timeout() ), this, SLOT( updateWidget() ) );
    this->getWidgetUpdater()->setInterval( 20 );
    this->getWidgetUpdater()->start();
}

CursorControllerWidget::~CursorControllerWidget()
{
    delete this->getController();
    delete this->getControllerTexture();
    delete this->getWidgetUpdater();
}

void CursorControllerWidget::initializeGL()
{
    glClearColor( 0, 0, 0, 0 );
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
}

void CursorControllerWidget::resizeGL( int width, int height )
{
    glViewport( 0, 0, width, height );
}

void CursorControllerWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho( 0, RESOLUTION_WIDTH, 0, RESOLUTION_HEIGHT, 1, 1000 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glEnable( GL_TEXTURE_2D );
    glColor3f( 1, 1, 1 );
    glBindTexture( GL_TEXTURE_2D, *this->getControllerTexture()->getId() );
    glBegin( GL_QUADS );

        glTexCoord2f( 0, 0 ); glVertex3f( 0, RESOLUTION_HEIGHT, -999 );
        glTexCoord2f( 1, 0 ); glVertex3f( RESOLUTION_WIDTH, RESOLUTION_HEIGHT, -999 );
        glTexCoord2f( 1, 1 ); glVertex3f( RESOLUTION_WIDTH, 0, -999 );
        glTexCoord2f( 0, 1 ); glVertex3f( 0, 0, -999 );

    glEnd();
    glDisable( GL_TEXTURE_2D );
}

void CursorControllerWidget::keyPressEvent( QKeyEvent *event )
{
    switch( event->key() )
    {
    case Qt::Key_C:

        this->calibrate();
        break;

    case Qt::Key_D:

        this->changeShowProcessing( !FeaturesProcessor::getInstance()->getDrawProcessing() );
        break;
    }
}

CursorController *CursorControllerWidget::getController() const
{
    return controller;
}

void CursorControllerWidget::setController( CursorController *value )
{
    controller = value;
}

Texture *CursorControllerWidget::getControllerTexture() const
{
    return controllerTexture;
}

void CursorControllerWidget::setControllerTexture(Texture *value)
{
    controllerTexture = value;
}

QTimer *CursorControllerWidget::getWidgetUpdater() const
{
    return widgetUpdater;
}

void CursorControllerWidget::setWidgetUpdater(QTimer *value)
{
    widgetUpdater = value;
}

void CursorControllerWidget::updateWidget()
{
    this->getControllerTexture()->setMat( this->getController()->getDataMat() );
    this->getControllerTexture()->generateFromMat();
    this->updateGL();
}

void CursorControllerWidget::calibrate()
{
    this->getController()->setNeedCalibrate( true );
}

void CursorControllerWidget::changeShowProcessing( bool show )
{
    FeaturesProcessor::getInstance()->setDrawProcessing( show );
}
