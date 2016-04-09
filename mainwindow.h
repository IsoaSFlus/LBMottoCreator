#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
extern "C"{
#include "lbrender.h"
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_2_textEdited(int num);

private:
    Ui::MainWindow *ui;
    QImage *img;
    uchar *img_b;
    const QString sectA = "Dialogue: 0,0:00:00.00,0:00:06.00,Default,,0000,0000,0000,,{\\an5\\fs37\\blur3\\pos(500,";
    const QString sectB = ")}你为什么这么熟练啊";
    char *sub;
    QString all;
};

#endif // MAINWINDOW_H
