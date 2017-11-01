#ifndef FACEDETECTOR_HPP
#define FACEDETECTOR_HPP

// qt includes
#include <QObject>
#include <QTimer>
#include <QPoint>
#include <QRect>

// std includes
#include <vector>

// opencv includes
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class FaceDetector : public QObject
{
    Q_OBJECT

private:

    explicit FaceDetector( QObject *parent = NULL );
    static FaceDetector *instance;

    CascadeClassifier *faceClassifier;

public:

    static FaceDetector *getInstance();
    ~FaceDetector();

    CascadeClassifier *getFaceClassifier() const;
    void setFaceClassifier( CascadeClassifier *value );

    QRect process( Mat *mat );
};

#endif // FACEDETECTOR_HPP
