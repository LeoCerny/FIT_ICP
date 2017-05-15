#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameBoard.h"

#include <QMainWindow>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    unsigned int defaultHeight = 600;
    unsigned int defaultWidth = 591;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setWindowSize(unsigned int count) {
        if (count > 1) count = 2;
        setFixedSize(defaultWidth * count, defaultHeight * count);
    }

public slots:
    void On_Clicked(int index);
    void On_IconClicked(int index);

private slots:
    void on_actionAddGame_triggered();

private:
    Ui::MainWindow *ui;
    vector <GameBoard *> games;
    GameBoard *createGame();
};

#endif // MAINWINDOW_H
