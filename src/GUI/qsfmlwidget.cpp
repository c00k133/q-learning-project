#include "qsfmlwidget.h"

QSFMLWidget::QSFMLWidget(QWidget* Parent, const QPoint& Position, const QSize& Size, int FrameTime) :
QWidget       (Parent),
myInitialized (false)
{
    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);

    // Setup the widget geometry
    move(Position);
    resize(Size);

    // Setup the timer
    myTimer.setInterval(FrameTime);
}
QSFMLWidget::~QSFMLWidget() {}

void QSFMLWidget::showEvent(QShowEvent*)
{
    if (!myInitialized)
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        // Create the SFML window with the widget handle
        //Create(winId());
        RenderWindow::create(winId());
        //this->createWinId();
        // Let the derived class do its specific stuff
        OnInit();

        // Setup the timer to trigger a refresh at specified framerate
        connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        myTimer.start();

        myInitialized = true;
    }
}

QPaintEngine* QSFMLWidget::paintEngine() const
{
    return nullptr;
}

void QSFMLWidget::paintEvent(QPaintEvent*)
{
    //clear();
    //RenderWindow::clear();
    // Let the derived class do its specific stuff
    OnUpdate();

    // Display on screen
    //Display();
    //display();
    sf::RenderWindow::display();

}
