#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

#include "httpmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setCurrentTime();
    void processImage(QPixmap *);
    void processStockJson(QJsonObject *json);
    void processStockTwoJson(QJsonObject *json);
    void processMemeLinkJson(QJsonObject *json);
    void processMapsJson(QJsonObject *json);
    void processPushBulletJson(QJsonObject *json);
    void processNewsJson(QJsonObject *json);


    void on_pushBullSendButton_clicked();

    void on_refreshButton_clicked();

    void on_pushBullMsg_returnPressed();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    HTTPManager *httpManager;

};

#endif // MAINWINDOW_H
