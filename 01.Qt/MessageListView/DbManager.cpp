#include "DbManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>

namespace app {
    DbManager::DbManager()
    {
        if (QSqlDatabase::drivers().isEmpty()) {
            qDebug() << "No database drivers found This demo requires at least one Qt database driver. "
                        "Please check the documentation how to build the "
                        "Qt SQL plugins.";
        }
    }

    DbManager::~DbManager()
    {
//        QSqlDatabase db = QSqlDatabase::database(m_activeDb);
//        if (db.isOpen()) {
//            db.close();
//        }
    }

    bool DbManager::addConnection(const QString &driver, const QString &dbName, const QString &name)
    {
        QSqlError err;
        QSqlDatabase db = QSqlDatabase::addDatabase(driver, name);
        db.setDatabaseName(dbName);

        if (!db.open()) {
            qDebug() << db.lastError().text();
            db = QSqlDatabase();
            QSqlDatabase::removeDatabase(name);
            return false;
        }

        m_activeDb = name;

        return true;
    }

    bool DbManager::isOpen() const
    {
        return QSqlDatabase::database(m_activeDb).isOpen();
    }

    bool DbManager::createTable()
    {
        QSqlQuery query(QSqlDatabase::database(m_activeDb));
        query.prepare("CREATE TABLE message (id	INTEGER NOT NULL, message TEXT NOT NULL, datetime INTEGER NOT NULL, PRIMARY KEY(id AUTOINCREMENT));");

        if (!query.exec()) {
            qDebug() << "create failed: " << query.lastError().text();
            return false;
        }

        return true;
    }

    bool DbManager::add(const QString &message, const int &datetime)
    {
        if ((message.isEmpty()) || (datetime < 0)) {
            qDebug() << "add failed: message or datetime empty";
            return false;
        }

        QSqlQuery query(QSqlDatabase::database(m_activeDb));
        query.prepare("INSERT INTO message (message, datetime) VALUES (:message, :datetime)");
        query.bindValue(":message", message);
        query.bindValue(":datetime", datetime);

        if (!query.exec()) {
            qDebug() << "add failed: " << query.lastError().text();
            return false;
        }

        return true;
    }

    bool DbManager::removeFirst()
    {
        return false;
    }

    bool DbManager::removeAll()
    {
        QSqlQuery query(QSqlDatabase::database(m_activeDb));
        query.prepare("DELETE FROM message");

        if (!query.exec()) {
            qDebug() << "remove all failed: " << query.lastError();
            return false;
        }

        return true;
    }

    bool DbManager::get(QVariantList &data)
    {
        QSqlQuery query(QSqlDatabase::database(m_activeDb));
        query.prepare("SELECT * FROM message");

        if (!query.exec()) {
            qDebug() << "get failed: " << query.lastError().text();
            return false;
        }

        while (query.next()) {
            QSqlRecord record = query.record();
            int count = record.count();
            QVariantMap map;
            for(int i = 0; i < count; ++i) {
              map[record.field(i).name()] = record.value(i);
            }
            data.push_back(map);
        }

        return true;
    }
}   // namespace app
