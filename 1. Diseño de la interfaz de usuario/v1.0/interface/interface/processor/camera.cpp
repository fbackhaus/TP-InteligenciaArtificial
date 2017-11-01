#include "camera.hpp"

Camera::Camera( QObject *parent ) :
    QObject( parent )
{
    this->setVideoCapture( new VideoCapture( 0 ) );
    this->setSceneTimer( new QTimer( this ) );
    this->setCameraTexture( new Mat() );

    QString faceClassifier( APPLICATION_PATH );
    faceClassifier.append( CLASSIFIERS_PATH );
    faceClassifier.append( "face.xml" );
    string face = faceClassifier.toStdString();

    QString smileClassifier( APPLICATION_PATH );
    smileClassifier.append( CLASSIFIERS_PATH );
    smileClassifier.append( "smile.xml" );
    string smile = smileClassifier.toStdString();

    this->setFrontalFaceClassifier( new CascadeClassifier( face ) );
    this->setSmileClassifier( new CascadeClassifier( smile ) );
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

CascadeClassifier *Camera::getSmileClassifier() const
{
    return smileClassifier;
}

void Camera::setSmileClassifier( CascadeClassifier *value )
{
    smileClassifier = value;
}

int Camera::getSize() const
{
    return size;
}

void Camera::setSize( int value )
{
    size = value;
}

bool Camera::getSmiling() const
{
    return smiling;
}

void Camera::setSmiling( bool value )
{
    smiling = value;
}

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

        emit positionDetected( index );

        vector< Rect > detectedSmiles;
        detectedSmiles.clear();

        detectedFaces.operator []( 0 ).width -= detectedFaces.operator []( 0 ).width % 3;

        Mat face( *this->getCameraTexture(), detectedFaces.at( 0 ) );

        smileClassifier->detectMultiScale( face, detectedSmiles,
                                          1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 50, 50 ) );

        if( detectedSmiles.size() > 0 )
        {
            if( !this->getSmiling() )
            {
                emit smileDetected( index );
                this->setSmiling( true );
            }
        }
        else
        {
            if( smiling )
            {
                this->setSmiling( false );
            }
        }
    }
}

void Camera::calibrate()
{
    calibration.x = currentFace.x + currentFace.width / 4;
    calibration.y = currentFace.y + currentFace.height / 4;
    calibration.width = currentFace.width / 2;
    calibration.height = currentFace.height / 2;
}
