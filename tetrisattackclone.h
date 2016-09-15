#ifndef TETRISATTACKCLONE_H
#define TETRISATTACKCLONE_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QStack>

#include "gameover.h"
#include "highscoresdbmanager.h"
#include "soundeffects.h"


class Player;

namespace Ui {
class TetrisAttackClone;
}

class Game;
class HighScores;
class DifficultySelect;
class HowToPlay;
class About;

class TetrisAttackClone : public QMainWindow
{
    Q_OBJECT
public:
    explicit TetrisAttackClone(QWidget *parent = 0);
    ~TetrisAttackClone();

    void initUi();
    void showEvent(QShowEvent *);
    void initGame(QString difficulty);
public slots:
    void update();
    void on_exitButton_clicked();
    void on_startButton_clicked();
    void on_highScoresButton_clicked();

private slots:
    void on_howToPlayButton_clicked();

    void on_aboutButton_clicked();

private:
    QTimer* updateTimer;
    Game* game;
    Ui::TetrisAttackClone *ui;
    DifficultySelect* selectionScreen;
    GameOver* gameOverScreen;
    HighScores* highScoresScreen;
    HighScoresManager* highScoresManager;
    HowToPlay* howToPlay;
    About* about;
};

#endif // TETRISATTACKCLONE_H
