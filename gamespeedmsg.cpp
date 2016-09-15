#include <QFont>
#include <QTimer>

#include "gamespeedmsg.h"
#include "singlegamemode.h"

GameSpeedMsg::GameSpeedMsg()
{
    speedTimer = new QTimer();
    setFont(QFont("Press Start K", 16));
    setDefaultTextColor(QColor(255,255,255));
    setPlainText("Speed:\n" + QString::number(SingleGameMode::gameSpeed, 'f', 2));
}

GameSpeedMsg::~GameSpeedMsg()
{
    stopSpeedTimer();
    delete speedTimer;
}

void GameSpeedMsg::startSpeedTimer()
{
    connect(speedTimer, SIGNAL(timeout()), this, SLOT(updateSpeed()));
    speedTimer->start(30000);
}

void GameSpeedMsg::stopSpeedTimer()
{
    disconnect(speedTimer, SIGNAL(timeout()), this, SLOT(updateSpeed()));
    speedTimer->stop();
}

void GameSpeedMsg::updateSpeed()
{
    SingleGameMode::gameSpeed += 0.03;
    setPlainText("Speed:\n" + QString::number(SingleGameMode::gameSpeed, 'f', 2));
}
