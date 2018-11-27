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
/*protected:
    #ifndef QT_NO_CONTEXTMENU
        void contextMenuEvent(QContextMenuEvent *event) override;
    #endif // QT_NO_CONTEXTMENU
*/
private:
    void OnInit() override;

    void OnUpdate() override;

    sf::Texture myImage;
    sf::Sprite mySprite;
};

#endif // MyCanvas_H
