TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Array/Array.t.cpp \
    Vector/Vector.t.cpp \
    BitPointer.t.cpp \
    Vector/Vector.cpp \
    ContainerInterface/ContainerInterface.cpp
    
# Google Test
unix|win32: LIBS += -L$$PWD/../../../googletest-master/googletest/lib/ -lgtest

INCLUDEPATH += $$PWD/../../../googletest-master/googletest/include
DEPENDPATH += $$PWD/../../../googletest-master/googletest/include

INCLUDEPATH += Vector \
            Array \
            ContainerInterface

HEADERS += \
    ContainerInterface.hpp \
    Array/Array.h \
    Array/Array.hpp \
    ContainerInterface/ContainerInterface.h \
    ContainerInterface/ContainerInterface.hpp \
    Vector/Vector.h \
    Vector/Vector.hpp \
    Iterator.h \
    BitPointer.h

