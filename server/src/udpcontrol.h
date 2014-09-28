#ifndef __UDPCONTROL_H__
#define __UDPCONTROL_H__

#include <QUdpSocket>

class UdpCore : public QObject{
    Q_OBJECT

public:
    UdpCore();
    //~UdpCore();


private slots:
    void read();

private:
    QUdpSocket *socket;
};

#endif
