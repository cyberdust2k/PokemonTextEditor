#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <string.hpp>
#include <QList>


uchar *rom;
uint szrom;


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
        for (; i < slen-1; i++)
            if (rom[current+i] != (uchar)(seq.at(i)))
                break;

        if (i == slen-1)
            occurrences.push_back((uint)current);

        current = indexof(seq.at(0), (uint)(current + slen));
    }

    return occurrences;
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


void searchwindow::settree(QTreeWidget *tree)
{
    utree = tree;
}

void searchwindow::setini(QString path)
{
    fpini = path;
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
    if (index == texts.size()-1)
        ui->pushButton_5->setEnabled(false);

    currpos = index;
    ui->plainTextEdit_2->setPlainText(texts.at(index));
}

void searchwindow::on_pushButton_2_clicked()
{
    setResult(0);
    close();
}

void searchwindow::on_pushButton_3_clicked()
{
    texts.clear();
    currpos = 0;
    ui->groupBox_2->setEnabled(false);

    QString search = ui->plainTextEdit->toPlainText();
    bool searchbeg = ui->checkBox->isChecked();
    QByteArray bin = getstringbytes(search);
    if (bin.isNull() || bin.isEmpty())
        return;

    // search all occ
    QList<uint> offsets = searchsequence(bin);
    if (offsets.isEmpty())
    {
        QMessageBox::warning(this, "Search", "The text could not be found anywhere in the ROM!");
        return;
    }

    foreach (uint off, offsets)
        texts.push_back(readpokestring(rom, off, searchbeg));

    ui->groupBox_2->setEnabled(true);
    setstr(0);
}
