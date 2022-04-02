#pragma once

#include <QObject>
#include <QString>

namespace app {
    class MessageItem : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY changed)
        Q_PROPERTY(QString date READ date WRITE setDate NOTIFY changed)

    public:
        explicit MessageItem(const QString& message = "", const QString& date = "");

    public:
        QString message();
        QString date();

        void setMessage(const QString& value);
        void setDate(const QString& value);

    signals:
        void changed();

    private:
        QString m_message;
        QString m_date;
    };
}   // namespace app

