#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include "Provider.h"

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterUncreatableType<app::MessageItem>( "App", 1, 0, "MessageItem", "interface" );
    qmlRegisterUncreatableType<app::QObjectListModel_MessageItem>( "App", 1, 0, "ListModel_MessageItem", "interface" );

    qmlRegisterType<app::MessageProvider>( "App", 1, 0, "Provider" );

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/MessageListView/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
