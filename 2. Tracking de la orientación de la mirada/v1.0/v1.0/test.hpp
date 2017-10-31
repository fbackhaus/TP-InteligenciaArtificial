#ifndef TEST_HPP
#define TEST_HPP

#include <QWidget>
#include <QCursor>
#include <QKeyEvent>

#include "cameraprocessor.hpp"

namespace Ui
{
    class Test;
}

class Test : public QWidget
{
    Q_OBJECT

private:

    Ui::Test *ui;
    bool trackMouse;

    int x,X,y,Y;

public:

    explicit Test( QWidget *parent = NULL );
    ~Test();

protected:
    void keyPressEvent( QKeyEvent *event );

private slots:

    void calibrate();
    void cameraCalibration( bool success );
    void cameraTracking( QPoint target );

};

#endif // TEST_HPP
