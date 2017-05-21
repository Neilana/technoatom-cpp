TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += TIXML_USE_STL

SOURCES += main.cpp \
    Level.cpp \
    tinyxml2.cpp \
    Character.cpp \
   # GameEngine.cpp

HEADERS += \
    Level.h \
    tinyxml2.h \
    Level.h \
    Character.h \
   # GameEngine.h \
    constants.h
	
	
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

