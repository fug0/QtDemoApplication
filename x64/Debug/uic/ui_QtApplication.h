/********************************************************************************
** Form generated from reading UI file 'QtApplication.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTAPPLICATION_H
#define UI_QTAPPLICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtApplicationClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtApplicationClass)
    {
        if (QtApplicationClass->objectName().isEmpty())
            QtApplicationClass->setObjectName(QString::fromUtf8("QtApplicationClass"));
        QtApplicationClass->resize(600, 400);
        menuBar = new QMenuBar(QtApplicationClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QtApplicationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtApplicationClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtApplicationClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtApplicationClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QtApplicationClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtApplicationClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtApplicationClass->setStatusBar(statusBar);

        retranslateUi(QtApplicationClass);

        QMetaObject::connectSlotsByName(QtApplicationClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtApplicationClass)
    {
        QtApplicationClass->setWindowTitle(QCoreApplication::translate("QtApplicationClass", "QtApplication", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtApplicationClass: public Ui_QtApplicationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTAPPLICATION_H
