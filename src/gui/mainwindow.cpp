#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyCanvas* SFMLView = new MyCanvas(ui->frame, QPoint(0, 0), QSize(800, 800));
    SFMLView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

