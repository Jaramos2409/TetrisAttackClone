#include "player.h"

#include <QDebug>
#include <QGraphicsItem>


Player::Player(int posX, int posY, SingleGameMode* game, QTimer* moveTimer)
{
    QImage playerSkin = QImage(":/player/playercursor.png");
    setPixmap(QPixmap::fromImage(playerSkin));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setPos(posX,posY);
    setZValue(5);
    show();

    this->moveTimer = moveTimer;
    connect(this->moveTimer,SIGNAL(timeout()),this,SLOT(move()));

    gameIn = game;

    paused = false;
}

Player::~Player()
{
    disconnect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
}

void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        if (pos().x() > gameIn->rect().x())
        {
            setPos(x()-66,y());
        }
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 132 < gameIn->rect().x() + gameIn->rect().width())
        {
            setPos(x()+66,y());
        }
    }
    else if (event->key() == Qt::Key_Up){
        if (pos().y() > gameIn->y())
        {
            setPos(x(),y()-66);
        }
    }
    else if (event->key() == Qt::Key_Down){
        if (pos().y() + 66 < gameIn->rect().height())
        {
            setPos(x(),y()+66);
        }
    }
    else if (event->key() == Qt::Key_Space)
    {
       gameIn->swapBlocks();
    }
    else if (event->key() == Qt::Key_Escape)
    {
        if (!paused)
        {
           gameIn->pauseGame();
           paused = true;
        }
        else
        {
            gameIn->resumeGame();
            paused = false;
        }
    }
}

void Player::move()
{
    setPos(x(),y()-SingleGameMode::gameSpeed);

    if (y() < -66)
    {
        setPos(x(),y()+66);
    }
}
