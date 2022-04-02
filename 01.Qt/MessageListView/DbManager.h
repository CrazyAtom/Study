#pragma once

#include <QSqlDatabase>

namespace app {
    class DbManager
    {
    public:
        static DbManager* GetInstance() {
            static DbManager instance;
            return &instance;
        }

    private:
        DbManager();
        virtual ~DbManager();

    public:
        bool addConnection(const QString &driver, const QString &dbName, const QString &name);
        bool isOpen() const;
        bool createTable();
        bool add(const QString &message, const int &datetime);
        bool removeFirst();
        bool removeAll();
        bool get(QVariantList &data);

    private:
        QString m_activeDb;
    };
}   // namespace app

