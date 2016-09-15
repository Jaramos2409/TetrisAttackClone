#include <QGraphicsView>
#include <QScrollBar>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>
#include <QStack>
#include <QDebug>

#include "game.h"
#include "block.h"
#include "player.h"
#include "countdown.h"
#include "gamemessage.h"
#include "soundeffects.h"

SingleGameMode *Game::getGame() const
{
    return game;
}

QGraphicsScene *Game::getScene() const
{
    return scene;
}

Game::Game(QObject* mainWindow, QWidget* parent, QString difficulty)
{
    view = new QGraphicsView(parent);

    scene = new QGraphicsScene(0,0, 800, 600, mainWindow);
    scene->setBackgroundBrush(Qt::black);

    game = new SingleGameMode(difficulty);
    scene->addItem(game);

    game->initGameElements();

    view->setScene(scene);
    view->setSceneRect(0,0, 800, 600);
    view->setFixedSize(800, 600);

    view->horizontalScrollBar()->blockSignals(true);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->verticalScrollBar()->blockSignals(true);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setFocusPolicy(Qt::StrongFocus);
    view->show();

    scene->update();
}

Game::~Game()
{
    scene->clear();
    delete view;
    delete scene;
}

QGraphicsView *Game::getView() const
{
    return view;
}
