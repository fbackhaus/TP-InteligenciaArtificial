#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow )
{
    ui->setupUi( this );

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
}

MainWindow::~MainWindow()
{
    delete ui;
}
