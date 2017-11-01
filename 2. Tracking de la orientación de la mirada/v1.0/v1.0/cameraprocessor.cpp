#include "cameraprocessor.hpp"

CameraProcessor *CameraProcessor::instance = NULL;

CameraProcessor::CameraProcessor( QObject *parent ) :
    QObject( parent )
{
    this->setCamera( new VideoCapture( 0 ) );
    this->setCameraTimer( new QTimer( this ) );
    this->setCurrentFrame( new Mat() );
    this->setFaceClassifier( new CascadeClassifier( "../classifiers/face.xml" ) );
    this->setNeedCalibrate( false );

    this->connect( this->getCameraTimer(), SIGNAL( timeout() ), this, SLOT( process() ) );
    this->getCameraTimer()->setInterval( 10 );
    this->getCameraTimer()->start();

    // Tracking

    termcrit = TermCriteria( TermCriteria::COUNT | TermCriteria::EPS, 20, 0.03 );
    subPixWinSize = Size( 10, 10 );
    winSize = Size( 31, 31 );
    maxCount = 1000;
    needToInit = true;
    nightMode = false;
    primerasDetecciones = true;
    contadorPrimerasDetecciones = 0;
    calibrationFaceRect.x = 0;
    calibrationFaceRect.y = 0;
    calibrationFaceRect.width = 640;
    calibrationFaceRect.height = 480;
    centrox = 0;
    centroy = 0;
    desvx = 0;
    desvy = 0;
    primerCentroide = true;
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
    delete this->getInstance();
    delete this->getCameraTimer();
    delete this->getCamera();
    delete this->getCurrentFrame();
    delete this->getFaceClassifier();
}

QTimer *CameraProcessor::getCameraTimer() const
{
    return cameraTimer;
}

void CameraProcessor::setCameraTimer( QTimer *value )
{
    cameraTimer = value;
}

VideoCapture *CameraProcessor::getCamera() const
{
    return camera;
}

void CameraProcessor::setCamera( VideoCapture *value )
{
    camera = value;
}

Mat *CameraProcessor::getCurrentFrame() const
{
    return currentFrame;
}

void CameraProcessor::setCurrentFrame(Mat *value)
{
    currentFrame = value;
}

CascadeClassifier *CameraProcessor::getFaceClassifier() const
{
    return faceClassifier;
}

void CameraProcessor::setFaceClassifier( CascadeClassifier *value )
{
    faceClassifier = value;
}

bool CameraProcessor::getNeedCalibrate() const
{
    return needCalibrate;
}

void CameraProcessor::setNeedCalibrate( bool value )
{
    needCalibrate = value;
}

void CameraProcessor::process()
{
    this->getCamera()->operator >>( *this->getCurrentFrame() );

    flip( *this->getCurrentFrame(), *this->getCurrentFrame(), 1 );

    if( this->getNeedCalibrate() )
    {
        vector< Rect > detectedFaces;
        detectedFaces.clear();

        faceClassifier->detectMultiScale( *this->getCurrentFrame(), detectedFaces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 150, 150 ) );

        if( detectedFaces.size() > 0 )
        {
            calibrationFaceRect = detectedFaces.at( 0 );
            calibrationFaceRect.x += calibrationFaceRect.width / 3;
            calibrationFaceRect.width =  calibrationFaceRect.width * 1 / 3;
            calibrationFaceRect.y += calibrationFaceRect.height / 2;
            calibrationFaceRect.height = calibrationFaceRect.height * 1 / 3;


            centrox = calibrationFaceRect.x + calibrationFaceRect.width / 2;
            centroy = calibrationFaceRect.y + calibrationFaceRect.height / 2;


            emit calibration( true );
        }
        else
        {
            emit calibration( false );
        }

        this->setNeedCalibrate( false );

        // Tracking

        needToInit = true;
        contadorPrimerasDetecciones = 0;
        primerasDetecciones = true;

        primerCentroide = true;
    }

    // Tracking

    if( currentFrame->empty() )
    {
        return;
    }

    currentFrame->copyTo( image );
    cvtColor( image, gray, COLOR_BGR2GRAY );

    if( nightMode )
    {
        image = Scalar::all(0);
    }

    if( needToInit )
    {
        goodFeaturesToTrack( gray, points[1], maxCount, 0.01, 10, Mat(), 3, 0, 0.04 );
        cornerSubPix( gray, points[1], subPixWinSize, Size( -1, -1 ), termcrit );
        addRemovePt = false;
    }
    else
    {
        if( !points[0].empty() )
        {
            vector< uchar > status;
            vector< float > err;
            if( prevGray.empty() )
            {
                gray.copyTo( prevGray );
            }

            calcOpticalFlowPyrLK( prevGray, gray, points[0], points[1], status, err, winSize, 3, termcrit, 0, 0.001 );
            size_t i, k;
            for( i = k = 0; i < points[1].size(); i++ )
            {
                if( addRemovePt )
                {
                    if( norm( point - points[1][i] ) <= 5 )
                    {
                        addRemovePt = false;
                        continue;
                    }
                }

                if( !status[i] )
                {
                    continue;
                }

                points[1][k++] = points[1][i];

                circle( image, points[1][i], 1, Scalar( 255, 255, 255 ), 2, 8 );
            }
            points[1].resize( k );
        }
    }

    if( addRemovePt && points[1].size() < ( size_t )maxCount )
    {
        vector< Point2f > tmp;
        tmp.push_back( point );
        cornerSubPix( gray, tmp, winSize, Size( -1, -1 ), termcrit );
        points[1].push_back( tmp[0] );
        addRemovePt = false;
    }

    needToInit = false;

    *currentFrame = image.clone();

    std::swap( points[1], points[0] );

    if( primerasDetecciones )
    {
        contadorPrimerasDetecciones++;
        for( unsigned int i = 0; i < points[0].size(); i++ )
        {
            if( points[0][i].x < calibrationFaceRect.x ||
                points[0][i].x > calibrationFaceRect.x + calibrationFaceRect.width ||
                points[0][i].y < calibrationFaceRect.y ||
                points[0][i].y > calibrationFaceRect.y + calibrationFaceRect.height )
            {
                points[0].erase( points[0].begin() + i );
            }
        }
        if( contadorPrimerasDetecciones == 10 )
        {
            primerasDetecciones = false;
        }
    }
    else
    {
        // Centroide

        int centroidex = 0;
        int centroidey = 0;
        int cantidadPuntos = 0;
        for( unsigned int i = 0; i < points[0].size(); i++ )
        {
            centroidex += points[0][i].x;
            centroidey += points[0][i].y;
            cantidadPuntos++;
        }
        if( cantidadPuntos != 0 )
        {
            centroidex /= cantidadPuntos;
            centroidey /= cantidadPuntos;
        }

        cv::putText( *currentFrame, "centroide", Point( centroidex, centroidey ), 0,  1, Scalar( 255, 0, 0 ) );
        circle( *currentFrame, Point( centroidex, centroidey ), 10, Scalar( 255, 0, 0 ), 2 );

        if( primerCentroide )
        {
            desvx = centrox - centroidex;
            desvy = centroy - centroidey;
        }
        primerCentroide = false;


        cv::putText( *currentFrame, "seguimiento", Point( centroidex + desvx, centroidey + desvy ), 0,  1, Scalar( 255, 255, 0 ) );
        circle( *currentFrame, Point( centroidex + desvx, centroidey + desvy ), 10, Scalar( 255, 255, 0 ), 2 );

        emit tracking( QPoint( centroidex, centroidey ) );
    }

    cv::putText( *currentFrame, "centro", Point( centrox, centroy ), 0,  1, Scalar( 0, 0, 255 ) );
    circle( *currentFrame, Point( centrox, centroy ), 2, Scalar( 0, 0, 255 ), 2 );

    cv::swap( prevGray, gray );

    rectangle(*currentFrame,calibrationFaceRect,Scalar( 255, 0, 255 ), 1 );
}
