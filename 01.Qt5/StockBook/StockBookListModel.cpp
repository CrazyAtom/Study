#include "StockBookListModel.h"

StockBookListModel::StockBookListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_columnNames[(int)ColumnNames::name] = "name";
    m_columnNames[(int)ColumnNames::market] = "market";
    m_columnNames[(int)ColumnNames::stockPrice] = "stockPrice";
}

StockBookListModel::~StockBookListModel()
{

}

int StockBookListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (nullptr == m_pStockBookList)
        return 0;
    return m_pStockBookList->size();
}

QVariant StockBookListModel::data(const QModelIndex &index, int role) const
{
    const int nRow = index.row();
    if (0 > nRow)
        return QVariant();

    STOCK_BOOK_ITEM item = m_pStockBookList->at(nRow);
    switch ((ColumnNames)role)
    {
    case ColumnNames::name:
        return item.Name;
    case ColumnNames::market:
        return item.Market;
    case ColumnNames::stockPrice:
        return item.StockPrice;
    }

    return QVariant();
}

QHash<int, QByteArray> StockBookListModel::roleNames() const
{
    return m_columnNames;
}

void StockBookListModel::SetStockBookList(QList<STOCK_BOOK_ITEM> *pStockBookList)
{
    m_pStockBookList = pStockBookList;
}
