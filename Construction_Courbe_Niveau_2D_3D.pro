QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cube.cpp \
    cubestate.cpp \
    lagrangeinterpolation.cpp \
    lookuptable.cpp \
    lookuptablecube.cpp \
    main.cpp \
    marchingcube.cpp \
    marchingsquare.cpp \
    splineinterpolation.cpp \
    square.cpp \
    squarestate.cpp \
    linearinterpolation.cpp\
    bilinearinterpolation.cpp \
    unionfind.cpp \
    akimainterpolation.cpp

HEADERS += \
    cube.h \
    cubestate.h \
    lagrangeinterpolation.h \
    lookuptable.h \
    lookuptablecube.h \
    marchingcube.h \
    marchingsquare.h \
    splineinterpolation.h \
    square.h \
    squarestate.h \
    linearinterpolation.h\
    bilinearinterpolation.h \
    unionfind.h \
    akimainterpolation.h


RESOURCES = Data

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix: INCLUDEPATH += /usr/local/include/
unix: LIBS += -L/usr/local/li -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lgmp

macx: LIBS += -L$$PWD/../../../../../usr/local/Cellar/opencv/4.5.1_3/lib/ -lopencv_core.4.5.1

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/opencv/4.5.1_3/include/opencv4
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/opencv/4.5.1_3/include/opencv4

macx: LIBS += -L$$PWD/../../../../../usr/local/Cellar/opencv/4.5.1_3/lib/ -lopencv_imgcodecs.4.5.1

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/opencv/4.5.1_3/include/opencv4
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/opencv/4.5.1_3/include/opencv4

macx: LIBS += -L$$PWD/../../../../../usr/local/Cellar/opencv/4.5.1_3/lib/ -lopencv_highgui.4.5.1

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/opencv/4.5.1_3/include/opencv4
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/opencv/4.5.1_3/include/opencv4


macx: LIBS += -L$$PWD/../../../../../usr/local/Cellar/gmp/6.2.1/lib/ -lgmp.10

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/gmp/6.2.1/include
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/gmp/6.2.1/include

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp
