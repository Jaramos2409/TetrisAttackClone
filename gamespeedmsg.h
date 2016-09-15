#ifndef GAMESPEEDMSG_H
#define GAMESPEEDMSG_H

#include <QGraphicsTextItem>

class GameSpeedMsg : public QGraphicsTextItem
{
    Q_OBJECT
    QTimer* speedTimer;
public:
    GameSpeedMsg();
    ~GameSpeedMsg();

    void startSpeedTimer();
    void stopSpeedTimer();

private slots:
    void updateSpeed();
};

#endif // GAMESPEEDTRACKER_H
