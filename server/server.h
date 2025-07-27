#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>

#include <QVector>

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QDateTime>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>

class server: public QTcpServer
{
    Q_OBJECT

public:
    server();
    QTcpSocket *socket;

private:
    QVector <QTcpSocket*> sockets;
    quint16 blockSize;

    QSqlDatabase db;
    QSqlQuery *query;

    QByteArray Data;
    QByteArray byteArray;

    QJsonObject jsonSendData;
    QString jsonSendType;

    void sendToClient(bool);
    void createJson(bool);
    void createMessageBox(QString, QString);

    void registerNewAccount(const QJsonObject&);
    void loginAccount(const QJsonObject&);
    void updateChat(QJsonObject&);
    void loadChat();

public slots:
    void incomingConnection(qintptr);
    void slotReadyRead();
    void clientDisconnected();
};

#endif // SERVER_H
