#ifndef LOBBY_H
#define LOBBY_H

#include <QDialog>

namespace Ui {
class lobby;
}

class lobby : public QDialog
{
    Q_OBJECT

public:
    explicit lobby(QWidget *parent = nullptr);
    ~lobby();

signals:
    void goToRegisterPage();
    void goToLoginPage();
    void goToChatPage();

private slots:
    void on_toRegisterPageButton_clicked();
    void on_toLoginPageButton_clicked();
    void on_toChatForAllButton_clicked();

private:
    Ui::lobby *ui;
};

#endif // LOBBY_H
