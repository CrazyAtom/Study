#include "sqlconversationsmodel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QUuid>

static const char *contactsTableName = "Contacts";

static void createTable()
{
    if (QSqlDatabase::database().tables().contains(contactsTableName)) {
        return;
    }

    QSqlQuery query;
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS 'Contacts' ("
        " 'convid' TEXT NOT NULL,"
        " 'lastmessage' TEXT,"
        " 'lasttimestamp' TEXT,"
        " PRIMARY KEY(convid)"
        " )")) {
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }
}

SqlConversationsModel::SqlConversationsModel(QObject *parent)
    : QSqlTableModel(parent)
{
    createTable();
    setTable(contactsTableName);
//    setSort(2, Qt::DescendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

QVariant SqlConversationsModel::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    const QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> SqlConversationsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Qt::UserRole] = "convid";
    names[Qt::UserRole + 1] = "lastmessage";
    names[Qt::UserRole + 2] = "lasttimestamp";
    return names;
}

void SqlConversationsModel::add(const QString &conversationid)
{
    QString _conversationid = conversationid;
    if (_conversationid.isEmpty()) {
        _conversationid = QUuid::createUuid().toString().replace('-',"").mid(1, 10);
    }

    QSqlRecord newRecord = record();
    newRecord.setValue("convid", _conversationid);
    if (!insertRecord(rowCount(), newRecord)) {
        qWarning() << "Failed to send message:" << lastError().text();
        return;
    }

    submitAll();
}
