/********************************************************************************
** Form generated from reading UI file 'lecteurvue.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LECTEURVUE_H
#define UI_LECTEURVUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lecteurVue
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *lecteurVue)
    {
        if (lecteurVue->objectName().isEmpty())
            lecteurVue->setObjectName(QString::fromUtf8("lecteurVue"));
        lecteurVue->resize(800, 600);
        centralwidget = new QWidget(lecteurVue);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lecteurVue->setCentralWidget(centralwidget);
        menubar = new QMenuBar(lecteurVue);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        lecteurVue->setMenuBar(menubar);
        statusbar = new QStatusBar(lecteurVue);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        lecteurVue->setStatusBar(statusbar);

        retranslateUi(lecteurVue);

        QMetaObject::connectSlotsByName(lecteurVue);
    } // setupUi

    void retranslateUi(QMainWindow *lecteurVue)
    {
        lecteurVue->setWindowTitle(QCoreApplication::translate("lecteurVue", "lecteurVue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lecteurVue: public Ui_lecteurVue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECTEURVUE_H
