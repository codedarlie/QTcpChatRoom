#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::serverDisconnected);

    blockSize = 0;

    signup = new signUp();
    signin = new signIn();
    lobbyPage = new lobby();

    connect(signup, &signUp::switchTosignIn, signin, &signIn::show);
    connect(signin, &signIn::switchTosignUp, signup, &signUp::show);

    connect(signup, &signUp::signUpAccount, this, &MainWindow::signUpAccount);
    connect(signin, &signIn::signInAccount, this, &MainWindow::signInAccount);

    connect(lobbyPage, &lobby::goToRegisterPage, signup, &signUp::show);
    connect(lobbyPage, &lobby::goToLoginPage, signin, &signIn::show);
    connect(lobbyPage, &lobby::goToChatPage, this, &MainWindow::showChatForUnreg);

    connect(signup, &signUp::switchToLobby, lobbyPage, &lobby::show);
    connect(signin, &signIn::switchToLobby, lobbyPage, &lobby::show);

    lobbyPage->show();
    QTimer::singleShot(0, this, &MainWindow::close); // this->close() не работает
}

MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
    delete signin;
    delete signup;
    delete lobbyPage;
}

void MainWindow::serverDisconnected() {
    ui->textLineEdit->clear();
    ui->textLineEdit->setText("Сервер отключился...");
    ui->textLineEdit->setEnabled(false);
    ui->sendMessageButton->setEnabled(false);
    ui->goToLobbyButton->hide();
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket); // работа с данными которые там находятся
    in.setVersion(QDataStream::Qt_6_2); // указать версию наверняка
    if (in.status() == QDataStream::Ok) {
        while (true) {
            // qDebug() << "socket->bytesAvailable() = " << socket->bytesAvailable();
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
            QJsonObject data = json["data"].toObject();

            if (type == "messagebox") {
                QString messageboxtype = data["type"].toString();
                QString messageboxmessage = data["message"].toString();

                if (messageboxtype == "critical") QMessageBox::critical(this, "Сообщение от сервера", messageboxmessage);
                else if (messageboxtype == "information") QMessageBox::information(this, "Сообщение от сервера", messageboxmessage);

            } else if (type == "registration") {
                QString answer = data["answer"].toString();
                if (answer == "registered") {
                    loginName = data["giveName"].toString();

                    signup->close();

                    this->show();
                    ui->goToLobbyButton->close();
                } else signup->clearSignUpLoginLineEdit();
            } else if (type == "login") {
                QString answer = data["answer"].toString();
                if (answer == "logged") {
                    loginName = data["giveName"].toString();
                    userId = data["giveId"].toInt();

                    signin->close();

                    this->show();
                    ui->goToLobbyButton->close();
                }
            } else if (type == "loadChat") {
                QJsonArray messages = data["messages"].toArray();
                for (const QJsonValue& message: messages) {
                    QDateTime datetime = QDateTime::fromString(message["dateTime"].toString(), "yyyy-MM-dd HH:mm:ss");
                    QString time = datetime.time().toString("HH:mm");

                    QString str = "<span style=\"color: #7d7d7d;\">" + time + "</span> | <b>" + message["nickName"].toString() + "</b>: " + message["text"].toString();
                    ui->textBrowser->append(str);
                }
            } else if (type == "updateChat") {
                QJsonObject message = data["message"].toObject();

                QDateTime datetime = QDateTime::fromString(message["dateTime"].toString(), "yyyy-MM-dd HH:mm:ss");
                QString time = datetime.time().toString("HH:mm");

                QString str = "<span style=\"color: #7d7d7d;\">" + time + "</span> | <b>" + message["nickName"].toString() + "</b>: " + message["text"].toString();
                ui->textBrowser->append(str);
            }
        }
    } else qDebug() << "Read Error";
}

void MainWindow::sendToServer()
{
    if (!connectedToSocket) {
        socket->connectToHost("127.0.0.1", 2323);
        connectedToSocket = true;
    }
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly); // массив байтов и режим работы
    out.setVersion(QDataStream::Qt_6_2);
    out << quint16(0) << byteArray; // 0 чтобы выделились 2 байта
    out.device()->seek(0); // переходим в самое начало блока, туда запишем размер блока
    out << quint16(Data.size()-sizeof(quint16));
    socket->write(Data);
    byteArray.clear();
}

void MainWindow::signUpAccount() {
    jsonSendType = signup->getJsonSendType();
    jsonSendData = signup->getJsonSendData();
    createJson();
}

void MainWindow::signInAccount() {
    jsonSendType = signin->getJsonSendType();
    jsonSendData = signin->getJsonSendData();
    createJson();
}

void MainWindow::createJson() {
    QJsonObject json;
    json["type"] = jsonSendType;
    json["data"] = jsonSendData;
    // qDebug().noquote() << QJsonDocument(json).toJson(QJsonDocument::Indented);
    byteArray = QJsonDocument(json).toJson(QJsonDocument::Compact);
    sendToServer();

    jsonSendData = QJsonObject();
    jsonSendType = QString();
}

void MainWindow::on_sendMessageButton_clicked() {
    sendNewMessage();
}

void MainWindow::on_textLineEdit_returnPressed() {
    sendNewMessage();
}

void MainWindow::sendNewMessage() {
    if (ui->textLineEdit->text().size() > 0) {

        jsonSendType = "newMessage";
        jsonSendData = QJsonObject();

        { // Creating message
            QJsonObject message;
            message.insert("id", userId);
            message.insert("nickName", loginName);
            message.insert("text", ui->textLineEdit->text());

            { // Creating datetime
                QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
                message.insert("dateTime", dateTime);
            }
            jsonSendData["message"] = message;
        }

        createJson();
        ui->textLineEdit->clear();
    }
}

void MainWindow::on_goToLobbyButton_clicked()
{
    ui->textBrowser->clear();
    this->close();
    lobbyPage->show();
}

void MainWindow::showChatForUnreg() {
    this->show();

    jsonSendType = "loadChatForUnreg";
    jsonSendData = QJsonObject();
    createJson();
}

void MainWindow::on_textLineEdit_textChanged(const QString &arg1)
{
    ui->sendMessageButton->setEnabled(arg1.size() > 0);
}

