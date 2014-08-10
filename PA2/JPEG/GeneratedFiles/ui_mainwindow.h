/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *img_original;
    QPushButton *Browsefor;
    QLabel *img_processed;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *verYCha;
    QPushButton *verQA;
    QPushButton *verQB;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1452, 679);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        img_original = new QLabel(centralWidget);
        img_original->setObjectName(QStringLiteral("img_original"));
        img_original->setGeometry(QRect(36, 48, 640, 480));
        img_original->setAutoFillBackground(true);
        img_original->setAlignment(Qt::AlignCenter);
        Browsefor = new QPushButton(centralWidget);
        Browsefor->setObjectName(QStringLiteral("Browsefor"));
        Browsefor->setGeometry(QRect(452, 8, 75, 23));
        img_processed = new QLabel(centralWidget);
        img_processed->setObjectName(QStringLiteral("img_processed"));
        img_processed->setGeometry(QRect(764, 48, 640, 480));
        img_processed->setAutoFillBackground(true);
        img_processed->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(196, 552, 305, 85));
        label->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("System"));
        font.setPointSize(25);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(948, 552, 305, 85));
        label_2->setMaximumSize(QSize(16777215, 16777215));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(328, 12, 113, 13));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        verYCha = new QPushButton(centralWidget);
        verYCha->setObjectName(QStringLiteral("verYCha"));
        verYCha->setGeometry(QRect(960, 8, 85, 23));
        verQA = new QPushButton(centralWidget);
        verQA->setObjectName(QStringLiteral("verQA"));
        verQA->setGeometry(QRect(1060, 8, 85, 23));
        verQB = new QPushButton(centralWidget);
        verQB->setObjectName(QStringLiteral("verQB"));
        verQB->setGeometry(QRect(1156, 8, 85, 23));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        img_original->setText(QApplication::translate("MainWindow", "Get your image", 0));
        Browsefor->setText(QApplication::translate("MainWindow", "Browse...", 0));
        img_processed->setText(QApplication::translate("MainWindow", "Encoded", 0));
        label->setText(QApplication::translate("MainWindow", "Original File", 0));
        label_2->setText(QApplication::translate("MainWindow", "Encoded\343\200\200File", 0));
        label_3->setText(QApplication::translate("MainWindow", "Get your image here...", 0));
        verYCha->setText(QApplication::translate("MainWindow", "See Y Channel", 0));
        verQA->setText(QApplication::translate("MainWindow", "Quantization A", 0));
        verQB->setText(QApplication::translate("MainWindow", "Quantization B", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
