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
    void picRender();

private slots:
    void siteAChanged(int num);
    void siteBChanged(int num);
    void siteBhChanged(int num);
    void lineEditAChanged(const QString &mottoIn);
    void lineEditBChanged(const QString &nameIn);
    void spinBoxAChanged(int value);
    void spinBoxBChanged(int value);
    void showFont();

private:
    Ui::MainWindow *ui;
    QImage *img;
    uchar *img_b;
    char *sub;
    QString all;
    int siteA, siteB, fsA, fsB, siteB_h;
    QString font;
    QString motto;
    QString name;

};

#endif // MAINWINDOW_H
