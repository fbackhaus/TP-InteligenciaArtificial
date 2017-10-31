#ifndef CAMERAPROCESSOR_HPP
#define CAMERAPROCESSOR_HPP

#include <QObject>
#include <QTimer>
#include <QPoint>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <stdlib.h>
#include <vector>

using namespace cv;
using namespace std;

class CameraProcessor : public QObject
{
    Q_OBJECT

private:

    explicit CameraProcessor( QObject *parent = NULL );
    static CameraProcessor *instance;

    QTimer *cameraTimer;
    VideoCapture *camera;
    Mat *currentFrame;
    CascadeClassifier *faceClassifier;
    bool needCalibrate;

    // Tracking

    TermCriteria termcrit;
    Size subPixWinSize;
    Size winSize;
    int maxCount;
    bool needToInit;
    bool nightMode;
    bool addRemovePt;
    Point2f point;
    Mat gray, prevGray, image, frame;
    vector< Point2f > points[2];

    bool primerasDetecciones;
    int contadorPrimerasDetecciones;
    Rect calibrationFaceRect;
    int desvx;
    int desvy;
    int centrox;
    int centroy;
    bool primerCentroide;

public:

    static CameraProcessor *getInstance();
    ~CameraProcessor();

    QTimer *getCameraTimer() const;
    void setCameraTimer( QTimer *value );

    VideoCapture *getCamera() const;
    void setCamera( VideoCapture *value );

    Mat *getCurrentFrame() const;
    void setCurrentFrame( Mat *value );

    CascadeClassifier *getFaceClassifier() const;
    void setFaceClassifier( CascadeClassifier *value );

    bool getNeedCalibrate() const;
    void setNeedCalibrate( bool value );

private slots:

    void process();

signals:

    void calibration( bool success );
    void tracking( QPoint target );
};

#endif // CAMERAPROCESSOR_HPP
