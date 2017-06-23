QT += core gui sql
TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += qt
DEFINES += TIXML_USE_STL
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

SOURCES += main.cpp \
    classes/Level.cpp \
    classes/Game.cpp \
    ../../Libs/tinyxml2/tinyxml2.cpp \
    "../../Libs/Box2D-SFML2-Debug-Draw/Box2D-SFML Debug Draw/SFMLDebugDraw.cpp" \
    ../../Libs/b2dJson/c++/b2dJson.cpp \
    ../../Libs/b2dJson/c++/jsoncpp.cpp \
    ../../Libs/b2dJson/c++/b2dJsonImage.cpp \
    classes/Bullet.cpp \
    classes/screens/Screen.cpp \
    classes/screens/ScreenGame.cpp \
    classes/screens/ScreenMenuMain.cpp \
    classes/screens/ScreenChoseCharacters.cpp \
    classes/GameDatabase.cpp \
    classes/Base.cpp \
    Level.t.cpp \
    classes/screens/ScreenMenu.cpp \
    classes/screens/ScreenMenuLoad.cpp \
    classes/screens/ScreenMenuSave.cpp \
    classes/MyContactListener.cpp \
    classes/Ground.cpp \
    classes/Event/EventListener.cpp \
    classes/constants.cpp \
    classes/Event/Event.cpp \
    classes/Weapons.cpp \
    classes/Factories.cpp \
    classes/screens/ScreenMenuChoseMap.cpp \
    classes/characters/Сharacter.cpp

HEADERS += \
    classes/Level.h \
    constants.h \
    classes/Game.h \
    ../../Libs/tinyxml2/tinyxml2.h \
    ../../Libs/Box2D/Box2D/Box2D.h \
    "../../Libs/Box2D-SFML2-Debug-Draw/Box2D-SFML Debug Draw/SFMLDebugDraw.h" \
    classes/Bullet.h \
    classes/screens/Screen.h \
    classes/screens/ScreenGame.h \
    classes/screens/ScreenMenuMain.h \
    classes/screens/ScreenChoseCharacters.h \
    classes/GameDatabase.h \
    classes/Base.h \
    classes/screens/ScreenMenu.h \
    classes/screens/ScreenMenuLoad.h \
    classes/screens/ScreenMenuSave.h \
    classes/MyContactListener.h \
    classes/Ground.h \
    classes/Factories.h \
    classes/Weapons.h \
    classes/Event/Event.h \
    classes/Event/EventListener.h \
    classes/screens/ScreenMenuChoseMap.h \
    classes/characters/Character.h
    # ForTestbedCharacter.h

INCLUDEPATH += classes/ \
  classes/screens \
  classes/characters \
  classes/Event

LIBS += -L$$PWD/../../Libs/Box2D/Build/ -lBox2D
INCLUDEPATH += $$PWD/../../Libs/Box2D/

win32:LIBS += -L$$PWD/../../Libs/SFML/Build -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
unix: LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
INCLUDEPATH += $$PWD/../../Libs/SFML/include

win32:LIBS += -L$$PWD/../../Libs/tinyxml2/Build/ -llibtinyxml2.dll
INCLUDEPATH += $$PWD/../../Libs/tinyxml2/

#repo: https://github.com/MrPlow442/Box2D-SFML2-Debug-Draw/
INCLUDEPATH += "$$PWD/../../Libs/Box2D-SFML2-Debug-Draw/Box2D-SFML Debug Draw/"

#repo: https://github.com/iforce2d/b2dJson
INCLUDEPATH += $$PWD/../../Libs/b2dJson/c++

# Google Test
unix|win32: LIBS += -L$$PWD/../../../googletest-master/googletest/lib/ -lgtest

INCLUDEPATH += $$PWD/../../../googletest-master/googletest/include
DEPENDPATH += $$PWD/../../../googletest-master/googletest/include
