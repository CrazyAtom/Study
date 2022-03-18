#include <QDebug>
#include "StockBookViewModel.h"

StockBookViewModel::StockBookViewModel(QObject *parent)
    : QObject{parent}
{
    qDebug() << "StockBookViewModel - created";

    m_stockBookList.clear();
    m_stockBookList.append(STOCK_BOOK_ITEM("Apple", 1, 1));
    m_stockBookList.append(STOCK_BOOK_ITEM("Microsoft", 2, 2));
    m_stockBookList.append(STOCK_BOOK_ITEM("Google", 3, 3));
    m_stockBookList.append(STOCK_BOOK_ITEM("Saudi Aramco", 4, 4));
    m_stockBookList.append(STOCK_BOOK_ITEM("Amazon", 5, 5));
    m_stockBookList.append(STOCK_BOOK_ITEM("Tesla", 6, 6));
    m_stockBookList.append(STOCK_BOOK_ITEM("Meta", 7, 7));
    m_stockBookList.append(STOCK_BOOK_ITEM("NVIDIA", 8, 8));
    m_stockBookList.append(STOCK_BOOK_ITEM("TSMC", 9, 9));

    m_stockBookListModel.SetStockBookList(&m_stockBookList);
}

StockBookViewModel::~StockBookViewModel()
{
    qDebug() << "StockBookViewModel - destoryed";
}

QString StockBookViewModel::getDisplayMsg()
{
    return "Index No" + QString::number(m_selectedPos) + " is selected!";
}

void StockBookViewModel::selectRow(int iPos)
{
    qDebug() << "selected pos : " + QString::number((m_selectedPos));

    m_selectedPos = iPos;
    emit displayMsgChanged();
}
