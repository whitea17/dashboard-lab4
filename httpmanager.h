#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include "sensitiveinfohandler.h"

class HTTPManager : public QObject
{
    Q_OBJECT
public:
    explicit HTTPManager(QObject *parent = nullptr);
    ~HTTPManager();

    void sendImageRequest(QString zip);
    void sendStockRequest(QString SymOne);
    const SensitiveInfoHandler SECRETS;

signals:
    void ImageReady(QPixmap *image);
    void StockJsonReady(QJsonObject *json);

private slots:
    void ImageDownloadedHandler(QNetworkReply *reply);
    void StockDownloadedHandler(QNetworkReply *reply);

private:
    QNetworkAccessManager *imageDownloadManager;
    QNetworkAccessManager *stockAPIManager;

    QByteArray downloadedData;
};

#endif // HTTPMANAGER_H
