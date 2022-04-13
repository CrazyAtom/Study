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
    qDebug("SqlConversationsModel::SqlConversationsModel()");

    createTable();
    setTable(contactsTableName);
//    setSort(2, Qt::DescendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

SqlConversationsModel::~SqlConversationsModel()
{
    qDebug("SqlConversationsModel::~SqlConversationsModel()");
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

int SqlConversationsModel::selectedRow()
{
    return m_selectedRow;
}

void SqlConversationsModel::setSelectedRow(const int &row)
{
    if (m_selectedRow != row) {
        m_selectedRow = row;
        emit selectedRowChanged();
    }
}

QString SqlConversationsModel::lastmessage()
{
    const QSqlRecord sqlRecord = record(m_selectedRow);
    if (!sqlRecord.isEmpty()) {
        return sqlRecord.value("lastmessage").toString();
    }
    return QString();
}

void SqlConversationsModel::setLastmessage(const QString &message)
{
    setData(index(m_selectedRow, 1), message);
    if (submitAll()) {
        emit lastmessageChanged();
    }
}

QString SqlConversationsModel::lasttimestamp()
{
    const QSqlRecord sqlRecord = record(m_selectedRow);
    if (!sqlRecord.isEmpty()) {
        return sqlRecord.value("lasttimestamp").toString();
    }
    return QString();
}

void SqlConversationsModel::setLasttimestamp(const QString &timestamp)
{
    setData(index(m_selectedRow, 2), timestamp);
    if (submitAll()) {
        emit lasttimestampChanged();
    }
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

QString SqlConversationsModel::getConvId() const
{
    const QSqlRecord sqlRecord = record(m_selectedRow);
    if (!sqlRecord.isEmpty()) {
        return sqlRecord.value("convid").toString();
    }
    return QString();
}
