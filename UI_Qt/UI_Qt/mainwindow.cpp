#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QSerialPortInfo>
#include <QTimer>
#include <QSerialPort>
#include <QDateTime>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    //khởi tạo biến thành viên serialPort
    , serialPort(new QSerialPort(this))
{
    ui->setupUi(this);//hàm khởi tạo giao diện

    //đổi tên title của window
    setWindowTitle("DUMMY ECUS FOR TESTING");

    //Đổi màu các button và lable
    ui->lblTen->setStyleSheet("collor: green;");//đổi màu chữ
    ui->btnConnect->setStyleSheet("background-color: green; color: while;");//đổi màu background là màu xanh và chữ là màu trắng
    ui->btnConnectRx->setStyleSheet("background-color: green;color: while;");//đổi màu background là màu xanh và chữ là màu trắng
    ui->btnDisConnect->setStyleSheet("background-color:red; color: while;");//đổi màu background là màu đỏ và chữ là màu trắng
    ui->btnDisconnectRx->setStyleSheet("background-color:red; color: while;");//đổi màu background là màu đỏ và chữ là màu trắng
    ui->btn_ClearSent->setStyleSheet("background-color: orange");
    ui->btn_ClearReceive->setStyleSheet("background-color: orange");

    // liệt kê các cổng COM hiện có và đưa vào Combobox.
    QList<QSerialPortInfo> ports = info.availablePorts();//Lấy danh sách tất cả các cổng COM đang kết nối với máy tínhh
    QList<QString> stringPorts;//Tạo danh sách chuỗi rỗng để lưu tên các cổng COM dưới dạng QString
    //Duyệt qua từng cổng COM trong danh sách
    for(int i = 0 ; i < ports.size() ; i++)
    {
        //Thêm cổng COM vào danh sách stringPorts
        stringPorts.append(ports.at(i).portName());
    }
    //Đưa danh sách tên các cổng COM vào hai ComboBox: comboBox_COM (Tx) và comboBox_COM_RX (Rx)
    ui->comboBox_COM->addItems(stringPorts);
    ui->comboBox_COM_RX->addItems(stringPorts);

    // Baud Rate Ratios đoạn này dùng để lấy và hiển thị Baud Rate chuẩn mà máy tính hỗ trợ lên ComboBox.
    QList<qint32> baudRates = info.standardBaudRates();// Lấy ra danh sách các Baud rate chuẩn mà Qt hỗ trợ
    QList<QString> stringBaudRates;
    //duyệt qua từng phần tử trong BaudRate hiện có
    for(int i = 0 ; i < baudRates.size() ; i++)
    {
        //Vì ComboBox chỉ nhận dữ liệu dạng chuỗi, còn Baud Rate là số nguyên
        //Cần chuyển BaudRate từ dạng số nguyên về dạng chuỗi để hiển thị lên ComboBox = cách dùng hàm QString::number(...)
        //Thêm vào danh sách stringBaudRates bằng hàm append().
        stringBaudRates.append(QString::number(baudRates.at(i)));
    }
    //Gán BaudRates vào ComboxBox_BAUD
    ui->comboBox_BAUD->addItems(stringBaudRates);

    // Data Bits
    ui->comboBox_DTS->addItem("");
    ui->comboBox_DTS->addItem("5");
    ui->comboBox_DTS->addItem("6");
    ui->comboBox_DTS->addItem("7");
    ui->comboBox_DTS->addItem("8");

    //CAN ID
    ui->comboBox_CANID->addItem("");
    ui->comboBox_CANID->addItem("0x101");
    ui->comboBox_CANID->addItem("0x102");
    ui->comboBox_CANID->addItem("0x103");
    ui->comboBox_CANID->addItem("0x104");
    ui->comboBox_CANID->addItem("0x105");
    //Các giá trị 0x101 0x102 0x103 0x104 0x105 ở dạng String do ComboBox chỉ lưu ở dạng String

    //Cycle
    for (int i = 0; i <= 1000; i += 5) {
        ui->comboBox_CYCLE->addItem(QString::number(i) + " ms");
    }
    // // Stop Bits
    // ui->comboBox_STOP->addItem("");
    // ui->comboBox_STOP->addItem("1 Bit");
    // ui->comboBox_STOP->addItem("1,5 Bits");
    // ui->comboBox_STOP->addItem("2 Bits");

    //Thiết lập số cột và tên của từng cột trong QTableWidget
    ui->tableWidget->setColumnCount(6);// Tạo bảng hiển thị có 6 cột
    ui->tableWidget->setHorizontalHeaderLabels({"TimeStamp", "CAN ID", "DLC", "Data", "CRC", "Cycle"});//đặt tên của các cột trong bảng

    ui->tableWidget_Receive->setColumnCount(6);
    ui->tableWidget_Receive->setHorizontalHeaderLabels({"TimeStamp", "CAN ID", "DLC", "Data", "CRC", "Status"});

    //Thực hiện connect giữa btnDisconnect với hàm on_btnDisconnect_clicked
    connect(ui->btnDisConnect, &QPushButton::clicked, this, &::MainWindow::on_btnDisconnect_clicked);
    //Khi nhấn btnDisConnect thì hàm on_btnDisconnect_clicked sẽ thực hiện

    //Khởi tạo serialPortRx và connect giữa serialPortRx với hàm readUARTResponse
    serialPortRx = new QSerialPort(this);
    connect(serialPortRx, &QSerialPort::readyRead, this, &MainWindow::readUARTResponse);
    //Khi có dữ liệu UART đến, QT sẽ phát tín hiệu readRead và chương trình thực hiện hàm readUARTResponse

    // connect(serialPortRx, &QSerialPort::readyRead, this, &MainWindow::onSerialDataReceived); không dùng tới
    connect(ui->btnDisconnectRx, &QPushButton::clicked, this, &MainWindow::on_btnDisconnectRx_clicked);

    //Kiểm tra có cần hàm sau không
    //Thực hiện connect giữa btnClearSent với hàmon_btn_ClearSent_clicked
    connect(ui->btn_ClearSent, &QPushButton::clicked, this, &MainWindow::on_btn_ClearSent_clicked);
    //Thực hiện connect giữa btnClearReceipt với hàmon_btn_ClearSent_clicked
    connect(ui->btn_ClearReceive, &QPushButton::clicked, this, &MainWindow::on_btn_ClearReceive_clicked);
}

MainWindow::~MainWindow()
{
    if (canDevice) {
        canDevice->disconnectDevice();
        delete canDevice;
    }

    delete ui;
}
//Viết hàm đóng tool
void MainWindow::closeEvent(QCloseEvent *event)
{
    //Hiển thị hộp thoại thông báo trước khi đóng
    if(QMessageBox::question(this,"Confirm","Do you want to exit?") == QMessageBox::No)
    {
        event->ignore();//bỏ qua việc đóng form
    }
}
quint8 MainWindow::calculateCRC8_AUTOSAR(const QByteArray &data)
{
    // const quint8 poly = 0x2F;
    // quint8 crc = 0xFF;

    // for (char byte : data) {
    //     crc ^= static_cast<quint8>(byte);
    //     for (int i = 0; i < 8; ++i) {
    //         if (crc & 0x80)
    //             crc = (crc << 1) ^ poly;
    //         else
    //             crc <<= 1;
    //     }
    // }

    // return crc ^ 0xFF;
    const quint8 poly = 0x2F;
    quint8 crc = 0x00;

    for (char byte : data) {
        crc ^= static_cast<quint8>(byte);
        for (int i = 0; i < 8; ++i) {
            if (crc & 0x80)
                crc = (crc << 1) ^ poly;
            else
                crc <<= 1;
        }
    }

    return crc; //  Không XOR cuối
}
void MainWindow::on_comboBox_COM_activated(int index)//Xử lý khi người dùng chọn cổng COM trong ComboBox
{
    (void)index;
    QString portName = ui->comboBox_COM->currentText();//lấy chuỗi COM được chọn và gán vào biến, ví dụ "COM3", "COM4"
    //Kiểm tra đã chọn cổng COM chưa và hiển thị thông báo lên Status Connect Port
    if (portName.isEmpty())
    {
        ui->lineEdit_Inforcn->setTextColor(Qt::red);
        ui->lineEdit_Inforcn->setText("Vui lòng chọn cổng COM!");
    } else {
        ui->lineEdit_Inforcn->setTextColor(Qt::blue);
        ui->lineEdit_Inforcn->setText("Cổng COM đã chọn: " + portName);
    }
}

void MainWindow::on_btnConnect_clicked()//Xử lý khi user nhấn button Connect bên truyền
{
    QString portName = ui->comboBox_COM->currentText();//Lấy chuỗi cổng COM được chọn, ví dụ "COM3", "COM4"
    QString stringbaudRate = ui->comboBox_BAUD->currentText();//Lấy chuỗi BaudRate được chọn, ví dụ "9600", "12500"
    QString dataBits = ui->comboBox_DTS->currentText();//Lấy chuỗi databit được chọn, ví dụ "8", "5"
    // QString stopBits = ui->comboBox_STOP->currentText();//Lấy chuỗi Stop bit được chọn, ví dụ "1 bit stop"

    // Kiểm tra nếu chưa chọn đủ thông số
    // if (portName.isEmpty() || stringbaudRate.isEmpty() || dataBits.isEmpty() || stopBits.isEmpty()) {
    if (portName.isEmpty() || stringbaudRate.isEmpty() || dataBits.isEmpty())
    {
        ui->lineEdit_Inforcn->setTextColor(Qt::red);
        ui->lineEdit_Inforcn->setText("Vui lòng chọn đầy đủ thông số trước khi kết nối!");
        return;
    }

    // Cấu hình Serial Port
    serialPort->setPortName(portName);//gán tên cổng cho serialPort
    serialPort->setBaudRate(stringbaudRate.toInt());//Chuyển chuỗi stringbaudRate("112500") thành giá trị nugyene 112500

    // Cấu hình Data Bits
    bool validDataSize = true;//biến kiểm tra giá trị của datasize có hợp lệ hay khônng
    switch (dataBits.toInt())
    {
        case 5: serialPort->setDataBits(QSerialPort::Data5); break;//Thiết lập số bit dữ liệu là 5
        case 6: serialPort->setDataBits(QSerialPort::Data6); break;
        case 7: serialPort->setDataBits(QSerialPort::Data7); break;
        case 8: serialPort->setDataBits(QSerialPort::Data8); break;
        default:
            validDataSize = false;
            break;
    }

    if (!validDataSize)
    {
        ui->lineEdit_Inforcn->setTextColor(Qt::red);
        ui->lineEdit_Inforcn->setText("Data Size không hợp lệ!");
        return;
    }

    // // Cấu hình Stop Bits
    // if (stopBits == "1 Bit") serialPort->setStopBits(QSerialPort::OneStop);
    // else if (stopBits == "1,5 Bits") serialPort->setStopBits(QSerialPort::OneAndHalfStop);
    // else if (stopBits == "2 Bits") serialPort->setStopBits(QSerialPort::TwoStop);
    // else {
    //     ui->lineEdit_Inforcn->setTextColor(Qt::red);
    //     ui->lineEdit_Inforcn->setText("Stop Bits không hợp lệ!");
    //     return;
    // }

    // Mở cổng Serial
    if (!serialPort->open(QIODevice::ReadWrite))//Hàm này để mở cổng COM. QIODevice: Chỉ định chế độ mở cổng
    {
        ui->lineEdit_Inforcn->setTextColor(Qt::red);
        ui->lineEdit_Inforcn->setText("Cannot connect port COM!");
    } else {
        ui->lineEdit_Inforcn->setTextColor(Qt::green);
        ui->lineEdit_Inforcn->setText("Connect successfull with " + portName);
    }
}

void MainWindow::on_btnDisconnect_clicked()
{
    if (serialPort->isOpen()) {
        serialPort->close();
        ui->lineEdit_Inforcn->setTextColor(Qt::red);
        ui->lineEdit_Inforcn->setText("Đã ngắt kết nối cổng COM.");
    } else {
        ui->lineEdit_Inforcn->setTextColor(Qt::green);
        ui->lineEdit_Inforcn->setText("Cổng COM đã được ngắt hoặc chưa kết nối.");
    }
}

void MainWindow::loadPorts()
{
    //Dùng vòng lặp foreach để duyệt qua danh sách các cổng serial có sẵn trên hệ thống sử dụng QSerialPortInfo::availablePorts().
    foreach (auto &port, QSerialPortInfo::availablePorts())
    {
        ui->comboBox_COM->addItem(port.portName()); //Thêm tên của mỗi cổng serial vào combobox comPorts trên giao diện người dùng.
    }
}

// void MainWindow::on_btn_Sent_clicked()
// {
//     QString message = ui->textEdit_TEXT->toPlainText().trimmed();
//     if (message.isEmpty()) {
//         qDebug() << "Message is empty!";
//         return;
//     }

//     static const QRegularExpression hexPattern("[^0-9A-Fa-f ]");
//     if (message.contains(hexPattern)) {
//         qDebug() << "Invalid HEX input!";
//         return;
//     }

//     ui->textBrowser_Sent->setTextColor(Qt::black);
//     ui->textBrowser_Sent->append(message);

//     hexData = QByteArray::fromHex(message.toLatin1());
//     lengthUsingLength = hexData.length();
//     qDebug() << "lengthbyte:" << lengthUsingLength;

//     QByteArray messagefull;
//     messagefull.append(static_cast<char>(lengthUsingLength)); // Chuyển đổi kích thước sang byte
//     messagefull.append(hexData);

//     serialPort->write(messagefull);
//     serialPort->waitForBytesWritten(50); // Chờ gửi xong
// }


void MainWindow::on_btn_SentHEX_clicked()
{
    QString canIdText = ui->comboBox_CANID->currentText();//Lấy nội dung hiện tại của comboBox_CANID(chính là ID mà user chọn)
    QString hexDataText = ui->textEdit_HEX->toPlainText().trimmed();// Lấy nội dung trong textEdit_TEXT_HEX và gán cho biến hexDataText
    // Lấy nội dung trong textEdit_TEXT (nơi nhập dữ liệu bên cạnh button Sent_HEX) và gán cho biến hexDataText
    //toPlainText(): hàm dùng để lấy nội dung văn bản thuần túy(plain text), không định dạng từ một QTextEdit trong Qt.
    //Trimmed(): Loại bỏ khoảng trắng bị dư ở đầu/ cuối để tránh lỗi khi xử lý dữ liệu.

    // Lấy giá trị chu kỳ user chọn từ comboBox_CYCLE
    QString cycleText = ui->comboBox_CYCLE->currentText();//Lấy nội dung trong comboBox_cycle (chính là cycle do user chọn)
    // int cycleValue = cycleText.remove(" ms").toInt(); //Xóa phần " ms" khỏi chuỗi, sau đó phần chuyển chuỗi còn lại sang số nguyên để lấy giá trị cycle(ms)

    unsigned short cycleValue = cycleText.remove(" ms").toUShort();

    // Kiểm tra
    if (canIdText.isEmpty() || hexDataText.isEmpty())
    {
        QMessageBox::warning(this, "Cảnh báo", "Vui lòng nhập đủ CAN ID và dữ liệu HEX!");
        return;
    }

    // Validate HEX
    static const QRegularExpression hexPattern("^[0-9A-Fa-f ]+$");
    //chuỗi chỉ được phép chứa các ký tự hợp lệ là: 0–9, A–F, a–f, hoặc khoảng trắng($), và không được có bất kỳ ký tự nào khác.
    //Nếu có bất kì kí tự nào không thuộc regex trên thì báo lỗi
    if (!hexPattern.match(hexDataText).hasMatch()) {
        QMessageBox::critical(this, "Lỗi", "Dữ liệu HEX không hợp lệ!");
        return;
    }

    // Tạo gói tin: Length (1 byte) + CAN ID (2 byte) + Data
    bool ok;//lưu kq sau khi chuyển đổi
    uint16_t canId = canIdText.toUInt(&ok, 16);//chuyển chuỗi(Can_ID mà user nhập) thành kiểu int và 16: ở hệ 16
    if (!ok)//Nếu chuyển đổi không thành công: ok =FALSE, ngược lại là TRUE
    {
        QMessageBox::critical(this, "Lỗi", "CAN ID không hợp lệ!");
        return;
    }

    //Chuyển QString thành QByteArray với mã hóa Latin-1 (mỗi ký tự thành một byte).
    //Cần bước này vì fromHex() nhận đầu vào là QByteArray, không phải QString.
    QByteArray data = QByteArray::fromHex(hexDataText.toLatin1());//Chuyển chuỗi user nhập thành số ở hệ 16

    uint8_t length = 4 + data.length(); // 1 byte độ dài gói tín + 2byte CAN ID + các byte dữ liệu

    QByteArray packet;//Tạo packet để chứa toàn bộ gói tin nhị phân

    //1 Byte Độ dài gói tin
    packet.append(static_cast<char>(length));//Thêm byte đầu tiên: độ dài gói tin, ép kiểu sang char để đúng kiểu byte.
    //2 Bytes ID
    packet.append(static_cast<char>(canId & 0xFF));        // Low byte
    packet.append(static_cast<char>((canId >> 8) & 0xFF)); // High byte

    //Thêm các byte dữ liệu
    packet.append(data);
    //thêm byte cycle
    // packet.append(static_cast<char>(cycleValue/5)); // Ví dụ chia 5 để vừa 1 byte (nếu gửi dưới 1275ms)

    packet.append(static_cast<char>(cycleValue &0xFF));
    packet.append(static_cast<char>((cycleValue>>8) &0xFF));


    // Gửi UART
    if (serialPort->isOpen())//Nếu cổng serial mở, tiếp tục gửi
    {
        serialPort->write(packet);//gửi dữ liệu nhị phân Packet sang cổng Serial
        serialPort->waitForBytesWritten(50);//chờ cho gửi xong
        //Sau khi gửi xong, hiển thị thông báo lên textBrowser_Sent
        ui->textBrowser_Sent->append("Đã gửi: " + packet.toHex(' ').toUpper());

        QString timestamp = QDateTime::currentDateTime().toString("HH:mm:ss.zzz");//Lấy thời gian hiện tại, định dạng giờ:phút:giây.miligiây.
        QString canIdHex = QString("0x%1").arg(canId, 3, 16, QChar('0')).toUpper();//Định dạng số thành hex, độ dài tối thiểu 3 ký tự, thêm 0 phía trước nếu thiếu.
        //Ví dụ: 0x7A → 0x07A

        QString dataHex = data.toHex(' ').toUpper();
        QString crcHex = QString("0x%1").arg(calculateCRC8_AUTOSAR(data), 2, 16, QChar('0')).toUpper(); // hoặc tính CRC nếu cần
        QString cycleStr = QString::number(cycleValue) + " ms";
        //Hiển thị các thông tin trên lên tableWideget(table status)
        appendToTable(timestamp, canIdHex, data.length(), dataHex, crcHex, cycleStr);

    } else {
        QMessageBox::critical(this, "Lỗi", "Cổng Serial chưa mở!");
    }
}

void MainWindow::appendToTable(const QString &timestamp, const QString &canId, int dlc, const QString &data, const QString &crc, const QString &cycle)
{
    int rowCount = ui->tableWidget->rowCount();//Lấy số dòng hiện tại của bảng tableWidget, lưu vào biến rowCount
    ui->tableWidget->insertRow(rowCount);//Thêm một dòng mới vào vị trí rowCount (cuối bảng).

    //Thêm dữ liệu vào từng cột
    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(timestamp));//Gán giá trị timestamp vào ô nằm ở dòng rowCount, cột 0 của tableWidget.
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(canId));
    ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(dlc)));
    ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(data));
    ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(crc));
    ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(cycle));
}
void MainWindow::appendToReceiveTable(const QString &timestamp, const QString &canId, int dlc, const QString &data, const QString &crc,const QString &Status)
{
    int rowCount = ui->tableWidget_Receive->rowCount();
    ui->tableWidget_Receive->insertRow(rowCount);

    ui->tableWidget_Receive->setItem(rowCount, 0, new QTableWidgetItem(timestamp));
    ui->tableWidget_Receive->setItem(rowCount, 1, new QTableWidgetItem(canId));
    ui->tableWidget_Receive->setItem(rowCount, 2, new QTableWidgetItem(QString::number(dlc)));
    ui->tableWidget_Receive->setItem(rowCount, 3, new QTableWidgetItem(data));
    ui->tableWidget_Receive->setItem(rowCount, 4, new QTableWidgetItem(crc));
    ui->tableWidget_Receive->setItem(rowCount, 5, new QTableWidgetItem(Status));
}
//Received Data from F1
void MainWindow::on_btnConnectRx_clicked()
{
    QString portName = ui->comboBox_COM_RX->currentText();//gán cổng COM Rx đã chọn vào biến port Name.ví dụ "COM7"= portName
    //Nếu chưa có cổng COMRX-->báo lỗi
    if (portName.isEmpty())
    {
        QMessageBox::warning(this, "Cảnh báo", "Vui lòng chọn cổng COM RX!");
        return;
    }

    //Cấu hình cổng COM Rx
    serialPortRx->setPortName(portName);
    serialPortRx->setBaudRate(QSerialPort::Baud115200);  // hoặc cho phép chọn từ combobox
    serialPortRx->setDataBits(QSerialPort::Data8);
    serialPortRx->setStopBits(QSerialPort::OneStop);
    serialPortRx->setParity(QSerialPort::NoParity);

    //ReadOnly: chỉ nhận dữ liệu
    if (!serialPortRx->open(QIODevice::ReadOnly)) {//Nếu mở thất bại (cổng bận, sai tên...) → hiện lỗi:
        QMessageBox::critical(this, "Lỗi", "Không thể mở cổng COM RX!");
    } else {
        ui->lineEdit_Inforcn->setTextColor(Qt::darkBlue);
        ui->lineEdit_Inforcn->setText("Đã mở cổng COM RX: " + portName);
    }
}
void MainWindow::on_btnDisconnectRx_clicked()
{
    if (serialPortRx && serialPortRx->isOpen())//nếu serialPortRx tồn tại hoặc serialPortRx đang mở
    {
        serialPortRx->close();
        ui->lineEdit_Inforcn->setTextColor(Qt::darkRed);
        ui->lineEdit_Inforcn->setText("Đã ngắt kết nối cổng COM RX.");
    } else {
        ui->lineEdit_Inforcn->setTextColor(Qt::gray);
        ui->lineEdit_Inforcn->setText("Cổng COM RX đã được ngắt hoặc chưa mở.");
    }
}

void MainWindow::readUARTResponse()
{

    static QByteArray buffer;
    buffer.append(serialPortRx->readAll());

    const int frameLength = 12; // 2 (CAN ID) + 8 (data) + 1 (CRC) + 1 (status)

    while (buffer.size() >= frameLength) {
        QByteArray fullMessage = buffer.left(frameLength);
        buffer.remove(0, frameLength);

        // Tách CAN ID (Low trước)
        quint8 canIdLow  = static_cast<quint8>(fullMessage.at(0));
        quint8 canIdHigh = static_cast<quint8>(fullMessage.at(1));
        quint16 canId = (canIdHigh << 8) | canIdLow;

        // Tách dữ liệu (8 byte tiếp theo)
        QByteArray data = fullMessage.mid(2, 8);

        // Tách CRC
        quint8 crc = static_cast<quint8>(fullMessage.at(10));
        QString crcHex = QString("0x%1").arg(crc, 2, 16, QLatin1Char('0')).toUpper();
        // Nhận status
        quint8 statusByte = static_cast<quint8>(fullMessage.at(11));
        QString Status = (statusByte == 0x01) ? "Valid" : "Invalid";


        // Hiển thị
        QString timestamp = QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
        QString canIdStr = QString("0x%1").arg(canId, 3, 16, QLatin1Char('0')).toUpper();
        QString dataHex = data.toHex(' ').toUpper();

        appendToReceiveTable(timestamp, canIdStr, data.size(), dataHex, crcHex, Status);


        ui->textBrowser_Receip->append("Đã nhận: " + fullMessage.toHex(' ').toUpper());
        }

}
void MainWindow::on_multiCanWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
}


void MainWindow::on_btn_ClearSent_clicked()
{
    ui->textBrowser_Sent->clear();
    //Xóa nội dung toàn bộ bảng
    ui->tableWidget->clearContents();
    //xóa tất cả các dòng
    ui->tableWidget->setRowCount(0);
    // Đặt lại tiêu đề cột (nếu muốn giữ nguyên tiêu đề)
    QStringList headers = { "TimeStamp", "CAN ID", "DLC", "Data", "CRC", "Cycle" };
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}


void MainWindow::on_btn_ClearReceive_clicked()
{
    ui->textBrowser_Receip->clear();
    // ui->tableWidget_Receive->clear();
    // Xóa toàn bộ nội dung bảng
    ui->tableWidget_Receive->clearContents();
    // Xóa tất cả các dòng
    ui->tableWidget_Receive->setRowCount(0);
    // Đặt lại tiêu đề cột (nếu muốn giữ nguyên tiêu đề)
    QStringList headers = { "TimeStamp", "CAN ID", "DLC", "Data", "CRC", "Status" };
    ui->tableWidget_Receive->setHorizontalHeaderLabels(headers);
}

