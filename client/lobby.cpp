#include "lobby.h"
#include "ui_lobby.h"

lobby::lobby(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::lobby)
{
    ui->setupUi(this);
}

lobby::~lobby()
{
    delete ui;
}

void lobby::on_toRegisterPageButton_clicked()
{
    emit goToRegisterPage();
    this->close();
}

void lobby::on_toLoginPageButton_clicked()
{
    emit goToLoginPage();
    this->close();
}

void lobby::on_toChatForAllButton_clicked()
{
    emit goToChatPage();
    this->close();
}



