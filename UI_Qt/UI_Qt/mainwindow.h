#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QSerialPort>
#include <QThread>
#include <stdbool.h>
#include <cstring>
#include <QDataStream>
#include <QByteArray>
#include <QSerialPortInfo>
#include <QMainWindow>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//Viết hàm cho QcloseEvent
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    // void on_btn_Sent_clicked();
    void on_comboBox_COM_activated(int index);
    void on_btn_SentHEX_clicked();
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();
    void readUARTResponse();

    void on_multiCanWidget_customContextMenuRequested(const QPoint &pos);
    void appendToTable(const QString &timestamp, const QString &canId, int dlc, const QString &data, const QString &crc, const QString &cycle);
    void appendToReceiveTable(const QString &timestamp, const QString &canId, int dlc, const QString &data, const QString &crc,const QString &Status);

    // void onSerialDataReceived();

    void on_btnConnectRx_clicked();
    void on_btnDisconnectRx_clicked();
    void on_btn_ClearSent_clicked();

    void on_btn_ClearReceive_clicked();
    // void onSerialDataReceived();
    // void on_tableWidget_Receive_cellActivated(int row, int column);

private:
    Ui::MainWindow *ui;
    void loadPorts();
    QSerialPort *serialPort;
    QSerialPortInfo info;
    // QString buffer;
    // QString bufferHistory;
    // QString code;
    // int codeSize;
    QString dataReceived;
    // QVector<int> intValues;
    // QVector<int> intValuesHistory;
    // QString buff;
    int lengthUsingLength;
    // uint8_t byte1;
    // uint8_t byte2;
    // uint8_t byte3;
    // uint8_t byte4;
    // uint8_t byteSID;
    // uint8_t byteClock;
    // int remainingSize;
    // bool submittedSuccessfully;
    // int chunkIndex = 0;
    // int chunkSize = 4095;
    QByteArray hexData;
    QString message;
    // QByteArray chunk;
    // QByteArray hexLength;
    // QByteArray hexLengthStringbyte1;
    // QByteArray hexLengthStringbyte2;
    // QByteArray hexLengthStringbyte3;
    // QByteArray hexLengthStringbyte4;
    // QByteArray hexLengthStringbyteSID;
    // QByteArray hexLengthStringbyteClock;
    // QByteArray hexLength1;
    // QByteArray hexLength2;
    // QByteArray hexLength3;
    // QByteArray hexLength4;
    // QByteArray hexLengthSID;
    // QByteArray hexLengthClock;
    // QByteArray dataBA;
    // QByteArray dataPtr;
    // QByteArray receivedData;
    // int flag = 0;
    // uint32_t dataRecord = 0;
    QCanBusDevice *canDevice = nullptr;
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    quint8 calculateCRC8_AUTOSAR(const QByteArray &data);


    QString STT;
    QString timestamp;
    QString canId;
    int dlc;
    QString data;
    QString crc;
    QString QDateTime;

    QSerialPort *serialPortRx;

    // void initCAN();  // Hàm khởi tạo CAN
};


#endif // MAINWINDOW_H
