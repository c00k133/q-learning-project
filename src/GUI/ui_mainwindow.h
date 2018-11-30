/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionno_attributes_yet;
    QAction *actionno_sound_implemented;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QMenuBar *menuBar;
    QMenu *settings;
    QMenu *menuSound;
    QMenu *menuMute;
    QMenu *menuAttributes;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 800);
        MainWindow->setMinimumSize(QSize(300, 300));
        MainWindow->setMaximumSize(QSize(1000, 1000));
        MainWindow->setBaseSize(QSize(300, 300));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionExit->setShortcutVisibleInContextMenu(false);
        actionno_attributes_yet = new QAction(MainWindow);
        actionno_attributes_yet->setObjectName(QString::fromUtf8("actionno_attributes_yet"));
        actionno_sound_implemented = new QAction(MainWindow);
        actionno_sound_implemented->setObjectName(QString::fromUtf8("actionno_sound_implemented"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(300, 300));
        frame->setMaximumSize(QSize(1200, 1200));
        frame->setBaseSize(QSize(300, 300));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 25));
        settings = new QMenu(menuBar);
        settings->setObjectName(QString::fromUtf8("settings"));
        menuSound = new QMenu(settings);
        menuSound->setObjectName(QString::fromUtf8("menuSound"));
        menuMute = new QMenu(menuSound);
        menuMute->setObjectName(QString::fromUtf8("menuMute"));
        menuAttributes = new QMenu(menuBar);
        menuAttributes->setObjectName(QString::fromUtf8("menuAttributes"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(settings->menuAction());
        menuBar->addAction(menuAttributes->menuAction());
        settings->addAction(actionExit);
        settings->addAction(menuSound->menuAction());
        settings->addSeparator();
        settings->addSeparator();
        menuSound->addAction(menuMute->menuAction());
        menuMute->addAction(actionno_sound_implemented);
        menuAttributes->addAction(actionno_attributes_yet);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered(bool)), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionno_attributes_yet->setText(QApplication::translate("MainWindow", "no attributes yet", nullptr));
        actionno_sound_implemented->setText(QApplication::translate("MainWindow", "no sound implemented", nullptr));
        settings->setTitle(QApplication::translate("MainWindow", "Settings", nullptr));
        menuSound->setTitle(QApplication::translate("MainWindow", "Sound", nullptr));
        menuMute->setTitle(QApplication::translate("MainWindow", "Mute", nullptr));
        menuAttributes->setTitle(QApplication::translate("MainWindow", "Attributes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
