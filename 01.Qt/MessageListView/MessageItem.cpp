#include <QDebug>

#include "MessageItem.h"

namespace app {
    MessageItem::MessageItem(const QString& message, const QString& date)
        : QObject(Q_NULLPTR)
        , m_message(message)
        , m_date(date)
    {

    }

    QString MessageItem::message()
    {
        return m_message;
    }

    void MessageItem::setMessage(const QString& value)
    {
        if (value != m_message) {
            m_message = value;
            emit changed();
        }
    }

    QString MessageItem::date()
    {
        return m_date;
    }

    void MessageItem::setDate(const QString& value)
    {
        if (value != m_date) {
            m_date = value;
            emit changed();
        }
    }
}   // namespace app
