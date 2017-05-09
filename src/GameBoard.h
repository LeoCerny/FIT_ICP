#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <vector>

#include "ColumnOfButton.h"
#include "Game.h"

class GameBoard
{
public:
    QMainWindow *window;
    QSignalMapper *cardMapper = nullptr;
    GameBoard(QMainWindow *window, unsigned int id, unsigned int width, unsigned int height) {
        this->window = window;
        gameId = id;
        this->height = height;
        this->width = width;

        game = new Game(7);

        //nastaveni velikosti karet
        QSize size(73,98);
        cardSize = size;

        //nastaveni pozadi rubu
        QPixmap pixmap(":/cards/img/Rub.jpg");
        cardBack = pixmap;

        QIcon icon(cardBack);
        ButtonIcon = icon;
    }

    void setCardMapper(QSignalMapper *signal) {
        cardMapper = signal;
    }


    void initBoard();
    void drawBoard();

    unsigned int getX() {
        return (width * (gameId % 2));
    }
    unsigned int getY() {
        if (gameId > 1)
            return height;
        else
            return 0;
    }
private:
    unsigned int gameId;
    unsigned int width;
    unsigned int height;
    Game *game;
    vector <ColumnOfButton *> CardsBoard;
    vector <QPushButton *> CardsDeck;
    vector <ColumnOfButton *> CardsTop;
    QPixmap cardBack;
    QIcon ButtonIcon;
    QSize cardSize;
};

#endif // GAMEBOARD_H
