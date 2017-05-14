#include <QMessageBox>

#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createGame()->drawBoard();

}

MainWindow::~MainWindow()
{
    delete ui;
}

GameBoard *MainWindow::createGame() {
    unsigned int size = games.size();
    GameBoard *game = new GameBoard(this,  size, defaultWidth, defaultHeight);
    game->setCardMapper(new QSignalMapper(this));
    game->initBoard();
    games.insert(games.end(), game);

    if (games.size() < 2) setWindowSize(1);
    else setWindowSize(2);

    return game;
}

void MainWindow::On_Clicked(int index) {

    unsigned int col = 0;
    unsigned int gameId = 0;
    while (index >= 10000) {
        index -= 10000;
        gameId++;
    }
    while (index >= 100) {
        index -= 100;
        col++;
    }

    GameBoard *board = games.at(gameId);
    if (col != 11) {

        board->click(col, index);
    } else {
        board->getGame()->getRotateColumn()->rotateOne();
    }
    board->drawBoard();

}

void MainWindow::on_actionUndo_triggered()
{
    setWindowSize(2);
}
