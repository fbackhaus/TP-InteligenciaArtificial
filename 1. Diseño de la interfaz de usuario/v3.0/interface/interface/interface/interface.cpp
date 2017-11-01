#include "interface.hpp"
#include "ui_interface.h"

Interface::Interface( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::Interface )
{
    this->setGraph( new Graph( this ) );
    this->setCamera( new Camera( this ) );
    this->setBlockSelectionTimer( new QTimer( this ) );
    this->setBlockSelection( false );
    this->setSpeaker( new Speech( this ) );

    ui->setupUi( this );
    ui->scrollArea->setFixedHeight( SCROLL_AREA_HEIGHT );
    this->setStyle();

    connect( this->ui->calibrateButton,
             SIGNAL( pressed() ),
             this->getCamera(),
             SLOT( calibrate() ) );

    connect( this->getCamera(),
             SIGNAL( positionDetected( int ) ),
             SLOT( activateBlock( int ) ) );

    connect( this->getCamera(),
             SIGNAL( selectionDetected( int ) ),
             SLOT( clickBlock( int ) ) );

    connect( blockSelectionTimer,
             SIGNAL( timeout() ),
             SLOT( unblockSelection() ) );
}

Interface::~Interface()
{

}

void Interface::setStyle()
{
    this->setAutoFillBackground( true );

    QPalette palette( this->palette() );
    palette.setColor( QPalette::Background, Colorizer::getInstance()->getTheme()->getBackgroundColor() );
    palette.setColor( QPalette::WindowText, QColor( Qt::white ) );
    this->setPalette( palette );
}

void Interface::changeStyle()
{
     Colorizer::getInstance()->getNextTheme();

     QList< Block* > blocksList = this->findChildren< Block* >();
     for( int i = 0; i < blocksList.size(); i++ )
     {
         blocksList.at( i )->setStyle( false );
     }

     this->setStyle();
}

Graph *Interface::getGraph() const
{
    return graph;
}

void Interface::setGraph( Graph *value )
{
    graph = value;
}

Camera *Interface::getCamera() const
{
    return camera;
}

void Interface::setCamera( Camera *value )
{
    camera = value;
}

QTimer *Interface::getBlockSelectionTimer() const
{
    return blockSelectionTimer;
}

void Interface::setBlockSelectionTimer( QTimer *value )
{
    blockSelectionTimer = value;
}

bool Interface::getBlockSelection() const
{
    return blockSelection;
}

void Interface::setBlockSelection( bool value )
{
    blockSelection = value;
}

Speech *Interface::getSpeaker() const
{
    return speaker;
}

void Interface::setSpeaker( Speech *value )
{
    speaker = value;
}

bool Interface::initInterface( QFile *file )
{
    if( !this->getGraph()->initGraph( file ) )
    {
        // No se pudo iniciar el grafo

        return false;
    }

    Node *initialNode = this->getGraph()->get( INITIAL_NODE_ID );

    if( !initialNode )
    {
        // No se encontro el nodo inicial

        return false;
    }

    this->createAndSet( initialNode );

    return true;
}

void Interface::keyPressEvent( QKeyEvent *event )
{
    switch( event->key() )
    {
    case Qt::Key_C:

        this->changeStyle();

        break;

    case Qt::Key_I:

        this->ui->sentenceLabel->clear();
        this->createAndSet( this->getGraph()->get( INITIAL_NODE_ID ) );

        break;

    default:

        break;
    }
}

void Interface::createAndSet( Node *node )
{
    QList< Block* > blocksList = this->findChildren< Block* >();
    qDeleteAll( blocksList );

    this->ui->nodeTitleLabel->setText( node->getTitle() );

    if( node->getText() != "" )
    {
        QString sentence( ui->sentenceLabel->text() );
        sentence.append( " " );
        sentence.append( node->getText().toUpper() );
        this->ui->sentenceLabel->setText( sentence );
    }

    if( node->getChildren().size() == 1 &&
        node->getChildren().at( 0 ) == "none" )
    {
        //this->getSpeaker()->read( this->ui->sentenceLabel->text() );
        return;
    }

    for( int i = 0; i < node->getChildren().size(); i++ )
    {
        Node *newNode = this->getGraph()->get( node->getChildren().at( i ) );

        if( newNode )
        {
            Block *block = new Block( newNode, this );
            this->ui->blocksLayout->addWidget( block );
            connect( block, SIGNAL( clicked( Node* ) ), SLOT( createAndSet( Node* ) ) );
        }
    }

    this->getCamera()->setSize( node->getChildren().size() );
}

void Interface::activateBlock( int index )
{
    QList< Block* > blocksList = this->findChildren< Block* >();
    if( index >= 0 && index < blocksList.size() )
    {
        for( int i = 0; i < blocksList.size(); i++ )
        {
            blocksList.at( i )->setActive( false );
        }
        blocksList.at( index )->setActive( true );
    }
}

void Interface::clickBlock( int index )
{
    if( !this->getBlockSelection() )
    {
        QString sound( APPLICATION_PATH );
        sound.append( SOUNDS_PATH );
        sound.append( "selected.wav" );
        QSound::play( sound );

        QList< Block* > blocksList = this->findChildren< Block* >();
        if( index >= 0 && index < blocksList.size() )
        {
            blocksList.at( index )->simulateClick();
        }

        this->setBlockSelection( true );
        blockSelectionTimer->start( 1000 );
    }
}

void Interface::unblockSelection()
{
    blockSelectionTimer->stop();
    this->setBlockSelection( false );
}
