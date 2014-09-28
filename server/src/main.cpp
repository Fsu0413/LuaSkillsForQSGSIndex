#include <QCoreApplication>
#include "autoupdate.h"
#include "udpcontrol.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    AutoUpdater au;
    (void)au;

    UdpCore udp;
    (void)udp;

    return a.exec();
}
