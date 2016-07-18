#ifndef SEARCHWINDOW_HPP
#define SEARCHWINDOW_HPP

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class searchwindow;
}

class searchwindow : public QDialog
{
    Q_OBJECT

public:
    explicit searchwindow(QWidget *parent = 0);
    ~searchwindow();

    void setrom(uchar *r, uint n);
    void setstr(int index);
    QString selected();
    uint selectedOff();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_clicked();

private:
    Ui::searchwindow *ui;
    QTreeWidget *utree;
    QString fpini;
    QStringList texts;
    QList<uint> textoffs;
    int currpos;
};

#endif // SEARCHWINDOW_HPP
