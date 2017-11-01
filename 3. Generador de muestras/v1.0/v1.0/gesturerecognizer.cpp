#include "gesturerecognizer.hpp"

GestureRecognizer *GestureRecognizer::instance = NULL;

GestureRecognizer::GestureRecognizer( QObject *parent ) :
    QObject( parent )
{
    this->setPositionVectors( new QVector< QPointF >() );
    this->setVelocityVectors( new QVector< QPointF >() );

    this->setLogActive( false );
    this->setLogBaseName( "" );
    this->setLogCounter( 0 );
    this->setCurrentLogFile( NULL );
    this->setDataStream( new QTextStream() );
}

GestureRecognizer *GestureRecognizer::getInstance()
{
    if( instance == NULL )
    {
        instance = new GestureRecognizer( NULL );
    }
    return instance;
}

GestureRecognizer::~GestureRecognizer()
{
    delete this->getInstance();
    delete this->getPositionVectors();
    delete this->getVelocityVectors();

    if( this->getCurrentLogFile() != NULL )
    {
        delete this->getCurrentLogFile();
    }

    delete this->getDataStream();
}

QVector< QPointF > *GestureRecognizer::getPositionVectors() const
{
    return positionVectors;
}

void GestureRecognizer::setPositionVectors( QVector< QPointF > *value )
{
    positionVectors = value;
}

QVector< QPointF > *GestureRecognizer::getVelocityVectors() const
{
    return velocityVectors;
}

void GestureRecognizer::setVelocityVectors( QVector< QPointF > *value )
{
    velocityVectors = value;
}

QString GestureRecognizer::getLogBaseName() const
{
    return logBaseName;
}

void GestureRecognizer::setLogBaseName( const QString &value )
{
    logBaseName = value;
}

bool GestureRecognizer::getLogActive() const
{
    return logActive;
}

void GestureRecognizer::setLogActive( bool value )
{
    logActive = value;
}

int GestureRecognizer::getLogCounter() const
{
    return logCounter;
}

void GestureRecognizer::setLogCounter( int value )
{
    logCounter = value;
}

QFile *GestureRecognizer::getCurrentLogFile() const
{
    return currentLogFile;
}

void GestureRecognizer::setCurrentLogFile( QFile *value )
{
    currentLogFile = value;
}

QTextStream *GestureRecognizer::getDataStream() const
{
    return dataStream;
}

void GestureRecognizer::setDataStream( QTextStream *value )
{
    dataStream = value;
}

void GestureRecognizer::addPosition( QPointF position )
{
    this->getPositionVectors()->append( position );

    if( this->getPositionVectors()->size() > MAX_POSITIONS )
    {
        this->getPositionVectors()->removeFirst();
    }
}

void GestureRecognizer::addVelocity( QPointF velocity )
{
    this->getVelocityVectors()->append( velocity );

    if( this->getVelocityVectors()->size() > MAX_VELOCITIES )
    {
        this->getVelocityVectors()->removeFirst();
    }
}

void GestureRecognizer::initLog()
{
    this->setCurrentLogFile( new QFile( "../logs/" +
                                        this->getLogBaseName() + "_" +
                                        QString::number( this->getLogCounter() ) +
                                        ".txt" ) );

    this->getCurrentLogFile()->open( QIODevice::WriteOnly | QIODevice::Text );

    this->getDataStream()->setDevice( this->getCurrentLogFile() );

    this->setLogActive( true );
}

void GestureRecognizer::recognize()
{
    /// recognition

    /***
     *
     * REGISTRO DE VALORES PARA GENERAR CLASIFICADORES
     * -----------------------------------------------
     *
     * Los vectores de posiciones y de velocidades contienen un conjunto de los últimos X
     * valores tomados. En este caso, la cantidad de valores almacenados se encuentran en
     * las constantes MAX_POSITIONS y MAX_VELOCITIES respectivamente.
     *
     * Si queremos loguear los valores de las posición/velocidad tomados entre dos eventos
     * (por ejemplo, click del mouse) es importante que consideremos el último valor de cada
     * vector, ya que éste nos devolverá la última información, es decir, la del frame actual.
     *
     * Los últimos valores se encuentran en:
     *
     * this->getPositionVectors()->last();
     * this->getVelocityVectors()->last();
     *
     * Esta clase (GestureRecognizer) emitirá entonces los valores que otra clase recibirá
     * para loguear. Los valores se emitirán desde este método o se consultarán mediante
     * la instancia Singleton declarada en esta clase GestureRecognizer::getInstance().
     *
     ***/

    if( this->getLogActive() && this->getCurrentLogFile()->isOpen() )
    {
        QString valueString( QString::number( this->getVelocityVectors()->last().x() ) +
                             "\t\t" +
                             QString::number( this->getVelocityVectors()->last().y() ) );

        this->getDataStream()->operator << ( valueString + "\n" );
    }
}

void GestureRecognizer::finishLog()
{
    this->getCurrentLogFile()->close();

    delete this->getCurrentLogFile();

    this->setLogActive( false );

    this->setLogCounter( this->getLogCounter() + 1 );
}
