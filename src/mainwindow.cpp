#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pixmap("C:/Users/Ondra/Documents/Skola/ICP/Projekt/img/Rub.png");
    QIcon ButtonIcon(pixmap);
    ui->Deck->setIcon(ButtonIcon);
    ui->Deck->setIconSize(pixmap.rect().size());

    //mapovac signalu dynamicky generovanych tlacitek
    cardMapperr = new QSignalMapper(this);
    connect(cardMapper, SIGNAL(mapped(int)), this, SLOT(On_Clicked(int)));


    Game *game = new Game(7);
    QSize cardSize(73,98);
    //generovnai karet pro herni sloupce
    for (unsigned int x = 1; x < game->getCoutDeskCols() + 1; x++){
        ColumnOfCart  *col = game->getDeskColumn(x);
        for (unsigned int y = 1; y < col->size() +1; y++){
            QPushButton* card = new QPushButton(this);

            //Nataveni rozmeru tlacitka            
            card.setFixedSize(cardSize);

            //mapovani tlacitka se signalem
            cardMapper->setMapping(card, card);
            connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));

            //ulozeni tlacitka do vectoru
            CardsBoard.push_back(card);

        }
    }
    //generovani karet pro top 4 sloupce
    for (unsigned int x = 1; x < 4 +1; x++){
        for (unsigned int y = 1; y < velikostsloupce +1; y++){
            QPushButton* card = new QPushButton(this);

            //Nataveni rozmeru tlacitka
            card.setFixedSize(cardSize);

            //mapovani tlacitka se signalem
            cardMapper->setMapping(card, card);
            connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));

            //ulozeni tlacitka do vectoru
            CardsTop.push_back(card);

        }
    }
    //generovani karet pro balicek
    for (unsigned int y = 1; y < deck +1; y++){
        QPushButton* card = new QPushButton(this);

        //Nataveni rozmeru tlacitka        
        card.setFixedSize(cardSize);

        //mapovani tlacitka se signalem
        cardMapper->setMapping(card, card);
        connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));

        //ulozeni tlacitka do vectoru
        CardsDeck.push_back(card);

    }
    //generovani karet pro odkladaci balicek
    for (unsigned int y = 1; y < pile +1; y++){
        QPushButton* card = new QPushButton(this);


        //Nataveni rozmeru tlacitka

        card.setFixedSize(cardSize);

        //mapovani tlacitka se signalem
        cardMapper->setMapping(card, card);
        connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));

        //ulozeni tlacitka do vectoru
        CardsPile.push_back(card);

    }


}

MainWindow::~MainWindow()
{
    delete ui;

}

void drawGame() {


    for (unsigned int x = 1; x < game->getCoutDeskCols() + 1; x++){
        ColumnOfCart  *col = game->getDeskColumn(x);
        for (unsigned int y = 1; y < col->size() +1; y++){

            //Prirazeni obrazku karty + rub, nastaveni viditelnosti


            //vykresleni karty na desku



        }
    }
    //generovani karet pro top 4 sloupce
    for (unsigned int x = 1; x < 4 +1; x++){
        for (unsigned int y = 1; y < velikostsloupce +1; y++){


            //Prirazeni obrazku karty + rub, nastaveni viditelnosti


            //vykresleni karty na desku

        }
    }
    //generovani karet pro balicek
    for (unsigned int y = 1; y < deck +1; y++){


        //Prirazeni obrazku karty + rub, nastaveni viditelnosti


        //vykresleni karty na desku

    }
    //generovani karet pro odkladaci balicek
    for (unsigned int y = 1; y < pile +1; y++){



        //Prirazeni obrazku karty + rub, nastaveni viditelnosti


        //vykresleni karty na desku

    }

}

/*void BoardGUI::On_Clicked(int index) {

    //computer X and Y coordinates from index
    unsigned int boardWidth = game->getGameBoard().getWidth();
    unsigned int coordX = ((index % boardWidth) + 1);
    unsigned int coordY = (((index - index % boardWidth) / boardWidth) + 1);

    //put disk to selected coordinatess
    game->currentPlayerPutDisk(coordX, coordY);
}*/

int getX(const int x) {

    return x * 80;
}


int getY(const int y) {

    return y * 20;
}

void MainWindow::on_Deck_clicked()
{
    QPixmap pixmap("C:/Users/Ondra/Documents/Skola/ICP/Projekt/img/Hearts/HA.jpg");
    QIcon ButtonIcon(pixmap);
    ui->Pile->setIcon(ButtonIcon);
    ui->Pile->setIconSize(pixmap.rect().size());
}
