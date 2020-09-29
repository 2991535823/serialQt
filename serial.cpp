#include "serial.h"

Serial::Serial()
{
    port=new QSerialPort();
    for (auto info : QSerialPortInfo::availablePorts()) {
        portinfo.append(info.portName());
    }
    qDebug()<<"调用构造方法\r\n";
}

Serial::~Serial()
{
    qDebug()<<"调用析构方法\r\n";
}

void Serial::setup(QString com,
                   int BaudRate,
                   QSerialPort::DataBits DataBits,
                   QSerialPort::Parity Parity,
                   QSerialPort::StopBits StopBits,
                   QSerialPort::FlowControl FlowControl)
{
    port->setPortName(com);
    if(port->open(QIODevice::ReadWrite))
    {
        //配置串口相应参数
        port->setBaudRate(BaudRate);
        port->setDataBits(DataBits);
        port->setParity(Parity);
        port->setStopBits(StopBits);
        port->setFlowControl(FlowControl);
    }else {
        QMessageBox::about(nullptr,"ERROR","串口打开失败\r\n检查线是否连接正常!");
        port->close();
    }
    connect(port,&QSerialPort::readyRead,this,&Serial::sendsignal);
}

void Serial::close()
{
    port->close();
}

void Serial::send(QString msg)
{
    if(msg!="")
    {
        port->write(msg.toLatin1());
    }
}
//当接收到结束符发送一个信号\r\n为结束符
//定义校验符
//数据格式
/*  $GPHCD,15,5,2017,22850.20,305.3650,-4.51,0.00,0.08,31.0997333,121.1730611,
 10. 46,500486.410,3449462.395,-91.887,4,19*44 */
//莫名奇妙实现了原理
void Serial::sendsignal()
{
   static int position=0;
    packetArray += port->readAll();
    for (auto &&i : packetArray) {
        if(i!='\n'){
            position++;
        }else {
            //添加信息
            rmsg.append(packetArray);
            //删除一条完整数据
            packetArray.remove(0,position+1);
            //重置删除位置
            position=0;
            //发送消息到达信号
            emit arrivemsg();
            break;
        }
    }
}



