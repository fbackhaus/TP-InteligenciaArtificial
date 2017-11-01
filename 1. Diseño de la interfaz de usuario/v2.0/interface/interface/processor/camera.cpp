#include "camera.hpp"

Camera::Camera( QObject *parent ) :
    QObject( parent ),
    selectionData( new QVector< bool >() )
{
    this->setVideoCapture( new VideoCapture( 0 ) );
    this->setSceneTimer( new QTimer( this ) );
    this->setCameraTexture( new Mat() );

    QString faceClassifier( APPLICATION_PATH );
    faceClassifier.append( CLASSIFIERS_PATH );
    faceClassifier.append( "face.xml" );
    string face = faceClassifier.toStdString();

    this->setFrontalFaceClassifier( new CascadeClassifier( face ) );
    this->setSize( 0 );

    connect( this->getSceneTimer(), SIGNAL( timeout() ), SLOT( process() ) );
    this->getSceneTimer()->start( 10 );
}

VideoCapture *Camera::getVideoCapture() const
{
    return videoCapture;
}

void Camera::setVideoCapture( VideoCapture *value )
{
    videoCapture = value;
}

QTimer *Camera::getSceneTimer() const
{
    return sceneTimer;
}

void Camera::setSceneTimer( QTimer *value )
{
    sceneTimer = value;
}

Mat *Camera::getCameraTexture() const
{
    return cameraTexture;
}

void Camera::setCameraTexture( Mat *value )
{
    cameraTexture = value;
}

CascadeClassifier *Camera::getFrontalFaceClassifier() const
{
    return frontalFaceClassifier;
}

void Camera::setFrontalFaceClassifier( CascadeClassifier *value )
{
    frontalFaceClassifier = value;
}

int Camera::getSize() const
{
    return size;
}

void Camera::setSize( int value )
{
    size = value;
}
#include <QDebug>
void Camera::process()
{
    this->getVideoCapture()->operator >>( *this->getCameraTexture() );

    vector< Rect > detectedFaces;
    detectedFaces.clear();

    frontalFaceClassifier->detectMultiScale( *this->getCameraTexture(), detectedFaces,
                                     1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 150, 150 ) );

    if( detectedFaces.size() > 0 )
    {
        currentFace = detectedFaces.at( 0 );
    }

    if( detectedFaces.size() > 0 && size != 0 )
    {
        int xFaceCenter = detectedFaces.at( 0 ).x + detectedFaces.at( 0 ).width / 2;
        int yFaceCenter = detectedFaces.at( 0 ).y + detectedFaces.at( 0 ).height / 2;

        if( xFaceCenter < calibration.x ||
            xFaceCenter > calibration.x + calibration.width ||
            yFaceCenter < calibration.y ||
            yFaceCenter > calibration.y + calibration.height ) return;

        int index = this->getSize() - ( ( xFaceCenter - calibration.x ) / ( calibration.width / size ) ) - 1;

        // Selection detection

        int vertical = ( yFaceCenter - calibration.y ) / ( calibration.height / 3 );

        selectionData->append( vertical > 1 ? true : false );

        if( selectionData->size() > 20 )
        {
            selectionData->removeFirst();
        }

        if( !selectionData->first() &&
            !selectionData->last() &&
            selectionData->contains( true ) )
        {
            emit selectionDetected( index );
        }

        emit positionDetected( index );
    }
}

void Camera::calibrate()
{
    calibration.x = currentFace.x + currentFace.width / 4;
    calibration.y = currentFace.y + currentFace.height / 4;
    calibration.width = currentFace.width / 2;
    calibration.height = currentFace.height / 2;
}
