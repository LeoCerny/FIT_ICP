#include <QMessageBox>
#include <QPainterPath>

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
        cardMapper->setMapping(card,gameId * 10000 + cardCounter);
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
            cardMapper->setMapping(card, gameId * 10000 + cardCounter);
            window->connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));
            cardCounter++;

            //ulozeni tlacitka do vectoru
            buttons->push(card);
        }
        CardsBoard.insert(CardsBoard.end(), buttons);
    }

    //generovani karet pro top 4 sloupce
    for (unsigned int x = 0; x < 4; x++) {
        cardCounter = cardMultiplier*(x+7);

        //Nataveni rozmeru tlacitka
        QPushButton* card = new QPushButton(window);
        card->setFixedSize(cardSize);
        card->move(getX()+259+x*83,70+getY());

        //mapovani tlacitka se signalem
        cardMapper->setMapping(card, gameId * 10000 + cardCounter);
        window->connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));
        cardCounter++;

        //ulozeni tlacitka do vectoru
        CardsTop.insert(CardsTop.end(), card);
    }

    //generovani mista pro levy balicek
    cardCounter = cardMultiplier*11;
    cardLeft = new QPushButton(window);
    //Nataveni rozmeru tlacitka
    cardLeft->setFixedSize(cardSize);
    cardLeft->move(getX()+10,70+getY());
    //mapovani tlacitka se signalem
    cardMapper->setMapping(cardLeft, gameId * 10000 + cardCounter + 1);
    window->connect(cardLeft, SIGNAL(clicked()), cardMapper, SLOT(map()));

    //generovani karet pro balicek
    cardCounter = cardMultiplier*12;
    cardRight = new QPushButton(window);
    //Nataveni rozmeru tlacitka
    cardRight->setFixedSize(cardSize);
    cardRight->move(getX()+90,70+getY());
    //mapovani tlacitka se signalem
    cardMapper->setMapping(cardRight, gameId * 10000 + cardCounter + 1);
    window->connect(cardRight, SIGNAL(clicked()), cardMapper, SLOT(map()));
}

void GameBoard::drawBoard()
{
    //vykreslení karet pro herni sloupce na desce
    for (unsigned int x = 0; x < game->getCoutDeskCols(); x++) {
        ColumnOfCart  *col = game->getDeskColumn(x);
        for (unsigned int y = 1; y < col->size()+1; y++) {

            //Prirazeni obrazku karty + rub, nastaveni viditelnosti
            if (col->getCart(y-1)->isHide() == true){
                CardsBoard.at(x)->getByIndex(y)->setIcon(ButtonIcon);
                CardsBoard.at(x)->getByIndex(y)->setIconSize(cardBack.rect().size());
            }
            else {
                string karta;
                switch (col->getCart(y-1)->getType()) {
                    case Cart::HEART:
                        karta = ":/cards/img/Hearts/"+std::to_string(col->getCart(y-1)->getNumber()) +".jpg";
                        break;
                    case Cart::SPADES:
                        karta = ":/cards/img/Spades/"+std::to_string(col->getCart(y-1)->getNumber()) +".jpg";
                        break;
                    case Cart::SQUARE:
                        karta = ":/cards/img/Diamonds/"+std::to_string(col->getCart(y-1)->getNumber()) +".jpg";
                        break;
                    case Cart::LETTER:
                        karta = ":/cards/img/Crosses/"+std::to_string(col->getCart(y-1)->getNumber()) +".jpg";
                        break;
                }
                QPixmap card(karta.c_str());
                QIcon BIC(card);
                CardsBoard.at(x)->getByIndex(y)->setIcon(BIC);
                CardsBoard.at(x)->getByIndex(y)->setIconSize(card.rect().size());
            }
        }
    }

    //vykresleni mist pro top 4 sloupce
    for (unsigned int x = 0; x < 4; x++){
        ColumnOfCart *col = game->getResultColumn(x);
        if (col->size() == 0) {
            CardsTop.at(x)->setIcon(QIcon());
        } else {
            string karta;
            switch (col->getLastCart()->getType()) {
                case Cart::HEART:
                    karta = ":/cards/img/Hearts/"+std::to_string(col->getLastCart()->getNumber()) +".jpg";
                    break;
                case Cart::SPADES:
                    karta = ":/cards/img/Spades/"+std::to_string(col->getLastCart()->getNumber()) +".jpg";
                    break;
                case Cart::SQUARE:
                    karta = ":/cards/img/Diamonds/"+std::to_string(col->getLastCart()->getNumber()) +".jpg";
                    break;
                case Cart::LETTER:
                    karta = ":/cards/img/Crosses/"+std::to_string(col->getLastCart()->getNumber()) +".jpg";
                    break;
            }
            QPixmap card(karta.c_str());
            QIcon BIC(card);
            CardsTop.at(x)->setIcon(BIC);
            CardsTop.at(x)->setIconSize(card.rect().size());
        }
    }

    ColumnOfCart *col = game->getRotateColumn();

    //vykresleni mista pro levy rotacni balicek
    if (col->size()) {
        cardLeft->setIcon(ButtonIcon);
        cardLeft->setIconSize(cardBack.rect().size());
    } else {
        cardLeft->setIcon(QIcon());
    }

    //vykresleni mista pro pravy rotacni balicek
    if (col->size(true)) {
        string karta;
        switch (col->getLastCart(true)->getType()) {
            case Cart::HEART:
                karta = ":/cards/img/Hearts/"+std::to_string(col->getLastCart(true)->getNumber()) +".jpg";
                break;
            case Cart::SPADES:
                karta = ":/cards/img/Spades/"+std::to_string(col->getLastCart(true)->getNumber()) +".jpg";
                break;
            case Cart::SQUARE:
                karta = ":/cards/img/Diamonds/"+std::to_string(col->getLastCart(true)->getNumber()) +".jpg";
                break;
            case Cart::LETTER:
                karta = ":/cards/img/Crosses/"+std::to_string(col->getLastCart(true)->getNumber()) +".jpg";
                break;
        }
        QPixmap card(karta.c_str());
        QIcon BIC(card);
        cardRight->setIcon(BIC);
        cardRight->setIconSize(cardBack.rect().size());
    } else {
        cardRight->setIcon(QIcon());
    }
}

bool GameBoard::click(unsigned int col, unsigned int row) {
    if (click_actual == 0) {
        setFirstClick(col, row);
    } else if(click_actual == 1) {
        click_actual++;
        click_col2 = col;
    }

    if (click_actual == 2) {
        if (click_col < 7) {
            if (click_col2 < 7) {
                if (game->moveCartsOnDesk(click_col, click_col2, click_count)) {
                    removeButtons(click_col, click_count);
                    createButtons(click_col2, click_count);
                    return true;
                } else {
                    setFirstClick(col, row);
                }
            } else if (click_col2 < 11) {
                if (game->moveCartsDeskToResult(click_col, click_col2 - 7)) {
                    removeButtons(click_col, 1);
                    return true;
                } else {
                    setFirstClick(col, row);
                }
            }
        } else if (click_col < 11) {
            if (click_col2 < 7) {
                if (game->moveCarts(game->getResultColumn(click_col), game->getDeskColumn(click_col2), 1)) {
                    createButtons(click_col2, 1);
                    return true;
                } else {
                    setFirstClick(col, row);
                }
            } else if (click_col2 < 11) {
                if (game->moveCarts(game->getResultColumn(click_col-7), game->getResultColumn(click_col2-7), 1, true)) {
                    return true;
                } else {
                    setFirstClick(col, row);
                }
            }
        } else {
            if (click_col2 < 7) {
                if (game->moveCartsRotateToDesk(click_col2)) {
                    createButtons(click_col2, 1);
                    return true;
                } else {
                    setFirstClick(col, row);
                }
            } else if (click_col2 < 11) {
                if (game->moveCartsRotateToResult(click_col-7)) {
                    return true;
                } else {
                    setFirstClick(col, row);
                }
            }
        }
    }
    return false;
}

void GameBoard::removeButtons(unsigned int col, unsigned int count)
{
    ColumnOfButton *column = CardsBoard.at(col);
    for (unsigned int var = 0; var < count; var++) {
        delete column->popLast();
    }
}

void GameBoard::createButtons(unsigned int col, unsigned int count)
{
    for (unsigned int i = 0; i < count; i++) {
        ColumnOfCart *column = game->getDeskColumn(col);
        QPushButton *button = new QPushButton(window);
        //Nataveni rozmeru tlacitka
        button->setFixedSize(cardSize);
        button->move(getX()+10+col*83,270+(column->size())*20+getY());

        //mapovani tlacitka se signalem
        cardMapper->setMapping(button, gameId * 10000 + col * 100 + column->size());
        window->connect(button, SIGNAL(clicked()), cardMapper, SLOT(map()));

        ColumnOfButton*column2 = CardsBoard.at(col);
        column2->push(button);

    }

}

void GameBoard::printGame(Game *game) {
    string leftCol = "";
    string rightCol = "";
    if (!game->getRotateColumn()->size())
        leftCol = "X";
    else leftCol = "-";
    if (!game->getRotateColumn()->size(true))
        rightCol = "X";
    else rightCol = game->getRotateColumn()->getLastCart(true)->stringRepresentation();

    cout << "Rolovaci balicek: " << leftCol << " " << rightCol << endl;
    cout << "Odklaci baliek 1: " << game->resultColumnToString(0) << endl;
    cout << "Odklaci baliek 2: " << game->resultColumnToString(1) << endl;
    cout << "Odklaci baliek 3: " << game->resultColumnToString(2) << endl;
    cout << "Odklaci baliek 4: " << game->resultColumnToString(3) << endl;

    cout << endl;

    cout << "Hrací sloupce:" << endl;
    unsigned int row = 0;
    while (row < game->getMaxHeightCol()) {
        if (row == 0) {
            for (unsigned int col = 0; col < game->getCoutDeskCols(); col++) {
                cout << "\t " << col + 1 << ".";
            }
            cout << endl;
        }
        for (unsigned int col = 0; col < game->getCoutDeskCols(); col++) {
            try {
                cout << "\t" << game->getCart(col, row);
            } catch (invalid_argument e) {
                cout << "\t    ";
            }
        }
        cout << endl;
        row++;
    }
}
