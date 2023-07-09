#ifndef HUEAPI_H
#define HUEAPI_H

#include "qqmlengine.h"
#include <QObject>
#include <QSslSocket>
#include <QNetworkAccessManager>
#include <QNetworkReply>

struct HubDev_t {
    QString id;
    QString ip;
    double port;
};

class HueApi : public QObject
{
    Q_OBJECT

public:
    explicit HueApi(QObject *parent = nullptr);

signals:

private slots:
  void handleEncrypted();

private:
    QSslSocket* sock;
    QNetworkAccessManager* netMan;

    const QHash<QString, QString> resources =
        std::initializer_list<std::pair<QString, QString>> {
        {"lights","/lights"},
        {"groups","/groups"},
        {"configuration","/config"},
        {"schedules", "/schedules"},
        {"scenes", "/scenes"},
        {"sensors", "/sensors"},
        {"rules", "/rules"}
    };

    QString constructUrl(QString resource, QStringList additional);

    void updateHubsOnNetwork();

    QVector<HubDev_t> hubDevs;
    QList<HubDev_t> getDevicesOnNetwork();
};

#endif // HUEAPI_H
