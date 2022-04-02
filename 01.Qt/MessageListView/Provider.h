#pragma once

#include <QList>
#include <QObject>
#include <QSharedPointer>

#include "MessageItem.h"
#include "QObjectListModel.h"

namespace app {
    DECLARE_Q_OBJECT_LIST_MODEL(MessageItem)

    class MessageProvider : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QObjectListModel_MessageItem* items READ items CONSTANT)

    public:
        explicit MessageProvider(QObject *parent = Q_NULLPTR);
        virtual ~MessageProvider();

    public:
        void addItem(const QString& message, const int& datetime);

        Q_INVOKABLE void addItem(const QString& message);
        Q_INVOKABLE void removeItem(const int& index);

    private:
        QObjectListModel_MessageItem* items();

    private:
        QObjectListModel_MessageItem m_items;
    };
}   // namespace app

