#ifndef GRAPHER_HPP
#define GRAPHER_HPP

// qt includes
#include <QWidget>
#include <QVector>
#include <QPointF>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QPalette>

class Grapher : public QWidget
{
    Q_OBJECT

private:

    QVector< QPointF > *points;
    QTimer *updateTimer;

public:

    explicit Grapher( QWidget *parent = NULL );

    QVector< QPointF > *getPoints() const;
    void setPoints( QVector< QPointF > *value );

    QTimer *getUpdateTimer() const;
    void setUpdateTimer( QTimer *value );

protected:

    void paintEvent( QPaintEvent* );
};

#endif // GRAPHER_HPP
