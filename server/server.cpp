#include "server.h"

server::server()
{
    if (this->listen(QHostAddress::Any, 2323)) qDebug() << "Server started";
    else qDebug() << "Error!";

    blockSize = 0;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./database.db");

    if (db.open()) qDebug("DataBase Opened");
    else qDebug("DataBase Not Opened");

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE Accounts(Id INTEGER PRIMARY KEY AUTOINCREMENT, Login TEXT, Password TEXT);");
    query->exec("CREATE TABLE Chat(Id INTEGER, NickName TEXT, Message TEXT, DateTime DATETIME);");
}

void server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &server::clientDisconnected);
    sockets.push_back(socket);
}

void server::clientDisconnected() {
    sockets.removeOne(socket);
    socket->deleteLater();
}

void server::slotReadyRead()
{
    socket = (QTcpSocket*)sender(); // сокет с которого пришел запрос
    QDataStream in(socket); // данные находятся тут
    in.setVersion(QDataStream::Qt_6_2); // указать версию наверняка
    if (in.status() == QDataStream::Ok) { // проверяем нет ли еще ошибок
        while (true) {
            if (blockSize == 0) {
                if (socket->bytesAvailable() < 2) break;
                in >> blockSize;
            }
            if (socket->bytesAvailable() < blockSize) break;

            byteArray.clear();
            in >> byteArray;
            blockSize = 0;

            QJsonObject json = QJsonDocument::fromJson(byteArray).object();
            QString type = json["type"].toString();

            if (type == "signUp") registerNewAccount(json);
            else if (type == "signIn") loginAccount(json);
            else if (type == "newMessage") updateChat(json);
            else if (type == "loadChatForUnreg") loadChat();

            break;
        }
    } else {
        qDebug() << "DataStream Error";
    }
}

void server::sendToClient(bool forAll = false) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly); // массив байтов и режим работы
    out.setVersion(QDataStream::Qt_6_2);
    out << quint16(0) << byteArray; // 0 чтобы выделились 2 байта
    out.device()->seek(0); // переходим в самое начало блока, туда запишем размер блока
    out << quint16(Data.size()-sizeof(quint16));
    if (forAll) {
        for (int i = 0; i < sockets.size(); ++i) sockets[i]->write(Data);
    } else socket->write(Data);
    byteArray.clear();
}

void server::createJson(bool forAll = false) {
    QJsonObject json;
    json["type"] = jsonSendType;
    json["data"] = jsonSendData;
    // qDebug().noquote() << QJsonDocument(json).toJson(QJsonDocument::Indented);
    byteArray = QJsonDocument(json).toJson(QJsonDocument::Compact);
    sendToClient(forAll);

    jsonSendData = QJsonObject();
    jsonSendType = QString();
}

void server::createMessageBox(QString messageType, QString message) {
    jsonSendData.insert("type", messageType);
    jsonSendData.insert("message", message);
    jsonSendType = "messagebox";
    createJson();
}

void server::registerNewAccount(const QJsonObject& json) {
    QJsonObject data = json["data"].toObject();
    QString clientLogin = data["login"].toString();
    QString clientPassword = data["password"].toString();

    if (clientPassword.size() < 1 || clientLogin.size() < 1) {
        createMessageBox("critical", "Не удалось провести регистрацию: минимальные допустимые размер логина - 1, пароля - 1.");
        return;
    }

    query->prepare("SELECT Login FROM Accounts WHERE Login = :login");
    query->bindValue(":login", clientLogin);
    query->exec();

    if ((query->next())) {
        createMessageBox("critical", "Не удалось провести регистрацию - уже есть пользователь с таким логином.");
    } else {
        query->prepare("INSERT INTO Accounts (Login, Password) VALUES (:login, :password)");
        query->bindValue(":login", clientLogin);
        query->bindValue(":password", clientPassword);
        query->exec();
        int clientId = query->lastInsertId().toInt();

        jsonSendData = QJsonObject();
        jsonSendData.insert("answer", "registered");
        jsonSendData.insert("giveName", clientLogin);
        jsonSendData.insert("giveId", clientId);
        jsonSendType = "registration";

        createJson();
        createMessageBox("information", "Ваш аккаунт успешно зарегистрирован!");

        loadChat();
    }
}

void server::loginAccount(const QJsonObject& json) {
    QJsonObject data = json["data"].toObject();
    QString clientLogin = data["login"].toString();
    QString clientPassword = data["password"].toString();

    if (clientPassword.size() < 1 || clientLogin.size() < 1) {
        createMessageBox("critical", "Не удалось войти в аккаунт: минимальные допустимые размер логина - 1, пароля - 1.");
        return;
    }

    query->prepare("SELECT Id, Login, Password FROM Accounts WHERE Login = :login AND Password = :password");
    query->bindValue(":login", clientLogin);
    query->bindValue(":password", clientPassword);
    query->exec();

    QJsonObject sendData;

    if (query->next()) {
        int clientId = query->value(0).toInt();

        jsonSendData = QJsonObject();
        jsonSendData.insert("answer", "logged");
        jsonSendData.insert("giveName", clientLogin);
        jsonSendData.insert("giveId", clientId);
        jsonSendType = "login";

        createJson();

        createMessageBox("information", "Вы успешно вошли в аккаунт!");
        loadChat();

    } else {
        createMessageBox("critical", "Не удалось войти в аккаунт - неверные данные.");
    }
}

void server::loadChat() {
    query->exec("SELECT * FROM Chat");

    QJsonArray messages;

    while (query->next()) { // Creating message
        QJsonObject message;
        message.insert("id", query->value(0).toString());
        message.insert("nickName", query->value(1).toString());
        message.insert("text", query->value(2).toString());

        { // Creating datetime
            QString dateTime = query->value(3).toDateTime().toString("yyyy-MM-dd HH:mm:ss");
            message.insert("dateTime", dateTime);
        }

        messages.append(message);
    }

    jsonSendData = QJsonObject();
    jsonSendData["messages"] = messages;
    jsonSendType = "loadChat";

    createJson();
}

void server::updateChat(QJsonObject& json) {
    QJsonObject data = json["data"].toObject();
    QJsonObject message = data["message"].toObject();

    int userId = message["id"].toInt();
    QString nickName = message["nickName"].toString();
    QString text = message["text"].toString();
    QString dateTime = message["dateTime"].toString();

    query->prepare("INSERT INTO Chat (Id, NickName, Message, DateTime) "
                  "VALUES (:id, :nickname, :message, :datetime)");
    query->bindValue(":id", userId);
    query->bindValue(":nickname", nickName);
    query->bindValue(":message", text);
    query->bindValue(":datetime", dateTime);
    query->exec();

    jsonSendData = data;
    jsonSendType = "updateChat";

    createJson(true);
}
