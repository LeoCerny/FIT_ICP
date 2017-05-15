#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QMessageBox>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <vector>
#include <QFileDialog>

#include "ColumnOfButton.h"
#include "Game.h"

class GameBoard
{
public:
    QMainWindow *window;
    QSignalMapper *cardMapper = nullptr;
    QSignalMapper *headMapper = nullptr;
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

        //nastaveni velikosti ikon
        QSize iSize(32, 32);
        iconSize = iSize;

        //nastaveni pozadi rubu
        QPixmap pixmap(":/cards/img/Rub.jpg");
        cardBack = pixmap;

        QIcon icon(cardBack);
        ButtonIcon = icon;

        //nastaveni pozadi pro icony
        headIconsPath.push_back(":/menu/img/new_game.png");
        headIconsPath.push_back(":/menu/img/Undo.png");
        headIconsPath.push_back(":/menu/img/Save.png");
        headIconsPath.push_back(":/menu/img/Load.png");

    }

    void setCardMapper(QSignalMapper *signal) {
        cardMapper = signal;
    }

    void setHeadMapper(QSignalMapper *signal) {
        headMapper = signal;
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
            click_count = game->getDeskColumn(col)->size() - row + 1;
        } else {
            click_count = 1;
        }
    }

    bool click(unsigned int col, unsigned int row);
    bool isFinished() {
        return !game->activeGame;
    }

    void removeButtons(unsigned int col, unsigned int count);
    void createButtons(unsigned int col);

    void destroy() {
        for (unsigned int var = 0; var < game->getCoutDeskCols(); var++) {
            removeButtons(var, 30);
        }
        delete game;
    }
    void createNewGame() {
        destroy();
        game = new Game(7);
        for (unsigned int var = 0; var < game->getCoutDeskCols(); var++) {
            createButtons(var);
        }
        drawBoard();
    }
    void save() {
        QFileDialog dialog(0, "Uloit hru", QDir::currentPath());
        dialog.selectNameFilter("Text Files (*.txt)");
        if (game->save(dialog.getSaveFileName().toStdString())) {
            QMessageBox msgBox;
            msgBox.setText("Hra je ulozena");
            msgBox.exec();
        } else {
            QMessageBox msgBox;
            msgBox.setText("Hru se nepodarilo ulozit");
            msgBox.exec();
        }
    }

    void load() {
        QFileDialog dialog(0, "Nahrat hru", QDir::currentPath() );
        dialog.selectNameFilter("Text Files (*.txt)");
        Game *game = new Game(7, false);
        if (game->load(dialog.getOpenFileName().toStdString())) {
            destroy();
            this->game = game;
            printGame(game);
            for (unsigned int var = 0; var < game->getCoutDeskCols(); var++) {
                createButtons(var);
            }
            drawBoard();
            QMessageBox msgBox;
            msgBox.setText("Hra je nahrana");
            msgBox.exec();

        } else {
            QMessageBox msgBox;
            msgBox.setText("Hru se nepodarilo nahrat");
            msgBox.exec();
        }
    }


private:
    unsigned int gameId;
    unsigned int width;
    unsigned int height;

    unsigned int marginDeskTop = 190;

    unsigned int click_col;
    unsigned int click_col2;
    unsigned int click_count;
    Game *game;
    vector <ColumnOfButton *> CardsBoard;
    vector <QPushButton *> CardsDeck;
    vector <QPushButton *> CardsTop;
    vector <QPushButton *> headerPanel;
    QPixmap cardBack;
    QIcon ButtonIcon;
    vector <string> headIconsPath;
    QSize cardSize;
    QSize iconSize;
    QPushButton *cardLeft;
    QPushButton *cardRight;
};

#endif // GAMEBOARD_H
