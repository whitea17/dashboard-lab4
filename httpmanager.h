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
    void sendStockRequestTwo(QString SymOne);

    const SensitiveInfoHandler SECRETS;
    const SensitiveInfoHandler SECRETS2;


signals:
    void ImageReady(QPixmap *image);
    void StockJsonReady(QJsonObject *json);
    void StockTwoJsonReady(QJsonObject *json);

private slots:
    void ImageDownloadedHandler(QNetworkReply *reply);
    void StockDownloadedHandler(QNetworkReply *reply);
    void StockTwoDownloadedHandler(QNetworkReply *reply);

private:
    QNetworkAccessManager *imageDownloadManager;
    QNetworkAccessManager *stockAPIManager;
    QNetworkAccessManager *stockTwoAPIManager;

    QByteArray downloadedData;
};

#endif // HTTPMANAGER_H
