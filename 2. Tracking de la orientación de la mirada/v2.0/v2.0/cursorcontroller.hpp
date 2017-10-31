#ifndef CURSORCONTROLLER_HPP
#define CURSORCONTROLLER_HPP

// qt includes
#include <QObject>
#include <QTimer>
#include <QPoint>
#include <QCursor>
#include <QApplication>
#include <QDesktopWidget>

// opencv includes
#include <opencv2/opencv.hpp>

// project includes
#include "cameraprocessor.hpp"
#include "facedetector.hpp"
#include "featuresprocessor.hpp"
#include "pointmapper.hpp"

using namespace cv;

class CursorController : public QObject
{
    Q_OBJECT

private:

    QTimer *processingTimer;
    Mat *dataMat;
    bool needCalibrate;
    QRect roi;
    bool controlMouse;

public:

    explicit CursorController( QObject *parent = NULL );
    ~CursorController();

    QTimer *getProcessingTimer() const;
    void setProcessingTimer( QTimer *value );

    Mat *getDataMat() const;
    void setDataMat( Mat *value );

    bool getNeedCalibrate() const;
    void setNeedCalibrate( bool value );

    QRect getRoi() const;
    void setRoi( const QRect &value );

    bool getControlMouse() const;

private slots:

    void processData();

signals:

    void cursorTracking( QPoint target );

public slots:

    void setControlMouse( bool value );
};

#endif // CURSORCONTROLLER_HPP
