#ifndef FSWINDOW_HPP
#define FSWINDOW_HPP

#include <QDialog>

namespace Ui {
class fswindow;
}

class fswindow : public QDialog
{
    Q_OBJECT

public:
    explicit fswindow(QWidget *parent = 0);
    ~fswindow();

    void setrom(uchar *r, uint n);
    void setneeded(uint n);
    uint found();

private slots:
    void on_pushButton_2_clicked();
    void on_checkBox_toggled(bool checked);
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();

    void on_spinBox_3_editingFinished();

private:
    Ui::fswindow *ui;
    uint fndoff;
};

#endif // FSWINDOW_HPP
