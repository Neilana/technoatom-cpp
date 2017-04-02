TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    CPU.cpp \
    CPU.t.cpp

HEADERS += \
    CPU.h

# Google Test
unix|win32: LIBS += -L$$PWD/../../../googletest-master/googletest/lib/ -lgtest

INCLUDEPATH += $$PWD/../../../googletest-master/googletest/include
DEPENDPATH += $$PWD/../../../googletest-master/googletest/include

# Array, Vector, Stack
INCLUDEPATH += ../Containers \
            ../Containers/Vector \
            ../Containers/Array \
            ../Containers/ContainerInterface \
            ../../foreveralone/Stack
