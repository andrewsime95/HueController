#include "hueapi.h"

HueApi::HueApi(QObject *parent)
    : QObject{parent}
{
    QNetworkAccessManager *netMan = new QNetworkAccessManager();
    QSslCertificate localCert = QSslCertificate("Certificates/ssl.pem");
    connect(netMan, &QNetworkAccessManager::finished, this, [](QNetworkReply* reply){
        qDebug() << reply->readAll();
    });
    QNetworkRequest req = QNetworkRequest(QUrl("https://discovery.meethue.com"));
    netMan->get(req);
}

QString HueApi::constructUrl(QString resource, QStringList additional)
{
    return "";
}
void HueApi::handleEncrypted()
{
    qDebug() << "Connected";
}
