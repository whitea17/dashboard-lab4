#include "httpmanager.h"
#include <QJsonDocument>
#include <QJsonObject>


HTTPManager::HTTPManager(QObject *parent) :
    QObject(parent),
    imageDownloadManager(new QNetworkAccessManager),
    stockAPIManager(new QNetworkAccessManager),
    stockTwoAPIManager(new QNetworkAccessManager),
    memeLinkAPIManager(new QNetworkAccessManager),
    mapsAPIManager(new QNetworkAccessManager),
    pushBulletAPIManager(new QNetworkAccessManager),
    newsAPIManager(new QNetworkAccessManager)


{
    connect(imageDownloadManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(ImageDownloadedHandler(QNetworkReply*)));

    connect(stockAPIManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(StockDownloadedHandler(QNetworkReply*)));

    connect(stockTwoAPIManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(StockTwoDownloadedHandler(QNetworkReply*)));

    connect(memeLinkAPIManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(MemeLinkDownloadedHandler(QNetworkReply*)));

    connect(mapsAPIManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(MapsDownloadedHandler(QNetworkReply*)));

    connect(pushBulletAPIManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(PushBulletDownloadedHandler(QNetworkReply*)));

    connect(newsAPIManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(NewsDownloadedHandler(QNetworkReply*)));

}

HTTPManager::~HTTPManager()
{
    delete imageDownloadManager;
    delete stockAPIManager;
    delete stockTwoAPIManager;
    delete memeLinkAPIManager;
    delete mapsAPIManager;
    delete pushBulletAPIManager;
    delete newsAPIManager;



}

void HTTPManager::sendImageRequest(QString link)
{
    QNetworkRequest request;


    request.setUrl(QUrl(link));
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
    qDebug() << SECRETS.STOCK_API_KEY;
    QNetworkRequest request;

    QString address = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol="
            + SymOne
            + "&apikey="
            + SECRETS.STOCK_API_KEY;

    request.setUrl(QUrl(address));
    stockTwoAPIManager->get(request);
    qDebug() << "Stock Request Sent to Address " << request.url();
}

// Shout-out to Dev Daksan who created this api, https://github.com/R3l3ntl3ss/Meme_Api
void HTTPManager::sendMemeLinkRequest()
{
    QNetworkRequest request;

    QString address = "https://meme-api.herokuapp.com/gimme";

    request.setUrl(QUrl(address));
    memeLinkAPIManager->get(request);
    qDebug() << "Stock Request Sent to Address " << request.url();
}

void HTTPManager::mapsRequest(QString fromZip, QString toZip)
{
    QNetworkRequest request;

    QString address = "https://maps.googleapis.com/maps/api/distancematrix/json?origins=" + fromZip + "&destinations=" + toZip + "&key=" + SECRETS.MAP_API_KEY;

    request.setUrl(QUrl(address));
    mapsAPIManager->get(request);
    qDebug() << "Stock Request Sent to Address " << request.url();
}

void HTTPManager::sendPushBulletRequest(QString data)
{
    QNetworkRequest request;

    QString address = "https://api.pushbullet.com/v2/pushes";
    request.setUrl(QUrl(address));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Access-Token", SECRETS.PUSHBULLET_API_KEY.toUtf8());




    QJsonObject jsonData;
    jsonData.insert("type", "note");
    jsonData.insert("title", data.left(15));
    jsonData.insert("body", data);

    QJsonDocument tmp(jsonData);
    QByteArray formatedData = tmp.toJson();

    pushBulletAPIManager->post(request, formatedData);
    qDebug() << "PushBullet Request Sent to Address " << request.url();
}

void HTTPManager::sendNewsRequest()
{
    QNetworkRequest request;

    QString address = "http://newsapi.org/v2/top-headlines?country=us&apiKey="
            + SECRETS.NEWS_API_KEY;

    request.setUrl(QUrl(address));
    newsAPIManager -> get(request);
    qDebug() << "News Request Sent to Address " << request.url();
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

void HTTPManager::MemeLinkDownloadedHandler(QNetworkReply *reply)
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

    emit MemeLinkJsonReady(jsonObj);
}

void HTTPManager::MapsDownloadedHandler(QNetworkReply *reply)
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

    emit MapsJsonReady(jsonObj);
}

void HTTPManager::PushBulletDownloadedHandler(QNetworkReply *reply)
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

    emit PushBulletJsonReady(jsonObj);
}

void HTTPManager::NewsDownloadedHandler(QNetworkReply *reply)
{
    qDebug() << "News Reply has arrived";
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    qDebug() << "Download was successful";

    QString answer = reply -> readAll();
    reply -> deleteLater();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject *jsonObj = new QJsonObject(jsonResponse.object());

    emit NewsJsonReady(jsonObj);
}
