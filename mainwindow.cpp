#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFontDialog>

MainWindow::~MainWindow()
{
    delete ui;
    delete img;
    img_b = NULL;

}

void picRender()
{
    QString temp;
    temp = all + "Style: Default," + font +",54,&H00FFFFFF,&H00FFFFFF,&H00295479,&H00FFFFFF,-1,0,0,0,100,100,3,0,1,2,0,5,10,10,10,1" + "\n" + "[Events]" + "Dialogue: 0,0:00:00.00,0:00:06.00,Default,,0000,0000,0000,,{\\an5\\fs"
}

void MainWindow::on_lineEdit_2_textEdited(int num)
{

    QImage img_temp = img->copy();

    siteA = 321 - num;
    QString temp;
    temp = all + sectA + QString("%1").arg(num) + sectB + "\n";
    const std::string str = temp.toStdString();
    //qDebug()<<temp;
    strcpy(sub,str.c_str());

    img_b = img_temp.bits();

    lb_render(img_b, sub, all.length()+300);
    ui->label->setPixmap(QPixmap::fromImage(img_temp));
}

void MainWindow::showFont()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok);
    f.family();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalSlider->setRange(0,321);
    ui->verticalSlider_2->setRange(0,321);
    QFile file("/home/midorikawa/qt/untitled5/lb.ass");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in_stream(&file);
    all = in_stream.readAll();
    sub = (char*)malloc(all.length()+300);
    //in_stream.flush();
    file.close();

    img = new QImage("/home/midorikawa/qt/untitled5/EF_WR_BG00.png");
    img_b = img->bits();


    //lb_render(img_b, sub, all.length()+300);
//    free(sub);
  //  qDebug()<<"110";
    ui->label->setPixmap(QPixmap::fromImage(*img));

    connect(ui->verticalSlider, &QSlider::valueChanged, this, &MainWindow::on_lineEdit_2_textEdited);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::showFont);
}
