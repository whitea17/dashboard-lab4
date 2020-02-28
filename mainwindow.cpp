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

//    connect(timer, SIGNAL(timeout()),
//            this, SLOT(setCurrentTime()));

//    setCurrentTime();
//    timer->start(1000);

//    connect(httpManager, SIGNAL(ImageReady(QPixmap *)),
//            this, SLOT(processImage(QPixmap *)));

    connect(httpManager, SIGNAL(StockJsonReady(QJsonObject *)),
            this, SLOT(processStockJson(QJsonObject *)));

    connect(httpManager, SIGNAL(StockTwoJsonReady(QJsonObject *)),
            this, SLOT(processStockTwoJson(QJsonObject *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::setCurrentTime()
//{
//    QTime time = QTime::currentTime();
//    QString hour = time.toString("hh");
//    QString minute = time.toString("mm");
//    QString second = time.toString("ss");

//    ui->hourLCD->display(hour);
//    ui->minuteLCD->display(hour);
//    ui->secondLCD->display(second);
//}

//void MainWindow::processImage(QPixmap *image)
//{
//    ui->imageLabel->setPixmap(*image);
//}

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

    if(stockPercentChange.startsWith("-")){
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

    if(stockPercentChange.startsWith("-")){
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

//void MainWindow::on_imageDownloadButton_clicked()
//{
//    QString zip = ui->zipCodeEdit->text();
//    qDebug() << zip;
//    httpManager->sendImageRequest(zip);
//}


void MainWindow::on_stockDown_clicked()
{
    QString sym = "MSFT";

    qDebug() << sym;
    httpManager->sendStockRequest(sym);
    httpManager->sendStockRequestTwo("NVDA");

}
