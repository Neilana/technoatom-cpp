TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    #Array.cpp \
    Array.t.cpp \
    Vector.t.cpp

# Google Test
INCLUDEPATH += /usr/include/gtest
LIBS += -lgtest -L /usr/include/gtest

HEADERS += \
    Array.h \
    Vector.h
