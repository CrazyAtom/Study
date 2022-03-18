#pragma once

#include <QObject>

class SignalGenerator : public QObject
{
    Q_OBJECT
public:
    explicit SignalGenerator(QObject *parent = nullptr);

    void GenerateTextSignal();

signals:
    void textSignal();

};

