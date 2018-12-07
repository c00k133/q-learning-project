#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "qsfmlwidget.h"
#include <QMainWindow>


class MyCanvas : public QSFMLWidget
{
    Q_OBJECT
public:
    explicit MyCanvas(QWidget *Parent,
                         const QPoint& Position,
                         const QSize& Size);

    ~MyCanvas();

private:
    void OnInit() override;

    void OnUpdate() override;

    sf::Texture myImage;
    sf::Sprite mySprite;
    sf::RenderWindow* window;
    sf::View view;
};

#endif // MyCanvas_H
