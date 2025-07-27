#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QByteArray>
#include <QJsonObject>

namespace Ui {
class signUp;
}

class signUp : public QDialog
{
    Q_OBJECT

public:
    explicit signUp(QWidget *parent = nullptr);
    ~signUp();

    void clearSignUpLoginLineEdit() const;

    QString getJsonSendType() const;
    QJsonObject getJsonSendData() const;

signals:
    void switchToLobby();
    void switchTosignIn();
    void signUpAccount();

private slots:
    void on_goToLobbyButton_clicked();
    void on_goToSignInButton_clicked();
    void on_registerPushButton_clicked();
    void on_loginLineEdit_textChanged(const QString &arg1);
    void on_passwordLineEdit_textChanged(const QString &arg1);

private:
    Ui::signUp *ui;
    QByteArray byteArray;

    QJsonObject jsonSendData;
    QString jsonSendType;
};

#endif // SIGNUP_H
