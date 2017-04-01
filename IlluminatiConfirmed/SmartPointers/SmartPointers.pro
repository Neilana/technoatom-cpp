TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    shared_ptr.t.cpp

HEADERS += \
    auto_ptr.h \
    unique_ptr.h \
    shared_ptr.h

# Google Test
unix|win32: LIBS += -L$$PWD/../../../googletest-master/googletest/lib/ -lgtest

INCLUDEPATH += $$PWD/../../../googletest-master/googletest/include
DEPENDPATH += $$PWD/../../../googletest-master/googletest/include
