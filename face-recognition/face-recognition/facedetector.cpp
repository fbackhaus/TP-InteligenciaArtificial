#include "facedetector.hpp"

FaceDetector *FaceDetector::instance = NULL;

FaceDetector::FaceDetector( QObject *parent ) :
    QObject( parent )
{
    this->setFaceClassifier( new CascadeClassifier( "/Users/fbackhaus/qt/TP-InteligenciaArtificial/face-recognition/classifiers/face.xml" ) );
}

FaceDetector *FaceDetector::getInstance()
{
    if( instance == NULL )
    {
        instance = new FaceDetector( NULL );
    }
    return instance;
}

FaceDetector::~FaceDetector()
{
    delete this->getFaceClassifier();
    delete this->getInstance();
}

CascadeClassifier *FaceDetector::getFaceClassifier() const
{
    return faceClassifier;
}

void FaceDetector::setFaceClassifier( CascadeClassifier *value )
{
    faceClassifier = value;
}

QRect FaceDetector::process( Mat *mat )
{
    vector< Rect > faces;

    faces.clear();

    this->getFaceClassifier()->detectMultiScale( *mat, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 150, 150 ) );

    Rect roi( 0, 0, 0, 0 );

    if( faces.size() > 0 )
    {
        roi = faces.at( 0 );

        // current nose tip region

        roi.x = roi.x + roi.width / ( double )3;
        roi.y = roi.y + roi.height / ( double )2;
        roi.width = roi.width * 1 / ( double )3;
        roi.height = roi.height * 1 / ( double )3;
    }

    return QRect( roi.x, roi.y, roi.width, roi.height );
}
