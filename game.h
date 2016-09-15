#ifndef GAMESINGLEMODE_H
#define GAMESINGLEMODE_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>

class SingleGameMode;

class Game
{
    QGraphicsView* view;
    QGraphicsScene* scene;
    SingleGameMode* game;
public:
    Game(QObject *mainWindow, QWidget *parent = NULL, QString difficulty = "EASY");
    ~Game();

    QGraphicsView *getView() const;
    SingleGameMode *getGame() const;
    QGraphicsScene *getScene() const;
};

#endif // GAMESINGLEMODE_H
