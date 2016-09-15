#ifndef GAMECLOCK_H
#define GAMECLOCK_H

#include <QGraphicsTextItem>
#include <QTime>

class GameClock : public QGraphicsTextItem
{
    Q_OBJECT
    QTime currentTime;
    QTimer* updateTimer;
    QString timeAsText;
    QTime pausedTime;
public:
    GameClock();
    ~GameClock();

    void startTimer();
    void stopTimer();
    void pauseTimer();
    void resumeTimer();
    QString getCurrentTime();

public slots:
    void showTime();
};

#endif // GAMECLOCK_H
