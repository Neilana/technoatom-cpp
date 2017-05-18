TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += TIXML_USE_STL

SOURCES += main.cpp \
    level.cpp \
    /home/neilana/Downloads/tunyxml/tinyxml2-4.0.1/tinyxml2.cpp

HEADERS += \
    level.h \
    /home/neilana/Downloads/tunyxml/tinyxml2-4.0.1/tinyxml2.h

#LIBS += -lopengl32
#LIBS += -L$$PWD/../../../tinyxml2/Build/ -llibtinyxml2.dll
LIBS += -L$$PWD/../../../../SFML-2.4.2/Build/Libs

#CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += $$PWD/../../../../SFML-2.4.2/include
INCLUDEPATH += $$PWD/../../../tinyxml2
