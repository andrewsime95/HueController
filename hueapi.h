#ifndef HUEAPI_H
#define HUEAPI_H

#include "qqmlengine.h"
#include <QObject>
#include <QSslSocket>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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

    struct HueDeviceStruct {

    };

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
};

#endif // HUEAPI_H
