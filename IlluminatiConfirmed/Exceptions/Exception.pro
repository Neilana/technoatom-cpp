TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    Exception.h

INCLUDEPATH += ..\Containers\ContainerInterface \
                ..\Containers\
