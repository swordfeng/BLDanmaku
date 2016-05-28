TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    Graphic/Graphic.cpp \
    Graphic/GraphicPrivate.cpp \
    Graphic/Mode1.cpp \
    Graphic/Plain.cpp \
    BLDanmaku.cpp \
    DanmakuModel.cpp \
    Sprite/SyncTextureSprite.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Utils.h \
    Graphic/Graphic.h \
    Graphic/GraphicPrivate.h \
    Graphic/Mode1.h \
    Graphic/Plain.h \
    Sprite/ISprite.h \
    Sprite/AsyncRasterSprite.h \
    BLDanmaku.h \
    DanmakuModel.h \
    Sprite/SyncTextureSprite.h
