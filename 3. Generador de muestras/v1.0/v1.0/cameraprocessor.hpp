#ifndef CAMERAPROCESSOR_HPP
#define CAMERAPROCESSOR_HPP

// qt includes
#include <QObject>
#include <QTimer>
#include <QPoint>

// opencv includes
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class CameraProcessor : public QObject
{
    Q_OBJECT

private:

    explicit CameraProcessor( QObject *parent = NULL );
    static CameraProcessor *instance;

    VideoCapture *frameCapturer;
    Mat *currentFrame;
    QTimer *frameUpdater;

public:

    static CameraProcessor *getInstance();
    ~CameraProcessor();

    VideoCapture *getFrameCapturer() const;
    void setFrameCapturer( VideoCapture *value );

    Mat *getCurrentFrame() const;
    void setCurrentFrame( Mat *value );

    QTimer *getFrameUpdater() const;
    void setFrameUpdater( QTimer *value );

    int getFrameCapturerBrightness();
    int getFrameCapturerContrast();
    int getFrameCapturerSaturation();
    int getFrameCapturerHue();

private slots:

    void updateCurrentFrame();

public slots:

    void setFrameCapturerBrightness( int value );
    void setFrameCapturerContrast( int value );
    void setFrameCapturerSaturation( int value );
    void setFrameCapturerHue( int value );
};

#endif // CAMERAPROCESSOR_HPP
