#include "fswindow.hpp"
#include "ui_fswindow.h"

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
