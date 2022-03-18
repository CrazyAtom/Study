#include "SignalGenerator.h"

SignalGenerator::SignalGenerator(QObject *parent)
    : QObject{parent}
{

}

void SignalGenerator::GenerateTextSignal()
{
    emit textSignal();
}
