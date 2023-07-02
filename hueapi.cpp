#include "hueapi.h"

HueApi::HueApi(QObject *parent)
    : QObject{parent}
{
    QSslSocket* sock = new QSslSocket();
    QNetworkAccessManager *netMan = new QNetworkAccessManager();
    connect(sock, &QSslSocket::encrypted, this, &HueApi::handleEncrypted);
    connect(sock, &QSslSocket::hostFound, this, [](){qDebug()<<"HOST FOUND";});
    connect(sock, &QSslSocket::readyRead, this, [&](){qDebug()<<sock->readAll();;});
    //sock->setLocalCertificate("Certificates/ssl.pem");
    sock->connectToHostEncrypted("discovery.meethue.com", 443);
    qDebug() << "INITIALISED";
}

QString HueApi::constructUrl(QString resource, QStringList additional)
{
    return "";
}
void HueApi::handleEncrypted()
{
    qDebug() << "Connected";
}
