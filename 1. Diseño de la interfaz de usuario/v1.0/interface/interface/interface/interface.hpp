#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#define INITIAL_NODE_ID "inicio"

#include <QWidget>
#include <QPalette>
#include <QList>
#include <QKeyEvent>
#include <QSound>

#include "graph/graph.hpp"
#include "theme/colorizer.hpp"
#include "interface/block.hpp"
#include "processor/camera.hpp"

#include "common.hpp"

namespace Ui
{
    class Interface;
}

class Interface : public QWidget
{
    Q_OBJECT

private:

    Ui::Interface *ui;
    Graph *graph;
    Camera *camera;

    QTimer *blockSmileTimer;
    bool blockSmile;

    void setStyle();
    void changeStyle();

public:

    explicit Interface( QWidget *parent = NULL );
    ~Interface();

    Graph *getGraph() const;
    void setGraph( Graph *value );

    Camera *getCamera() const;
    void setCamera( Camera *value );

    QTimer *getBlockSmileTimer() const;
    void setBlockSmileTimer( QTimer *value );

    bool getBlockSmile() const;
    void setBlockSmile( bool value );

    bool initInterface( QFile *file );

protected:

    void keyPressEvent( QKeyEvent *event );

private slots:

    void createAndSet( Node *node );
    void activateBlock( int index );
    void clickBlock( int index );
    void unblockSmile();
};

#endif // INTERFACE_HPP

