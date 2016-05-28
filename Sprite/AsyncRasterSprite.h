#pragma once

#include "ISprite.h"
#include <QImage>
#include <QPainter>
#include "../Graphic/GraphicPrivate.h"
#include "../BLDanmaku.h"
#include <QQuickWindow>

class AsyncRasterSprite :public ISprite
{
public:
	QImage image;

    explicit AsyncRasterSprite(const Comment &comment, BLDanmaku *item)
	{
        QSize size = item->size();
        QFont font = GraphicPrivate::getFont(comment.font*GraphicPrivate::getScale(comment.mode, comment.date, size));
		QSize need = GraphicPrivate::getSize(comment.string, font);
		image = GraphicPrivate::getCache(comment.string, comment.color, font, need, comment.isLocal());
	}

	void draw(QPainter *painter, QRectF dest)
	{
		painter->drawImage(dest, image);
	}

	QSize getSize()
	{
		return image.size();
	}
};
