#ifndef TEXTURE_HPP
#define TEXTURE_HPP

// qt includes
#include <QGLWidget>

// opencv includes
#include <opencv2/opencv.hpp>

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

    QString getName() const;
    void setName( const QString &value );

    Mat *getMat() const;
    void setMat( Mat *value );

    GLuint *getId() const;
    void setId( GLuint *value );

    void generateFromMat();
};

#endif // TEXTURE_HPP
