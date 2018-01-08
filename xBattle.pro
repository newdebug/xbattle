TARGET = xBattle
TEMPLATE = app
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

COCOS_ROOT = D:/cocos2d-x/3.16/win32

DEPENDPATH += $$COCOS_ROOT
INCLUDEPATH += $$PWD/src $$PWD/src/actor $$PWD/src/scene $$PWD/src/layer \
	    $$COCOS_ROOT/include \
	    $$COCOS_ROOT/include/cocos \
	    $$COCOS_ROOT/include/cocos\audio\include \
	    $$COCOS_ROOT/include/external \
	    $$COCOS_ROOT/include/external/win32-specific \
	    $$COCOS_ROOT/include/external/glfw3/include/win32 \
	    $$COCOS_ROOT/include/external/win32-specific/gles/include/OGLES

contains(COCOS2D-X_MODULES,extensions)
{
	INCLUDEPATH += $$COCOS_ROOT/extensions
}
contains(COCOS2D-X_MODULES,box2d)
{
	INCLUDEPATH += $$COCOS_ROOT/external/Box2D
}
contains(COCOS2D-X_MODULES,chipmunk)
{
	INCLUDEPATH += $$COCOS_ROOT/external/chipmunk/include/chipmunk
}

CONFIG(debug, debug|release){
    COCOS2D_DEBUG = $$1
    DEFINES += COCOS2D_DEBUG
}


win32:{
    DEFINES += _WIN32 _WINDOWS
    INCLUDEPATH += $$COCOS_ROOT/cocos/platform/win32
    CONFIG += _WINDOWS
    OTHER_FILES += \
	    resources/game.rc
    RC_FILE = resources/game.rc
#    QMAKE_LFLAGS_CONSOLE = /SUBSYSTEM:CONSOLE ,"5.01"
#    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS
}

SOURCES += main.cpp \
    src/actor/ActorBreed.cpp \
    src/AppDelegate.cpp \
    src/scene/GameScene.cpp \
    src/scene/PreLoadScene.cpp \
    src/layer/MissionLayer.cpp \
    src/actor/MonsterBreed.cpp \
    src/actor/PlayerBreed.cpp \
    src/actor/Player.cpp \
    src/actor/Actor.cpp \
    src/actor/Monster.cpp \
    src/layer/TerrainLayer.cpp \
    src/actor/Bullet.cpp \
    src/actor/BulletBreed.cpp \
    src/scene/MenuScene.cpp \
    src/actor/Actor3D.cpp


HEADERS += \
    src/actor/ActorBreed.h \
    src/AppDelegate.h \
    src/scene/GameScene.h \
    src/scene/PreLoadScene.h \
    src/layer/MissionLayer.h \
    src/actor/MonsterBreed.h \
    src/actor/PlayerBreed.h \
    src/actor/Player.h \
    src/actor/Actor.h \
    src/actor/Monster.h \
    src/layer/TerrainLayer.h \
    src/actor/Bullet.h \
    src/actor/BulletBreed.h \
    src/scene/MenuScene.h \
    src/actor/Actor3D.h


LIBS += -L$$COCOS_ROOT/lib \
     -llibbox2d \
     -llibcocos2d \
     -llibrecast -llibSpine \
     -llibcurl \
    -lopengl32 \
    -lglew32 \
    -llibzlib \
    -llibwebp \
    -llibiconv \
    -lfreetype \
    -lwinmm \
    -lws2_32 \
    -lkernel32 \
    -luser32 \
    -lgdi32 \
    -lwinspool \
    -lcomdlg32 \
    -ladvapi32 \
    -lshell32 \
    -lole32 \
    -loleaut32 \
    -luuid \
    -lodbc32 \
    -lodbccp32


#pragma warnind( disable: 4251 )
win32-msvc*:{
    QMAKE_CXXFLAGS += /wd"4251"
    QMAKE_CXXFLAGS += /wd"4819"
}
