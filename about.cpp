#include <QFont>

#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setFont(QFont("Press Start K", 20));
}

About::~About()
{
    delete ui;
}
