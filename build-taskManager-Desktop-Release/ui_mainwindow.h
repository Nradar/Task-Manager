/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget_INFO;
    QWidget *MemoryInfo;
    QGroupBox *groupBox;
    QProgressBar *progressBar_CPU;
    QLabel *label_11;
    QGroupBox *groupBox_2;
    QProgressBar *progressBar_RAM;
    QProgressBar *progressBar_SWAP;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_20;
    QLabel *label_RAM_Used;
    QLabel *label_RAM_Left;
    QLabel *label_RAM_Total;
    QLabel *label_SWAP_Total;
    QLabel *label_SWAP_Used;
    QLabel *label_SWAP_Left;
    QWidget *Process;
    QListWidget *listWidget_process;
    QPushButton *pushButton_pkill;
    QPushButton *pushButton_prefresh;
    QLabel *label;
    QLabel *label_pNum;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_pRun;
    QLabel *label_pSleep;
    QLabel *label_pZombie;
    QWidget *Module;
    QPushButton *pushButton_Model_install;
    QPushButton *pushButton_Model_remove;
    QPushButton *pushButton_Model_refresh;
    QListWidget *listWidget_model;
    QWidget *System;
    QGroupBox *groupBox_3;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_CPUName;
    QLabel *label_CPUType;
    QLabel *label_CPUFrequency;
    QLabel *label_CatheCapacity;
    QGroupBox *groupBox_4;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_SystemType;
    QLabel *label_SystemVersion;
    QLabel *label_GCCVersion;
    QWidget *tab;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QPushButton *pushButton_reboot;
    QPushButton *pushButton_halt;
    QMenuBar *menuBar;
    QMenu *menuSysMontior;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(605, 438);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget_INFO = new QTabWidget(centralWidget);
        tabWidget_INFO->setObjectName(QStringLiteral("tabWidget_INFO"));
        tabWidget_INFO->setGeometry(QRect(0, 0, 611, 341));
        tabWidget_INFO->setCursor(QCursor(Qt::ArrowCursor));
        tabWidget_INFO->setTabShape(QTabWidget::Triangular);
        tabWidget_INFO->setMovable(false);
        MemoryInfo = new QWidget();
        MemoryInfo->setObjectName(QStringLiteral("MemoryInfo"));
        groupBox = new QGroupBox(MemoryInfo);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 591, 81));
        progressBar_CPU = new QProgressBar(groupBox);
        progressBar_CPU->setObjectName(QStringLiteral("progressBar_CPU"));
        progressBar_CPU->setGeometry(QRect(50, 30, 431, 23));
        progressBar_CPU->setValue(24);
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(0, 30, 66, 17));
        groupBox_2 = new QGroupBox(MemoryInfo);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 80, 591, 231));
        progressBar_RAM = new QProgressBar(groupBox_2);
        progressBar_RAM->setObjectName(QStringLiteral("progressBar_RAM"));
        progressBar_RAM->setGeometry(QRect(50, 50, 431, 23));
        progressBar_RAM->setValue(24);
        progressBar_SWAP = new QProgressBar(groupBox_2);
        progressBar_SWAP->setObjectName(QStringLiteral("progressBar_SWAP"));
        progressBar_SWAP->setGeometry(QRect(50, 140, 431, 23));
        progressBar_SWAP->setValue(24);
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(0, 50, 66, 17));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(0, 140, 41, 17));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(50, 80, 66, 17));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(200, 80, 66, 17));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(380, 80, 66, 17));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(380, 170, 66, 17));
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(50, 170, 66, 17));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(200, 170, 66, 17));
        label_RAM_Used = new QLabel(groupBox_2);
        label_RAM_Used->setObjectName(QStringLiteral("label_RAM_Used"));
        label_RAM_Used->setGeometry(QRect(90, 80, 66, 17));
        label_RAM_Left = new QLabel(groupBox_2);
        label_RAM_Left->setObjectName(QStringLiteral("label_RAM_Left"));
        label_RAM_Left->setGeometry(QRect(240, 80, 66, 17));
        label_RAM_Total = new QLabel(groupBox_2);
        label_RAM_Total->setObjectName(QStringLiteral("label_RAM_Total"));
        label_RAM_Total->setGeometry(QRect(420, 80, 66, 17));
        label_SWAP_Total = new QLabel(groupBox_2);
        label_SWAP_Total->setObjectName(QStringLiteral("label_SWAP_Total"));
        label_SWAP_Total->setGeometry(QRect(420, 170, 66, 17));
        label_SWAP_Used = new QLabel(groupBox_2);
        label_SWAP_Used->setObjectName(QStringLiteral("label_SWAP_Used"));
        label_SWAP_Used->setGeometry(QRect(90, 170, 66, 17));
        label_SWAP_Left = new QLabel(groupBox_2);
        label_SWAP_Left->setObjectName(QStringLiteral("label_SWAP_Left"));
        label_SWAP_Left->setGeometry(QRect(240, 170, 66, 17));
        tabWidget_INFO->addTab(MemoryInfo, QString());
        Process = new QWidget();
        Process->setObjectName(QStringLiteral("Process"));
        listWidget_process = new QListWidget(Process);
        listWidget_process->setObjectName(QStringLiteral("listWidget_process"));
        listWidget_process->setGeometry(QRect(0, 0, 421, 271));
        pushButton_pkill = new QPushButton(Process);
        pushButton_pkill->setObjectName(QStringLiteral("pushButton_pkill"));
        pushButton_pkill->setGeometry(QRect(20, 280, 98, 27));
        pushButton_prefresh = new QPushButton(Process);
        pushButton_prefresh->setObjectName(QStringLiteral("pushButton_prefresh"));
        pushButton_prefresh->setGeometry(QRect(170, 280, 98, 27));
        label = new QLabel(Process);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(430, 30, 81, 17));
        label_pNum = new QLabel(Process);
        label_pNum->setObjectName(QStringLiteral("label_pNum"));
        label_pNum->setGeometry(QRect(520, 30, 66, 17));
        label_2 = new QLabel(Process);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(430, 70, 66, 17));
        label_3 = new QLabel(Process);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(430, 110, 71, 17));
        label_4 = new QLabel(Process);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(430, 150, 66, 17));
        label_pRun = new QLabel(Process);
        label_pRun->setObjectName(QStringLiteral("label_pRun"));
        label_pRun->setGeometry(QRect(520, 70, 66, 17));
        label_pSleep = new QLabel(Process);
        label_pSleep->setObjectName(QStringLiteral("label_pSleep"));
        label_pSleep->setGeometry(QRect(520, 110, 66, 17));
        label_pZombie = new QLabel(Process);
        label_pZombie->setObjectName(QStringLiteral("label_pZombie"));
        label_pZombie->setGeometry(QRect(520, 150, 66, 17));
        tabWidget_INFO->addTab(Process, QString());
        Module = new QWidget();
        Module->setObjectName(QStringLiteral("Module"));
        pushButton_Model_install = new QPushButton(Module);
        pushButton_Model_install->setObjectName(QStringLiteral("pushButton_Model_install"));
        pushButton_Model_install->setGeometry(QRect(20, 280, 98, 27));
        pushButton_Model_remove = new QPushButton(Module);
        pushButton_Model_remove->setObjectName(QStringLiteral("pushButton_Model_remove"));
        pushButton_Model_remove->setGeometry(QRect(180, 280, 98, 27));
        pushButton_Model_refresh = new QPushButton(Module);
        pushButton_Model_refresh->setObjectName(QStringLiteral("pushButton_Model_refresh"));
        pushButton_Model_refresh->setGeometry(QRect(350, 280, 98, 27));
        listWidget_model = new QListWidget(Module);
        listWidget_model->setObjectName(QStringLiteral("listWidget_model"));
        listWidget_model->setGeometry(QRect(0, 0, 561, 271));
        tabWidget_INFO->addTab(Module, QString());
        System = new QWidget();
        System->setObjectName(QStringLiteral("System"));
        groupBox_3 = new QGroupBox(System);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 0, 591, 171));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 40, 81, 17));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(50, 70, 81, 17));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(50, 100, 111, 17));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(50, 130, 81, 17));
        label_CPUName = new QLabel(groupBox_3);
        label_CPUName->setObjectName(QStringLiteral("label_CPUName"));
        label_CPUName->setGeometry(QRect(160, 40, 321, 31));
        label_CPUType = new QLabel(groupBox_3);
        label_CPUType->setObjectName(QStringLiteral("label_CPUType"));
        label_CPUType->setGeometry(QRect(160, 70, 151, 31));
        label_CPUFrequency = new QLabel(groupBox_3);
        label_CPUFrequency->setObjectName(QStringLiteral("label_CPUFrequency"));
        label_CPUFrequency->setGeometry(QRect(160, 100, 66, 17));
        label_CatheCapacity = new QLabel(groupBox_3);
        label_CatheCapacity->setObjectName(QStringLiteral("label_CatheCapacity"));
        label_CatheCapacity->setGeometry(QRect(160, 130, 66, 17));
        groupBox_4 = new QGroupBox(System);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 180, 591, 121));
        label_17 = new QLabel(groupBox_4);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(70, 30, 131, 16));
        label_18 = new QLabel(groupBox_4);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(70, 60, 61, 17));
        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(70, 90, 111, 17));
        label_SystemType = new QLabel(groupBox_4);
        label_SystemType->setObjectName(QStringLiteral("label_SystemType"));
        label_SystemType->setGeometry(QRect(200, 30, 151, 17));
        label_SystemVersion = new QLabel(groupBox_4);
        label_SystemVersion->setObjectName(QStringLiteral("label_SystemVersion"));
        label_SystemVersion->setGeometry(QRect(200, 60, 281, 17));
        label_GCCVersion = new QLabel(groupBox_4);
        label_GCCVersion->setObjectName(QStringLiteral("label_GCCVersion"));
        label_GCCVersion->setGeometry(QRect(200, 90, 371, 17));
        tabWidget_INFO->addTab(System, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_21 = new QLabel(tab);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(20, 30, 66, 17));
        label_22 = new QLabel(tab);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(100, 30, 231, 17));
        label_23 = new QLabel(tab);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(100, 70, 201, 17));
        label_24 = new QLabel(tab);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(20, 70, 66, 17));
        label_25 = new QLabel(tab);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(100, 110, 191, 17));
        label_26 = new QLabel(tab);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(20, 110, 81, 17));
        tabWidget_INFO->addTab(tab, QString());
        pushButton_reboot = new QPushButton(centralWidget);
        pushButton_reboot->setObjectName(QStringLiteral("pushButton_reboot"));
        pushButton_reboot->setGeometry(QRect(380, 350, 98, 27));
        pushButton_halt = new QPushButton(centralWidget);
        pushButton_halt->setObjectName(QStringLiteral("pushButton_halt"));
        pushButton_halt->setGeometry(QRect(500, 350, 98, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 605, 22));
        menuSysMontior = new QMenu(menuBar);
        menuSysMontior->setObjectName(QStringLiteral("menuSysMontior"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSysMontior->menuAction());

        retranslateUi(MainWindow);

        tabWidget_INFO->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
#ifndef QT_NO_TOOLTIP
        MemoryInfo->setToolTip(QApplication::translate("MainWindow", "Memory Info", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        MemoryInfo->setWhatsThis(QApplication::translate("MainWindow", "\345\206\205\345\255\230\344\277\241\346\201\257", 0));
#endif // QT_NO_WHATSTHIS
        groupBox->setTitle(QApplication::translate("MainWindow", "CPU", 0));
        label_11->setText(QApplication::translate("MainWindow", "CPU:", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Memory & Swap Partition", 0));
        label_9->setText(QApplication::translate("MainWindow", "RAM:", 0));
        label_10->setText(QApplication::translate("MainWindow", "Swap:", 0));
        label_12->setText(QApplication::translate("MainWindow", "Used:", 0));
        label_13->setText(QApplication::translate("MainWindow", "Left:", 0));
        label_14->setText(QApplication::translate("MainWindow", "Total:", 0));
        label_15->setText(QApplication::translate("MainWindow", "Total:", 0));
        label_16->setText(QApplication::translate("MainWindow", "Used:", 0));
        label_20->setText(QApplication::translate("MainWindow", "Left:", 0));
        label_RAM_Used->setText(QApplication::translate("MainWindow", "0", 0));
        label_RAM_Left->setText(QApplication::translate("MainWindow", "0", 0));
        label_RAM_Total->setText(QApplication::translate("MainWindow", "0", 0));
        label_SWAP_Total->setText(QApplication::translate("MainWindow", "0", 0));
        label_SWAP_Used->setText(QApplication::translate("MainWindow", "0", 0));
        label_SWAP_Left->setText(QApplication::translate("MainWindow", "0", 0));
        tabWidget_INFO->setTabText(tabWidget_INFO->indexOf(MemoryInfo), QApplication::translate("MainWindow", "Memory Info", 0));
        pushButton_pkill->setText(QApplication::translate("MainWindow", "kill", 0));
        pushButton_prefresh->setText(QApplication::translate("MainWindow", "refresh", 0));
        label->setText(QApplication::translate("MainWindow", "Process:", 0));
        label_pNum->setText(QApplication::translate("MainWindow", "0", 0));
        label_2->setText(QApplication::translate("MainWindow", "Running:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Sleeping:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Zombie:", 0));
        label_pRun->setText(QApplication::translate("MainWindow", "0", 0));
        label_pSleep->setText(QApplication::translate("MainWindow", "0", 0));
        label_pZombie->setText(QApplication::translate("MainWindow", "0", 0));
        tabWidget_INFO->setTabText(tabWidget_INFO->indexOf(Process), QApplication::translate("MainWindow", "Processes", 0));
        pushButton_Model_install->setText(QApplication::translate("MainWindow", "Install", 0));
        pushButton_Model_remove->setText(QApplication::translate("MainWindow", "Romove", 0));
        pushButton_Model_refresh->setText(QApplication::translate("MainWindow", "refresh", 0));
        tabWidget_INFO->setTabText(tabWidget_INFO->indexOf(Module), QApplication::translate("MainWindow", "Module", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Cpu Info", 0));
        label_5->setText(QApplication::translate("MainWindow", "CPU Name:", 0));
        label_6->setText(QApplication::translate("MainWindow", "CPU Series:", 0));
        label_7->setText(QApplication::translate("MainWindow", "CPU Frequency:", 0));
        label_8->setText(QApplication::translate("MainWindow", "CPU Cache:", 0));
        label_CPUName->setText(QApplication::translate("MainWindow", "Unknown", 0));
        label_CPUType->setText(QApplication::translate("MainWindow", "Unknown", 0));
        label_CPUFrequency->setText(QApplication::translate("MainWindow", "Unknown", 0));
        label_CatheCapacity->setText(QApplication::translate("MainWindow", "Unknown", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Operating System Info", 0));
        label_17->setText(QApplication::translate("MainWindow", "Operating System:", 0));
        label_18->setText(QApplication::translate("MainWindow", "Version:", 0));
        label_19->setText(QApplication::translate("MainWindow", "GCC Compiler:", 0));
        label_SystemType->setText(QApplication::translate("MainWindow", "Unknown", 0));
        label_SystemVersion->setText(QApplication::translate("MainWindow", "Unknown", 0));
        label_GCCVersion->setText(QApplication::translate("MainWindow", "Unknown", 0));
        tabWidget_INFO->setTabText(tabWidget_INFO->indexOf(System), QApplication::translate("MainWindow", "System Info", 0));
        label_21->setText(QApplication::translate("MainWindow", "Project:", 0));
        label_22->setText(QApplication::translate("MainWindow", "Linux Task Manager based on QT", 0));
        label_23->setText(QApplication::translate("MainWindow", "Tiancheng Zhao, Yinfeng Hu", 0));
        label_24->setText(QApplication::translate("MainWindow", "Author:", 0));
        label_25->setText(QApplication::translate("MainWindow", "COMP3000", 0));
        label_26->setText(QApplication::translate("MainWindow", "Course No.", 0));
        tabWidget_INFO->setTabText(tabWidget_INFO->indexOf(tab), QApplication::translate("MainWindow", "About", 0));
        pushButton_reboot->setText(QApplication::translate("MainWindow", "reboot", 0));
        pushButton_halt->setText(QApplication::translate("MainWindow", "shutdown", 0));
        menuSysMontior->setTitle(QApplication::translate("MainWindow", "TaskManager", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
