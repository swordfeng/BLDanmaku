#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "BLDanmaku.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<BLDanmaku>("bldanmaku", 1, 0, "BLDanmaku");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
