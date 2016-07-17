#ifndef SEARCHWINDOW_HPP
#define SEARCHWINDOW_HPP

#include <QDialog>

namespace Ui {
class searchwindow;
}

class searchwindow : public QDialog
{
    Q_OBJECT

public:
    explicit searchwindow(QWidget *parent = 0);
    ~searchwindow();

private:
    Ui::searchwindow *ui;
};

#endif // SEARCHWINDOW_HPP
