#ifndef GAMESCORE_H
#define GAMESCORE_H

#include <QGraphicsTextItem>

class GameScore : public QGraphicsTextItem
{
    int score;
public:
    GameScore();
    int getScore() const;
    void setScore(int value);
    void incrementScore(int incrementValue);
};

#endif // GAMESCORE_H
