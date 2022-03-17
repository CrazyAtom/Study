#pragma once

#include <QObject>

class SlotProcessor : public QObject
{
    Q_OBJECT
public:
    explicit SlotProcessor(QObject *parent = nullptr);

signals:

public slots:
    void onSlotMessage();
};

