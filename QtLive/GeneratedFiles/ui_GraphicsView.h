/********************************************************************************
** Form generated from reading UI file 'GraphicsView.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICSVIEW_H
#define UI_GRAPHICSVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphicsView
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *GraphicsView)
    {
        if (GraphicsView->objectName().isEmpty())
            GraphicsView->setObjectName(QStringLiteral("GraphicsView"));
        GraphicsView->resize(400, 300);
        pushButton = new QPushButton(GraphicsView);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(150, 60, 75, 23));
        pushButton_2 = new QPushButton(GraphicsView);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 170, 75, 23));

        retranslateUi(GraphicsView);

        QMetaObject::connectSlotsByName(GraphicsView);
    } // setupUi

    void retranslateUi(QWidget *GraphicsView)
    {
        GraphicsView->setWindowTitle(QApplication::translate("GraphicsView", "GraphicsView", Q_NULLPTR));
        pushButton->setText(QApplication::translate("GraphicsView", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("GraphicsView", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GraphicsView: public Ui_GraphicsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICSVIEW_H
