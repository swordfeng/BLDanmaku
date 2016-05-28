#pragma once

#include "ISprite.h"
#include <QOpenGLFunctions>
#include "../BLDanmaku.h"

class OpenGLRenderPrivate;

class SyncTextureSprite :public ISprite
{
public:
	GLuint texture;
	QImage *source;
    BLDanmaku *item;
    QOpenGLFunctions *glFunctions;

    SyncTextureSprite(const Comment &comment, BLDanmaku *item);
	virtual ~SyncTextureSprite();
	void draw(QPainter *painter, QRectF dest);
    QSize getSize();
};
