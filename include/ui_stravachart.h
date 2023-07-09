/********************************************************************************
** Form generated from reading UI file 'stravachart.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STRAVACHART_H
#define UI_STRAVACHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StravaChart
{
public:
    QWidget *centralwidget;
    QComboBox *comboBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StravaChart)
    {
        if (StravaChart->objectName().isEmpty())
            StravaChart->setObjectName(QString::fromUtf8("StravaChart"));
        StravaChart->resize(800, 600);
        centralwidget = new QWidget(StravaChart);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(360, 0, 79, 23));
        StravaChart->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StravaChart);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        StravaChart->setMenuBar(menubar);
        statusbar = new QStatusBar(StravaChart);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        StravaChart->setStatusBar(statusbar);

        retranslateUi(StravaChart);

        QMetaObject::connectSlotsByName(StravaChart);
    } // setupUi

    void retranslateUi(QMainWindow *StravaChart)
    {
        StravaChart->setWindowTitle(QCoreApplication::translate("StravaChart", "StravaChart", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("StravaChart", "Test123", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("StravaChart", "Testt456", nullptr));

    } // retranslateUi

};

namespace Ui {
    class StravaChart: public Ui_StravaChart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STRAVACHART_H
