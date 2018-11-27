#ifndef GUARD
#define GUARD

#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif

#include <SFML/Graphics.hpp>
#include <QTimer>
#include <QObject>
#include <QWidget>



class QSFMLWidget : public QWidget, public sf::RenderWindow
{
public :

    QSFMLWidget(QWidget* Parent, const QPoint& Position, const QSize& Size, int FrameTime = 0);

    virtual ~QSFMLWidget();

private :

    virtual void OnInit()=0;

    virtual void OnUpdate()=0;

    virtual QPaintEngine* paintEngine() const;

    //initializes the SFML View
    virtual void showEvent(QShowEvent*);

    //refreshes the SFML view
    virtual void paintEvent(QPaintEvent*);

    QTimer myTimer;
    bool   myInitialized;
};

#endif
