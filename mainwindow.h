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
    void picRender(int siteA, int siteB, int fsA, int fsB, int siteB_h, QString font, QString motto, QString name);

private slots:
    void on_lineEdit_2_textEdited(int num);
    void showFont();

private:
    Ui::MainWindow *ui;
    QImage *img;
    uchar *img_b;
    const QString sectA = "Dialogue: 0,0:00:00.00,0:00:06.00,Default,,0000,0000,0000,,{\\an5\\fs37\\blur3\\pos(500,";
    const QString sectB = ")}你为什么这么熟练啊";
    char *sub;
    QString all;
    int siteA, siteB, fsA, fsB, siteB_h;
    QString font;
    QString motto;
    QString name;

};

#endif // MAINWINDOW_H
