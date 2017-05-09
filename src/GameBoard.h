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

    unsigned int click_actual = 0;
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

    void rotate() {
        game->getRotateColumn()->rotateOne();
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
    Game *getGame() {
        return game;
    }
    void printGame(Game *game);
    void setFirstClick(unsigned int col, unsigned int row) {
        click_actual = 1;
        click_col = col;
        if (click_col < 7) {
            click_count = game->getDeskColumn(click_col)->size() - row + 1;
        } else {
            click_count = 1;
        }
    }

    bool click(unsigned int col, unsigned int row);
    void removeButtons(unsigned int col, unsigned int count);
    void createButtons(unsigned int col, unsigned int count);

private:
    unsigned int gameId;
    unsigned int width;
    unsigned int height;

    unsigned int click_col;
    unsigned int click_col2;
    unsigned int click_count;
    Game *game;
    vector <ColumnOfButton *> CardsBoard;
    vector <QPushButton *> CardsDeck;
    vector <QPushButton *> CardsTop;
    QPixmap cardBack;
    QIcon ButtonIcon;
    QSize cardSize;
    QPushButton *cardLeft;
    QPushButton *cardRight;
};

#endif // GAMEBOARD_H
