TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += TIXML_USE_STL

SOURCES += main.cpp \
    level.cpp

HEADERS += \
    level.h

LIBS += -lopengl32
LIBS += -L$$PWD/../../../tinyxml2/Build/ -llibtinyxml2.dll
LIBS += -L$$PWD/../../../../SFML-2.4.2/Build/Libs

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += $$PWD/../../../../SFML-2.4.2/include
INCLUDEPATH += $$PWD/../../../tinyxml2
