TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread

SOURCES += main.cpp \
    assembler.t.cpp \
    cpu.cpp \
    assembler.cpp \
    cpu.t.cpp \
    disassembler.t.cpp \
    all.t.cpp \
    disassembler.cpp

HEADERS += \
    cpu.h \
    assembler.h \
    disassembler.h

# Google Test
unix|win32: LIBS += -L$$PWD/../../../googletest-master/googletest/lib/ -lgtest

INCLUDEPATH += $$PWD/../../../googletest-master/googletest/include
DEPENDPATH += $$PWD/../../../googletest-master/googletest/include
