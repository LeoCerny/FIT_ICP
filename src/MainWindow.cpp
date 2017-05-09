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
    games.insert(games.end(), game);

    if (games.size() < 2) setWindowSize(1);
    else setWindowSize(2);

    return game;
}

void MainWindow::On_Clicked(int index){

    QMessageBox mess;
    string text;
    //int backupIndex = index;
    unsigned int col = 0;
    while (index >= 100) {
        index -= 100;
        col++;
    }

    //podminka, ktera opravuje index v ramci ulozeni karet bez prazdneho tlacitka navic
    if(index > 0){
        index--;

        text = "Zmackli jste kartu na sloupci " + to_string(col) + " cislo " + to_string(index);
        mess.setText(text.c_str());
        mess.exec();
    }else {
        // zde bude cast kodu, ktera osetruje stlaceni na praznde tlacitko ve sloupci
    }

}

void MainWindow::on_actionUndo_triggered()
{
    setWindowSize(2);
}

//*/
