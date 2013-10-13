TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += main.cpp \
	Star.cpp \
	RandomNumberGenerator.cpp \
	Player.cpp \
	Option.cpp \
	MenuState.cpp \
	IState.cpp \
	IEntity.cpp \
	GameState.cpp \
	Game.cpp \
	Background.cpp \
	Ambulance.cpp \
	StringUtilities.cpp \
	RandomGenerator.cpp \
	AudioManager.cpp \
        XML.cpp \
        tinyxml2.cpp \
    ConfigLoader.cpp \
    VectorUtilities.cpp \
    InputInterval.cpp \
    Optionstate.cpp \
    Laser.cpp \
    Baldus.cpp


INCLUDEPATH += C:\SFMLMinGW\include
DEPENDPATH += C:\SFMLMinGW\include
LIBS += -LC:\SFMLMinGW\lib

CONFIG(release, release|debug){
LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
win32: LIBS += -lsfml-main
}

CONFIG(debug, release|debug){
LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
win32: LIBS += -lsfml-main-d
}

HEADERS += \
	Star.h \
	RandomNumberGenerator.h \
	Player.h \
	Option.h \
	MenuState.h \
	IState.h \
	IEntity.h \
	GameState.h \
	Game.h \
	Background.h \
	Ambulance.h \
	StringUtilities.h \
	RandomGenerator.h \
	AudioManager.h \
        XML.h \
	XML_Loader.h \
        tinyxml2.h \
        ConfigLoader.h \
    VectorUtilities.h \
    InputInterval.h \
    Optionstate.h \
    Laser.h \
    Baldus.h
