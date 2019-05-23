/********************************************************************************
** Form generated from reading UI file 'QtD3d9Player.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTD3D9PLAYER_H
#define UI_QTD3D9PLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtD3d9PlayerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtD3d9PlayerClass)
    {
        if (QtD3d9PlayerClass->objectName().isEmpty())
            QtD3d9PlayerClass->setObjectName(QStringLiteral("QtD3d9PlayerClass"));
        QtD3d9PlayerClass->resize(600, 400);
        menuBar = new QMenuBar(QtD3d9PlayerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtD3d9PlayerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtD3d9PlayerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtD3d9PlayerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtD3d9PlayerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtD3d9PlayerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtD3d9PlayerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtD3d9PlayerClass->setStatusBar(statusBar);

        retranslateUi(QtD3d9PlayerClass);

        QMetaObject::connectSlotsByName(QtD3d9PlayerClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtD3d9PlayerClass)
    {
        QtD3d9PlayerClass->setWindowTitle(QApplication::translate("QtD3d9PlayerClass", "QtD3d9Player", 0));
    } // retranslateUi

};

namespace Ui {
    class QtD3d9PlayerClass: public Ui_QtD3d9PlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTD3D9PLAYER_H
