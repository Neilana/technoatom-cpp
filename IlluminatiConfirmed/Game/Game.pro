QT += core gui sql
TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
#CONFIG -= qt
DEFINES += TIXML_USE_STL

SOURCES += main.cpp \
    classes/Level.cpp \
    classes/Character.cpp \
    classes/Game.cpp \
    ../../Libs/tinyxml2/tinyxml2.cpp \
    "../../Libs/Box2D-SFML2-Debug-Draw/Box2D-SFML Debug Draw/SFMLDebugDraw.cpp" \
    classes/Bullet.cpp \
    classes/screens/Screen.cpp \
    classes/screens/ScreenGame.cpp \
    classes/screens/ScreenMenu.cpp \
    classes/screens/ScreenChoseCharacters.cpp \
    classes/GameDatabase.cpp

HEADERS += \
    classes/Level.h \
    constants.h \
    classes/Game.h \
    classes/Character.h \
    ../../Libs/tinyxml2/tinyxml2.h \
    ../../Libs/Box2D/Box2D/Box2Box2D.h \
    "../../Libs/Box2D-SFML2-Debug-Draw/Box2D-SFML Debug Draw/SFMLDebugDraw.h" \
    classes/Bullet.h \
    classes/screens/Screen.h \
    classes/screens/ScreenGame.h \
    classes/screens/ScreenMenu.h \
    classes/screens/ScreenChoseCharacters.h \
    classes/GameDatabase.h
   # ForTestbedCharacter.h

INCLUDEPATH += classes/ \
  classes/screens

LIBS += -L$$PWD/../../Libs/Box2D/Build/ -lBox2D
INCLUDEPATH += $$PWD/../../Libs/Box2D/

LIBS += -L$$PWD/../../Libs/SFML/Build -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
INCLUDEPATH += $$PWD/../../Libs/SFML/include

win32:LIBS += -L$$PWD/../../Libs/tinyxml2/Build/ -llibtinyxml2.dll
INCLUDEPATH += $$PWD/../../Libs/tinyxml2/

#repo: https://github.com/MrPlow442/Box2D-SFML2-Debug-Draw/
INCLUDEPATH += "$$PWD/../../Libs/Box2D-SFML2-Debug-Draw/Box2D-SFML Debug Draw/"
