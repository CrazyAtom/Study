#pragma once

#ifndef __SQLCONVERSATIONMODEL_H__
#define __SQLCONVERSATIONMODEL_H__

#include <QSqlTableModel>

class SqlConversationModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(QString recipient READ recipient WRITE setRecipient NOTIFY recipientChanged)

public:
    explicit SqlConversationModel(QObject *parent = Q_NULLPTR);

    // QAbstractItemModel interface
public:
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public:
    QString recipient() const;
    void setRecipient(const QString &recipient);

    Q_INVOKABLE void sendMessage(const QString &recipient, const QString &message);

signals:
    void recipientChanged();

private:
    QString m_recipient;
};

#endif // __SQLCONVERSATIONMODEL_H__
