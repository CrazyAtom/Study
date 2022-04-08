#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QStandardPaths>
#include <QSqlDatabase>
#include <QSqlError>

//#include "models/sqlcontactmodel.h"
#include "models/sqlconversationsmodel.h"
#include "models/sqlconversationmodel.h"

static void connectToDatabase()
{
    if (QSqlDatabase::drivers().isEmpty()) {
        qDebug() << "No database drivers found This demo requires at least one Qt database driver. "
                    "Please check the documentation how to build the "
                    "Qt SQL plugins.";
    }

    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        database = QSqlDatabase::addDatabase("QSQLITE");
        if (!database.isValid()) {
            qFatal("Cannot add database: %s", qPrintable(database.lastError().text()));
        }
    }

    const QDir writeDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/user_data";
    if (!writeDir.mkpath("."))
            qFatal("Failed to create writable directory at %s", qPrintable(writeDir.absolutePath()));

    // Ensure that we have a writable location on all devices.
    const QString fileName = writeDir.absolutePath() + "/chatplus.sqlite3";
    // When using the SQLite driver, open() will create the SQLite database if it doesn't exist.
    database.setDatabaseName(fileName);
    if (!database.open()) {
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
        QFile::remove(fileName);
    }
}

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

//    qmlRegisterType<SqlContactModel>("com.crazyatom.chatplus", 1, 0, "SqlContactModel");
    qmlRegisterType<SqlConversationsModel>("com.crazyatom.chatplus", 1, 0, "SqlConversationsModel");
    qmlRegisterType<SqlConversationModel>("com.crazyatom.chatplus", 1, 0, "SqlConversationModel");

    connectToDatabase();

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/resources/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
