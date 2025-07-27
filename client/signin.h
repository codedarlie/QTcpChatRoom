#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include <QByteArray>
#include <QJsonObject>

namespace Ui {
class signIn;
}

class signIn : public QDialog
{
    Q_OBJECT

public:
    explicit signIn(QWidget *parent = nullptr);
    ~signIn();

    QString getJsonSendType() const;
    QJsonObject getJsonSendData() const;

signals:
    void switchTosignUp();
    void switchToLobby();
    void signInAccount();

private slots:
    void on_goToLobbyButton_clicked();
    void on_goToSignUpButton_clicked();
    void on_signInButton_clicked();
    void on_loginLineEdit_textChanged(const QString &arg1);
    void on_passwordLineEdit_textChanged(const QString &arg1);

private:
    Ui::signIn *ui;
    QByteArray byteArray;

    QJsonObject jsonSendData;
    QString jsonSendType;
};

#endif // SIGNIN_H
