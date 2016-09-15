#include <QBrush>
#include <QList>
#include <QTime>
#include <QGraphicsScene>
#include <QCoreApplication>
#include <QEventLoop>
#include <QSoundEffect>
#include <QDebug>

#include "singlegamemode.h"
#include "block.h"
#include "player.h"
#include "countdown.h"
#include "gamemessage.h"
#include "gamescore.h"
#include "gamespeedmsg.h"
#include "soundeffects.h"
#include "soundtype.h"

double SingleGameMode::gameSpeed = 1.5;

QString SingleGameMode::getDifficulty() const
{
    return difficulty;
}

SingleGameMode::SingleGameMode(QString difficulty)
{
    setRect(200,0,396,600);
    setBrush(Qt::white);
    setOpacity(0.15);
    show();

    moveTimer = new QTimer();

    hasReachedTop = false;
    gameState = INITGAME;

    this->difficulty = difficulty;

    if (difficulty == "EASY")
    {
        gameSpeed = 0.2;
        numOfBlockTypes = 4;
    }
    else if (difficulty == "MEDIUM")
    {
        gameSpeed = 0.4;
        numOfBlockTypes = 5;
    }
    else
    {
        gameSpeed = 0.6;
        numOfBlockTypes = 6;
    }
}

SingleGameMode::~SingleGameMode()
{
    qDeleteAll(blocks.begin(), blocks.end());
    blocks.clear();
    stacksOfMatchedBlocks.clear();
    delete player;
    delete moveTimer;
    delete gameStartCountdown;
    delete gameEndCountdown;
    delete gameClock;
    delete gameScore;
    delete losingMsg;
    delete difficultyMsg;
    delete gameSpeedMsg;
}

void SingleGameMode::initGameElements()
{
    initPlayer();

    gameStartCountdown = new Countdown(3);
    gameStartCountdown->setPos((scene()->width()/2) - gameStartCountdown->boundingRect().width()/2
                               , scene()->height()/2 - 50);
    scene()->addItem(gameStartCountdown);

    gameClock = new GameClock();
    gameClock->setPos(scene()->width()-gameClock->boundingRect().width(), 0);
    scene()->addItem(gameClock);

    gameEndCountdown = new Countdown(5);
    gameEndCountdown->setPos(scene()->width()-gameEndCountdown->boundingRect().width(),
                             gameClock->y()+gameClock->boundingRect().height());

    losingMsg = new GameMessage("You're\nLosing!", 20);
    losingMsg->setPos(scene()->width()-losingMsg->boundingRect().width(),
                      gameEndCountdown->y()+gameEndCountdown->boundingRect().height());

    gameScore = new GameScore();
    gameScore->setPos(0, 0);
    scene()->addItem(gameScore);

    difficultyMsg = new GameMessage("Mode:\n" + difficulty, 16);
    difficultyMsg->setPos(0,
                          gameScore->boundingRect().height() +
                          gameScore->y() +
                          difficultyMsg->boundingRect().height());
    scene()->addItem(difficultyMsg);

    gameSpeedMsg = new GameSpeedMsg();
    gameSpeedMsg->setPos(0,
                         difficultyMsg->boundingRect().height() +
                         difficultyMsg->y() +
                         gameSpeedMsg->boundingRect().height());
    scene()->addItem(gameSpeedMsg);
}

double SingleGameMode::getGameSpeed() const
{
    return gameSpeed;
}

GameState SingleGameMode::getGameState() const
{
    return gameState;
}

void SingleGameMode::setGameState(const GameState &value)
{
    gameState = value;
}

GameScore *SingleGameMode::getGameScore() const
{
    return gameScore;
}

Countdown *SingleGameMode::getCountdown() const
{
    return gameStartCountdown;
}

void SingleGameMode::setCountdown(Countdown *value)
{
    gameStartCountdown = value;
}

GameClock *SingleGameMode::getGameClock() const
{
    return gameClock;
}

void SingleGameMode::setGameClock(GameClock *value)
{
    gameClock = value;
}

void SingleGameMode::swapBlocks()
{
    Block* blocksToBeSwapped[2] = {NULL};
    int count = 0;

    int blockListSize = blocks.size();

    for(int i = 0; i < blockListSize; i++)
    {
        QPointF mappedPoint = player->mapFromScene(blocks[i]->center());
        if (player->contains(mappedPoint))
        {
            blocksToBeSwapped[count] = blocks[i];
            count++;
        }

        if (count > 1) break;
    }

    SoundEffects::getSoundEffect(SWAPBLOCKS)->play();

    if (blocksToBeSwapped[1] != NULL)
    {
        QPointF blockOnePos = blocksToBeSwapped[0]->pos();
        QPointF blockTwoPos = blocksToBeSwapped[1]->pos();

        blocksToBeSwapped[0]->setPos(blockTwoPos);
        blocksToBeSwapped[1]->setPos(blockOnePos);
        blocks.swap(blocks.indexOf(blocksToBeSwapped[0])
                , blocks.indexOf(blocksToBeSwapped[1]));
    }
}


void SingleGameMode::initBlocks()
{
    qsrand(QTime::currentTime().msec());
    int x = 200;
    for (int i = 0; i < 6; i++)
    {
        Block* newBlock = new Block(randBlockType(), x, 600, false, moveTimer);
        blocks.push_back(newBlock);
        scene()->addItem(newBlock);
        x += 66;
    }
}

bool SingleGameMode::newBlockChk()
{
    bool result = true;

    foreach(Block* curBlock, blocks)
    {
        result = curBlock->collidesWithItem(this, Qt::ContainsItemBoundingRect);
        if (result == false)
        {
            break;
        }
    }

    return result;
}

BlockType SingleGameMode::randBlockType()
{
    BlockType randomBlockType = RED;

    int randNum = qrand()%numOfBlockTypes;

    switch(randNum)
    {
        case 0:
            randomBlockType = RED;
            break;
        case 1:
            randomBlockType = GREEN;
            break;
        case 2:
            randomBlockType = BLUE;
            break;
        case 3:
            randomBlockType = YELLOW;
            break;
        case 4:
            randomBlockType = ORANGE;
            break;
        case 5:
            randomBlockType = PURPLE;
            break;
    }

    return randomBlockType;
}

void SingleGameMode::initPlayer()
{
    player = new Player(332, 534, this, moveTimer);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene()->addItem(player);
}

//Code taken from the following stack overflow question:
//https://stackoverflow.com/questions/12776872/how-to-use-qvector-as-two-dimensional-array
int SingleGameMode::index(int y, int x) {
    return x + 6 * y;
}

bool SingleGameMode::findMatches()
{
    QList<Block*> matchedBlocks;
    bool vertMatchesFound = false;
    bool horizMatchesFound = false;
    int blockSize = blocks.size();
    int maxRowNum = blockSize/6;

    for (int y = 0; y < maxRowNum - 2 && !vertMatchesFound ; y++) //vertical matching
    {
        for (int x = 0; x < 6 && !vertMatchesFound; x++)
        {
            if (blocks[index(y,x)]->getAllowMatch()
                && blocks[index(y+1,x)]->getAllowMatch()
                && blocks[index(y+2, x)]->getAllowMatch()
                && blocks[index(y,x)]->getBlockType() != EMPTY
                && blocks[index(y+1,x)]->getBlockType() != EMPTY
                && blocks[index(y+2,x)]->getBlockType() != EMPTY
                && blocks[index(y,x)]->getBlockType() == blocks[index(y+1,x)]->getBlockType()
                && blocks[index(y+1,x)]->getBlockType() == blocks[index(y+2,x)]->getBlockType())
            {
                vertMatchesFound = true;
                matchedBlocks.push_back(blocks[index(y,x)]);
                matchedBlocks.push_back(blocks[index(y+1,x)]);
                matchedBlocks.push_back(blocks[index(y+2,x)]);

                int lastYMatched = y+2;

                while (blocks[index(lastYMatched+1,x)]->getAllowMatch()
                       && blocks[index(lastYMatched+1, x)]->getBlockType() != EMPTY
                       && blocks[index(lastYMatched, x)]->getBlockType() == blocks[index(lastYMatched+1, x)]->getBlockType())
                {
                    matchedBlocks.push_back(blocks[index(lastYMatched+1, x)]);
                    lastYMatched += 1;
                }
            }
        }
    }


    for (int y = 0; y < maxRowNum - 1 && !horizMatchesFound ; y++) //horizontal matching
    {
        for (int x = 0; x < 4 && !horizMatchesFound; x++)
        {
            if (blocks[index(y,x)]->getAllowMatch()
                && blocks[index(y,x+1)]->getAllowMatch()
                && blocks[index(y, x+2)]->getAllowMatch()
                && blocks[index(y,x)]->getBlockType() != EMPTY
                && blocks[index(y,x+1)]->getBlockType() != EMPTY
                && blocks[index(y,x+2)]->getBlockType() != EMPTY
                && blocks[index(y,x)]->getBlockType() == blocks[index(y,x+1)]->getBlockType()
                && blocks[index(y,x+1)]->getBlockType() == blocks[index(y,x+2)]->getBlockType())
            {
                horizMatchesFound = true;
                matchedBlocks.push_back(blocks[index(y,x)]);
                matchedBlocks.push_back(blocks[index(y,x+1)]);
                matchedBlocks.push_back(blocks[index(y,x+2)]);

                int lastXMatched = x+2;

                while (lastXMatched < 5
                       && blocks[index(y,lastXMatched+1)]->getAllowMatch()
                       && blocks[index(y, lastXMatched+1)]->getBlockType() != EMPTY
                       && blocks[index(y, lastXMatched)]->getBlockType() == blocks[index(y, lastXMatched+1)]->getBlockType())
                {
                    matchedBlocks.push_back(blocks[index(y, lastXMatched+1)]);
                    lastXMatched += 1;
                }
            }
        }
    }


    if (!matchedBlocks.isEmpty()) // checks for duplicates in a special match
    {
        QMutableListIterator<Block*> it(matchedBlocks);

        while (it.hasNext())
        {
            it.next();

            int firstIndexOf = matchedBlocks.indexOf(it.value());
            int lastIndexOf = matchedBlocks.lastIndexOf(it.value());

            if (firstIndexOf != lastIndexOf)
            {
                it.remove();
            }
        }
    }


    if (vertMatchesFound || horizMatchesFound)
    {
        bool specialCheck = true;
        QMutableListIterator<Block*> it(matchedBlocks);

        if (vertMatchesFound && horizMatchesFound)
        {
            qDebug() <<"BOTH MATCH TYPES FOUND";

            it.toBack();            // to check type of horizMatches if they exist
            Block* lastMatchedBlock = it.peekPrevious();
            it.value()->setBlockType(it.previous()->getMatchType());
            BlockType blockType = it.value()->getBlockType();
            it.toFront();           // return to front of list to
                                    // check vertMatches type if they exist

            while (it.hasNext() && it.next() != lastMatchedBlock)        //changes the blocks skin to matched skins
            {                                                           // AND checks if all the blocks are the same type
                it.value()->setBlockType(it.value()->getMatchType());

                if (it.value()->getBlockType() != blockType
                        && vertMatchesFound && horizMatchesFound
                        && specialCheck)
                {
                    specialCheck = false;
                }
            }
        }
        else
        {
            while (it.hasNext())
            {
                it.value()->setBlockType(it.next()->getMatchType());
            }
            specialCheck = false;
        }


        SoundEffects::getSoundEffect(MATCHED)->play();

        moveTimer->stop();
        delay(150);

        stacksOfMatchedBlocks.push(matchedBlocks);

        while (!matchedBlocks.isEmpty())
        {
            Block* matchedBlock = matchedBlocks.takeLast();
            if (specialCheck)
            {
                qDebug() << "SPECIAL MATCH FOUND" << matchedBlock->getBlockType();
                matchedBlock->setBlockType(SPECMATCHED);
            }
            else
            {
                qDebug() << "REGULAR MATCH FOUND" << matchedBlock->getBlockType();
                matchedBlock->setBlockType(REGMATCHED);
            }
            matchedBlock->setAllowMatch(false);
        }
    }

    return vertMatchesFound;
}

bool SingleGameMode::emptyBlockHoleHandler()
{
    int blockListSize = blocks.size();
    int maxRowNum = blockListSize/6;
    bool emptyFound = false;
    int lowestBlockYIndex = 0;

    for (int y = maxRowNum - 2; y  >= 0; y--)
    {
        for (int x = 5; x >= 0; x--)
        {
            if (blocks[index(y,x)]->getBlockType() != EMPTY
                    && y+1 < maxRowNum
                    && blocks[index(y+1,x)]->getBlockType() == EMPTY)
            {
                emptyFound = true;

                lowestBlockYIndex = y+1;
                bool isNextEmpty = true;

                while(isNextEmpty)
                {
                    if (y+1 < maxRowNum
                            && blocks[index(lowestBlockYIndex + 1,x)]->getBlockType() == EMPTY)
                    {
                        lowestBlockYIndex = lowestBlockYIndex +1 ;
                    }
                    else
                    {
                        isNextEmpty = false;
                    }
                }

                QPointF originalPos = blocks[index(y,x)]->pos();
                QPointF newPos = blocks[index(lowestBlockYIndex, x)]->pos();

                blocks[index(y,x)]->setPos(newPos);
                blocks[index(lowestBlockYIndex, x)]->setPos(originalPos);
                blocks.swap(index(y,x), index(lowestBlockYIndex, x));
            }
        }
    }

    return emptyFound;
}

void SingleGameMode::allowMatches()
{
    int blocksListSize = blocks.size();

    for (int i = 0; i < blocksListSize; i++)
    {
        BlockType blockType = blocks[i]->getBlockType();
        if (blockType == RED || blockType == GREEN || blockType == BLUE
                || blockType == YELLOW || blockType == ORANGE || blockType == PURPLE)
        {
            blocks[i]->setAllowMatch(true);
        }
    }
}

void SingleGameMode::removeMatches()
{
    if (!stacksOfMatchedBlocks.isEmpty())
    {
        if (!hasReachedTop)
        {
            stopMoveTimer();
        }
        else
        {
            gameEndCountdown->pauseCountdown();
        }

        QList<Block*> matchedBlocks = stacksOfMatchedBlocks.pop();
        int incrementValue = 1;   // default score increment

        if (matchedBlocks.first()->getBlockType() == SPECMATCHED)
        {
            incrementValue = 2;
            SoundEffects::getSoundEffect(SPECIALMATCH)->play();
        }

        while (!matchedBlocks.isEmpty())
        {
            Block* matchedBlock = matchedBlocks.takeLast();
            matchedBlock->setBlockType(DEAD);

            SoundEffects::getSoundEffect(REMOVEMATCH)->play();
            delay(100);

            scene()->removeItem(matchedBlock);

            Block* emptyBlock = new Block(EMPTY, matchedBlock->x(), matchedBlock->y(), false, moveTimer);
            scene()->addItem(emptyBlock);

qDebug() << "Block Index " << blocks.indexOf(matchedBlock) << " removed";
            blocks.replace(blocks.indexOf(matchedBlock), emptyBlock);

            delete matchedBlock;

            gameScore->incrementScore(incrementValue);
            delay(200);
        }

        if (!hasReachedTop)
        {
            startMoveTimer();
            realignPlayer();
        }
        else
        {
            gameEndCountdown->resumeCountdown();
        }
    }
}


/**
 * Purpose: Creates a timer that halts the program for the amount of
 * secondsToWait needed in order to create a delay effect.
 *
 * This function was found on the following Stack Overflow question:
 * https://stackoverflow.com/questions/3752742/how-do-i-create-a-pause-wait-function-using-qt
 */
void SingleGameMode::delay( int secondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( secondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void SingleGameMode::checkTop()
{
    if (blocks[0]->pos().y() <= 10)
    {
        if (isTopRowEmpty())
        {
            for (int i = 0; i < 6; i++)
            {
                Block* emptyBlock = blocks.takeFirst();
                scene()->removeItem(emptyBlock);
                delete emptyBlock;
            }
        }
        else if (!hasReachedTop)
        {
            stopMoveTimer();
            scene()->addItem(gameEndCountdown);
            scene()->addItem(losingMsg);
            losingMsg->startAnimation();
            gameEndCountdown->startCountdown();
            SoundEffects::getSoundEffect(LOSING)->play();
            hasReachedTop = true;
        }
    }


    if (hasReachedTop)
    {
        if (blocks[0]->pos().y() > 10)
        {
            startMoveTimer();
            realignPlayer();
            hasReachedTop = false;
            gameEndCountdown->stopCountdown();
            scene()->removeItem(gameEndCountdown);
            scene()->removeItem(losingMsg);
            losingMsg->stopAnimation();
            SoundEffects::getSoundEffect(LOSING)->stop();
        }
        else if (gameEndCountdown->getCounter() < 0)
        {
            gameClock->stopTimer();
            gameState = GAMEOVER;
        }
    }
}

bool SingleGameMode::isTopRowEmpty()
{
    bool result = true;
    for (int i = 0; i < 6 && result; i++)
    {
        result = blocks[i]->getBlockType() == EMPTY ? true : false;
    }
    return result;
}

void SingleGameMode::stopMoveTimer()
{
    moveTimer->stop();
}

void SingleGameMode::startMoveTimer()
{
    moveTimer->start(17);
}

void SingleGameMode::gameUpdate()
{
    switch(gameState)
    {
        case INITGAME:
        {
            windowFocusChk();
            gameState = COUNTDOWN;
            gameStartCountdown->startCountdown();
            break;
        }
        case COUNTDOWN:
        {
            windowFocusChk();
            scene()->update();
            if (gameStartCountdown->getCounter() == 0)
            {
                playerFocusChk();
                initBlocks();
                startMoveTimer();
                gameClock->startTimer();
                gameSpeedMsg->startSpeedTimer();
                gameState = PLAYING;
                SoundEffects::getSoundEffect(GAMESTART)->play();
            }
            break;
        }
        case PLAYING:
        {
            if (newBlockChk())
            {
                allowMatches();
                initBlocks();
            }
            findMatches();
            removeMatches();
            if (emptyBlockHoleHandler()) realignPlayer();
            checkTop();

            scene()->update();
            playerFocusChk();

            //printBlocksInfo();
            break;
        }
        case PAUSE:
        {
            break;
        }
    }
}


void SingleGameMode::playerFocusChk()
{
    if (!player->hasFocus())
    {
        player->setFocus();
    }
}


void SingleGameMode::windowFocusChk()
{
    if (!this->hasFocus())
    {
        this->setFocus(Qt::ActiveWindowFocusReason);
    }
}


void SingleGameMode::realignPlayer()
{
    int shortestManLength = 0;
    QPointF alignedPos;

    foreach(Block* block, blocks)
    {
         QPointF distanceFromPlayer = player->pos() - block->pos();

        if (shortestManLength == 0) shortestManLength = distanceFromPlayer.manhattanLength();

        int manLength = distanceFromPlayer.manhattanLength();

        if (manLength < shortestManLength)
        {
            alignedPos = block->pos();
            shortestManLength = manLength;
        }
    }

    //qDebug() << "Shortest Manhattan Length" << shortestManLength;
    //qDebug() << "Aligned Position" << alignedPos;
    //qDebug() << "Current Player Position" << player->pos();

    if (shortestManLength < 3)
    {
        player->setPos(alignedPos);
    }
}

void SingleGameMode::pauseGame()
{
    if (gameState == PLAYING)
    {
        stopMoveTimer();
        if (hasReachedTop)
        {
            gameEndCountdown->pauseCountdown();
            losingMsg->stopAnimation();
            SoundEffects::getSoundEffect(LOSING)->stop();
        }
    }
    SoundEffects::getSoundEffect(GAMEPAUSE)->play();
}

void SingleGameMode::resumeGame()
{
    if (gameState == PLAYING)
    {
        if (hasReachedTop)
        {
            gameEndCountdown->resumeCountdown();
            losingMsg->startAnimation();
            SoundEffects::getSoundEffect(LOSING)->play();
        }
        else
        {
            startMoveTimer();
        }
    }
    SoundEffects::getSoundEffect(GAMEPAUSE)->play();
}

