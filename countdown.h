#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QGraphicsTextItem>
#include <QObject>

#include "soundeffects.h"

class Countdown : public QGraphicsTextItem
{
    Q_OBJECT
    int counter;
    int initialCount;
    QTimer* countdownUpdateTimer;

public:
    Countdown(int = 3);
    ~Countdown();


    int getCounter() const;
    void setCounter(int value);
    void startCountdown();
    void stopCountdown();
    void pauseCountdown();
    void resumeCountdown();
public slots:
    void update();
};

#endif // COUNTDOWN_H
