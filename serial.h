#ifndef SERIAL_H
#define SERIAL_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QList>
#include <QMessageBox>
#include <QDebug>
#include <QObject>
class Serial:public QObject
{
    Q_OBJECT
public:
    QList<QString> portinfo;
    QList<QString> rmsg;
    QString packet;


    Serial(const Serial&)=delete;
    Serial& operator=(const Serial&)=delete;

    //打开串口
    void setup(QString com,
               int BaudRate,
               QSerialPort::DataBits DataBits=QSerialPort::Data8,
               QSerialPort::Parity Parity=QSerialPort::NoParity,
               QSerialPort::StopBits StopBits=QSerialPort::OneStop,
               QSerialPort::FlowControl FlowControl=QSerialPort::NoFlowControl);

    //关闭串口
    void close();
    void send(QString msg);
    //实现单例模式
    static Serial & get_instance(){
        static Serial instance;
        return instance;
    }
    //信号
signals:
    void arrivemsg();
    //槽
private slots:
    void sendsignal();

private:
    QSerialPort *port;
    QSerialPortInfo *info;
    QByteArray packetArray;

    Serial();
    ~Serial();
};

#endif // SERIAL_H
