#include <QFont>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QGraphicsScene>

#include "countdown.h"
#include "soundeffects.h"

int Countdown::getCounter() const
{
    return counter;
}

void Countdown::setCounter(int value)
{
    counter = value;
}

Countdown::Countdown(int counter)
{
    this->counter = counter;
    this->initialCount = counter;

    countdownUpdateTimer = new QTimer(this);

    setFont(QFont("Press Start K", 72));
    setDefaultTextColor(QColor(255,255,255));
    adjustSize();
    setPlainText(QString::number(this->counter));
}

Countdown::~Countdown()
{
    disconnect(countdownUpdateTimer,SIGNAL(timeout()),this,SLOT(update()));
    delete countdownUpdateTimer;
}

void Countdown::update()
{
    counter -= 1;
    setPlainText(QString::number(counter));

    if (counter < 0)
    {
        disconnect(countdownUpdateTimer,SIGNAL(timeout()),this,SLOT(update()));
        countdownUpdateTimer->stop();
        scene()->removeItem(this);
    }
    SoundEffects::getSoundEffect(COUNTDOWN_SOUND)->play();
}

void Countdown::startCountdown()
{
    connect(countdownUpdateTimer,SIGNAL(timeout()),this,SLOT(update()));
    countdownUpdateTimer->start(1000);
}

void Countdown::stopCountdown()
{
    disconnect(countdownUpdateTimer,SIGNAL(timeout()),this,SLOT(update()));
    countdownUpdateTimer->stop();
    counter = initialCount;
    setPlainText(QString::number(this->counter));
}

void Countdown::pauseCountdown()
{
    countdownUpdateTimer->stop();
}

void Countdown::resumeCountdown()
{
    countdownUpdateTimer->start(1000);
}
