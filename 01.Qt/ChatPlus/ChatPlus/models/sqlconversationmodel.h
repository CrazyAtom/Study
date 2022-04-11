#pragma once

#ifndef __SQLCONVERSATIONMODEL_H__
#define __SQLCONVERSATIONMODEL_H__

#include <QSqlTableModel>

class SqlConversationModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(QString conversationid READ conversationid WRITE setConversationid NOTIFY conversationidChanged)

public:
    explicit SqlConversationModel(QObject *parent = Q_NULLPTR);

    // QAbstractItemModel interface
public:
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public:
    QString conversationid() const;
    void setConversationid(const QString &conversationid="");

public:
    Q_INVOKABLE void sendMessage(const QString &conversationid, const QString &author, const QString &message);

signals:
    void conversationidChanged();

private:
    QString m_conversationid;
};

#endif // __SQLCONVERSATIONMODEL_H__
