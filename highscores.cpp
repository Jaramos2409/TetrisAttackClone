#include <QStandardItemModel>
#include <QFont>
#include <QStringList>

#include "highscores.h"
#include "ui_highscores.h"
#include "tetrisattackclone.h"
#include "ui_tetrisattackclone.h"

HighScores::HighScores(QWidget *parent, QList<QString>* listOfScores) :
    QWidget(parent),
    ui(new Ui::HighScores)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    ui->Title->setFont(QFont("Press Start K", 18));
    ui->mainmenuButton->setFont(QFont("Press Start K", 18));
    ui->scoreHeader->setFont(QFont("Press Start K", 12));
    ui->difficultyHeader->setFont(QFont("Press Start K", 12));
    ui->timeHeader->setFont(QFont("Press Start K", 12));
    ui->speedHeader->setFont(QFont("Press Start K", 12));

    int posX = 150;
    int posY = 300;

    while(!listOfScores->isEmpty())
    {
        QStringList scoreRecord = listOfScores->takeFirst().split(" ");

        QLabel* score = new QLabel(this);
        score->setText(scoreRecord[0]);
        score->setFont(QFont("Press Start K", 12));
        score->setGeometry(posX, posY, 100, 25);
        score->setStyleSheet("QLabel {color: rgb(255, 255, 255, 245); background-color: rgb(0,0,0,245);}");
        score->setAlignment(Qt::AlignHCenter);
        score->show();
        dataLabels.push_back(score);

        posX += 100;

        QLabel* difficulty = new QLabel(this);
        difficulty->setText(scoreRecord[1]);
        difficulty->setFont(QFont("Press Start K", 12));
        difficulty->setGeometry(posX, posY, 175, 25);
        difficulty->setStyleSheet("QLabel {color: rgb(255, 255, 255, 245); background-color: rgb(0,0,0,245);}");
        difficulty->setAlignment(Qt::AlignHCenter);
        difficulty->show();
        dataLabels.push_back(difficulty);

        posX += 175;

        QLabel* time = new QLabel(this);
        time->setText(scoreRecord[2]);
        time->setFont(QFont("Press Start K", 12));
        time->setGeometry(posX, posY, 100, 25);
        time->setStyleSheet("QLabel {color: rgb(255, 255, 255, 245); background-color: rgb(0,0,0,245);}");
        time->setAlignment(Qt::AlignHCenter);
        time->show();
        dataLabels.push_back(time);

        posX += 100;

        QLabel* speed = new QLabel(this);
        speed->setText(scoreRecord[3]);
        speed->setFont(QFont("Press Start K", 12));
        speed->setGeometry(posX, posY, 125, 25);
        speed->setStyleSheet("QLabel {color: rgb(255, 255, 255); background-color: rgb(0,0,0,245);}");
        speed->setAlignment(Qt::AlignHCenter);
        speed->show();
        dataLabels.push_back(speed);

        posX = 150;
        posY += 25;
    }
}

HighScores::~HighScores()
{
    delete ui;
}

void HighScores::on_mainmenuButton_clicked()
{
    ((TetrisAttackClone*)parent())->initUi();
    close();
}
