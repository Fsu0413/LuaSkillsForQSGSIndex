#include "udpcontrol.h"
#include "QCoreApplication"
#include <iostream>
using std::cout;
using std::endl;

UdpCore::UdpCore() {
    socket = new QUdpSocket(this);
    socket->bind(30000);

    connect(socket, &QUdpSocket::readyRead, this, &UdpCore::read);
}

void UdpCore::read() {
    while (socket->hasPendingDatagrams()) {
        QByteArray s;
        s.resize(socket->pendingDatagramSize());
        QHostAddress ad;
        quint16 port;
        socket->readDatagram(s.data(), socket->pendingDatagramSize(), &ad, &port);

        cout << ad.toString().toLatin1().constData() << ":" << port << endl << s.constData() << endl;

        QString S = s;
        if (S.contains("Quit"))
            qApp->quit();
        else
            ; // wait for the git repo
    }
}
