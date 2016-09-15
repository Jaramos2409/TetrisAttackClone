#include "gameover.h"
#include "ui_gameover.h"
#include "tetrisattackclone.h"
#include "ui_tetrisattackclone.h"

GameOver::GameOver(QWidget *parent, QString difficulty) :
    QWidget(parent),difficulty(difficulty), ui(new Ui::GameOver)
{
    ui->setupUi(this);
    ui->Title->setFont(QFont("Press Start K", 18));
    ui->retryButton->setFont(QFont("Press Start K", 18));
    ui->highscoresButton->setFont(QFont("Press Start K", 18));
    ui->mainmenuButton->setFont(QFont("Press Start K", 18));
    ui->exitButton->setFont(QFont("Press Start K", 18));
    setAttribute(Qt::WA_DeleteOnClose);
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::on_retryButton_clicked()
{
    ((TetrisAttackClone*)parent())->initGame(difficulty);
    close();
}

void GameOver::on_highscoresButton_clicked()
{
     ((TetrisAttackClone*)parent())->on_highScoresButton_clicked();
    close();
}

void GameOver::on_mainmenuButton_clicked()
{
    ((TetrisAttackClone*)parent())->initUi();
    close();
}

void GameOver::on_exitButton_clicked()
{
    close();
    exit(0);
}
