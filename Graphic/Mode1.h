#pragma once

#include "Plain.h"

class Mode1 :public Plain
{
public:
    Mode1(const Comment &comment, BLDanmaku *item);
    QList<QRectF> locate();
	bool move(double time);
	uint intersects(Graphic *other);

private:
	double speed;
};
