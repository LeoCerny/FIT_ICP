#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Deck_clicked();

private:
    Ui::MainWindow *ui;
    QSignalMapper* cardMapper = nullptr;

};

std::vector <QPushButton> CardsBoard;
std::vector <QPushButton> CardsDeck;
std::vector <QPushButton> CardsPile;
std::vector <QPushButton> CardsTop;

#endif // MAINWINDOW_H
