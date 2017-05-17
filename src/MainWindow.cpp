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
    game->setHeadMapper(new QSignalMapper(this));
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
    if (board->isFinished()) {
        QMessageBox msgBox;
        msgBox.setText("Hra je jiz dohrana");
        msgBox.exec();
    } else if (col != 11) {
        board->click(col, index);
        if (board->isFinished()) {
            QMessageBox msgBox;
            msgBox.setText("KONEC HRY");
            msgBox.exec();
        }
        board->drawBoard();
    } else {
        board->rotate();
        board->drawBoard();
    }
}

void MainWindow::On_IconClicked(int index)
{
    unsigned int gameId = 0;

    while (index >= 100) {
        index -= 100;
        gameId++;
    }

    GameBoard *game = games.at(gameId);
    cout << endl << "icon " ;
    switch (index) {
    case 0://new
        game->createNewGame();
        break;
    case 1://undo
        game->undo();
        break;
    case 2://save
        game->save();
        break;
    case 3://load
        game->load();
        break;
    default:
        cout << "unknown icon" << endl;
        break;
    }
    cout << "OK" << endl;
}

void MainWindow::on_actionAddGame_triggered()
{
    createGame()->drawBoard();
}
