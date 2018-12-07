#include "mycanvas.h"
#include <iostream>
MyCanvas::MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLWidget(Parent, Position, Size)
    { }

MyCanvas::~MyCanvas() {
    delete window;
}

void MyCanvas::OnInit()
{
//    // Load the image
//    sf::RenderWindow window(sf::VideoMode(300,300),"SFML WORKS!");
//
//    if((myImage.loadFromFile("Ball.png"))){
//        std::cout << "successful loadFromFile\n";
//    }
//    // Setup the sprite
//    mySprite.setTexture(myImage);
//    //mySprite.setCenter(mySprite.GetSize() / 2.f);
//    draw(mySprite);
//    window.display();
    view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(300, 300));
    window = new sf::RenderWindow(sf::VideoMode(300, 300), "Testing");
    window->setFramerateLimit(60);
}
//What should be displayed on update
void MyCanvas::OnUpdate()
{
//    std::cout << "updated\n";
//    // Clear screen when updating
//    window.clear();
//    // Rotate the sprite
//    //mySprite.rotate(GetFrameTime() * 100.f);
//
//    // Draw it to the rendered frame
//    window.draw(mySprite);
//
//    //Finally display the rendered frame
//    window.display();

    window->setView(view);
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
    window->clear(sf::Color::White);
    window->display();
}

