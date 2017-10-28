#-------------------------------------------------
#
# Proyecto para CoNaIISI - Investigacion
#
#-------------------------------------------------

QT += core gui opengl network multimedia widgets

TARGET   = RCM-RA
TEMPLATE = app

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

LIBS += -L/usr/local/Cellar/opencv@2/2.4.13.4/lib/

SOURCES += main.cpp\
           mainwindow.cpp \
           scene.cpp \
           aruco/ar_omp.cpp \
           aruco/arucofidmarkers.cpp \
           aruco/board.cpp \
           aruco/boarddetector.cpp \
           aruco/cameraparameters.cpp \
           aruco/chromaticmask.cpp \
           aruco/cvdrawingutils.cpp \
           aruco/highlyreliablemarkers.cpp \
           aruco/marker.cpp \
           aruco/markerdetector.cpp \
           aruco/subpixelcorner.cpp

HEADERS += mainwindow.h \
           model.h \
           scene.h \
           texture.h \
           video.h \
           webimage.h \
           webmusic.h \
           logo.h \
           aruco/ar_omp.h \
           aruco/aruco.h \
           aruco/arucofidmarkers.h \
           aruco/board.h \
           aruco/boarddetector.h \
           aruco/cameraparameters.h \
           aruco/chromaticmask.h \
           aruco/cvdrawingutils.h \
           aruco/exports.h \
           aruco/highlyreliablemarkers.h \
           aruco/marker.h \
           aruco/markerdetector.h \
           aruco/subpixelcorner.h

FORMS   += mainwindow.ui
