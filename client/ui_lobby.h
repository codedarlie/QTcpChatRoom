/********************************************************************************
** Form generated from reading UI file 'lobby.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOBBY_H
#define UI_LOBBY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_lobby
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *toRegisterPageButton;
    QPushButton *toLoginPageButton;
    QLabel *label;
    QPushButton *toChatForAllButton;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *lobby)
    {
        if (lobby->objectName().isEmpty())
            lobby->setObjectName("lobby");
        lobby->resize(299, 294);
        gridLayout = new QGridLayout(lobby);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        toRegisterPageButton = new QPushButton(lobby);
        toRegisterPageButton->setObjectName("toRegisterPageButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toRegisterPageButton->sizePolicy().hasHeightForWidth());
        toRegisterPageButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(toRegisterPageButton);

        toLoginPageButton = new QPushButton(lobby);
        toLoginPageButton->setObjectName("toLoginPageButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toLoginPageButton->sizePolicy().hasHeightForWidth());
        toLoginPageButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(toLoginPageButton);

        label = new QLabel(lobby);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        toChatForAllButton = new QPushButton(lobby);
        toChatForAllButton->setObjectName("toChatForAllButton");
        sizePolicy1.setHeightForWidth(toChatForAllButton->sizePolicy().hasHeightForWidth());
        toChatForAllButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(toChatForAllButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);


        retranslateUi(lobby);

        toLoginPageButton->setDefault(false);


        QMetaObject::connectSlotsByName(lobby);
    } // setupUi

    void retranslateUi(QDialog *lobby)
    {
        lobby->setWindowTitle(QCoreApplication::translate("lobby", "\320\236\320\272\320\275\320\276 \320\273\320\276\320\261\320\261\320\270", nullptr));
        toRegisterPageButton->setText(QCoreApplication::translate("lobby", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        toLoginPageButton->setText(QCoreApplication::translate("lobby", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        label->setText(QCoreApplication::translate("lobby", "\320\230\320\273\320\270", nullptr));
        toChatForAllButton->setText(QCoreApplication::translate("lobby", "\320\222\320\276\320\271\321\202\320\270 \320\262 \320\276\320\261\321\211\320\270\320\271 \321\207\320\260\321\202 \320\261\320\265\320\267 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lobby: public Ui_lobby {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOBBY_H
