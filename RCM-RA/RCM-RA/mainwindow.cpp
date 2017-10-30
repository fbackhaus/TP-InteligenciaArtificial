#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent ) : QWidget( parent ),
                                            ui( new Ui::MainWindow ),
                                            suggestionsManager( new QNetworkAccessManager( this ) )
{
    ui->setupUi( this );
    ui->mainWindowLayout->setColumnStretch( 0, 1 );

    this->setFont( QFont( "Tahoma", 8 ) );

    connect( ui->fullScreenPushButton, SIGNAL( clicked() ), SLOT( slot_fullScreenPushButtonClicked() ) );

    connect( ui->searchImagesLineEdit, SIGNAL( textChanged( QString ) ), SLOT( slot_searchTextChanged( QString ) ) );
    connect( ui->searchMusicLineEdit, SIGNAL( textChanged( QString ) ), SLOT( slot_searchTextChanged( QString ) ) );
    connect( suggestionsManager, SIGNAL( finished( QNetworkReply* ) ), SLOT( slot_suggestionsDownloaded( QNetworkReply* ) ) );
    connect( ui->scene, SIGNAL( message( QString ) ), SLOT( slot_writeMessage( QString ) ) );

    connect( ui->searchImagesLineEdit, SIGNAL( returnPressed() ), SLOT( slot_searchImagesButtonClicked() ) );
    connect( ui->searchImagesButton, SIGNAL( clicked() ), SLOT( slot_searchImagesButtonClicked() ) );

    connect( ui->searchMusicLineEdit, SIGNAL( returnPressed() ), SLOT( slot_searchMusicButtonClicked() ) );
    connect( ui->searchMusicButton, SIGNAL( clicked() ), SLOT( slot_searchMusicButtonClicked() ) );

    connect( ui->detectMarkersCheckBox, SIGNAL( toggled( bool ) ), SLOT( slot_detectMarkersCheckBoxValueChanged( bool ) ) );
    connect( ui->rotateCheckBox, SIGNAL( toggled( bool ) ), SLOT( slot_rotateCheckBoxValueChanged( bool ) ) );
    connect( ui->rotationVelocitySlider, SIGNAL( valueChanged( int ) ), SLOT( slot_rotationVelocitySliderValueChanged( int ) ) );
    connect( ui->descriptionCheckBox, SIGNAL( toggled( bool ) ), SLOT( slot_descriptionCheckBoxValueChanged( bool ) ) );
    connect( ui->scaleSpinBox, SIGNAL( valueChanged( int ) ), SLOT( slot_scaleSpinBoxValueChanged( int ) ) );

    connect( ui->xTranslationSpinBox, SIGNAL( valueChanged( double ) ), SLOT( slot_xTranslationSpinBoxValueChanged( double ) ) );
    connect( ui->yTranslationSpinBox, SIGNAL( valueChanged( double ) ), SLOT( slot_yTranslationSpinBoxValueChanged( double ) ) );
    connect( ui->zTranslationSpinBox, SIGNAL( valueChanged( double ) ), SLOT( slot_zTranslationSpinBoxValueChanged( double ) ) );

    connect( ui->xRotationSpinBox, SIGNAL( valueChanged( int ) ), SLOT( slot_xRotationSpinBoxValueChanged( int ) ) );
    connect( ui->yRotationSpinBox, SIGNAL( valueChanged( int ) ), SLOT( slot_yRotationSpinBoxValueChanged( int ) ) );
    connect( ui->zRotationSpinBox, SIGNAL( valueChanged( int ) ), SLOT( slot_zRotationSpinBoxValueChanged( int ) ) );
}

void MainWindow::enableImagesSearch()
{
    ui->searchImagesButton->setText( "Buscar" );
    ui->searchImagesButton->setEnabled( true );
    ui->searchImagesLineEdit->setEnabled( true );
    ui->searchImagesLineEdit->setFocus();
    ui->searchImagesLineEdit->selectAll();
}

void MainWindow::enableMusicSearch()
{
    ui->searchMusicButton->setText( "Buscar" );
    ui->searchMusicButton->setEnabled( true );
    ui->searchMusicLineEdit->setEnabled( true );
    ui->searchMusicLineEdit->setFocus();
    ui->searchMusicLineEdit->selectAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_fullScreenPushButtonClicked()
{
    this->setVisible( false );
    ui->scene->setParent( NULL );
    ui->scene->showFullScreen();
}

void MainWindow::slot_searchTextChanged( QString search )
{
    suggestionsManager->get( QNetworkRequest( QUrl( "https://www.google.com/complete/search?output=toolbar&q=" + search ) ) );
}

void MainWindow::slot_suggestionsDownloaded( QNetworkReply *reply )
{
    QString xmlCode = QString::fromUtf8( reply->readAll() );

    QString preSuggestionCode = "<suggestion data=\"";
    QString postSuggestionCode = "\"/>";

    QStringList *suggestions = new QStringList;

    while( xmlCode.contains( preSuggestionCode ) )
    {
        xmlCode.remove( 0, xmlCode.indexOf( preSuggestionCode ) + preSuggestionCode.size() );
        suggestions->append( xmlCode.mid( 0, xmlCode.indexOf( postSuggestionCode ) ) );
    }

    QCompleter *completer = new QCompleter( *suggestions );
    completer->setCaseSensitivity( Qt::CaseInsensitive );
    completer->setCompletionMode( QCompleter::InlineCompletion );

    ui->searchImagesLineEdit->setCompleter( completer );
    ui->searchMusicLineEdit->setCompleter( completer );
}

void MainWindow::slot_writeMessage( QString text )
{
    ui->messagesTextEdit->append( text );
}

void MainWindow::slot_searchImagesButtonClicked()
{
    ui->searchImagesLineEdit->setText( ui->searchImagesLineEdit->text().simplified() );
    if( ui->searchImagesLineEdit->text() == "" )
    {
        ui->scene->setWebImageTextureId( 0 );
        return;
    }

    ui->searchImagesLineEdit->setEnabled( false );
    ui->searchImagesButton->setEnabled( false );
    ui->searchImagesButton->setText( "Buscando" );


    WebImage *webImage = new WebImage( this );

    if( ui->allImagesButton->isChecked() )
    {
        ui->messagesTextEdit->append( "Buscando imagenes: " + ui->searchImagesLineEdit->text() + "..." );
        webImage->searchForAllImages( ui->searchImagesLineEdit->text() );
    }
    if( ui->streetViewImagesButton->isChecked() )
    {
        ui->messagesTextEdit->append( "Buscando lugar: " + ui->searchImagesLineEdit->text() + "..." );
        webImage->searchForStreetViewImage( ui->searchImagesLineEdit->text() );
    }

    connect( webImage, SIGNAL( notImage() ), SLOT( slot_webImageNotImage() ) );
    connect( webImage, SIGNAL( imageReady( GLuint ) ), SLOT( slot_webImageReady( GLuint ) ) );
}

void MainWindow::slot_webImageNotImage()
{
    ui->messagesTextEdit->append( "<div style=\"color:red;\">Imagen: Sin resultados</div>" );
    ui->scene->setWebImageTextureId( 0 );
    enableImagesSearch();
}

void MainWindow::slot_webImageReady( GLuint textureId )
{
    ui->messagesTextEdit->append( "<div style=\"color:green;\">Imagen descargada</div>" );
    ui->scene->setWebImageTextureId( textureId );
    enableImagesSearch();
}

void MainWindow::slot_searchMusicButtonClicked()
{
    ui->searchMusicLineEdit->setText( ui->searchMusicLineEdit->text().simplified() );
    if( ui->searchMusicLineEdit->text() == "" )
    {
        ui->scene->setWebMusicImageTextureId( 0 );
        ui->scene->setWebMusicPlayerMedia( "" );
        return;
    }

    ui->searchMusicLineEdit->setEnabled( false );
    ui->searchMusicButton->setEnabled( false );
    ui->searchMusicButton->setText( "Buscando" );

    ui->messagesTextEdit->append( "Buscando musica: " + ui->searchMusicLineEdit->text() + "..." );

    WebMusic *webMusic = new WebMusic( this );
    webMusic->searchMusic( ui->searchMusicLineEdit->text() );

    connect( webMusic, SIGNAL( notMusic() ), SLOT( slot_webMusicNotMusic() ) );
    connect( webMusic, SIGNAL( musicReady( QString ) ), SLOT( slot_webMusicReady( QString ) ) );
    connect( webMusic, SIGNAL( musicImageReady( GLuint ) ), SLOT( slot_webMusicAssociatedImageReady( GLuint ) ) );
}

void MainWindow::slot_webMusicNotMusic()
{
    ui->messagesTextEdit->append( "<div style=\"color:red;\">Musica: Sin resultados</div>" );
    ui->scene->setWebMusicPlayerMedia( "" );
    enableMusicSearch();
}

void MainWindow::slot_webMusicReady( QString uri )
{
    ui->messagesTextEdit->append( "<div style=\"color:green;\">Musica encontrada</div>" );
    ui->messagesTextEdit->append( "Reproduciendo desde: " + uri );
    ui->scene->setWebMusicPlayerMedia( uri );
    enableMusicSearch();
}

void MainWindow::slot_webMusicAssociatedImageReady( GLuint textureId )
{
    ui->messagesTextEdit->append( "<div style=\"color:green;\">Caratula encontrada</div>" );
    ui->scene->setWebMusicImageTextureId( textureId );
}

void MainWindow::slot_detectMarkersCheckBoxValueChanged( bool checked )
{
    ui->scene->detectMarkersOption = checked;

    if( checked )
    {
        ui->rotateCheckBox->setEnabled( true );
        ui->descriptionCheckBox->setEnabled( true );
        ui->scaleLabel->setEnabled( true );
        ui->scaleSpinBox->setEnabled( true );
        ui->xTranslationLabel->setEnabled( true );
        ui->xTranslationSpinBox->setEnabled( true );
        ui->yTranslationLabel->setEnabled( true );
        ui->yTranslationSpinBox->setEnabled( true );
        ui->zTranslationLabel->setEnabled( true );
        ui->zTranslationSpinBox->setEnabled( true );
        ui->xRotationLabel->setEnabled( true );
        ui->xRotationSpinBox->setEnabled( true );
        ui->yRotationLabel->setEnabled( true );
        ui->yRotationSpinBox->setEnabled( true );
        ui->zRotationLabel->setEnabled( true );
        ui->zRotationSpinBox->setEnabled( true );
    }
    else
    {
        ui->rotateCheckBox->setEnabled( false );
        ui->rotateCheckBox->setChecked( false );
        ui->descriptionCheckBox->setEnabled( false );
        ui->scaleLabel->setEnabled( false );
        ui->scaleSpinBox->setEnabled( false );
        ui->xTranslationLabel->setEnabled( false );
        ui->xTranslationSpinBox->setEnabled( false );
        ui->yTranslationLabel->setEnabled( false );
        ui->yTranslationSpinBox->setEnabled( false );
        ui->zTranslationLabel->setEnabled( false );
        ui->zTranslationSpinBox->setEnabled( false );
        ui->xRotationLabel->setEnabled( false );
        ui->xRotationSpinBox->setEnabled( false );
        ui->yRotationLabel->setEnabled( false );
        ui->yRotationSpinBox->setEnabled( false );
        ui->zRotationLabel->setEnabled( false );
        ui->zRotationSpinBox->setEnabled( false );
    }
}

void MainWindow::slot_rotateCheckBoxValueChanged( bool checked )
{
    ui->scene->rotateOption = checked;

    if( checked )
    {
        ui->rotationVelocityLabel->setEnabled( true );
        ui->rotationVelocitySlider->setEnabled( true );
        ui->yRotationLabel->setEnabled( false );
        ui->yRotationSpinBox->setEnabled( false );
    }
    else
    {
        ui->rotationVelocityLabel->setEnabled( false );
        ui->rotationVelocitySlider->setEnabled( false );
        ui->yRotationLabel->setEnabled( true );
        ui->yRotationSpinBox->setEnabled( true );
        ui->yRotationSpinBox->setValue( 0 );
        slot_yRotationSpinBoxValueChanged( ui->yRotationSpinBox->value() );
    }
}

void MainWindow::slot_rotationVelocitySliderValueChanged( int value )
{
    ui->scene->rotationVelocityOption = value;
}

void MainWindow::slot_descriptionCheckBoxValueChanged( bool checked )
{
    ui->scene->descriptionOption = checked;
}

void MainWindow::slot_scaleSpinBoxValueChanged( int value )
{
    ui->scene->scaleOption = value;
}

void MainWindow::slot_xTranslationSpinBoxValueChanged( double value )
{
    ui->scene->xTranslationOption = value;
}

void MainWindow::slot_yTranslationSpinBoxValueChanged( double value )
{
    ui->scene->yTranslationOption = value;
}

void MainWindow::slot_zTranslationSpinBoxValueChanged( double value )
{
    ui->scene->zTranslationOption = value;
}

void MainWindow::slot_xRotationSpinBoxValueChanged( int value )
{
    if( value == -360 || value == 360 ) ui->xRotationSpinBox->setValue( 0 );
    ui->scene->xRotationOption = value;
}

void MainWindow::slot_yRotationSpinBoxValueChanged( int value )
{
    if( value == -360 || value == 360 ) ui->yRotationSpinBox->setValue( 0 );
    ui->scene->yRotationOption = value;
}

void MainWindow::slot_zRotationSpinBoxValueChanged( int value )
{
    if( value == -360 || value == 360 ) ui->zRotationSpinBox->setValue( 0 );
    ui->scene->zRotationOption = value;
}
