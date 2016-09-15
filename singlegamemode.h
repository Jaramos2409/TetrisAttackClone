#ifndef GAME_H
#define GAME_H

#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QStack>
#include "blocktype.h"
#include "gameclock.h"
#include "soundeffects.h"

class Block;
class Player;
class Countdown;
class GameMessage;
class GameScore;
class GameSpeedMsg;

enum GameState{INITGAME, COUNTDOWN, PLAYING, PAUSE, GAMEOVER};

class SingleGameMode : public QGraphicsRectItem
{
    static double gameSpeed;
    QString difficulty;
    int numOfBlockTypes;
    QList<Block*> blocks;
    QTimer* moveTimer;
    QStack<QList<Block*> > stacksOfMatchedBlocks;
    Player* player;
    bool hasReachedTop;
    GameState gameState;
    Countdown* gameStartCountdown;
    Countdown* gameEndCountdown;
    GameClock* gameClock;
    GameMessage* losingMsg;
    GameScore* gameScore;
    GameMessage* difficultyMsg;
    GameSpeedMsg* gameSpeedMsg;


    BlockType randBlockType();
    void initPlayer();
    void swapBlocks();
    void initBlocks();
    bool newBlockChk();
    int index(int, int);
    bool findMatches();
    bool emptyBlockHoleHandler();
    void allowMatches();
    void removeMatches();
    void delay(int);
    void checkTop();
    bool isTopRowEmpty();
    void stopMoveTimer();
    void startMoveTimer();
    void gameUpdate();
    void playerFocusChk();
    void windowFocusChk();
    void realignPlayer();
    void pauseGame();
    void resumeGame();

public:
    SingleGameMode(QString difficulty);
    ~SingleGameMode();

    void initGameElements();
    Countdown *getCountdown() const;
    void setCountdown(Countdown *value);
    GameClock *getGameClock() const;
    void setGameClock(GameClock *value);
    GameState getGameState() const;
    void setGameState(const GameState &value);
    GameScore *getGameScore() const;
    double getGameSpeed() const;
    QString getDifficulty() const;

    friend class Block;
    friend class Player;
    friend class TetrisAttackClone;
    friend class GameSpeedMsg;
};
#endif // GAME_H
