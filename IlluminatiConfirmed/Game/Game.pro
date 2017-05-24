TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += TIXML_USE_STL

SOURCES += main.cpp \
    Level.cpp \
    Character.cpp \
    Game.cpp \
    ../../Libs/tinyxml2/tinyxml2.cpp \
    constants.cpp

HEADERS += \
    Level.h \
    constants.h \
    Game.h \
    Character.h \
    ../../Libs/tinyxml2/tinyxml2.h \
    ../../Libs/Box2D/Box2D.h
    ForTestbedCharacter.h


LIBS += -L$$PWD/../../Libs/Box2D/Build/ -lBox2D
INCLUDEPATH += $$PWD/../../Libs/Box2D/

LIBS += -L$$PWD/../../Libs/SFML/Build -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
INCLUDEPATH += $$PWD/../../Libs/SFML/include

win32:LIBS += -L$$PWD/../../Libs/tinyxml2/Build/ -llibtinyxml2.dll
INCLUDEPATH += $$PWD/../../Libs/tinyxml2/

