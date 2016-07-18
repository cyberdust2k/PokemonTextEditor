#include "insertwindow.h"
#include "ui_insertwindow.h"


QWidget *oldparent = NULL;


insertwindow::insertwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insertwindow)
{
    ui->setupUi(this);
}

insertwindow::~insertwindow()
{
    tree->collapseAll();
    tree->setParent(oldparent);
    delete ui;
}

void insertwindow::settree(QTreeWidget *t)
{
    oldparent = t->parentWidget();
    ui->gridLayout->removeWidget(ui->treeWidget);
    ui->gridLayout->addWidget(t);
    tree = t;

    t->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(t, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_treeWidget_customContextMenuRequested(QPoint)));
    connect(t, SIGNAL(itemSelectionChanged()), this, SLOT(on_treeWidget_itemSelectionChanged()));
}

QTreeWidgetItem *insertwindow::selected()
{
    return item;
}

QTreeWidgetItem *insertwindow::inserted()
{
    return iins;
}

void insertwindow::on_pushButton_2_clicked()
{
    disconnect(tree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_treeWidget_customContextMenuRequested(QPoint)));
    disconnect(tree, SIGNAL(itemSelectionChanged()), this, SLOT(on_treeWidget_itemSelectionChanged()));
    reject();
}

void insertwindow::on_pushButton_clicked()
{
    item = tree->selectedItems().at(0);
    iins = new QTreeWidgetItem(QStringList(ui->lineEdit->text()));
    disconnect(tree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_treeWidget_customContextMenuRequested(QPoint)));
    disconnect(tree, SIGNAL(itemSelectionChanged()), this, SLOT(on_treeWidget_itemSelectionChanged()));
    accept();
}

void insertwindow::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *item = tree->itemAt(pos);

    if (item->data(0, Qt::UserRole).toUInt() == 0)
    {
        // is folder
        QMenu contextMenu;
        QAction *add = contextMenu.addAction("Add sub-folder");
        if (contextMenu.exec(tree->mapToGlobal(pos)) == add)
        {
            bool result = false;
            QString name = QInputDialog::getText(
                        this,
                        "Choose folder name",
                        "Name:",
                        QLineEdit::Normal,
                        "Folder",
                        &result
                        );

            if (result && !name.isEmpty())
            {
                QTreeWidgetItem *i = new QTreeWidgetItem;
                i->setText(0, name);
                i->setData(0, Qt::UserRole, 0U);
                item->addChild(i);
                tree->update();
            }
        }
    }
}

void insertwindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->pushButton->setEnabled(!arg1.isEmpty() && tree->selectedItems().size() != 0 && tree->selectedItems().at(0)->data(0, Qt::UserRole).toUInt() == 0);
}

void insertwindow::on_treeWidget_itemSelectionChanged()
{
    ui->pushButton->setEnabled(tree->selectedItems().size() != 0 && ui->lineEdit->text().length() != 0 && tree->selectedItems().at(0)->data(0, Qt::UserRole).toUInt() == 0);
}
