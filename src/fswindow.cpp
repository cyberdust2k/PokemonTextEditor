#include "fswindow.h"
#include "ui_fswindow.h"
#include <QtWidgets>


/* reminder: texts end with 0xFF -> search for one more 0xFF, increase offset by one */


namespace {
uchar *rom;
uint szrom;
uint bytes;
}


fswindow::fswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fswindow)
{
    ui->setupUi(this);
}

fswindow::~fswindow()
{
    delete ui;
}


uint fswindow::found()
{
    return fndoff;
}

void fswindow::setrom(uchar *r, uint n)
{
    rom = r;
    szrom = n;

    ui->spinBox->setMaximum(n-1);
    ui->spinBox_2->setMaximum(n-1);
    ui->spinBox_3->setMaximum(n-1);
}

void fswindow::setneeded(uint n)
{
    if (n)
    {
        ui->spinBox_2->setValue(n);
        ui->spinBox_2->setEnabled(false);
        bytes = n;
    }
}

void fswindow::on_pushButton_2_clicked()
{
    if (ui->spinBox_2->value() == 0)
    {
        QMessageBox::warning(
                    this,
                    "Search",
                    "You should at least search for one byte!");

        return;
    }


    // search for specified bytes
    int tosearch = ui->spinBox_2->value();
    int iter = 0;
    uint start = (uint)(ui->spinBox->value());
    uchar *romloc = rom + start;

    while (romloc < rom + szrom && iter < tosearch)
    {
        if (*romloc++ != 0xFF)
        {
            iter = 0;
            start = (romloc - rom);
        }
        else
        {
            iter++;
        }
    }

    // check if found
    if (iter == tosearch)
    {
        fndoff = start + 1;
        ui->spinBox_3->setValue(fndoff);
        ui->pushButton->setEnabled(true);
    }
    else
    {
        QMessageBox::warning(
                    this,
                    "Search",
                    QString("There aren't 0x%0 free bytes, starting from 0x%1!").arg(QString::number(tosearch, 16), QString::number(start, 16)));

        fndoff = 0;
        ui->spinBox_3->setValue(0);
        ui->pushButton->setEnabled(false);
    }
}

void fswindow::on_checkBox_toggled(bool checked)
{
    ui->spinBox_3->setReadOnly(!checked);
    ui->spinBox_3->setEnabled(checked);
}

void fswindow::on_pushButton_3_clicked()
{
    reject();
}

void fswindow::on_pushButton_clicked()
{
    fndoff = (uint)(ui->spinBox_3->value());
    accept();
}

void fswindow::on_spinBox_3_editingFinished()
{
    ui->pushButton->setEnabled(ui->spinBox_3->value() > 0);
}
