#include "mycanvas.h"
#include <iostream>
MyCanvas::MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLWidget(Parent, Position, Size)
    { }


void MyCanvas::OnInit()
{
    // Load the image
    sf::RenderWindow window(sf::VideoMode(300,300),"SFML WORKS!");

    if((myImage.loadFromFile("Ball.png"))){
        std::cout << "successful loadFromFile\n";
    }
    // Setup the sprite
    mySprite.setTexture(myImage);
    //mySprite.setCenter(mySprite.GetSize() / 2.f);
    draw(mySprite);
    window.display();

}
//What should be displayed on update
void MyCanvas::OnUpdate()
    {

    std::cout << "updated\n";
    // Clear screen when updating
    window.clear();
    // Rotate the sprite
    //mySprite.rotate(GetFrameTime() * 100.f);

    // Draw it to the rendered frame
    window.draw(mySprite);

    //Finally display the rendered frame
    window.display();
}

