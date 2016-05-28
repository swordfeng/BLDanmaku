#pragma once

#include "Graphic.h"
#include "../Sprite/ISprite.h"

class Plain :public Graphic
{
public:
	void draw(QPainter *painter);

protected:
    ISprite *sprite;

    explicit Plain(const Comment &comment, BLDanmaku *item);
	virtual ~Plain();

	double evaluate(QString expression);
};
