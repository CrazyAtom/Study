#include "SlotProcessor.h"
#include <QDateTime>

SlotProcessor::SlotProcessor(QObject *parent)
    : QObject{parent}
{

}

void SlotProcessor::onSlotMessage()
{
    QDateTime t = QDateTime::currentDateTime();
    qDebug() << (t.toString("yyyy-MM-dd HH:mm:ss"));
}
