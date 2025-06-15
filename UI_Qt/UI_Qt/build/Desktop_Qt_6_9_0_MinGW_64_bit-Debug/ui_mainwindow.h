/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btn_Sent;
    QTextBrowser *lineEdit_Inforcn;
    QLabel *lbl_SCP;
    QComboBox *comboBox_COM;
    QLabel *lblCOM;
    QComboBox *comboBox_BAUD;
    QLabel *lblBAUD;
    QLabel *lblDT;
    QComboBox *comboBox_DTS;
    QComboBox *comboBox_STOP;
    QLabel *lblSTOP;
    QLabel *lblTen;
    QPushButton *btnConnect;
    QComboBox *comboBox_CANID;
    QLabel *lblCANID;
    QTextEdit *textEdit_TEXT;
    QTextEdit *textEdit_HEX;
    QPushButton *btn_SentHEX;
    QTableWidget *tableWidget;
    QTextBrowser *textBrowser_Sent;
    QLabel *lbl_DATASent;
    QLabel *label;
    QPushButton *btnDisConnect;
    QTextBrowser *textBrowser_Receip;
    QLabel *lblCANID_2;
    QLabel *lblCANID_3;
    QComboBox *comboBox_CYCLE;
    QPushButton *btnConnectRx;
    QPushButton *btnDisconnectRx;
    QComboBox *comboBox_COM_RX;
    QPushButton *btn_ClearSent;
    QPushButton *btn_ClearReceive;
    QLabel *lblCOMRx;
    QTableWidget *tableWidget_Receive;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1090, 765);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btn_Sent = new QPushButton(centralwidget);
        btn_Sent->setObjectName("btn_Sent");
        btn_Sent->setGeometry(QRect(20, 390, 93, 29));
        lineEdit_Inforcn = new QTextBrowser(centralwidget);
        lineEdit_Inforcn->setObjectName("lineEdit_Inforcn");
        lineEdit_Inforcn->setGeometry(QRect(370, 100, 351, 181));
        lbl_SCP = new QLabel(centralwidget);
        lbl_SCP->setObjectName("lbl_SCP");
        lbl_SCP->setGeometry(QRect(470, 70, 141, 20));
        comboBox_COM = new QComboBox(centralwidget);
        comboBox_COM->setObjectName("comboBox_COM");
        comboBox_COM->setGeometry(QRect(130, 110, 76, 26));
        lblCOM = new QLabel(centralwidget);
        lblCOM->setObjectName("lblCOM");
        lblCOM->setGeometry(QRect(40, 110, 81, 20));
        comboBox_BAUD = new QComboBox(centralwidget);
        comboBox_BAUD->setObjectName("comboBox_BAUD");
        comboBox_BAUD->setGeometry(QRect(130, 160, 76, 26));
        lblBAUD = new QLabel(centralwidget);
        lblBAUD->setObjectName("lblBAUD");
        lblBAUD->setGeometry(QRect(40, 160, 81, 20));
        lblDT = new QLabel(centralwidget);
        lblDT->setObjectName("lblDT");
        lblDT->setGeometry(QRect(40, 210, 81, 20));
        comboBox_DTS = new QComboBox(centralwidget);
        comboBox_DTS->setObjectName("comboBox_DTS");
        comboBox_DTS->setGeometry(QRect(130, 210, 76, 26));
        comboBox_STOP = new QComboBox(centralwidget);
        comboBox_STOP->setObjectName("comboBox_STOP");
        comboBox_STOP->setGeometry(QRect(130, 260, 76, 26));
        lblSTOP = new QLabel(centralwidget);
        lblSTOP->setObjectName("lblSTOP");
        lblSTOP->setGeometry(QRect(40, 260, 71, 20));
        lblTen = new QLabel(centralwidget);
        lblTen->setObjectName("lblTen");
        lblTen->setGeometry(QRect(270, 20, 571, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(24);
        font.setBold(true);
        lblTen->setFont(font);
        btnConnect = new QPushButton(centralwidget);
        btnConnect->setObjectName("btnConnect");
        btnConnect->setGeometry(QRect(240, 160, 93, 29));
        comboBox_CANID = new QComboBox(centralwidget);
        comboBox_CANID->setObjectName("comboBox_CANID");
        comboBox_CANID->setGeometry(QRect(130, 350, 76, 26));
        lblCANID = new QLabel(centralwidget);
        lblCANID->setObjectName("lblCANID");
        lblCANID->setGeometry(QRect(40, 350, 63, 20));
        textEdit_TEXT = new QTextEdit(centralwidget);
        textEdit_TEXT->setObjectName("textEdit_TEXT");
        textEdit_TEXT->setGeometry(QRect(130, 390, 201, 31));
        textEdit_HEX = new QTextEdit(centralwidget);
        textEdit_HEX->setObjectName("textEdit_HEX");
        textEdit_HEX->setGeometry(QRect(130, 440, 201, 31));
        btn_SentHEX = new QPushButton(centralwidget);
        btn_SentHEX->setObjectName("btn_SentHEX");
        btn_SentHEX->setGeometry(QRect(20, 440, 93, 29));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(370, 310, 711, 161));
        textBrowser_Sent = new QTextBrowser(centralwidget);
        textBrowser_Sent->setObjectName("textBrowser_Sent");
        textBrowser_Sent->setGeometry(QRect(740, 100, 341, 181));
        lbl_DATASent = new QLabel(centralwidget);
        lbl_DATASent->setObjectName("lbl_DATASent");
        lbl_DATASent->setGeometry(QRect(870, 70, 71, 20));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(670, 290, 81, 20));
        btnDisConnect = new QPushButton(centralwidget);
        btnDisConnect->setObjectName("btnDisConnect");
        btnDisConnect->setGeometry(QRect(240, 210, 93, 29));
        textBrowser_Receip = new QTextBrowser(centralwidget);
        textBrowser_Receip->setObjectName("textBrowser_Receip");
        textBrowser_Receip->setGeometry(QRect(740, 480, 341, 161));
        lblCANID_2 = new QLabel(centralwidget);
        lblCANID_2->setObjectName("lblCANID_2");
        lblCANID_2->setGeometry(QRect(40, 310, 63, 20));
        lblCANID_3 = new QLabel(centralwidget);
        lblCANID_3->setObjectName("lblCANID_3");
        lblCANID_3->setGeometry(QRect(220, 310, 63, 20));
        comboBox_CYCLE = new QComboBox(centralwidget);
        comboBox_CYCLE->setObjectName("comboBox_CYCLE");
        comboBox_CYCLE->setGeometry(QRect(130, 310, 76, 26));
        btnConnectRx = new QPushButton(centralwidget);
        btnConnectRx->setObjectName("btnConnectRx");
        btnConnectRx->setGeometry(QRect(630, 530, 101, 29));
        btnDisconnectRx = new QPushButton(centralwidget);
        btnDisconnectRx->setObjectName("btnDisconnectRx");
        btnDisconnectRx->setGeometry(QRect(630, 570, 101, 29));
        comboBox_COM_RX = new QComboBox(centralwidget);
        comboBox_COM_RX->setObjectName("comboBox_COM_RX");
        comboBox_COM_RX->setGeometry(QRect(630, 490, 101, 26));
        btn_ClearSent = new QPushButton(centralwidget);
        btn_ClearSent->setObjectName("btn_ClearSent");
        btn_ClearSent->setGeometry(QRect(240, 250, 93, 29));
        btn_ClearReceive = new QPushButton(centralwidget);
        btn_ClearReceive->setObjectName("btn_ClearReceive");
        btn_ClearReceive->setGeometry(QRect(630, 610, 101, 31));
        lblCOMRx = new QLabel(centralwidget);
        lblCOMRx->setObjectName("lblCOMRx");
        lblCOMRx->setGeometry(QRect(520, 490, 111, 31));
        tableWidget_Receive = new QTableWidget(centralwidget);
        tableWidget_Receive->setObjectName("tableWidget_Receive");
        tableWidget_Receive->setGeometry(QRect(20, 490, 491, 211));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1090, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_Sent->setText(QCoreApplication::translate("MainWindow", "Sent", nullptr));
        lbl_SCP->setText(QCoreApplication::translate("MainWindow", "Status Connect Port", nullptr));
        lblCOM->setText(QCoreApplication::translate("MainWindow", "COM PORT", nullptr));
        lblBAUD->setText(QCoreApplication::translate("MainWindow", "BAUD RATE", nullptr));
        lblDT->setText(QCoreApplication::translate("MainWindow", "DATA SIZE", nullptr));
        lblSTOP->setText(QCoreApplication::translate("MainWindow", "STOP BITS", nullptr));
        lblTen->setText(QCoreApplication::translate("MainWindow", "DUMMY ECUS FOR TESTING", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        lblCANID->setText(QCoreApplication::translate("MainWindow", "CAN ID", nullptr));
        btn_SentHEX->setText(QCoreApplication::translate("MainWindow", "Sent_HEX", nullptr));
        lbl_DATASent->setText(QCoreApplication::translate("MainWindow", "DATA Sent", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Table Status", nullptr));
        btnDisConnect->setText(QCoreApplication::translate("MainWindow", "DisConnect", nullptr));
        lblCANID_2->setText(QCoreApplication::translate("MainWindow", "CYCLE", nullptr));
        lblCANID_3->setText(QCoreApplication::translate("MainWindow", "ms", nullptr));
        btnConnectRx->setText(QCoreApplication::translate("MainWindow", "ConnectRx", nullptr));
        btnDisconnectRx->setText(QCoreApplication::translate("MainWindow", "DisconnectRx", nullptr));
        btn_ClearSent->setText(QCoreApplication::translate("MainWindow", "ClearSent", nullptr));
        btn_ClearReceive->setText(QCoreApplication::translate("MainWindow", "ClearReceive", nullptr));
        lblCOMRx->setText(QCoreApplication::translate("MainWindow", "COM_PORT_RX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
