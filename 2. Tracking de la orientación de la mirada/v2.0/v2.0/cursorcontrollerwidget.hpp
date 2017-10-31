#ifndef CURSORCONTROLLERWIDGET_HPP
#define CURSORCONTROLLERWIDGET_HPP

#define RESOLUTION_WIDTH    640
#define RESOLUTION_HEIGHT   480

// qt includes
#include <QTimer>
#include <QGLWidget>
#include <QKeyEvent>

// project includes
#include "cursorcontroller.hpp"
#include "texture.hpp"

class CursorControllerWidget : public QGLWidget
{
    Q_OBJECT

private:

    CursorController *controller;
    Texture *controllerTexture;
    QTimer *widgetUpdater;

public:

    CursorControllerWidget( QWidget *parent = 0 );
    ~CursorControllerWidget();

    CursorController *getController() const;
    void setController( CursorController *value );

    Texture *getControllerTexture() const;
    void setControllerTexture( Texture *value );

    QTimer *getWidgetUpdater() const;
    void setWidgetUpdater( QTimer *value );

protected:

    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();

    void keyPressEvent( QKeyEvent *event );

private slots:

    void updateWidget();

public slots:

    void calibrate();
    void changeShowProcessing( bool show );
};

#endif // CURSORCONTROLLERWIDGET_HPP
