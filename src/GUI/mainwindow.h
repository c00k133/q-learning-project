#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mycanvas.h"
#include <QMainWindow>
#include <QFrame>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  //Macro that tells the pre-compiler that this class has gui elements
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //Access all widgets in the window using this object
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
