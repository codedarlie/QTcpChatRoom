#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QTimer>

#include "signup.h"
#include "signin.h"
#include "lobby.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendMessageButton_clicked();
    void on_textLineEdit_returnPressed();
    void on_goToLobbyButton_clicked();
    void on_textLineEdit_textChanged(const QString &arg1);

    void slotReadyRead();
    void serverDisconnected();
    void signInAccount();
    void signUpAccount();
    void showChatForUnreg();

private:
    Ui::MainWindow* ui;
    QTcpSocket* socket;
    bool connectedToSocket = false;
    quint16 blockSize;

    QByteArray Data;
    QByteArray byteArray;

    QJsonObject jsonSendData;
    QString jsonSendType;

    signUp* signup;
    signIn* signin;
    lobby* lobbyPage;

    void sendToServer();
    void createJson();
    void sendNewMessage();

    QString loginName = "Unnamed";
    int userId = -1;
};
#endif // MAINWINDOW_H
