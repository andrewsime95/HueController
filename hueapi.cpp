#include "hueapi.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

HueApi::HueApi(QObject *parent)
    : QObject{parent}
{
    QSslCertificate localCert = QSslCertificate("Certificates/ssl.pem");
}

QString HueApi::constructUrl(QString resource, QStringList additional)
{
    return "";
}
void HueApi::handleEncrypted()
{
    qDebug() << "Connected";
}

QVector<HubDev_t> *HueApi::getDevicesOnNetwork()
{
    return hubDevs;
}

void HueApi::updateHubsOnNetwork()
{
    QNetworkAccessManager *netMan = new QNetworkAccessManager();
    connect(netMan, &QNetworkAccessManager::finished, this, &HueApi::handleReceived);
    QNetworkRequest req = QNetworkRequest(QUrl("https://discovery.meethue.com"));
    netMan->get(req);
}

void HueApi::handleReceived(QNetworkReply* reply)
{
    if(reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error occured: " << reply->error();
        return;
    }
    hubDevs = new QVector<HubDev_t>;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll().simplified());
    QJsonArray jsonArr = jsonDoc.array();

    qDebug() << jsonArr;

    foreach(auto jsonArrEl, jsonArr) {
        QJsonObject jsonObj = jsonArrEl.toObject();
        HubDev_t newHub;
        foreach(auto key, jsonObj.keys()) {
            if(key == "id") {
                newHub.id = jsonObj.value(key).toString();
            } else if(key == "internalipaddress") {
                newHub.ip = jsonObj.value(key).toString();
            } else if(key == "port") {
                newHub.port = jsonObj.value(key).toDouble();
            }
        }
        hubDevs->append(newHub);
    }
}
