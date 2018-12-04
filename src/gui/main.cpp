#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  //Initiates a QMainWindow and shows it
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;
    w->setWindowTitle("Q-learning");
   // w->resize(520,500);
    w->show();

    /*QWidget* f = new QWidget(w);
    f->setWindowTitle("SFML");
    f->resize(1600, 900);
    f->show();

    MyCanvas* SFMLView = new MyCanvas(f, QPoint(0, 0), QSize(1600, 1600));
    SFMLView->show();

*/
    return a.exec();
}
