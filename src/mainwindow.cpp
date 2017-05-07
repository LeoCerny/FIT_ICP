#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "GameBoard.h"

//globalni promenna


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*GameBoard *gameBoard = new GameBoard(0,0);
    gameBoard->setPossition(0,0);
    gameBoard->initBoard();*/

    QPixmap pixmap(":/cards/img/Rub.jpg");
    QIcon ButtonIcon(pixmap);
    //ui->Deck->setIcon(ButtonIcon);
    //ui->Deck->setIconSize(pixmap.rect().size());

    //mapovac signalu dynamicky generovanych tlacitek
    this->cardMapper = new QSignalMapper(this);
    connect(cardMapper, SIGNAL(mapped(int)), this, SLOT(On_Clicked(int)));


    this->game = new Game(7);
    QSize cardSize(73,98);

    //generovnai karet pro herni sloupce
    for (unsigned int x = 0; x < game->getCoutDeskCols(); x++){
        ColumnOfCart *col = game->getDeskColumn(x);
        for (unsigned int y = 0; y < col->size(); y++){
            QPushButton* card = new QPushButton(this);

            //Nataveni rozmeru tlacitka            
            card->setFixedSize(cardSize);
            card->move(10+x*83,270+y*20);

            //mapovani tlacitka se signalem
            cardMapper->setMapping(card, card);
            connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));

            //ulozeni tlacitka do vectoru
            CardsBoard.push_back(card);

        }
    }
    //generovani karet pro top 4 sloupce
    for (unsigned int x = 0; x < 4; x++){
        ColumnOfCart  *col = game->getResultColumn(x);
        unsigned int size = col->size();
        QPushButton* card = new QPushButton(this);

        //Nataveni rozmeru tlacitka
        card->setFixedSize(cardSize);
        card->move(259+x*83,70);

        //mapovani tlacitka se signalem
        cardMapper->setMapping(card, card);
        connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));

        //ulozeni tlacitka do vectoru
        CardsTop.push_back(card);
        for (unsigned int y = 0; y < size; y++){
            QPushButton* card = new QPushButton(this);

            //Nataveni rozmeru tlacitka
            card->setFixedSize(cardSize);
            card->move(259+x*83,70);

            //mapovani tlacitka se signalem
            cardMapper->setMapping(card, card);
            connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));

            //ulozeni tlacitka do vectoru            
            CardsTop.push_back(card);

        }
    }
    //generovani karet pro balicek
    for (unsigned int y = 0; y < game->getRotateColumn()->size(); y++){
        QPushButton* card = new QPushButton(this);

        //Nataveni rozmeru tlacitka        
        card->setFixedSize(cardSize);
        card->move(10,70);

        //mapovani tlacitka se signalem
        cardMapper->setMapping(card, card);
        connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));

        //ulozeni tlacitka do vectoru
        CardsDeck.push_back(card);
    }
    //this->drawGame();
//*/
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::drawGame() {

    int cardType;
    int cardValue;
    bool cardHidden;

    QPixmap cardBack(":/cards/img/Rub.jpg");
    QIcon ButtonIconBack(cardBack);


    //generace karet pro herni sloupce na desce
    for (unsigned int x = 0; x < game->getCoutDeskCols(); x++){
        ColumnOfCart  *col = game->getDeskColumn(x);
        for (unsigned int y = 0; y < col->size(); y++){

            //zjisteni attributu karty
            cardType = game->getCart(x,y)->getType();
            cardValue = game->getCart(x,y)->getNumber();
            cardHidden = game->getCart(x,y)->isHide();

            //Prirazeni obrazku karty + rub, nastaveni viditelnosti
            if (cardHidden == true){
                CardsBoard[x * col->size() + y]->setIcon(ButtonIconBack);
                CardsBoard[x * col->size() + y]->setIconSize(cardBack.rect().size());
            }

            //vykresleni karty na desku



        }
    }
    //generovani karet pro top 4 sloupce
    /*for (unsigned int x = 1; x < 4 +1; x++){
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

    }*/

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
    //ui->Pile->setIcon(ButtonIcon);
    //ui->Pile->setIconSize(pixmap.rect().size());
    this->drawGame();
}

void MainWindow::on_actionUndo_triggered()
{
    this->setFixedWidth(1200);
}
