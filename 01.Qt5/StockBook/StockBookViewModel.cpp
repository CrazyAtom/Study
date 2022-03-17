#include <QDebug>
#include "StockBookViewModel.h"

StockBookViewModel::StockBookViewModel(QObject *parent)
    : QObject{parent}
{
    qDebug() << "StockBookViewModel - created";
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
