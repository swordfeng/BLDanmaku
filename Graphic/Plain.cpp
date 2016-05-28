#include "Plain.h"
#include "GraphicPrivate.h"
#include "../Sprite/AsyncRasterSprite.h"

using namespace GraphicPrivate;

Plain::Plain(const Comment &comment, BLDanmaku *item):
    Graphic(item)
{
	source = &comment;
    //sprite = ARender::instance()->getSprite(comment);
    sprite = item->getSprite(comment);
	rect.setSize(sprite->getSize());
}

Plain::~Plain()
{
	delete sprite;
}

void Plain::draw(QPainter *painter)
{
	if (enabled){
		sprite->draw(painter, rect);
	}
}

double Plain::evaluate(QString expression)
{
    /*
	expression.replace("%{width}", QString::number(rect.width()), Qt::CaseInsensitive);
	try{
		return Utils::evaluate(expression);
	}
	catch (std::runtime_error){
		throw args_prasing_error();
	}
    */
}
