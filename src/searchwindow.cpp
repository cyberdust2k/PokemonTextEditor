#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <string.hpp>
#include <QList>


uchar *rom;
uint szrom;


namespace {
qint64 indexof(uchar b, uint i)
{
    for (; i < szrom; i++)
        if (rom[i] == b)
            return i;

    return -1;
}

QList<uint> searchsequence(const QByteArray &seq)
{
    int slen = seq.length();
    QList<uint> occurrences;
    qint64 current = indexof(seq.at(0), 0x100);

    while (current >= 0 && current <= (szrom - slen))
    {
        // check if following bytes are same as sequence
        int i = 1;
        for (; i < slen; i++)
            if (rom[current+i] != (uchar)(seq.at(i)))
                break;

        if (i == slen)
            occurrences.push_back((uint)current);

        current = indexof(seq.at(0), (uint)(current + i));
    }

    return occurrences;
}
}


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

void searchwindow::setrom(uchar *r, uint n)
{
    rom = r;
    szrom = n;
}

void searchwindow::setstr(int index)
{
    if (index == 0)
        ui->pushButton_4->setEnabled(false);
    else
        ui->pushButton_4->setEnabled(true);
    if (index == texts.size()-1)
        ui->pushButton_5->setEnabled(false);
    else
        ui->pushButton_5->setEnabled(true);

    currpos = index;
    ui->plainTextEdit_2->setPlainText(texts.at(index));
}

QString searchwindow::selected()
{
    return texts[currpos];
}

uint searchwindow::selectedOff()
{
    return textoffs[currpos];
}

void searchwindow::on_pushButton_2_clicked()
{
    reject();
}

void searchwindow::on_pushButton_3_clicked()
{
    texts.clear();
    currpos = 0;
    ui->groupBox_2->setEnabled(false);

    QString search = ui->plainTextEdit->toPlainText();
    bool searchbeg = ui->checkBox->isChecked();

    // ignores newline characters
    search.replace("\n", "");

    QByteArray bin = getstringbytes(search);
    if (bin.isNull() || bin.isEmpty())
        return;

    // search all occ
    textoffs = searchsequence(bin);
    if (textoffs.isEmpty())
    {
        QMessageBox::warning(this, "Search", "The text could not be found anywhere in the ROM!");
        return;
    }

    foreach (uint off, textoffs)
        texts.push_back(readpokestring(rom, off, searchbeg).replace("\\n", "\\n\n").replace("\\p", "\\p\n").replace("\\l", "\\l\n"));

    ui->groupBox_2->setEnabled(true);
    ui->pushButton->setEnabled(true);
    setstr(0);
}

void searchwindow::on_pushButton_4_clicked()
{
    setstr(currpos-1);
}

void searchwindow::on_pushButton_5_clicked()
{
    setstr(currpos+1);
}

void searchwindow::on_pushButton_clicked()
{
    accept();
}
