TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += TIXML_USE_STL

SOURCES += main.cpp \
    Level.cpp \
    Character.cpp \
   # GameEngine.cpp
    libs/tinyxml/tinyxml2.cpp

HEADERS += \
    Level.h \
    tinyxml2.h \
    Level.h \
    Character.h \
   # GameEngine.h \
    constants.h \
    libs/tinyxml/tinyxml2.h \
    libs/Box2D/Box2D.h
	
	
#LIBS += -lopengl32
#LIBS += -L$$PWD/../../../tinyxml2/Build/ -llibtinyxml2.dll
LIBS += -L$$PWD/../../../../SFML-2.4.2/Build/Libs

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
#CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
#CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += "/usr/include/SFML"
DEPENDPATH +=  "/usr/include/SFML"

INCLUDEPATH += $$PWD/../../../../SFML-2.4.2/include
INCLUDEPATH += $$PWD/../../../tinyxml2


# Box2D
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/Box2D/Build/release/ -lBox2D
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/Box2D/Build/debug/ -lBox2D
else:unix:!macx: LIBS += -L$$PWD/libs/Box2D/Build/ -lBox2D

INCLUDEPATH += $$PWD/libs/Box2D/Build
DEPENDPATH += $$PWD/libs/Box2D/Build

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/Box2D/Build/release/libBox2D.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/Box2D/Build/debug/libBox2D.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/Box2D/Build/release/Box2D.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/Box2D/Build/debug/Box2D.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/libs/Box2D/Build/libBox2D.a
