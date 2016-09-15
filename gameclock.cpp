#include <QTimer>
#include <QFont>
#include <QDebug>
#include "gameclock.h"

GameClock::GameClock()
{
    currentTime = QTime(0,0,0);
    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(showTime()));
    timeAsText = "Time:\n" + currentTime.toString("mm:ss");

    setFont(QFont("Press Start K", 16));
    setDefaultTextColor(QColor(255,255,255));
    setPlainText(timeAsText);
    currentTime.start();
}

GameClock::~GameClock()
{
    disconnect(updateTimer, SIGNAL(timeout()), this, SLOT(showTime()));
    delete updateTimer;
}

void GameClock::showTime()
{
    QTime timeSince = QTime(0,0,0);
    timeSince = timeSince.addMSecs(currentTime.elapsed());
    timeAsText = "Time:\n" + timeSince.toString("mm:ss");
    setPlainText(timeAsText);
}

QString GameClock::getCurrentTime()
{
    QTime timeSince = QTime(0,0,0);
    timeSince = timeSince.addMSecs(currentTime.elapsed());

    return timeSince.toString("mm:ss");
}

void GameClock::startTimer()
{
    updateTimer->start(1000);
    currentTime.restart();
}

void GameClock::stopTimer()
{
    updateTimer->stop();
}
