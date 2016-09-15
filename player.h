#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>

#include "block.h"

class SingleGameMode;

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    SingleGameMode* gameIn;
    QTimer* moveTimer;
    bool paused;
public:
    Player(int posX, int posY, SingleGameMode* game, QTimer *moveTimer);
    ~Player();

    void keyPressEvent(QKeyEvent*);
    void setScore(int value);

public slots:
    void move();

    friend class SingleGameMode;
friend class Block;
};

#endif // PLAYER_H
