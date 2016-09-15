#include "difficultyselect.h"
#include "ui_difficultyselect.h"
#include "tetrisattackclone.h"
#include "ui_tetrisattackclone.h"

DifficultySelect::DifficultySelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DifficultySelect)
{
    ui->setupUi(this);
    ui->difficultyTitle->setFont(QFont("Press Start K", 18));
    ui->easyButton->setFont(QFont("Press Start K", 18));
    ui->mediumButton->setFont(QFont("Press Start K", 18));
    ui->hardButton->setFont(QFont("Press Start K", 18));
    setAttribute(Qt::WA_DeleteOnClose);
}

DifficultySelect::~DifficultySelect()
{
    delete ui;
}

void DifficultySelect::on_easyButton_clicked()
{
    ((TetrisAttackClone*)parent())->initGame("EASY");
    close();
}

void DifficultySelect::on_mediumButton_clicked()
{
    ((TetrisAttackClone*)parent())->initGame("MEDIUM");
    close();
}

void DifficultySelect::on_hardButton_clicked()
{
    ((TetrisAttackClone*)parent())->initGame("HARD");
    close();
}
