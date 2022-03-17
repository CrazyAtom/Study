#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "StockBookViewModel.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<StockBookViewModel>("ViewModel", 1, 0, "StockBookViewModel");

    const QUrl url(u"qrc:/StockBook/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
