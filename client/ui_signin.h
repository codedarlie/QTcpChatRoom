/********************************************************************************
** Form generated from reading UI file 'signin.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNIN_H
#define UI_SIGNIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_signIn
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *loginLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *passwordLineEdit;
    QPushButton *signInButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *goToLobbyButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *goToSignUpButton;

    void setupUi(QDialog *signIn)
    {
        if (signIn->objectName().isEmpty())
            signIn->setObjectName("signIn");
        signIn->resize(315, 300);
        signIn->setSizeGripEnabled(false);
        signIn->setModal(false);
        gridLayout_2 = new QGridLayout(signIn);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(signIn);
        label->setObjectName("label");
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setHintingPreference(QFont::PreferDefaultHinting);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(signIn);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_2);

        loginLineEdit = new QLineEdit(signIn);
        loginLineEdit->setObjectName("loginLineEdit");

        horizontalLayout->addWidget(loginLineEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(signIn);
        label_3->setObjectName("label_3");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_3);

        passwordLineEdit = new QLineEdit(signIn);
        passwordLineEdit->setObjectName("passwordLineEdit");

        horizontalLayout_2->addWidget(passwordLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_2);

        signInButton = new QPushButton(signIn);
        signInButton->setObjectName("signInButton");
        signInButton->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(signInButton->sizePolicy().hasHeightForWidth());
        signInButton->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(signInButton);


        gridLayout->addLayout(verticalLayout_2, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        goToLobbyButton = new QPushButton(signIn);
        goToLobbyButton->setObjectName("goToLobbyButton");

        horizontalLayout_3->addWidget(goToLobbyButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        goToSignUpButton = new QPushButton(signIn);
        goToSignUpButton->setObjectName("goToSignUpButton");

        horizontalLayout_3->addWidget(goToSignUpButton);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        retranslateUi(signIn);

        QMetaObject::connectSlotsByName(signIn);
    } // setupUi

    void retranslateUi(QDialog *signIn)
    {
        signIn->setWindowTitle(QCoreApplication::translate("signIn", "\320\236\320\272\320\275\320\276 \320\262\321\205\320\276\320\264\320\260", nullptr));
        label->setText(QCoreApplication::translate("signIn", "\320\222\321\205\320\276\320\264", nullptr));
        label_2->setText(QCoreApplication::translate("signIn", "\320\233\320\276\320\263\320\270\320\275:", nullptr));
        label_3->setText(QCoreApplication::translate("signIn", "\320\237\320\260\321\200\320\276\320\273\321\214:", nullptr));
        signInButton->setText(QCoreApplication::translate("signIn", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        goToLobbyButton->setText(QCoreApplication::translate("signIn", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        goToSignUpButton->setText(QCoreApplication::translate("signIn", "\320\235\320\265\321\202 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class signIn: public Ui_signIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNIN_H
