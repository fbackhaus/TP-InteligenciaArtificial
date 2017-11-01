#ifndef EXAMPLER_HPP
#define EXAMPLER_HPP

#include <QThread>

class Exampler : public QThread
{
    Q_OBJECT

private:

    explicit Exampler( QObject *parent = NULL );
    static Exampler *instance;

    QString currentExample;

    void run();

public:

    static Exampler *getInstance();
    ~Exampler();

    QString getCurrentExample() const;
    void setCurrentExample( const QString &value );
};

#endif // EXAMPLER_HPP
