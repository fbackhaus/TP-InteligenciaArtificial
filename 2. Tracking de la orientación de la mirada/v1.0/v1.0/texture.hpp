#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <QGLWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Texture : public QObject
{
    Q_OBJECT

private:

    QString name;
    GLuint *id;
    Mat *mat;

public:

    explicit Texture( QString name = "",
                      QObject *parent = 0 );
    ~Texture();

    void generateFromMat();

    QString getName() const;
    void setName( const QString &value );

    Mat *getMat() const;
    void setMat( Mat *value );

    GLuint *getId() const;
    void setId( GLuint *value );
};

#endif // TEXTURE_HPP
