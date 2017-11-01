QT += widgets opengl

LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_core.so"
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_video.so"
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_highgui.so"
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_imgproc.so"
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_objdetect.so"

HEADERS += \
    cameraprocessor.hpp \
    test.hpp \
    scene.hpp \
    texture.hpp

SOURCES += \
    cameraprocessor.cpp \
    main.cpp \
    test.cpp \
    scene.cpp \
    texture.cpp

FORMS += \
    test.ui
