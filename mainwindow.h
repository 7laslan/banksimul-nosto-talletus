#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnDeposit_clicked();
    void on_btnWithdraw_clicked();

    void DepositSlot(QNetworkReply *reply);
    void WithdrawSlot(QNetworkReply *reply);

    void on_lineID_textChanged(const QString &arg1);
    void on_lineAccNum_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *DepositManager;
    QNetworkReply *DepositReply;

    QNetworkAccessManager *WithdrawManager;
    QNetworkReply *WithdrawReply;
};
#endif // MAINWINDOW_H
