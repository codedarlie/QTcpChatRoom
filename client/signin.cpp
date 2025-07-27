#include "signin.h"
#include "ui_signin.h"


signIn::signIn(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signIn)
{
    ui->setupUi(this);
}

signIn::~signIn()
{
    delete ui;
}

void signIn::on_goToLobbyButton_clicked()
{
    this->close();
    emit switchToLobby();
}

void signIn::on_goToSignUpButton_clicked()
{
    this->close();
    emit switchTosignUp();
}

void signIn::on_signInButton_clicked() {
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    jsonSendData = QJsonObject();
    jsonSendData.insert("login", login);
    jsonSendData.insert("password", password);
    jsonSendType = "signIn";

    emit signInAccount();
}


void signIn::on_loginLineEdit_textChanged(const QString &arg1)
{
    ui->signInButton->setEnabled(!(ui->passwordLineEdit->text().size() < 1 || arg1.size() < 1));
}


void signIn::on_passwordLineEdit_textChanged(const QString &arg1)
{
    ui->signInButton->setEnabled(!(arg1.size() < 1 || ui->loginLineEdit->text().size() < 1));
}

QString signIn::getJsonSendType() const {
    return jsonSendType;
}

QJsonObject signIn::getJsonSendData() const {
    return jsonSendData;
}

