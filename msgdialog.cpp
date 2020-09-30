#include "msgdialog.h"
#include "ui_msgdialog.h"

MsgDialog::MsgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Analysis");
}

MsgDialog::~MsgDialog()
{
    delete ui;
}

void MsgDialog::analysismsg(QString msg)
{
    auto m_msg=msg.split(',');
    //新建一个类来存放数据;
    auto direction=m_msg[5];
    auto Pitch=m_msg[6];
    auto VTG=m_msg[8];
    auto Lat=m_msg[9];
    auto Lon=m_msg[10];
    auto Alt=m_msg[11];
    ui->label->setText("航向角:"+direction+"°");
    ui->label_2->setText("俯仰角:"+Pitch+"°");
    ui->label_3->setText("速度:"+VTG);
    ui->label_4->setText("纬度:"+Lat+"°");
    ui->label_5->setText("经度:"+Lon+"°");
    ui->label_6->setText("海拔:"+Alt+"m");
}

void MsgDialog::startshow()
{
    this->show();
}
