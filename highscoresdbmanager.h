#ifndef HIGHSCORESDBMANAGER_H
#define HIGHSCORESDBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQueryModel>

class HighScoresManager
{
    QSqlDatabase highscores_db;
public:
    HighScoresManager(QString path);
    ~HighScoresManager();

    bool addHighScore(int score, QString difficulty, QString time, double speed);
    bool loadHighScoresModel(QList<QString>* listofStrings);
};

#endif // HIGHSCORESMANAGER_H
