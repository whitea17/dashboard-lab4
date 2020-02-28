#include "httpmanager.h"
#include <QJsonDocument>
#include <QJsonObject>


HTTPManager::HTTPManager(QObject *parent) :
    QObject(parent),
    imageDownloadManager(new QNetworkAccessManager),
    stockAPIManager(new QNetworkAccessManager),
    stockTwoAPIManager(new QNetworkAccessManager)

{
    connect(imageDownloadManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(ImageDownloadedHandler(QNetworkReply*)));

    connect(stockAPIManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(StockDownloadedHandler(QNetworkReply*)));

    connect(stockTwoAPIManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(StockTwoDownloadedHandler(QNetworkReply*)));
}

HTTPManager::~HTTPManager()
{
    delete imageDownloadManager;
    delete stockAPIManager;
    delete stockTwoAPIManager;

}

void HTTPManager::sendImageRequest(QString zip)
{
    QNetworkRequest request;

    // use your key for bing map api!
    QString address = "https://dev.virtualearth.net/REST/V1/Imagery/Map/AerialWithLabels/"
            + zip
            + "/7?mapSize=400,200&mapLayer=TrafficFlow&format=png&key=AuGr51cDnR0CotgpcjsFPnIun9_0A_gj0eCx_mdxTxsDQ1XY-CNwY_wKukV118Pa";
    request.setUrl(QUrl(address));
    imageDownloadManager->get(request);
    qDebug() << "Image Request Sent to Address " << request.url();
}

void HTTPManager::sendStockRequest(QString SymOne)
{
    QNetworkRequest request;

    QString address = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol="
            + SymOne
            + "&apikey="
            + SECRETS.STOCK_API_KEY;

    request.setUrl(QUrl(address));
    stockAPIManager->get(request);
    qDebug() << "Stock Request Sent to Address " << request.url();
}

void HTTPManager::sendStockRequestTwo(QString SymOne)
{
    QNetworkRequest request;

    QString address = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol="
            + SymOne
            + "&apikey="
            + SECRETS.STOCK_API_KEY;

    request.setUrl(QUrl(address));
    stockTwoAPIManager->get(request);
    qDebug() << "Stock Request Sent to Address " << request.url();
}

void HTTPManager::ImageDownloadedHandler(QNetworkReply *reply)
{
    qDebug() << "Image Reply has arrived";
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    qDebug() << "Download was successful";
    QPixmap *image = new QPixmap();
    image->loadFromData(reply->readAll());
    reply->deleteLater();

    emit ImageReady(image);
}

void HTTPManager::StockDownloadedHandler(QNetworkReply *reply)
{
    qDebug() << "Stock Reply has arrived";
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    qDebug() << "Download was successful";

    QString answer = reply->readAll();
    reply->deleteLater();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject *jsonObj = new QJsonObject(jsonResponse.object());

    emit StockJsonReady(jsonObj);
}


void HTTPManager::StockTwoDownloadedHandler(QNetworkReply *reply)
{
    qDebug() << "Stock Reply has arrived";
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    qDebug() << "Download was successful";

    QString answer = reply->readAll();
    reply->deleteLater();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject *jsonObj = new QJsonObject(jsonResponse.object());

    emit StockTwoJsonReady(jsonObj);
}
