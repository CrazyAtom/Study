#include "sqlconversationmodel.h"

#include <QDateTime>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>

static const char *conversationsTableName = "Conversations";

static void createTable()
{
    if (QSqlDatabase::database().tables().contains(conversationsTableName)) {
        return;
    }

    QSqlQuery query;
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS 'Conversations' ("
        " 'convid' TEXT NOT NULL,"
        " 'author' TEXT NOT NULL,"
        " 'timestamp' TEXT NOT NULL,"
        " 'message' TEXT NOT NULL,"
        " FOREIGN KEY('convid') REFERENCES Contacts ( convid )"
        " )")) {
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }
}

SqlConversationModel::SqlConversationModel(QObject *parent)
    : QSqlTableModel(parent)
{
    createTable();
    setTable(conversationsTableName);
//    setSort(2, Qt::DescendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant SqlConversationModel::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    const QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> SqlConversationModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Qt::UserRole] = "convid";
    names[Qt::UserRole + 1] = "author";
    names[Qt::UserRole + 2] = "timestamp";
    names[Qt::UserRole + 3] = "message";
    return names;
}

QString SqlConversationModel::conversationid() const
{
    return m_conversationid;
}

void SqlConversationModel::setConversationid(const QString &conversationid)
{
    if (conversationid == m_conversationid)
        return;

    m_conversationid = conversationid;

    const QString filterString = QString::fromLatin1("(convid = '%1')").arg(conversationid);
    setFilter(filterString);
    select();

    emit conversationidChanged();
}

void SqlConversationModel::sendMessage(const QString &conversationid, const QString &author, const QString &message)
{
    if (conversationid.isEmpty()) {
        qWarning() << "Failed to send message: conversationid is empty";
        return;
    }

    const QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);

    QSqlRecord newRecord = record();
    newRecord.setValue("convid", conversationid);
    newRecord.setValue("author", author);
    newRecord.setValue("timestamp", timestamp);
    newRecord.setValue("message", message);
    if (!insertRecord(rowCount(), newRecord)) {
        qWarning() << "Failed to send message:" << lastError().text();
        return;
    }

    submitAll();
}
