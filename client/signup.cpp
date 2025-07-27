#include "signup.h"
#include "ui_signup.h"

signUp::signUp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signUp)
{
    ui->setupUi(this);
}

signUp::~signUp()
{
    delete ui;
}

void signUp::on_goToLobbyButton_clicked()
{
    this->close();
    emit switchToLobby();
}

void signUp::on_goToSignInButton_clicked()
{
    this->close();
    emit switchTosignIn();
}

void signUp::on_registerPushButton_clicked() {
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    jsonSendData = QJsonObject();
    jsonSendData.insert("login", login);
    jsonSendData.insert("password", password);
    jsonSendType = "signUp";

    emit signUpAccount();
}

void signUp::clearSignUpLoginLineEdit() const {
    ui->loginLineEdit->clear();
}

void signUp::on_loginLineEdit_textChanged(const QString &arg1)
{
    ui->registerPushButton->setEnabled(!(ui->passwordLineEdit->text().size() < 1 || arg1.size() < 1));
}

void signUp::on_passwordLineEdit_textChanged(const QString &arg1)
{
    ui->registerPushButton->setEnabled(!(arg1.size() < 1 || ui->loginLineEdit->text().size() < 1));
}

QString signUp::getJsonSendType() const {
    return jsonSendType;
}

QJsonObject signUp::getJsonSendData() const {
    return jsonSendData;
}
