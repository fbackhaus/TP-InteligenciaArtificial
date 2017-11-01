#include "cameraprocessor.hpp"

CameraProcessor *CameraProcessor::instance = NULL;

CameraProcessor::CameraProcessor( QObject *parent ) :
    QObject( parent )
{
    this->setFrameCapturer( new VideoCapture( 0 ) );
    this->setFrameUpdater( new QTimer( this ) );
    this->setCurrentFrame( new Mat() );

    this->connect( this->getFrameUpdater(), SIGNAL( timeout() ), this, SLOT( updateCurrentFrame() ) );
    this->getFrameUpdater()->setInterval( 20 );
    this->getFrameUpdater()->start();
}

CameraProcessor *CameraProcessor::getInstance()
{
    if( instance == NULL )
    {
        instance = new CameraProcessor( NULL );
    }
    return instance;
}

CameraProcessor::~CameraProcessor()
{
    delete this->getFrameCapturer();
    delete this->getCurrentFrame();
    delete this->getFrameUpdater();
    delete this->getInstance();
}

VideoCapture *CameraProcessor::getFrameCapturer() const
{
    return frameCapturer;
}

void CameraProcessor::setFrameCapturer( VideoCapture *value )
{
    frameCapturer = value;
}

Mat *CameraProcessor::getCurrentFrame() const
{
    return currentFrame;
}

void CameraProcessor::setCurrentFrame(Mat *value)
{
    currentFrame = value;
}

QTimer *CameraProcessor::getFrameUpdater() const
{
    return frameUpdater;
}

void CameraProcessor::setFrameUpdater( QTimer *value )
{
    frameUpdater = value;
}

void CameraProcessor::updateCurrentFrame()
{
    this->getFrameCapturer()->operator >>( *this->getCurrentFrame() );
}
