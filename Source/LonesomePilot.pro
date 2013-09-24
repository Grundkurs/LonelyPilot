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
    RandomGenerator.cpp




INCLUDEPATH += C:\SFMLMinGW\include
DEPENDPATH += C:\SFMLMinGW\include
LIBS += -LC:\SFMLMinGW\lib

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

win32: LIBS += -lsfml-main

OTHER_FILES +=

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
    RandomGenerator.h
