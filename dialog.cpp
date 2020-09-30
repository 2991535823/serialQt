#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //加载串口
    for (auto info : manager.portinfo) {
        ui->comboBox->addItem(info);
    }
    //实现读取串口数据
    connect(&manager,&Serial::arrivemsg,this,&Dialog::refreshUI);
    connect(this,&Dialog::sendMsgToAnalysis,&analysisWindow,&MsgDialog::analysismsg);
    connect(this,&Dialog::startAnalysisWindow,&analysisWindow,&MsgDialog::startshow);
}

Dialog::~Dialog()
{
    delete ui;
}
//有消息到来，刷新页面
void Dialog::refreshUI()
{
    ui->Content->clear();
    QString msg=manager.getmsg();

    ui->Content->append(msg);
    emit sendMsgToAnalysis(msg);
}

void Dialog::on_connctButton_clicked()
{
    if(ui->connctButton->text()=="Start")
    {
        manager.setup(ui->comboBox->currentText(),ui->comboBox_2->currentText().toInt());
        ui->connctButton->setText("Stop");
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
    }else
    {
        manager.close();
        ui->connctButton->setText("Start");
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
    }
}

void Dialog::on_SendBtn_clicked()
{
    QString temp=ui->SendContent->toPlainText();
    manager.send(temp+'\n');
}

void Dialog::on_AnalysisBtn_clicked()
{
    emit startAnalysisWindow();
}
