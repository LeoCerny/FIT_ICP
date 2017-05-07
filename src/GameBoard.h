#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Game.h"

#include <QMainWindow>
#include <QWidget>
#include <QPixmap>
#include <QVector>
#include <vector>
#include <QPushButton>
#include <QSignalMapper>

class GameBoard
{
public:
    vector <QPushButton*> CardsBoard;
    vector <QPushButton*> CardsDeck;
    vector <QPushButton*> CardsTop;
    GameBoard(QWidget *parent):
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
        game = new Game(7);
    }

    void setPossition(unsigned int x, unsigned int y) {
        this->x = x;
        this->y = y;
    }

    unsigned int getGameX() {
        return x;
    }
    unsigned int getGameY() {
        return y;
    }

    int getX(const int x) {

        return x * 80;
    }


    int getY(const int y) {

        return y * 20;
    }
    void drawGame();
    void initBoard(QWidget *parent);
private:
    unsigned int x;
    unsigned int y;
    Game *game;
    Ui::MainWindow *ui;
    QSignalMapper* cardMapper = nullptr;
};

#endif // GAMEBOARD_H
