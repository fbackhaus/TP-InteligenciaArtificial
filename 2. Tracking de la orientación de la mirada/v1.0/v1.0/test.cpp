#include "test.hpp"
#include "ui_test.h"

Test::Test( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::Test )
{
    ui->setupUi( this );
    ui->sceneWidget->setFixedSize( 640, 480 );

    this->connect( this->ui->calibrateButton, SIGNAL( pressed() ), this, SLOT( calibrate() ) );
    this->connect( CameraProcessor::getInstance(), SIGNAL( calibration( bool ) ), this, SLOT( cameraCalibration( bool ) ) );
    this->connect( CameraProcessor::getInstance(), SIGNAL( tracking( QPoint ) ), this, SLOT( cameraTracking( QPoint ) ) );

    trackMouse = false;

    x = 640;
    X = 0;
    y = 480;
    Y = 0;
}

Test::~Test()
{
    delete ui;
}

void Test::keyPressEvent( QKeyEvent *event )
{
    if( event->key() == Qt::Key_C )
    {
        this->calibrate();
    }
    if( event->key() == Qt::Key_M )
    {
        trackMouse = !trackMouse;
    }
}

void Test::calibrate()
{
    x = 640;
    X = 0;
    y = 480;
    Y = 0;
    CameraProcessor::getInstance()->setNeedCalibrate( true );
}

void Test::cameraCalibration( bool success )
{
    ui->messageLabel->setText( success ? "Calibración exitosa" : "No se detectó ningún rostro" );
}

#include <QDebug>

void Test::cameraTracking( QPoint target )
{
    // Mapping

    if( target.x() < x ) x = target.x();
    if( target.x() > X ) X = target.x();

    if( target.y() < y ) y = target.y();
    if( target.y() > Y ) Y = target.y();

    if( X - x != 0 &&
        Y - y != 0 )
    {
        int _x = ( 1366 - ( ( X - target.x() ) * 1366  / ( X - x ) ));
        int _y = ( 768  - ( ( Y - target.y() ) * 768 / ( Y - y ) ));

        if( trackMouse )
        {
            qDebug() << _x << _y;
            QCursor::setPos( QPoint( _x, _y ) );
        }
    }
}
