QT += widgets opengl

LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_core.so"
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_video.so"
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_highgui.so"
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_imgproc.so"
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_objdetect.so"

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
