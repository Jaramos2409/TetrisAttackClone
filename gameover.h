#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>

namespace Ui {
class GameOver;
}

class GameOver : public QWidget
{
    Q_OBJECT
private:
    Ui::GameOver *ui;
    QString difficulty;

public:
    explicit GameOver(QWidget *parent = 0, QString difficulty = "HARD");
    ~GameOver();

private slots:
    void on_retryButton_clicked();

    void on_highscoresButton_clicked();

    void on_mainmenuButton_clicked();

    void on_exitButton_clicked();
};

#endif // GAMEOVER_H
