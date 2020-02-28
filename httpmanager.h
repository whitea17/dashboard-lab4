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

    void sendImageRequest(QString link);
    void sendStockRequest(QString SymOne);
    void sendStockRequestTwo(QString SymOne);
    void sendMemeLinkRequest();

    const SensitiveInfoHandler SECRETS;


signals:
    void ImageReady(QPixmap *image);
    void StockJsonReady(QJsonObject *json);
    void StockTwoJsonReady(QJsonObject *json);
    void MemeLinkJsonReady(QJsonObject *json);

private slots:
    void ImageDownloadedHandler(QNetworkReply *reply);
    void StockDownloadedHandler(QNetworkReply *reply);
    void StockTwoDownloadedHandler(QNetworkReply *reply);
    void MemeLinkDownloadedHandler(QNetworkReply *reply);

private:
    QNetworkAccessManager *imageDownloadManager;
    QNetworkAccessManager *stockAPIManager;
    QNetworkAccessManager *stockTwoAPIManager;
    QNetworkAccessManager *memeLinkAPIManager;

    QByteArray downloadedData;
};

#endif // HTTPMANAGER_H
