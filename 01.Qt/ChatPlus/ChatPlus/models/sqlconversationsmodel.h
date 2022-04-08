#pragma once

#ifndef __SQLCONVERSATIONSMODEL_H__
#define __SQLCONVERSATIONSMODEL_H__

#include <QSqlTableModel>

class SqlConversationsModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit SqlConversationsModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public:
    Q_INVOKABLE void add(const QString &conversationid="");

signals:

};

#endif // __SQLCONVERSATIONSMODEL_H__
