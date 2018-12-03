#include <QApplication>
#include "mainwindow.h"

#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
  /*
    //Initiates a QMainWindow and shows it
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;
    w->setWindowTitle("Q-learning");
   // w->resize(520,500);
    w->show();

    QWidget* f = new QWidget(w);
    f->setWindowTitle("SFML");
    f->resize(1600, 900);
    //f->show();

    MyCanvas* SFMLView = new MyCanvas(f, QPoint(0, 0), QSize(1600, 1600));
    SFMLView->show();

    return a.exec();
    */

  sf::View view(sf::Vector2f(0, 0), sf::Vector2f(300, 300));
  sf::RenderWindow window(sf::VideoMode(300, 300), "Testing");
  window.setFramerateLimit(60);

  while (window.isOpen()) {
    window.setView(view);

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::White);
    window.display();
  }

  return 0;
}
