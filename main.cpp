#include <QApplication>
#include <QDir>
#include <QDebug>

#include "tetrisattackclone.h"
#include "highscoresdbmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TetrisAttackClone w;
    w.show();
    return a.exec();
}
