#pragma once

#include <QObject>

class StockBookViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString displayMsg READ getDisplayMsg NOTIFY displayMsgChanged)

public:
    explicit StockBookViewModel(QObject *parent = nullptr);
    virtual ~StockBookViewModel();

    Q_INVOKABLE void selectRow(int iPos);

    QString getDisplayMsg();

signals:
    void displayMsgChanged();

protected:
    int m_selectedPos = -1;

};

