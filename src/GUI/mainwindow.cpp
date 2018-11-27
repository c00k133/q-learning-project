#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyCanvas* SFMLView = new MyCanvas(this->ui->frame, QPoint(20, 20), QSize(360, 360));
    SFMLView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
