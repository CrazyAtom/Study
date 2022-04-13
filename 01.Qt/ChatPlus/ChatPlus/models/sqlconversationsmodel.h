#pragma once

#ifndef __SQLCONVERSATIONSMODEL_H__
#define __SQLCONVERSATIONSMODEL_H__

#include <QQmlEngine>
#include <QSqlTableModel>

class SqlConversationsModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(int selectedRow READ selectedRow WRITE setSelectedRow NOTIFY selectedRowChanged)
    Q_PROPERTY(QString lastmessage READ lastmessage WRITE setLastmessage NOTIFY lastmessageChanged)
    Q_PROPERTY(QString lasttimestamp READ lasttimestamp WRITE setLasttimestamp NOTIFY lasttimestampChanged)

public:
    static SqlConversationsModel *instance() {
        static SqlConversationsModel *instance = new SqlConversationsModel();
        return instance;
    }

    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return instance();
    }

private:
    explicit SqlConversationsModel(QObject *parent = nullptr);
    virtual ~ SqlConversationsModel();

    // QAbstractItemModel interface
public:
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public:
    int selectedRow();
    void setSelectedRow(const int &row);

    QString lastmessage();
    void setLastmessage(const QString &message);

    QString lasttimestamp();
    void setLasttimestamp(const QString &timestamp);

public:
    Q_INVOKABLE void add(const QString &conversationid="");
    Q_INVOKABLE QString getConvId() const;

signals:
    void selectedRowChanged();
    void lastmessageChanged();
    void lasttimestampChanged();

private:
    int m_selectedRow = -1;
};

#endif // __SQLCONVERSATIONSMODEL_H__
