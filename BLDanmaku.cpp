#include "BLDanmaku.h"
#include "Utils.h"
#include "Sprite/AsyncRasterSprite.h"
#include "Sprite/SyncTextureSprite.h"
#include <QQuickWindow>

BLDanmaku::BLDanmaku(QQuickItem *parent):
    QQuickPaintedItem(parent) {

    setRenderTarget(QQuickPaintedItem::InvertedYFramebufferObject);

    danmaku = new DanmakuModel(this);

    Record load;
    Comment d;

    d.font = 24;
    d.mode = 1;
    d.color = 0xffffff;

    d.time = 0;
    d.string = "test";
    load.danmaku.append(d);

    d.string = "test2";
    load.danmaku.append(d);

    d.string = "test3";
    load.danmaku.append(d);

    d.string = "test4";
    load.danmaku.append(d);

    d.string = "test5";
    load.danmaku.append(d);

    d.string = "test5";
    load.danmaku.append(d);
    d.string = "test5";
    load.danmaku.append(d);
    d.string = "test5";
    load.danmaku.append(d);

    d.string = "test5";
    load.danmaku.append(d);

    d.string = "test5";
    load.danmaku.append(d);

    danmaku->appendToPool(&load);
    danmaku->setTime(0);

}

/*
void BLDanmaku::paint(QPainter *painter) {
    painter->setRenderHints(QPainter::SmoothPixmapTransform);
    static double time = 0;
    danmaku->setTime(time);
    time += 0.02;
    danmaku->draw(painter, 0.02);
}
*/

void BLDanmaku::update() {
    QQuickPaintedItem::update();
}

void BLDanmaku::clearup() {
    qDebug() << "GL destroy";
    delete danmaku;
    danmaku = nullptr;
}

BLDanmaku::~BLDanmaku() {
    qDebug() << "desctuct";
    delete danmaku;
    qDebug() << "desctucted";
}

ISprite *BLDanmaku::getSprite(const Comment &comment) {
    //return new AsyncRasterSprite(comment, this);
    return new SyncTextureSprite(comment, this);
}
