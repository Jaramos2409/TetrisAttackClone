#include <QGraphicsTextItem>
#include <QFont>
#include <QTime>
#include <QTimer>

#include "gamemessage.h"

GameMessage::GameMessage(QString msg, int fontSize)
{
    setFont(QFont("Press Start K", fontSize));
    setDefaultTextColor(QColor(255,255,255));
    setPlainText(msg);

    animationTimer = new QTimer(this);
    rainbowCounter = 0;
    qsrand(QTime::currentTime().msec());
}

GameMessage::~GameMessage()
{
    stopAnimation();
    delete animationTimer;
}


/**
 * Part of this function was taken from the following Stack Overflow answer:
 * https://stackoverflow.com/questions/19452530/how-to-render-a-rainbow-spectrum
 */
void GameMessage::animate()
{
    setDefaultTextColor(QColor::fromHslF(rainbowCounter/0.8, 0.95, 0.5));
    rainbowCounter = (qrand()%9) / 10.0;
    if (rainbowCounter < 0 || rainbowCounter > 1) rainbowCounter = 0.1;
}


void GameMessage::startAnimation()
{
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(animate()));
    animationTimer->start(17);
}


void GameMessage::stopAnimation()
{
    animationTimer->stop();
    disconnect(animationTimer,SIGNAL(timeout()),this,SLOT(animate()));
}
