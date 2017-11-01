#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    this->setLogging( false );

    ui->brightnessSlider->setValue( CameraProcessor::getInstance()->getFrameCapturerBrightness() );
    ui->contrastSlider->setValue( CameraProcessor::getInstance()->getFrameCapturerContrast() );
    ui->saturationSlider->setValue( CameraProcessor::getInstance()->getFrameCapturerSaturation() );
    ui->hueSlider->setValue( CameraProcessor::getInstance()->getFrameCapturerHue() );

    ui->positionGrapher->setPoints( GestureRecognizer::getInstance()->getPositionVectors() );
    ui->velocityGrapher->setPoints( GestureRecognizer::getInstance()->getVelocityVectors() );

    this->connect( ui->calibrateButton, SIGNAL( pressed() ), ui->cursorControllerWidget, SLOT( calibrate() ) );
    this->connect( ui->showProcessingCheckbox, SIGNAL( toggled( bool ) ), ui->cursorControllerWidget, SLOT( changeShowProcessing( bool ) ) );
    this->connect( ui->controlMouseCheckbox, SIGNAL( toggled( bool ) ), ui->cursorControllerWidget->getController(), SLOT( setControlMouse( bool ) ) );
    this->connect( ui->controlMouseCheckbox, SIGNAL( toggled( bool ) ), ui->calibrateButton, SLOT( setDisabled( bool ) ) );

    this->connect( ui->brightnessSlider, SIGNAL( valueChanged( int ) ), CameraProcessor::getInstance(), SLOT( setFrameCapturerBrightness( int ) ) );
    this->connect( ui->contrastSlider, SIGNAL( valueChanged( int ) ), CameraProcessor::getInstance(), SLOT( setFrameCapturerContrast( int ) ) );
    this->connect( ui->saturationSlider, SIGNAL( valueChanged( int ) ), CameraProcessor::getInstance(), SLOT( setFrameCapturerSaturation( int ) ) );
    this->connect( ui->hueSlider, SIGNAL( valueChanged( int ) ), CameraProcessor::getInstance(), SLOT( setFrameCapturerHue( int ) ) );

    this->connect( ui->loggerButton, SIGNAL( pressed() ), this, SLOT( log() ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::getLogging() const
{
    return logging;
}

void MainWindow::setLogging(bool value)
{
    logging = value;
}

void MainWindow::log()
{
    this->setLogging( !this->getLogging() );

    if( this->getLogging() )
    {
        GestureRecognizer::getInstance()->setLogBaseName( ui->loggerBaseNameLineEdit->text().trimmed() );
        GestureRecognizer::getInstance()->initLog();
        ui->loggerButton->setText( "Detener" );
    }
    else
    {
        GestureRecognizer::getInstance()->finishLog();
        ui->loggerButton->setText( "Iniciar" );
    }
}
