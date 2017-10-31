QT += widgets multimedia

LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_core.so"
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_highgui.so"
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_imgproc.so"
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_objdetect.so"

LIBS += "/usr/lib/x86_64-linux-gnu/libespeak.so.1"

SOURCES += \
    main.cpp \
    graph/graph.cpp \
    graph/node.cpp \
    graph/xmlreader.cpp \
    theme/colorizer.cpp \
    theme/theme.cpp \
    interface/block.cpp \
    interface/interface.cpp \
    processor/camera.cpp \
    interface/image.cpp \
    speech.cpp

HEADERS += \
    graph/graph.hpp \
    graph/node.hpp \
    graph/xmlreader.hpp \
    theme/colorizer.hpp \
    theme/theme.hpp \
    interface/block.hpp \
    interface/interface.hpp \
    processor/camera.hpp \
    common.hpp \
    interface/image.hpp \
    speech.hpp

FORMS += \
    interface/interface.ui \
    interface/block.ui
