QT += widgets opengl

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

LIBS += -L/usr/local/Cellar/opencv@2/2.4.13.4/lib/

SOURCES += \
    main.cpp \
    scene.cpp

HEADERS += \
    scene.h \
    texture.h
