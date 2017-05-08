#include "largewindow.h"
#include "ui_largewindow.h"

largeWindow::largeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::largeWindow)
{
    ui->setupUi(this);
    game = new Game(7);

    QPixmap pixmap(":/cards/img/Rub.jpg");
    QIcon ButtonIcon(pixmap);
    //ui->Deck->setIcon(ButtonIcon);
    //ui->Deck->setIconSize(pixmap.rect().size());

    //mapovac signalu dynamicky generovanych tlacitek
    this->cardMapper = new QSignalMapper(this);
    connect(cardMapper, SIGNAL(mapped(int)), this, SLOT(On_Clicked(int)));

    QSize cardSize(73,98);

    //generovnai karet pro herni sloupce
    for (unsigned int x = 0; x < game->getCoutDeskCols(); x++){
        ColumnOfCart *col = game->getDeskColumn(x);
        for (unsigned int y = 0; y < col->size(); y++){
            QPushButton* card = new QPushButton(this);

            //Nataveni rozmeru tlacitka
            card->setFixedSize(cardSize);
            card->move(getGameX()+10+x*83,getGameY()+270+y*20);

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
        card->move(getGameX()+200+x*83,getGameY()+70);

        //mapovani tlacitka se signalem
        cardMapper->setMapping(card, card);
        connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));

        //ulozeni tlacitka do vectoru
        CardsTop.push_back(card);
        for (unsigned int y = 0; y < size; y++){
            QPushButton* card = new QPushButton(this);

            //Nataveni rozmeru tlacitka
            card->setFixedSize(cardSize);
            card->move(getGameX()+200+x*83,getGameY()+70);

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
        card->move(getGameX() + 10, getGameY() + 70);

        //mapovani tlacitka se signalem
        cardMapper->setMapping(card, card);
        connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));

        //ulozeni tlacitka do vectoru
        CardsDeck.push_back(card);
    }
    //this->drawGame();
}

largeWindow::~largeWindow()
{
    delete ui;
}

void largeWindow::drawGame() {

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
}
