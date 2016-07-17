#include "searchwindow.hpp"
#include "ui_searchwindow.h"

searchwindow::searchwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchwindow)
{
    ui->setupUi(this);
}

searchwindow::~searchwindow()
{
    delete ui;
}
