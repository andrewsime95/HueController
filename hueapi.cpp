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

QList<HubDev_t> HueApi::getDevicesOnNetwork()
{
    return hubDevs;
}

void HueApi::updateHubsOnNetwork()
{
    QList<HubDev_t>* hubDevices = new QList<HubDev_t>;
    QNetworkAccessManager *netMan = new QNetworkAccessManager();
    connect(netMan, &QNetworkAccessManager::finished, this, [&](QNetworkReply* reply){
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
            hubDevices->append(newHub);
        }
    });
    QNetworkRequest req = QNetworkRequest(QUrl("https://discovery.meethue.com"));
    netMan->get(req);
}

//Key:  "id" 	Val:  QJsonValue(string, "ecb5fafffe0a6b4f")
//                 Key:  "internalipaddress" 	Val:  QJsonValue(string, "192.168.1.209")
//                                                 Key:  "port" 	Val:  QJsonValue(double, 443)
//
