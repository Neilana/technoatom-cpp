TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    Stack.t.cpp

HEADERS += \
    Stack.h

# Google Test
INCLUDEPATH += /usr/include/gtest
LIBS += -lgtest -L /usr/include/gtest
