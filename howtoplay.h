#ifndef HOWTOPLAY_H
#define HOWTOPLAY_H

#include <QTabWidget>

namespace Ui {
class HowToPlay;
}

class HowToPlay : public QTabWidget
{
    Q_OBJECT

public:
    explicit HowToPlay(QWidget *parent = 0);
    ~HowToPlay();

private:
    Ui::HowToPlay *ui;
};

#endif // HOWTOPLAY_H
