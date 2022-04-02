#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>

#include "Provider.h"
#include "DbManager.h"

namespace app {
    MessageProvider::MessageProvider(QObject *parent)
        : QObject(parent)
    {
        qDebug() << "MessageProvider::MessageProvider()";

        auto path = QString("%1%2").arg(qApp->applicationDirPath()).arg("/message.db");
        qDebug() << "Database path : " << path;

        if (DbManager::GetInstance()->addConnection("QSQLITE", path, "message")) {
            DbManager::GetInstance()->createTable();
            QVariantList data;
            if (DbManager::GetInstance()->get(data)) {
                for (const auto &item: data) {
                    auto map = item.toMap();
                    addItem(map["message"].toString(), map["datetime"].toInt());
                }
            }
        }
    }

    MessageProvider::~MessageProvider()
    {
        qDebug() << "MessageProvider::~MessageProvider()";
    }

    void MessageProvider::addItem(const QString &message, const int &datetime)
    {
        if (message.isEmpty() || datetime < 0)
            return;

        QDateTime _datetime = QDateTime::fromSecsSinceEpoch(datetime);
        qDebug() << "_temp: " << _datetime.toString("yyyy/MM/dd HH:mm");

        auto item = QSharedPointer<MessageItem>(new MessageItem(message, _datetime.toString("yyyy/MM/dd HH:mm")));
        m_items << item;
    }

    void MessageProvider::addItem(const QString& message)
    {
        if (message.isEmpty())
            return;

        QDateTime current = QDateTime::currentDateTime();
        qDebug() << "crrent: " << current.toString("yyyy/MM/dd HH:mm");
        qint64 offset = QDateTime::currentSecsSinceEpoch();
        qDebug() << "offset: " << offset;

        if (DbManager::GetInstance()->add(message, offset))
        {
            auto item = QSharedPointer<MessageItem>(new MessageItem(message, current.toString("yyyy/MM/dd HH:mm")));
            m_items << item;
        }
    }

    void MessageProvider::removeItem(const int& index)
    {
        if (DbManager::GetInstance()->removeFirst())
        {
            m_items.removeAt( index );
        }
    }

    QObjectListModel_MessageItem* MessageProvider::items()
    {
        return &m_items;
    }
}   // namespace app
