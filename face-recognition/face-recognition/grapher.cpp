#include "grapher.hpp"

Grapher::Grapher( QWidget *parent ) :
    QWidget( parent )
{
    this->setPoints( NULL );

    this->setUpdateTimer( new QTimer( this ) ) ;
    this->getUpdateTimer()->setInterval( 10 );
    this->connect( this->getUpdateTimer(), SIGNAL( timeout() ), this, SLOT( repaint() ) );
    this->getUpdateTimer()->start();

    this->setAutoFillBackground( true );
    QPalette palette( this->palette() );
    palette.setColor( QPalette::Background, QColor( 200, 200, 200 ) );
    this->setPalette( palette );
}

QVector< QPointF > *Grapher::getPoints() const
{
    return points;
}

void Grapher::setPoints( QVector< QPointF > *value )
{
    points = value;
}

QTimer *Grapher::getUpdateTimer() const
{
    return updateTimer;
}

void Grapher::setUpdateTimer( QTimer *value )
{
    updateTimer = value;
}

void Grapher::paintEvent( QPaintEvent* )
{
    QPainter painter( this );

    QPen pen;

    /// points

    pen.setWidth( 2 );
    pen.setStyle( Qt::SolidLine );
    pen.setBrush( Qt::red );
    painter.setPen( pen );

    if( this->getPoints() != NULL &&
        this->getPoints()->size() > 0 )
    {
        QPointF minimum( this->getPoints()->at( 0 ) );
        QPointF maximum( this->getPoints()->at( 0 ) );

        for( int i = 0; i < this->getPoints()->size(); i++ )
        {
            if( this->getPoints()->at( i ).x() < minimum.x() )
            {
                minimum.setX( this->getPoints()->at( i ).x() );
            }
            if( this->getPoints()->at( i ).y() < minimum.y() )
            {
                minimum.setY( this->getPoints()->at( i ).y() );
            }
            if( this->getPoints()->at( i ).x() > maximum.x() )
            {
                maximum.setX( this->getPoints()->at( i ).x() );
            }
            if( this->getPoints()->at( i ).y() > maximum.y() )
            {
                maximum.setY( this->getPoints()->at( i ).y() );
            }
        }

        float maxXDiff = maximum.x() - minimum.x();
        float maxYDiff = maximum.y() - minimum.y();

        if( maxXDiff != 0 && maxYDiff != 0 )
        {
            for( int i = 0; i < this->getPoints()->size(); i++ )
            {
                float x = ( this->getPoints()->at( i ).x() - minimum.x() ) * this->width() / ( double )maxXDiff;
                float y = ( this->getPoints()->at( i ).y() - minimum.y() ) * this->height() / ( double )maxYDiff;

                painter.drawPoint( QPointF( x, y ) );
            }
        }

        /// axis

        pen.setWidth( 1 );
        pen.setStyle( Qt::DashDotLine );
        pen.setBrush( Qt::black );
        painter.setPen( pen );

        painter.drawLine( QPointF( ( 0 - minimum.x() ) * this->width() / ( double )maxXDiff, 0 ),
                          QPointF( ( 0 - minimum.x() ) * this->width() / ( double )maxXDiff, this->height() ) );

        painter.drawLine( QPointF( 0, ( 0 - minimum.y() ) * this->height() / ( double )maxYDiff ),
                          QPointF( this->width(), ( 0 - minimum.y() ) * this->height() / ( double )maxYDiff ) );
    }
    else
    {

    }
}
