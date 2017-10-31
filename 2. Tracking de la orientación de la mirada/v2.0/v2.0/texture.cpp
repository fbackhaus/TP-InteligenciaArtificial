#include "texture.hpp"

Texture::Texture( QString name, QObject *parent ) :
    QObject( parent )
{
    this->setName( name );
    this->setId( new GLuint() );
    this->setMat( new Mat() );
    glGenTextures( 1, this->getId() );
}

Texture::~Texture()
{
    delete this->getId();
    delete this->getMat();
}

QString Texture::getName() const
{
    return name;
}

void Texture::setName( const QString &value )
{
    name = value;
}

Mat *Texture::getMat() const
{
    return mat;
}

void Texture::setMat( Mat *value )
{
    mat = value;
}

GLuint *Texture::getId() const
{
    return id;
}

void Texture::setId( GLuint *value )
{
    id = value;
}

void Texture::generateFromMat()
{
    glBindTexture( GL_TEXTURE_2D, *this->getId() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB,
                  this->getMat()->cols,
                  this->getMat()->rows,
                  1, GL_BGR, GL_UNSIGNED_BYTE,
                  this->getMat()->data );
}
