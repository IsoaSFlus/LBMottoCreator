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
    sub = NULL;
}

void MainWindow::picRender()
{
    QString temp;
    QImage img_temp = img->copy();

    temp = all + "Style: Default," + font +",54,&H00FFFFFF,&H00FFFFFF,&H00295479,&H00FFFFFF,-1,0,0,0,100,100,3,0,1,2,0,5,10,10,10,1" + QString("\n");
    temp += "[Events]" + QString("\n");
    temp += QString("Dialogue: 0,0:00:00.00,0:00:06.00,Default,,0000,0000,0000,,{\\an5\\fs") + QString("%1").arg(fsA) + QString("\\blur3\\pos(500,") + QString("%1").arg(siteA) + ")}" + motto + QString("\n");
    temp += QString("Dialogue: 0,0:00:00.00,0:00:06.00,Default,,0000,0000,0000,,{\\an5\\fs") + QString("%1").arg(fsB) + QString("\\blur3\\pos(") + QString("%1").arg(siteB_h) + "," +  QString("%1").arg(siteB) + QString(")}") + name + QString("\n");
    const std::string str = temp.toStdString();
    strcpy(sub,str.c_str());

    img_b = img_temp.bits();

    lb_render(img_b, sub, all.length()+1000);
    ui->label->setPixmap(QPixmap::fromImage(img_temp));
}
void MainWindow::siteAChanged(int num)
{
    siteA = 321 - num;
    picRender();
}

void MainWindow::siteBChanged(int num)
{
    siteB = 321 - num;
    picRender();
}
void MainWindow::siteBhChanged(int num)
{
    siteB_h = num;
    picRender();
}
void MainWindow::lineEditAChanged(const QString &mottoIn)
{
    motto = mottoIn;
    picRender();
}

void MainWindow::lineEditBChanged(const QString &nameIn)
{
    name = nameIn;
    picRender();
}
void MainWindow::spinBoxAChanged(int value)
{
    fsA = value;
    picRender();
}

void MainWindow::spinBoxBChanged(int value)
{
    fsB = value;
    picRender();
}

void MainWindow::showFont()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok);
    font = f.family();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalSlider->setRange(0,321);
    ui->verticalSlider_2->setRange(0,321);
    ui->horizontalSlider->setRange(0,1040);

    ui->verticalSlider->setValue(321-140);
    ui->verticalSlider_2->setValue(321-250);
    ui->horizontalSlider->setValue(800);

    QFile file("/home/midorikawa/qt/untitled5/lb.ass");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in_stream(&file);
    all = in_stream.readAll();
    sub = (char*)malloc(all.length()+1000);

    file.close();

    img = new QImage("/home/midorikawa/qt/untitled5/EF_WR_BG00.png");
    img_b = img->bits();
    siteA = 140;
    siteB = 250;
    siteB_h = 800;
    fsA = 55;
    fsB = 25;
    motto = "看来交易已经成功了";
    name = "Ludwig Van Beethoven";
    ui->lineEdit_2->setText(QString("看来交易已经成功了"));
    ui->lineEdit->setText(QString("Ludwig Van Beethoven"));
    ui->spinBox->setValue(55);
    ui->spinBox_2->setValue(25);

    ui->label->setPixmap(QPixmap::fromImage(*img));
    picRender();

    connect(ui->verticalSlider, &QSlider::valueChanged, this, &MainWindow::siteAChanged);
    connect(ui->verticalSlider_2, &QSlider::valueChanged, this, &MainWindow::siteBChanged);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::siteBhChanged);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this ,&MainWindow::lineEditAChanged);
    connect(ui->lineEdit, &QLineEdit::textChanged, this ,&MainWindow::lineEditBChanged);
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(spinBoxAChanged(int)));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(spinBoxBChanged(int)));
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::showFont);
}
