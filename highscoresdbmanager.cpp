#include <QDebug>
#include <QSqlQuery>
#include <QtAlgorithms>

#include "highscoresdbmanager.h"

HighScoresManager::HighScoresManager(QString path)
{
    highscores_db = QSqlDatabase::addDatabase("QSQLITE");

    qDebug() << highscores_db.isValid();

    highscores_db.setDatabaseName(path);


    if (!highscores_db.open())
   {
      qDebug() << "Error: connection with database fail";
   }
   else
   {
      qDebug() << "Database: connection ok";
    }
}

HighScoresManager::~HighScoresManager()
{
    if (highscores_db.isOpen())
    {
        highscores_db.close();
    }
}

bool HighScoresManager::addHighScore(int score, QString difficulty, QString time, double speed)
{
    bool result = false;
    QSqlQuery query;

    query.prepare("INSERT INTO HighScores (score, difficulty, time, speed) "
                   "VALUES (:score, :difficulty, :time, :speed)");
    query.bindValue(":score", score);
    query.bindValue(":difficulty", difficulty);
    query.bindValue(":time", time);
    query.bindValue(":speed", speed);

    if (query.exec())
    {
        result = true;
    }

    return result;
}

bool HighScoresManager::loadHighScoresModel(QList<QString>* listOfString)
{
    bool result = false;
    QSqlQuery query;

    QString preparedStatement("SELECT score, difficulty, time, speed "
             "FROM HighScores "
             "ORDER BY "
             "(CASE WHEN difficulty LIKE ? THEN 1 "
             "WHEN difficulty LIKE ? THEN 2 "
             "WHEN difficulty LIKE ? THEN 3 "
             "ELSE 5 "
             "END), "
             "score DESC, "
             "time ASC, "
             "speed DESC "
             "LIMIT 10");

    query.prepare(preparedStatement);
    query.bindValue(0,"HARD");
    query.bindValue(1, "MEDIUM");
    query.bindValue(2, "EASY");

    if (query.exec())
    {
        result = true;
    }

    while(query.next())
    {
        QString score = query.value(0).toString();
        QString difficulty = query.value(1).toString();
        QString time = query.value(2).toString();
        QString speed = query.value(3).toString();
        listOfString->push_back(score + " " + difficulty + " " + time + " " + speed);
    }

    return result;
}

