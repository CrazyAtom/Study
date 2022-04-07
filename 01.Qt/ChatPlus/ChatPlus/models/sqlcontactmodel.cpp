#include "sqlcontactmodel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

static const char *contactsTableName = "Contacts";

static void createTable()
{
    if (QSqlDatabase::database().tables().contains(contactsTableName)) {
        return;
    }

    QSqlQuery query;
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS 'Contacts' ("
        "   'name' TEXT NOT NULL,"
        "   PRIMARY KEY(name)"
        ")")) {
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }

    query.exec("INSERT INTO Contacts VALUES('Albert Einstein')");
    query.exec("INSERT INTO Contacts VALUES('Ernest Hemingway')");
    query.exec("INSERT INTO Contacts VALUES('Hans Gude')");
}

SqlContactModel::SqlContactModel(QObject *parent)
    : QSqlQueryModel(parent)
{
    createTable();

//    QSqlQuery query;
//    if (!query.exec("SELECT * FROM Contacts"))
//        qFatal("Contacts SELECT query failed: %s", qPrintable(query.lastError().text()));

    setQuery("SELECT * FROM Contacts");
    if (lastError().isValid())
        qFatal("Cannot set query on SqlContactModel: %s", qPrintable(lastError().text()));
}
