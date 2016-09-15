#include <QFont>

#include "gamescore.h"

GameScore::GameScore()
{
    score = 0;
    setFont(QFont("Press Start K", 16));
    setDefaultTextColor(QColor(255,255,255));
    setPlainText("Score:\n" + QString::number(score));
}


int GameScore::getScore() const
{
    return score;
}

void GameScore::setScore(int value)
{
    score = value;
}

void GameScore::incrementScore(int incrementValue)
{
    score += incrementValue;
    setPlainText("Score:\n" + QString::number(score));
}
