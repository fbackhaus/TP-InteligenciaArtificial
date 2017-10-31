#ifndef GESTURERECOGNIZER_HPP
#define GESTURERECOGNIZER_HPP

#define MAX_POSITIONS  500
#define MAX_VELOCITIES 500

// qt includes
#include <QObject>
#include <QVector>
#include <QPointF>
#include <QString>
#include <QFile>
#include <QTextStream>

class GestureRecognizer : public QObject
{
    Q_OBJECT

private:

    explicit GestureRecognizer( QObject *parent = NULL );
    static GestureRecognizer *instance;

    QVector< QPointF > *positionVectors;
    QVector< QPointF > *velocityVectors;

    bool logActive;
    QString logBaseName;
    int logCounter;
    QFile *currentLogFile;
    QTextStream *dataStream;

public:

    static GestureRecognizer *getInstance();
    ~GestureRecognizer();

    QVector< QPointF > *getPositionVectors() const;
    void setPositionVectors( QVector< QPointF > *value );

    QVector< QPointF > *getVelocityVectors() const;
    void setVelocityVectors( QVector< QPointF > *value );

    QString getLogBaseName() const;
    void setLogBaseName( const QString &value );

    bool getLogActive() const;
    void setLogActive( bool value );

    int getLogCounter() const;
    void setLogCounter( int value );

    QFile *getCurrentLogFile() const;
    void setCurrentLogFile( QFile *value );

    QTextStream *getDataStream() const;
    void setDataStream( QTextStream *value );

    void addPosition( QPointF position );
    void addVelocity( QPointF velocity );

public slots:

    void initLog();
    void recognize();
    void finishLog();
};

#endif // GESTURERECOGNIZER_HPP
