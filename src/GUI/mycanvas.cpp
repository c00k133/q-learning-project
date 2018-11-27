#include "mycanvas.h"

MyCanvas::MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLWidget(Parent, Position, Size)
    { }


void MyCanvas::OnInit()
{
    // Load the image
    myImage.loadFromFile("ball.png");

    // Setup the sprite
    mySprite.setTexture(myImage);
    //mySprite.setCenter(mySprite.GetSize() / 2.f);
}

void MyCanvas::OnUpdate()
    {
    // Clear screen
    RenderWindow::clear(sf::Color(0, 128, 0));

    // Rotate the sprite
    //mySprite.rotate(GetFrameTime() * 100.f);

    // Draw it
    RenderWindow::draw(mySprite);
}
