/********************************************************************************
** Form generated from reading UI file 'QtLive.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTLIVE_H
#define UI_QTLIVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtLiveClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtLiveClass)
    {
        if (QtLiveClass->objectName().isEmpty())
            QtLiveClass->setObjectName(QStringLiteral("QtLiveClass"));
        QtLiveClass->resize(686, 476);
        centralWidget = new QWidget(QtLiveClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        widget->setPalette(palette);
        widget->setAutoFillBackground(true);

        gridLayout->addWidget(widget, 1, 0, 1, 3);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        QtLiveClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtLiveClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 686, 23));
        QtLiveClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtLiveClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtLiveClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtLiveClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtLiveClass->setStatusBar(statusBar);

        retranslateUi(QtLiveClass);

        QMetaObject::connectSlotsByName(QtLiveClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtLiveClass)
    {
        QtLiveClass->setWindowTitle(QApplication::translate("QtLiveClass", "QtLive", Q_NULLPTR));
        pushButton->setText(QApplication::translate("QtLiveClass", "PushButton", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("QtLiveClass", "rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtLiveClass: public Ui_QtLiveClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTLIVE_H
