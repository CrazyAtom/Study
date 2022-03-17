#include <QCoreApplication>
#include "SignalGenerator.h"
#include "SlotProcessor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SignalGenerator sg;
    SlotProcessor sp;

    QObject::connect(&sg, &SignalGenerator::textSignal,
                     &sp, &SlotProcessor::onSlotMessage);

    sg.GenerateTextSignal();

    return a.exec();
}
