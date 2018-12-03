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
    //QSFMLWidget constructor:
    explicit QSFMLWidget(QWidget* Parent, const QPoint& Position, const QSize& Size, int FrameTime = 0);

    ~QSFMLWidget() = default;

private :

    //member function that will be overridden
    virtual void OnInit() = 0;

    //member function that will be overridden
    virtual void OnUpdate() = 0;

    virtual QPaintEngine* paintEngine() const;

    //initializes the SFML View
    virtual void showEvent(QShowEvent*);

    //refreshes the SFML view
    virtual void paintEvent(QPaintEvent*);

    QTimer myTimer;
    bool   myInitialized;
};

#endif
