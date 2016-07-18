#ifndef INSERTWINDOW_HPP
#define INSERTWINDOW_HPP

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class insertwindow;
}

class insertwindow : public QDialog
{
    Q_OBJECT

public:
    explicit insertwindow(QWidget *parent = 0);
    ~insertwindow();

    void settree(QTreeWidget *tree);
    QTreeWidgetItem *selected();
    QTreeWidgetItem *inserted();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);
    void on_lineEdit_textChanged(const QString &arg1);
    void on_treeWidget_itemSelectionChanged();

private:
    Ui::insertwindow *ui;
    QTreeWidget *tree;
    QTreeWidgetItem *item = NULL;
    QTreeWidgetItem *iins = NULL;
    int32_t poketextlen;
};

#endif // INSERTWINDOW_HPP
