#pragma once

#include <QObject>
#include "StockBookListModel.h"

class StockBookViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString displayMsg READ getDisplayMsg NOTIFY displayMsgChanged)

public:
    explicit StockBookViewModel(QObject *parent = nullptr);
    virtual ~StockBookViewModel();

    Q_INVOKABLE void selectRow(int iPos);
    Q_INVOKABLE StockBookListModel* getListModel() { return &m_stockBookListModel; }

    QString getDisplayMsg();

signals:
    void displayMsgChanged();

protected:
    int m_selectedPos = -1;
    StockBookListModel m_stockBookListModel;
    QList<STOCK_BOOK_ITEM> m_stockBookList;
};

