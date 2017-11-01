QT += widgets opengl

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

LIBS += -L/usr/local/Cellar/opencv@2/2.4.13.4/lib/

SOURCES += \
    main.cpp \
    cursorcontrollerwidget.cpp \
    cursorcontroller.cpp \
    cameraprocessor.cpp \
    texture.cpp \
    featuresprocessor.cpp \
    facedetector.cpp \
    gesturerecognizer.cpp \
    mainwindow.cpp \
    grapher.cpp \
    pointmapper.cpp \
    exampler.cpp

HEADERS += \
    cursorcontrollerwidget.hpp \
    cursorcontroller.hpp \
    cameraprocessor.hpp \
    texture.hpp \
    featuresprocessor.hpp \
    facedetector.hpp \
    gesturerecognizer.hpp \
    mainwindow.hpp \
    grapher.hpp \
    pointmapper.hpp \
    exampler.hpp

FORMS += \
    mainwindow.ui
