#pragma once

#include <QtGui>
#include <QtCore>

namespace GraphicPrivate
{
	QFont  getFont(int pixelSize,
        QString family = QFont().family()); //Config::getValue("/Danmaku/Font", QFont().family()));

	QSize  getSize(QString string,
		QFont font);

	QSizeF getPlayer(qint64 date);

	double getScale(int mode,
		qint64 date,
		QSize size);

	QImage getCache(QString string,
		int color,
		QFont font,
		QSize size,
		bool frame,
        int effect = 2, //Config::getValue("/Danmaku/Effect", 5) / 2,
        int opacity = 100); //Config::getValue("/Danmaku/Alpha", 100));

	double getOverlap(double ff, double fs, double sf, double ss);
}
