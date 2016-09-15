#include <QGraphicsVideoItem>

#include "howtoplay.h"
#include "ui_howtoplay.h"

HowToPlay::HowToPlay(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::HowToPlay)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

HowToPlay::~HowToPlay()
{
    delete ui;
}
