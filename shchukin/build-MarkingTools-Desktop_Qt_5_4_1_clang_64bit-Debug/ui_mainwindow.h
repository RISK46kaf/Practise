/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QFrame *frame_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *openButton;
    QLabel *label_2;
    QPushButton *zoomInButton;
    QFrame *frame_9;
    QPushButton *zoomOutButton;
    QFrame *frame_8;
    QPushButton *zoomAutoButton;
    QLabel *label_3;
    QTreeWidget *treeWidget;
    QFrame *frame_10;
    QPushButton *newButton;
    QFrame *frame_11;
    QPushButton *remButton;
    QFrame *frame_12;
    QLabel *label;
    QPushButton *arrButton;
    QFrame *frame_7;
    QPushButton *bboxButton;
    QFrame *frame_6;
    QPushButton *ellButton;
    QFrame *frame_5;
    QPushButton *polyButton;
    QFrame *frame_4;
    QPushButton *pushButton;
    QFrame *frame_13;
    QPushButton *confButton;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1165, 705);
        MainWindow->setMinimumSize(QSize(1145, 705));
        MainWindow->setStyleSheet(QStringLiteral("background-color: #303030;color: white;disabled{ background-color: #white};"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(1145, 649));
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 1218, 641));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(layoutWidget1);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(805, 605));
        gridLayoutWidget = new QWidget(frame);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(90, 70, 807, 607));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(gridLayoutWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setMinimumSize(QSize(805, 605));
        scrollArea->setWidgetResizable(false);
        scrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(78, 53, 647, 497));
        scrollArea->setWidget(scrollAreaWidgetContents);
        layoutWidget1->raise();

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        horizontalLayout->addWidget(frame);

        frame_2 = new QFrame(layoutWidget1);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(250);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setMinimumSize(QSize(250, 0));
        frame_2->setStyleSheet(QStringLiteral(""));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Raised);
        layoutWidget = new QWidget(frame_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 50, 226, 956));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        openButton = new QPushButton(layoutWidget);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setStyleSheet(QStringLiteral("background-color: #505050;"));

        verticalLayout->addWidget(openButton);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        zoomInButton = new QPushButton(layoutWidget);
        zoomInButton->setObjectName(QStringLiteral("zoomInButton"));
        zoomInButton->setEnabled(false);
        zoomInButton->setStyleSheet(QStringLiteral("background-color: #505050;"));

        verticalLayout->addWidget(zoomInButton);

        frame_9 = new QFrame(layoutWidget);
        frame_9->setObjectName(QStringLiteral("frame_9"));
        frame_9->setMinimumSize(QSize(0, 0));
        frame_9->setMaximumSize(QSize(16777215, 1));
        frame_9->setFrameShape(QFrame::NoFrame);
        frame_9->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame_9);

        zoomOutButton = new QPushButton(layoutWidget);
        zoomOutButton->setObjectName(QStringLiteral("zoomOutButton"));
        zoomOutButton->setEnabled(false);
        zoomOutButton->setStyleSheet(QStringLiteral("background-color: #505050;"));

        verticalLayout->addWidget(zoomOutButton);

        frame_8 = new QFrame(layoutWidget);
        frame_8->setObjectName(QStringLiteral("frame_8"));
        frame_8->setMaximumSize(QSize(16777215, 1));
        frame_8->setFrameShape(QFrame::NoFrame);
        frame_8->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame_8);

        zoomAutoButton = new QPushButton(layoutWidget);
        zoomAutoButton->setObjectName(QStringLiteral("zoomAutoButton"));
        zoomAutoButton->setEnabled(false);
        zoomAutoButton->setStyleSheet(QStringLiteral("background-color: #505050;"));

        verticalLayout->addWidget(zoomAutoButton);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        treeWidget = new QTreeWidget(layoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);

        frame_10 = new QFrame(layoutWidget);
        frame_10->setObjectName(QStringLiteral("frame_10"));
        frame_10->setMinimumSize(QSize(0, 0));
        frame_10->setMaximumSize(QSize(16777215, 1));
        frame_10->setFrameShape(QFrame::NoFrame);
        frame_10->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame_10);

        newButton = new QPushButton(layoutWidget);
        newButton->setObjectName(QStringLiteral("newButton"));
        newButton->setEnabled(false);
        newButton->setStyleSheet(QStringLiteral("background-color: #505050;"));

        verticalLayout->addWidget(newButton);

        frame_11 = new QFrame(layoutWidget);
        frame_11->setObjectName(QStringLiteral("frame_11"));
        frame_11->setMinimumSize(QSize(0, 0));
        frame_11->setMaximumSize(QSize(16777215, 1));
        frame_11->setFrameShape(QFrame::NoFrame);
        frame_11->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame_11);

        remButton = new QPushButton(layoutWidget);
        remButton->setObjectName(QStringLiteral("remButton"));
        remButton->setEnabled(false);
        remButton->setStyleSheet(QStringLiteral("background-color: #505050;"));

        verticalLayout->addWidget(remButton);

        frame_12 = new QFrame(layoutWidget);
        frame_12->setObjectName(QStringLiteral("frame_12"));
        frame_12->setMinimumSize(QSize(0, 0));
        frame_12->setMaximumSize(QSize(16777215, 1));
        frame_12->setFrameShape(QFrame::NoFrame);
        frame_12->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame_12);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        arrButton = new QPushButton(layoutWidget);
        arrButton->setObjectName(QStringLiteral("arrButton"));
        arrButton->setEnabled(false);
        arrButton->setStyleSheet(QStringLiteral("background-color: #505050;"));

        verticalLayout->addWidget(arrButton);

        frame_7 = new QFrame(layoutWidget);
        frame_7->setObjectName(QStringLiteral("frame_7"));
        frame_7->setMaximumSize(QSize(16777215, 1));
        frame_7->setFrameShape(QFrame::NoFrame);
        frame_7->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame_7);

        bboxButton = new QPushButton(layoutWidget);
        bboxButton->setObjectName(QStringLiteral("bboxButton"));
        bboxButton->setEnabled(false);
        bboxButton->setStyleSheet(QStringLiteral("background-color: #505050;"));

        verticalLayout->addWidget(bboxButton);

        frame_6 = new QFrame(layoutWidget);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setMaximumSize(QSize(16777215, 1));
        frame_6->setFrameShape(QFrame::NoFrame);
        frame_6->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame_6);

        ellButton = new QPushButton(layoutWidget);
        ellButton->setObjectName(QStringLiteral("ellButton"));
        ellButton->setEnabled(false);
        ellButton->setStyleSheet(QStringLiteral("background-color: #505050;"));

        verticalLayout->addWidget(ellButton);

        frame_5 = new QFrame(layoutWidget);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setMaximumSize(QSize(16777215, 1));
        frame_5->setFrameShape(QFrame::NoFrame);
        frame_5->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame_5);

        polyButton = new QPushButton(layoutWidget);
        polyButton->setObjectName(QStringLiteral("polyButton"));
        polyButton->setEnabled(false);
        polyButton->setStyleSheet(QStringLiteral("background-color: #505050;"));

        verticalLayout->addWidget(polyButton);

        frame_4 = new QFrame(layoutWidget);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setMaximumSize(QSize(16777215, 1));
        frame_4->setFrameShape(QFrame::NoFrame);
        frame_4->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame_4);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setEnabled(false);
        pushButton->setStyleSheet(QStringLiteral("background-color: #505050;"));

        verticalLayout->addWidget(pushButton);

        frame_13 = new QFrame(layoutWidget);
        frame_13->setObjectName(QStringLiteral("frame_13"));
        frame_13->setMinimumSize(QSize(0, 0));
        frame_13->setMaximumSize(QSize(16777215, 1));
        frame_13->setFrameShape(QFrame::NoFrame);
        frame_13->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame_13);

        confButton = new QPushButton(layoutWidget);
        confButton->setObjectName(QStringLiteral("confButton"));
        confButton->setEnabled(false);
        confButton->setStyleSheet(QStringLiteral("background-color: #505050;"));

        verticalLayout->addWidget(confButton);


        horizontalLayout->addWidget(frame_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 1165, 22));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(false);
        mainToolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Evidences Selector", 0));
        openButton->setText(QApplication::translate("MainWindow", "Open", 0));
        label_2->setText(QApplication::translate("MainWindow", "Zoom Settings", 0));
        zoomInButton->setText(QApplication::translate("MainWindow", "Zoom In", 0));
        zoomOutButton->setText(QApplication::translate("MainWindow", "Zoom Out", 0));
        zoomAutoButton->setText(QApplication::translate("MainWindow", "Zoom Auto", 0));
        label_3->setText(QApplication::translate("MainWindow", "Evidences list", 0));
        newButton->setText(QApplication::translate("MainWindow", "New Evidence", 0));
        remButton->setText(QApplication::translate("MainWindow", "Remove Evidence", 0));
        label->setText(QApplication::translate("MainWindow", "Selection Tools", 0));
        arrButton->setText(QApplication::translate("MainWindow", "Arrow", 0));
        bboxButton->setText(QApplication::translate("MainWindow", "Rectangle", 0));
        ellButton->setText(QApplication::translate("MainWindow", "Ellipse", 0));
        polyButton->setText(QApplication::translate("MainWindow", "Polygonal", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Pen", 0));
        confButton->setText(QApplication::translate("MainWindow", "Confirm Selection", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
