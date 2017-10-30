#-------------------------------------------------
#
# Proyecto para CoNaIISI - Investigacion
#
#-------------------------------------------------

QT += core gui opengl network widgets

TARGET   = RCM-RA
TEMPLATE = app

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

INCLUDEPATH += /usr/local/Cellar/lib3ds/1.3.0/include
DEPENDPATH += /usr/local/Cellar/lib3ds/1.3.0/include

LIBS += -L/usr/local/Cellar/opencv@2/2.4.13.4/lib/

SOURCES += main.cpp\
           scene.cpp

HEADERS += \
           model.h \
           scene.h \
           texture.h
