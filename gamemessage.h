#ifndef GAMEMESSAGE_H
#define GAMEMESSAGE_H

#include <QGraphicsTextItem>
#include <QString>

class GameMessage : public QGraphicsTextItem
{
    Q_OBJECT
    QTimer* animationTimer;
    double rainbowCounter;
public:
    GameMessage(QString msg = "Game Over", int fontSize = 48);
    ~GameMessage();

    void startAnimation();
    void stopAnimation();

public slots:
    void animate();
};

#endif // GAMEOVER_H
