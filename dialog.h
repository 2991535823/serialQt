#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "serial.h"
#include "msgdialog.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void refreshUI();
signals:
    void sendMsgToAnalysis(QString msg);
    void startAnalysisWindow();
private slots:
    void on_connctButton_clicked();

    void on_SendBtn_clicked();

    void on_AnalysisBtn_clicked();

private:
    Ui::Dialog *ui;
    Serial &manager =Serial::get_instance();
    MsgDialog analysisWindow;
};

#endif // DIALOG_H
