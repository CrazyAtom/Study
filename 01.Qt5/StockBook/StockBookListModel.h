#pragma once

#include <QAbstractListModel>
#include <QObject>

struct STOCK_BOOK_ITEM
{
    QString Name;
    int Market;
    int StockPrice;

    STOCK_BOOK_ITEM(const QString& name, const int& market, const int& stockPrice)
    {
        Name = name;
        Market = market;
        StockPrice = stockPrice;
    }
};

class StockBookListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    StockBookListModel(QObject *parent = nullptr);
    virtual ~StockBookListModel();

    enum class ColumnNames {
        name = Qt::UserRole,
        market,
        stockPrice
    };

// QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QHash<int, QByteArray> roleNames() const;

public:
    void SetStockBookList(QList<STOCK_BOOK_ITEM>* pStockBookList);

protected:
    QHash<int, QByteArray> m_columnNames;
    QList<STOCK_BOOK_ITEM>* m_pStockBookList;
};

