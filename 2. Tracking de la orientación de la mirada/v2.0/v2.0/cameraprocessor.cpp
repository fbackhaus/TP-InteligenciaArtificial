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

int CameraProcessor::getFrameCapturerBrightness()
{
    return this->getFrameCapturer()->get( CV_CAP_PROP_BRIGHTNESS ) * 100;
}

int CameraProcessor::getFrameCapturerContrast()
{
    return this->getFrameCapturer()->get( CV_CAP_PROP_CONTRAST ) * 100;
}

int CameraProcessor::getFrameCapturerSaturation()
{
    return this->getFrameCapturer()->get( CV_CAP_PROP_SATURATION ) * 100;
}

int CameraProcessor::getFrameCapturerHue()
{
    return this->getFrameCapturer()->get( CV_CAP_PROP_HUE ) * 100;
}

void CameraProcessor::updateCurrentFrame()
{
    this->getFrameCapturer()->operator >>( *this->getCurrentFrame() );
}

void CameraProcessor::setFrameCapturerBrightness( int value )
{
    this->getFrameCapturer()->set( CV_CAP_PROP_BRIGHTNESS, value / ( double )100 );
}

void CameraProcessor::setFrameCapturerContrast( int value )
{
    this->getFrameCapturer()->set( CV_CAP_PROP_CONTRAST, value / ( double )100 );
}

void CameraProcessor::setFrameCapturerSaturation( int value )
{
    this->getFrameCapturer()->set( CV_CAP_PROP_SATURATION, value / ( double )100 );
}

void CameraProcessor::setFrameCapturerHue( int value )
{
    this->getFrameCapturer()->set( CV_CAP_PROP_HUE, value / ( double )100 );
}
