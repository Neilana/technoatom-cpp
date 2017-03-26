TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../Containers/ContainerInterface/ContainerInterface.cpp \
    ../Containers/Vector/Vector.cpp
    
# Google Test
unix|win32: LIBS += -L$$PWD/../../../googletest-master/googletest/lib/ -lgtest

INCLUDEPATH += $$PWD/../../../googletest-master/googletest/include
DEPENDPATH += $$PWD/../../../googletest-master/googletest/include

HEADERS += \
    BugNumbers.h \
    ../Containers/ContainerInterface/ContainerInterface.h \
    ../Containers/Vector/Vector.h \
    ../Containers/Vector/Vector.hpp \
    ../Containers/Array/Array.h \
    ../Containers/Array/Array.hpp \
    Print.h

INCLUDEPATH += ../Containers/Vector \
            ../Containers/Array \
            ../Containers/ContainerInterface \
            ../Containers
