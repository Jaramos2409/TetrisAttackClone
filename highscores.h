#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class HighScores;
}

class HighScores : public QWidget
{
    Q_OBJECT
public:
    explicit HighScores(QWidget *parent = 0, QList<QString>* listOfScores = new QList<QString>());
    ~HighScores();

private slots:
    void on_mainmenuButton_clicked();

private:
    Ui::HighScores *ui;
    QList<QLabel*> dataLabels;
};

#endif // HIGHSCORES_H
