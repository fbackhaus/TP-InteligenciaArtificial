#include "cursorcontroller.hpp"

CursorController::CursorController( QObject *parent ) :
    QObject( parent )
{
    this->setProcessingTimer( new QTimer( this ) );
    this->setDataMat( new Mat() );
    this->setControlMouse( false );

    this->connect( this->getProcessingTimer(), SIGNAL( timeout() ), this, SLOT( processData() ) );
    this->getProcessingTimer()->setInterval( 20 );
    this->getProcessingTimer()->start();
}

CursorController::~CursorController()
{
    delete this->getProcessingTimer();
    delete this->getDataMat();
}

QTimer *CursorController::getProcessingTimer() const
{
    return processingTimer;
}

void CursorController::setProcessingTimer( QTimer *value )
{
    processingTimer = value;
}

Mat *CursorController::getDataMat() const
{
    return dataMat;
}

void CursorController::setDataMat( Mat *value )
{
    dataMat = value;
}

bool CursorController::getNeedCalibrate() const
{
    return needCalibrate;
}

void CursorController::setNeedCalibrate( bool value )
{
    needCalibrate = value;
}

QRect CursorController::getRoi() const
{
    return roi;
}

void CursorController::setRoi( const QRect &value )
{
    roi = value;
}

bool CursorController::getControlMouse() const
{
    return controlMouse;
}

void CursorController::setControlMouse( bool value )
{
    controlMouse = value;
}

void CursorController::processData()
{
    this->setDataMat( CameraProcessor::getInstance()->getCurrentFrame() );

    if( this->getDataMat()->empty() )
    {
        return;
    }
    
    if( this->getNeedCalibrate() )
    {
        this->setRoi( FaceDetector::getInstance()->process( this->getDataMat() ) );

        PointMapper::getInstance()->setContainerRect( QRect( 0, 0,
                  CameraProcessor::getInstance()->getFrameCapturer()->get( CV_CAP_PROP_FRAME_WIDTH ),
                  CameraProcessor::getInstance()->getFrameCapturer()->get( CV_CAP_PROP_FRAME_HEIGHT ) ) );

        PointMapper::getInstance()->setOriginRect( this->getRoi() );

        PointMapper::getInstance()->setTargetRect( QApplication::desktop()->screenGeometry() );

        FeaturesProcessor::getInstance()->setNeedToInitFT( true );
        FeaturesProcessor::getInstance()->setInitialFrames( true );
        FeaturesProcessor::getInstance()->setInitialFramesCounter( 0 );
        FeaturesProcessor::getInstance()->setFirstCentroid( true );

        this->setNeedCalibrate( false );
    }

    QPoint target = FeaturesProcessor::getInstance()->process( this->getDataMat(), this->getRoi() );

    if( this->getControlMouse() )
    {
        QCursor::setPos( PointMapper::getInstance()->map( target ) );
    }

    emit cursorTracking( target );
}
