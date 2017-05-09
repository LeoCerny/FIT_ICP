#include <QMessageBox>

#include "GameBoard.h"

void GameBoard::initBoard()
{
    //mapovac signalu dynamicky generovanych tlacitek
    window->connect(cardMapper, SIGNAL(mapped(int)), window, SLOT(On_Clicked(int)));

    int cardCounter = 0;
    int cardMultiplier = 100;

    //generovnai karet pro herni sloupce
    for (unsigned int x = 0; x < game->getCoutDeskCols(); x++) {
        cardCounter = cardMultiplier*x;
        ColumnOfButton *buttons = new ColumnOfButton;
        ColumnOfCart *col = game->getDeskColumn(x);

        //Nataveni rozmeru tlacitka pro zacatek sloupce
        QPushButton* card = new QPushButton(window);
        card->setFixedSize(cardSize);
        card->move(getX()+10+x*83,getY()+270);
        card->setFlat(true);

        //mapovani tlacitka se signalem
        cardMapper->setMapping(card, cardCounter);
        window->connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));
        cardCounter++;

        //ulozeni tlacitka do vectoru
        buttons->push(card);
        for (unsigned int y = 1; y < col->size()+1; y++){
            QPushButton* card = new QPushButton(window);

            //Nataveni rozmeru tlacitka
            card->setFixedSize(cardSize);
            card->move(getX()+10+x*83,270+(y-1)*20+getY());

            //mapovani tlacitka se signalem
            cardMapper->setMapping(card, cardCounter);
            window->connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));
            cardCounter++;

            //ulozeni tlacitka do vectoru
            buttons->push(card);
        }
        CardsBoard.insert(CardsBoard.end(), buttons);
    }

    //generovani karet pro top 4 sloupce
    for (unsigned int x = 0; x < 4; x++){
        cardCounter = cardMultiplier*(x+7);
        ColumnOfButton *buttons = new ColumnOfButton;
        ColumnOfCart  *col = game->getResultColumn(x);

        //Nataveni rozmeru tlacitka
        QPushButton* card = new QPushButton(window);
        card->setFixedSize(cardSize);
        card->move(getX()+259+x*83,70+getY());

        //mapovani tlacitka se signalem
        cardMapper->setMapping(card, cardCounter);
        window->connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));
        cardCounter++;

        //ulozeni tlacitka do vectoru
        buttons->push(card);
        for (unsigned int y = 0; y < col->size(); y++){
            QPushButton* card = new QPushButton(window);

            //Nataveni rozmeru tlacitka
            card->setFixedSize(cardSize);
            card->move(getX()+259+x*83,70+getY());

            //mapovani tlacitka se signalem
            cardMapper->setMapping(card, cardCounter);
            window->connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));
            cardCounter++;

            //ulozeni tlacitka do vectoru
            buttons->push(card);

        }
        CardsTop.insert(CardsTop.end(), buttons);
    }

    //generovani karet pro balicek
    cardCounter = cardMultiplier*11;
    for (unsigned int y = 0; y < game->getRotateColumn()->size() +1; y++) {

        QPushButton* card = new QPushButton(window);

        //Nataveni rozmeru tlacitka
        card->setFixedSize(cardSize);
        card->move(getX()+10,70+getY());

        //mapovani tlacitka se signalem
        cardMapper->setMapping(card, cardCounter);
        window->connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));
        cardCounter++;

        //ulozeni tlacitka do vectoru
        CardsDeck.push_back(card);
    }
    for (unsigned int y = 0; y < game->getRotateColumn()->size(true) +1; y++) {

        QPushButton* card = new QPushButton(window);

        //Nataveni rozmeru tlacitka
        card->setFixedSize(cardSize);
        card->move(getX()+90,70+getY());

        //mapovani tlacitka se signalem
        cardMapper->setMapping(card, cardCounter);
        window->connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));
        cardCounter++;

        //ulozeni tlacitka do vectoru
        CardsDeck.push_back(card);
    }
}

void GameBoard::drawBoard()
{
    initBoard();

    int cardType;
    int cardValue;
    bool cardHidden;

    string karta;

    //generace karet pro herni sloupce na desce
    for (unsigned int x = 0; x < game->getCoutDeskCols(); x++) {
        ColumnOfCart  *col = game->getDeskColumn(x);
        for (unsigned int y = 1; y < col->size()+1; y++) {

            //zjisteni attributu karty
            cardType = game->getCart(x,y-1)->getType();
            cardValue = game->getCart(x,y-1)->getNumber();
            cardHidden = game->getCart(x,y-1)->isHide();

            //Prirazeni obrazku karty + rub, nastaveni viditelnosti
            if (cardHidden == true){
                CardsBoard.at(x)->getByIndex(y)->setIcon(ButtonIcon);
                CardsBoard.at(x)->getByIndex(y)->setIconSize(cardBack.rect().size());
            }
            else {
                switch (cardType) {
                    case Cart::HEART:
                        karta = ":/cards/img/Hearts/"+std::to_string(cardValue) +".jpg";
                        break;
                    case Cart::SPADES:
                        karta = ":/cards/img/Spades/"+std::to_string(cardValue) +".jpg";
                        break;
                    case Cart::SQUARE:
                        karta = ":/cards/img/Diamonds/"+std::to_string(cardValue) +".jpg";
                        break;
                    case Cart::LETTER:
                        karta = ":/cards/img/Crosses/"+std::to_string(cardValue) +".jpg";
                        break;
                }
                QPixmap card(karta.c_str());
                QIcon BIC(card);
                CardsBoard.at(x)->getByIndex(y)->setIcon(BIC);
                CardsBoard.at(x)->getByIndex(y)->setIconSize(card.rect().size());
            }
        }
    }

    //generovani karet pro top 4 sloupce
    for (unsigned int x = 0; x < 4; x++){
        for (unsigned int y = 1; y < game->getResultColumn(x)->size() +1; y++){

            //zjisteni attributu karty (y-1) protoze prvni kartou je prazdne tlacitko
            cardType = game->getResultColumn(x)->getCart(y-1)->getType();
            cardValue = game->getResultColumn(x)->getCart(y-1)->getNumber();
            cardHidden = game->getResultColumn(x)->getCart(y-1)->isHide();
            //Prirazeni obrazku karty + rub, nastaveni viditelnosti
            if (cardHidden == true){
                CardsTop.at(x)->getByIndex(y)->setIcon(ButtonIcon);
                CardsTop.at(x)->getByIndex(y)->setIconSize(cardBack.rect().size());
            }
            else {
                switch (cardType) {
                    case Cart::HEART:
                        karta = ":/cards/img/Hearts/"+std::to_string(cardValue) +".jpg";
                        break;
                    case Cart::SPADES:
                        karta = ":/cards/img/Spades/"+std::to_string(cardValue) +".jpg";
                        break;
                    case Cart::SQUARE:
                        karta = ":/cards/img/Diamonds/"+std::to_string(cardValue) +".jpg";
                        break;
                    case Cart::LETTER:
                        karta = ":/cards/img/Crosses/"+std::to_string(cardValue) +".jpg";
                        break;
                }
                QPixmap card(karta.c_str());
                QIcon BIC(card);
                CardsTop.at(x)->getByIndex(y)->setIcon(BIC);
                CardsTop.at(x)->getByIndex(y)->setIconSize(card.rect().size());
            }
        }
    }
    ColumnOfCart *col = game->getRotateColumn();
    //generovani karet pro balicek
    for (unsigned int x = 1; x < col->size() + 1; x++){

        //zjisteni attributu karty
        cardType = col->getCart(x-1)->getType();
        cardValue = col->getCart(x-1)->getNumber();
        cardHidden = col->getCart(x-1)->isHide();

        //Prirazeni obrazku karty + rub, nastaveni viditelnosti
        if (cardHidden == true){
            CardsDeck[x]->setIcon(ButtonIcon);
            CardsDeck[x]->setIconSize(cardBack.rect().size());
        }
        else {
            switch (cardType) {
                case Cart::HEART:
                    karta = ":/cards/img/Hearts/"+std::to_string(cardValue) +".jpg";
                    break;
                case Cart::SPADES:
                    karta = ":/cards/img/Spades/"+std::to_string(cardValue) +".jpg";
                    break;
                case Cart::SQUARE:
                    karta = ":/cards/img/Diamonds/"+std::to_string(cardValue) +".jpg";
                    break;
                case Cart::LETTER:
                    karta = ":/cards/img/Crosses/"+std::to_string(cardValue) +".jpg";
                    break;
            }
            QPixmap card(karta.c_str());
            QIcon BIC(card);
            CardsDeck[x]->setIcon(BIC);
            CardsDeck[x]->setIconSize(cardBack.rect().size());
        }
    }
}

