#ifndef BLDANMAKU_H
#define BLDANMAKU_H

#include <QtQuick/QQuickPaintedItem>
#include "DanmakuModel.h"
#include "Utils.h"
#include "Sprite/ISprite.h"
#include <QQuickWindow>

class BLDanmaku : public QQuickPaintedItem
{
public:
    BLDanmaku(QQuickItem *parent = 0);
    //void paint(QPainter *painter);
    virtual ~BLDanmaku();
    ISprite *getSprite(const Comment &comment);
    QSize size() { return QSize(width(), height()); }

    Q_INVOKABLE void update();
private:
    DanmakuModel *danmaku;

public slots:
    void clearup();
};

#endif // BLDANMAKU_H
