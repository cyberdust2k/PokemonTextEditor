#ifndef ABOUTWINDOW_HPP
#define ABOUTWINDOW_HPP

#include <QDialog>

namespace Ui {
class aboutwindow;
}

class aboutwindow : public QDialog
{
    Q_OBJECT

public:
    explicit aboutwindow(QWidget *parent = 0);
    ~aboutwindow();

private:
    Ui::aboutwindow *ui;
};

#endif // ABOUTWINDOW_HPP
