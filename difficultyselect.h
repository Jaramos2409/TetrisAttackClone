#ifndef DIFFICULTYSELECT_H
#define DIFFICULTYSELECT_H

#include <QWidget>

namespace Ui {
class DifficultySelect;
}

class DifficultySelect : public QWidget
{
    Q_OBJECT

public:
    explicit DifficultySelect(QWidget *parent = 0);
    ~DifficultySelect();

private slots:
    void on_easyButton_clicked();

    void on_mediumButton_clicked();

    void on_hardButton_clicked();

private:
    Ui::DifficultySelect *ui;
};

#endif // DIFFICULTYSELECT_H
