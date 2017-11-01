#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QObject>
#include <QTimer>

#include <vector>

#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "common.hpp"

using namespace cv;
using namespace std;

class Camera : public QObject
{
    Q_OBJECT

private:

    VideoCapture *videoCapture;
    QTimer *sceneTimer;
    Mat *cameraTexture;

    CascadeClassifier *frontalFaceClassifier;
    CascadeClassifier *smileClassifier;

    Rect currentFace;
    Rect calibration;

    int size;
    bool smiling;

public:

    explicit Camera( QObject *parent = NULL );

    VideoCapture *getVideoCapture() const;
    void setVideoCapture( VideoCapture *value );

    QTimer *getSceneTimer() const;
    void setSceneTimer( QTimer *value );

    Mat *getCameraTexture() const;
    void setCameraTexture( Mat *value );

    CascadeClassifier *getFrontalFaceClassifier() const;
    void setFrontalFaceClassifier( CascadeClassifier *value);

    CascadeClassifier *getSmileClassifier() const;
    void setSmileClassifier( CascadeClassifier *value);

    int getSize() const;
    void setSize( int value );

    bool getSmiling() const;
    void setSmiling( bool value );

private slots:

    void process();

public slots:

    void calibrate();

signals:

    void positionDetected( int index );
    void selectionDetected( int index );
};

#endif // CAMERA_HPP
