#include <QFontDatabase>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>

#include "tetrisattackclone.h"
#include "ui_tetrisattackclone.h"
#include "gameover.h"
#include "gamescore.h"
#include "block.h"
#include "game.h"
#include "highscores.h"
#include "difficultyselect.h"
#include "howtoplay.h"
#include "about.h"

TetrisAttackClone::TetrisAttackClone(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TetrisAttackClone)
{
    QFontDatabase::addApplicationFont(":/fonts/prstartk.ttf");
    Block::Initialize();
    SoundEffects::Initialize();

    initUi();
    updateTimer = new QTimer(this);
    game = NULL;
    selectionScreen = NULL;
    gameOverScreen = NULL;
    highScoresScreen = NULL;
    highScoresManager = new HighScoresManager(qApp->applicationDirPath()
                    + "/highscores/highscores.db");
}

TetrisAttackClone::~TetrisAttackClone()
{
    delete ui;
}

//qApp portion of this code taken from the following forum
//post: https://forum.qt.io/topic/27072/semi-solved-update-loop-in-qt-qtimer-no-longer-working/8
void TetrisAttackClone::update()
{
    if (game->getGame()->getGameState() == GAMEOVER)
    {
        SoundEffects::stopPlayingAllSounds();
        SoundEffects::getSoundEffect(GAMEEND)->play();

        QString difficulty = game->getGame()->getDifficulty();
        qDebug () << highScoresManager->addHighScore(game->getGame()->getGameScore()->getScore()
                                        , difficulty
                                        , game->getGame()->getGameClock()->getCurrentTime()
                                        , game->getGame()->getGameSpeed());
        delete game->getGame();
        game = NULL;

        updateTimer->stop();
        disconnect(updateTimer,SIGNAL(timeout()),this,SLOT(update())); // creates update loop

        gameOverScreen = new GameOver(this, difficulty);
        setCentralWidget(gameOverScreen);
    }
    else
    {
        game->getGame()->gameUpdate();
        qApp->processEvents(QEventLoop::AllEvents);
    }
}

void TetrisAttackClone::on_exitButton_clicked()
{
    exit(0);
}

void TetrisAttackClone::on_startButton_clicked()
{
    selectionScreen = new DifficultySelect(this);
    selectionScreen->setFocus();
    setCentralWidget(selectionScreen);
    selectionScreen->setFocus();
    selectionScreen->activateWindow();
}

void TetrisAttackClone::initUi()
{
    ui->setupUi(this);
    ui->Title->setFont(QFont("Press Start K", 20));
    ui->startButton->setFont(QFont("Press Start K", 20));
    ui->highScoresButton->setFont(QFont("Press Start K", 20));
    ui->exitButton->setFont(QFont("Press Start K", 20));
    ui->howToPlayButton->setFont(QFont("Press Start K", 20));
    ui->aboutButton->setFont(QFont("Press Start K", 20));
}

void TetrisAttackClone::on_highScoresButton_clicked()
{
    QList<QString> highScoreList;
    highScoresManager->loadHighScoresModel(&highScoreList);

    highScoresScreen = new HighScores(this, &highScoreList);
    highScoresScreen->setFocus();
    setCentralWidget(highScoresScreen);
    highScoresScreen->setFocus();
    highScoresScreen->activateWindow();
}

void TetrisAttackClone::showEvent(QShowEvent * event)
{
    QWidget::showEvent(event);
    if (game != NULL)
    {
       game->getView()->activateWindow();
       game->getView()->setFocus();
    }
}

void TetrisAttackClone::initGame(QString difficulty)
{
    game = new Game(this, centralWidget(), difficulty);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(update())); // starts update loop
    updateTimer->start(17);

    centralWidget()->clearFocus();
    centralWidget()->close();

    game->getScene()->setFocus();
    game->getView()->setFocus();

    setCentralWidget(game->getView());

    game->getScene()->setFocus();
    game->getView()->setFocus();
}

void TetrisAttackClone::on_howToPlayButton_clicked()
{
    howToPlay = new HowToPlay();
    howToPlay->show();
}

void TetrisAttackClone::on_aboutButton_clicked()
{
    about = new About();
    about->show();
}
