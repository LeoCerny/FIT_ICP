#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Game.h"

#include <QMainWindow>
#include <QWidget>
#include <QPixmap>
#include <QVector>
#include <vector>
#include <QPushButton>
#include <QSignalMapper>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    vector <QPushButton*> CardsBoard;
    vector <QPushButton*> CardsDeck;
    vector <QPushButton*> CardsTop;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawGame();

private slots:
    void on_Deck_clicked();

    void on_actionUndo_triggered();

private:
    Ui::MainWindow *ui;
    QSignalMapper* cardMapper = nullptr;
    Game *game;

};



#endif // MAINWINDOW_H
