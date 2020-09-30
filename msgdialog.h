#ifndef MSGDIALOG_H
#define MSGDIALOG_H

#include <QDialog>
#include "serial.h"
#include <QString>
#include <QDebug>
namespace Ui {
class MsgDialog;
}

class MsgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MsgDialog(QWidget *parent = nullptr);
    ~MsgDialog();
public slots:
    void analysismsg(QString msg);
    void startshow();
private:
    Ui::MsgDialog *ui;
    Serial &manager =Serial::get_instance();
};

#endif // MSGDIALOG_H
