#ifndef LARGEWINDOW_H
#define LARGEWINDOW_H

#include "Game.h"

#include <QMainWindow>
#include <QWidget>
#include <QPixmap>
#include <QVector>
#include <vector>
#include <QPushButton>
#include <QSignalMapper>
#include <QMessageBox>

namespace Ui {
class largeWindow;
}

class largeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit largeWindow(QWidget *parent = 0);
    ~largeWindow();

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

    void drawGame();

private:
    Ui::largeWindow *ui;
    unsigned int x;
    unsigned int y;
    Game *game;
    QSignalMapper* cardMapper = nullptr;
    vector <QPushButton*> CardsBoard;
    vector <QPushButton*> CardsDeck;
    vector <QPushButton*> CardsTop;
};

#endif // LARGEWINDOW_H
