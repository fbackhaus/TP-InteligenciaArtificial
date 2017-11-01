#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    ui->cameraGroupBox->setFixedSize(CCW_WIDTH, CCW_HEIGHT);

    ui->positionGrapher->setPoints( GestureRecognizer::getInstance()->getPositionVectors() );
    ui->velocityGrapher->setPoints( GestureRecognizer::getInstance()->getVelocityVectors() );

    this->connect( ui->calibrateButton, SIGNAL( pressed() ), ui->cursorControllerWidget, SLOT( calibrate() ) );
    this->connect( ui->showProcessingCheckbox, SIGNAL( toggled( bool ) ), ui->cursorControllerWidget, SLOT( changeShowProcessing( bool ) ) );
    this->connect( ui->controlMouseCheckbox, SIGNAL( toggled( bool ) ), ui->cursorControllerWidget->getController(), SLOT( setControlMouse( bool ) ) );
    this->connect( ui->controlMouseCheckbox, SIGNAL( toggled( bool ) ), ui->calibrateButton, SLOT( setDisabled( bool ) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}


