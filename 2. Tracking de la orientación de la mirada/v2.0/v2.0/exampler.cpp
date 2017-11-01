#include "exampler.hpp"

Exampler *Exampler::instance = NULL;

Exampler::Exampler( QObject *parent ) :
    QThread( parent )
{

}

Exampler *Exampler::getInstance()
{
    if( instance == NULL )
    {
        instance = new Exampler( NULL );
    }
    return instance;
}

Exampler::~Exampler()
{

}

void Exampler::run()
{
    system( this->getCurrentExample().toStdString().c_str() );
}

QString Exampler::getCurrentExample() const
{
    return currentExample;
}

void Exampler::setCurrentExample( const QString &value )
{
    currentExample = value;
}
