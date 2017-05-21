TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += TIXML_USE_STL

SOURCES += main.cpp \
    Level.cpp \
    Character.cpp \
    Game.cpp \

HEADERS += \
    Level.h \
    Character.h \
    constants.h \
    Game.h

LIBS += -L$$PWD/../../Libs/Box2D/Build/ -lBox2D
INCLUDEPATH += $$PWD/../../Libs/Box2D/

LIBS += -L$$PWD/../../Libs/SFML/Build -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
INCLUDEPATH += $$PWD/../../Libs/SFML/include

LIBS += -L$$PWD/../../Libs/tinyxml2/Build/ -llibtinyxml2.dll
INCLUDEPATH += $$PWD/../../Libs/tinyxml2/

