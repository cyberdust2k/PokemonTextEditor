#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <QtWidgets>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupui(bool b);
    void loadini();
    void repoint(uint oldoff, uint newoff);
    const char *readByteArray(int n);
    unsigned int readWord();
    unsigned short readHWord();
    unsigned char readByte();
    void writeByteArray(const QByteArray &array);
    void writeWord(unsigned int word);
    void writeHWord(unsigned short hword);
    void writeByte(unsigned char byte);
    void seek(uint offs);
    void writeini();

private slots:
    void on_actionOpen_ROM_triggered();
    void on_actionExit_triggered();
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_actionSave_ROM_triggered();
    void on_actionCreate_specific_INI_triggered();
    void on_actionSearch_Text_triggered();
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);
    void on_actionAbout_triggered();
    void on_actionWrite_current_text_triggered();

    void on_plainTextEdit_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    std::fstream rom;
    uint bypos;
    QString fprom;
    QString fpini;
    QString fpspd;
    QTreeWidgetItem *last;
};

#endif // MAINWINDOW_H
