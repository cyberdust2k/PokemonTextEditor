#include "insertwindow.hpp"
#include "ui_insertwindow.h"

insertwindow::insertwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insertwindow)
{
    ui->setupUi(this);
}

insertwindow::~insertwindow()
{
    delete ui;
}
