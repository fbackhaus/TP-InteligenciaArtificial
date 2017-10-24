QT += widgets opengl

INCLUDEPATH += "/usr/include/GL/"                            # OpenGL
LIBS += "/usr/lib/x86_64-linux-gnu/libglut.so"               # OpenGL
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_features2d.so"  # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_objdetect.so"   # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_stitching.so"   # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_videostab.so"   # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_highgui.so"     # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_imgproc.so"     # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_contrib.so"     # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_calib3d.so"     # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_legacy.so"      # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_photo.so"       # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_flann.so"       # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_video.so"       # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_core.so"        # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_gpu.so"         # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_ocl.so"         # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_ml.so"          # OpenCV
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_ts.so"          # OpenCV

SOURCES += \
    main.cpp \
    scene.cpp

HEADERS += \
    scene.h \
    texture.h
