#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnDeposit_clicked()
{
    QString amount=ui->lineDepositAmount->text();
    QJsonObject json_obj;
    json_obj.insert("amount",amount);
    QString site_url="http://localhost:3000/transactions/debit_transaction";
    QString credentials="automat123:pass123";
    QNetworkRequest request((site_url)); request.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    DepositManager = new QNetworkAccessManager(this);
    connect(DepositManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(DepositSlot(QNetworkReply*)));
    DepositReply=DepositManager->post(request, QJsonDocument(json_obj).toJson());
}
void MainWindow::DepositSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("4078")==0){
        ui->labelResult->setText("Virhe tietokantayhteydessä");
    }
    else if(response_data.compare("0")==0){
        ui->labelResult->setText("Talletus ei onnistu");
    }
    else{
        ui->labelResult->setText("Talletus onnistui");
    }
    DepositReply->deleteLater();
    reply->deleteLater();
    DepositManager->deleteLater();
}

void MainWindow::on_btnWithdraw_clicked()
{
    QString amount=ui->lineWithdrawAmount->text();
    QJsonObject json_obj;
    json_obj.insert("amount",amount);
    QString site_url="http://localhost:3000/transactions/debit_transaction";
    QString credentials="automat123:pass123";
    QNetworkRequest request((site_url)); request.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    WithdrawManager = new QNetworkAccessManager(this);
    connect(WithdrawManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(WithdrawSlot(QNetworkReply*)));
    WithdrawReply=WithdrawManager->post(request, QJsonDocument(json_obj).toJson());
}
void MainWindow::WithdrawSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("-4078")==0){
        ui->labelResult->setText("Virhe tietokantayhteydessä");
    }
    else if(response_data.compare("0")==0){
        ui->labelResult->setText("Nosto ei onnistu");
    }
    else{
        ui->labelResult->setText("Nosto onnistui");
    }
    WithdrawReply->deleteLater();
    reply->deleteLater();
    WithdrawManager->deleteLater();
}
