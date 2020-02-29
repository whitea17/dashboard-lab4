#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer),
    httpManager(new HTTPManager)
{
    ui->setupUi(this);

    connect(timer, SIGNAL(timeout()),
            this, SLOT(setCurrentTime()));

    setCurrentTime();
    timer->start(1000);

    connect(httpManager, SIGNAL(ImageReady(QPixmap *)),
            this, SLOT(processImage(QPixmap *)));

    connect(httpManager, SIGNAL(StockJsonReady(QJsonObject *)),
            this, SLOT(processStockJson(QJsonObject *)));

    connect(httpManager, SIGNAL(StockTwoJsonReady(QJsonObject *)),
            this, SLOT(processStockTwoJson(QJsonObject *)));

    connect(httpManager, SIGNAL(MemeLinkJsonReady(QJsonObject *)),
            this, SLOT(processMemeLinkJson(QJsonObject *)));

    connect(httpManager, SIGNAL(MapsJsonReady(QJsonObject *)),
            this, SLOT(processMapsJson(QJsonObject *)));

    connect(httpManager, SIGNAL(PushBulletJsonReady(QJsonObject *)),
            this, SLOT(processPushBulletJson(QJsonObject *)));

    connect(httpManager, SIGNAL(NewsJsonReady(QJsonObject *)),
            this, SLOT(processNewsJson(QJsonObject *)));
    //on_refreshButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentTime()
{
    QTime time = QTime::currentTime();
    QString hour = time.toString("hh");
    QString minute = time.toString("mm");
    QString second = time.toString("ss");

    ui->hourLCD->display(hour);
    ui->minuteLCD->display(minute);
    ui->secondLCD->display(second);
}

void MainWindow::processImage(QPixmap *image)
{

    ui->imageBox->setPixmap(*image);
}

void MainWindow::processStockJson(QJsonObject *json)
{
    qDebug() << "Json ready";

    QString stockSymbol = json->value("Global Quote").toObject()["01. symbol"].toString();
    QString stockPrice = json->value("Global Quote").toObject()["05. price"].toString();
    QString stockPercentChange = json->value("Global Quote").toObject()["10. change percent"].toString();

    qDebug() << stockSymbol;
    qDebug() << stockPrice;
    qDebug() << stockPercentChange;

    ui->stockSym1->setText(stockSymbol);
    ui->stockPrice1->setText("$ " + stockPrice);
    ui->stockPercent1->setText(stockPercentChange);

    if(stockPercentChange.length() > 0 && stockPercentChange.startsWith("-")){
        ui->stockPercent1->setStyleSheet("color: red;");
        ui->stockPrice1->setStyleSheet("color: red;");
    }else{
        ui->stockPercent1->setStyleSheet("color: green;");
        ui->stockPrice1->setStyleSheet("color: green;");
    }


    //{
    //    "Global Quote": {
    //        "01. symbol": "MSFT",
    //        "02. open": "163.3200",
    //        "03. high": "167.0300",
    //        "04. low": "157.9800",
    //        "05. price": "158.1800",
    //        "06. volume": "92533438",
    //        "07. latest trading day": "2020-02-27",
    //        "08. previous close": "170.1700",
    //        "09. change": "-11.9900",
    //        "10. change percent": "-7.0459%"
    //    }
    //}

}

void MainWindow::processStockTwoJson(QJsonObject *json)
{
    qDebug() << "Json ready";

    QString stockSymbol = json->value("Global Quote").toObject()["01. symbol"].toString();
    QString stockPrice = json->value("Global Quote").toObject()["05. price"].toString();
    QString stockPercentChange = json->value("Global Quote").toObject()["10. change percent"].toString();

    qDebug() << stockSymbol;
    qDebug() << stockPrice;
    qDebug() << stockPercentChange;

    ui->stockSym1_2->setText(stockSymbol);
    ui->stockPrice1_2->setText("$ " + stockPrice);
    ui->stockPercent1_2->setText(stockPercentChange);

    if(stockPercentChange.length() > 0 && stockPercentChange.startsWith("-")){
        ui->stockPercent1_2->setStyleSheet("color: red;");
        ui->stockPrice1_2->setStyleSheet("color: red;");
    }else{
        ui->stockPercent1_2->setStyleSheet("color: green;");
        ui->stockPrice1_2->setStyleSheet("color: green;");
    }


    //{
    //    "Global Quote": {
    //        "01. symbol": "MSFT",
    //        "02. open": "163.3200",
    //        "03. high": "167.0300",
    //        "04. low": "157.9800",
    //        "05. price": "158.1800",
    //        "06. volume": "92533438",
    //        "07. latest trading day": "2020-02-27",
    //        "08. previous close": "170.1700",
    //        "09. change": "-11.9900",
    //        "10. change percent": "-7.0459%"
    //    }
    //}

}

void MainWindow::processMemeLinkJson(QJsonObject *json)
{
    qDebug() << "Json ready";
    qDebug() << json;
    QJsonValue memeUrl = json->value("url");

    qDebug() << memeUrl;

    httpManager->sendImageRequest(memeUrl.toString());

    // {"postLink":"https://redd.it/faf0dr","subreddit":"dankmemes","title":"Time to commit aliven't","url":"https://i.redd.it/gouzx46ayhj41.jpg"}

}

void MainWindow::processMapsJson(QJsonObject *json)
{
    qDebug() << "Json ready";

    QString timeToWorkVal = "5 min";//json->value("rows").toArray()[0].toObject()["elements"].toArray()[0].toObject()["duration"].toObject()["text"].toString();

    qDebug() << timeToWorkVal;


    ui->timeToWorkDisVal->setText(timeToWorkVal);

//    {
//       "destination_addresses" : [ "Seattle, WA 98119, USA" ],
//       "origin_addresses" : [ "Lynnwood, WA 98037, USA" ],
//       "rows" : [
//          {
//             "elements" : [
//                {
//                   "distance" : {
//                      "text" : "27.2 km",
//                      "value" : 27174
//                   },
//                   "duration" : {
//                      "text" : "30 mins",
//                      "value" : 1803
//                   },
//                   "status" : "OK"
//                }
//             ]
//          }
//       ],
//       "status" : "OK"
//    }

}

void MainWindow::processPushBulletJson(QJsonObject *json)
{
    qDebug() << "Json ready";


    qDebug() << json;
    ui->pushBullMsg->clear();


//    {
//        "active": true,
//        "iden": "REDACTED",
//        "created": 1582921781.1249077,
//        "modified": 1582921781.1327956,
//        "type": "note",
//        "dismissed": false,
//        "direction": "self",
//        "sender_iden": "REDACTED",
//        "sender_email": "REDACTED",
//        "sender_email_normalized": "REDACTED",
//        "sender_name": "REDACTED",
//        "receiver_iden": "REDACTED",
//        "receiver_email": "REDACTED",
//        "receiver_email_normalized": "REDACTED",
//        "title": "ahhhhhh",
//        "body": "yeah boi!"
//    }

}

void MainWindow::processNewsJson(QJsonObject *json)
{
    qDebug() << "Json ready";
    QString news1 = json->value("articles").toArray()[0].toObject()["title"].toString();
    QString news2 = json->value("articles").toArray()[1].toObject()["title"].toString();
    QString news3 = json->value("articles").toArray()[2].toObject()["title"].toString();
    QString news4 = json->value("articles").toArray()[3].toObject()["title"].toString();

    ui -> newsBox1 -> setText(news1);
    ui -> newsBox2 -> setText(news2);
    ui -> newsBox3 -> setText(news3);
    ui -> newsBox4 -> setText(news4);

    qDebug() << news1;
    qDebug() << news2;
    qDebug() << news3;
    qDebug() << news4;
//    QString newsUrl = json->value("articles").toArray()[0].toObject()["url"].toString();
//    QString newsDesc = json->value("articles").toArray()[0].toObject()["description"].toString();
//    QString newsImage = json->value("articles").toArray()[0].toObject()["urlToImage"].toString();
}


void MainWindow::on_pushBullSendButton_clicked()
{
    httpManager->sendPushBulletRequest(ui->pushBullMsg->text());
}

void MainWindow::on_refreshButton_clicked()
{
    // Time to work
    httpManager->mapsRequest("98037", "98119");

    // Meme
    httpManager->sendMemeLinkRequest();

    // Stocks
    httpManager->sendStockRequest("MSFT");
    httpManager->sendStockRequestTwo("NVDA");

    // News
    httpManager -> sendNewsRequest();


}
