#include <QMessageBox>
#include <QPainterPath>

#include "GameBoard.h"

void GameBoard::initBoard()
{
    cout << endl << "init ";

    //mapovac signalu hlavickovych tlacitek
    window->connect(headMapper, SIGNAL(mapped(int)), window, SLOT(On_IconClicked(int)));
    QSize size(32, 32);
    QPushButton *saveGame = new QPushButton(window);
    QPushButton *newGame = new QPushButton(window);
    QPushButton *loadGame = new QPushButton(window);
    QPushButton *undo = new QPushButton(window);

    headMapper->setMapping(newGame, gameId * 100 + 0);
    window->connect(newGame, SIGNAL(clicked()), headMapper, SLOT(map()));
    headMapper->setMapping(undo, gameId * 100 + 1);
    window->connect(undo, SIGNAL(clicked()), headMapper, SLOT(map()));
    headMapper->setMapping(saveGame, gameId * 100 + 2);
    window->connect(saveGame, SIGNAL(clicked()), headMapper, SLOT(map()));
    headMapper->setMapping(loadGame, gameId * 100 + 3);
    window->connect(loadGame, SIGNAL(clicked()), headMapper, SLOT(map()));

    newGame->setFixedSize(size);
    loadGame->setFixedSize(size);
    undo->setFixedSize(size);
    saveGame->setFixedSize(size);


    newGame->move(getX() + 10, getY() + 20);
    undo->move(getX() + 50, getY() + 20);
    saveGame->move(getX() + 90, getY() + 20);
    loadGame->move(getX() + 130, getY() + 20);

    saveGame->setFixedSize(size);
    newGame->setFixedSize(size);
    loadGame->setFixedSize(size);
    undo->setFixedSize(size);

    headerPanel.push_back(newGame);
    headerPanel.push_back(undo);
    headerPanel.push_back(saveGame);
    headerPanel.push_back(loadGame);

    for (unsigned int var = 0; var < headerPanel.size(); var++) {
        headerPanel.at(var)->show();
    }

    //mapovac signalu dynamicky generovanych tlacitek
    window->connect(cardMapper, SIGNAL(mapped(int)), window, SLOT(On_Clicked(int)));

    unsigned int cardCounter = 0;
    unsigned int cardMultiplier = 100;

    //generovnai karet pro herni sloupce
    for (unsigned int col = 0; col < game->getCoutDeskCols(); col++) {
        cardCounter = cardMultiplier*col;
        ColumnOfButton *buttons = new ColumnOfButton;
        ColumnOfCart *column = game->getDeskColumn(col);

        //Nataveni rozmeru tlacitka pro zacatek sloupce
        QPushButton* card = new QPushButton(window);
        card->setFixedSize(cardSize);
        card->move(getX() + 10 + col * 83, getY() + this->marginDeskTop);
        card->setFlat(true);
        card->show();

        //mapovani tlacitka se signalem
        cardMapper->setMapping(card, gameId * 10000 + cardCounter);
        window->connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));

        for (unsigned int y = 0; y < column->size(); y++) {
            cardCounter++;
            QPushButton* card = new QPushButton(window);

            //Nataveni rozmeru tlacitka
            card->setFixedSize(cardSize);
            card->move(getX() + 10 + col * 83, this->marginDeskTop + y * 20 + getY());
            card->show();

            //mapovani tlacitka se signalem
            cardMapper->setMapping(card, gameId * 10000 + cardCounter);
            window->connect(card, SIGNAL(clicked()), cardMapper, SLOT(map()));

            //ulozeni tlacitka do vectoru
            buttons->push(card);
        }
        CardsBoard.insert(CardsBoard.end(), buttons);
    }

    //generovani karet pro top 4 sloupce
    for (unsigned int x = 0; x < 4; x++) {
        cardCounter = cardMultiplier * (x + game->getCoutDeskCols());

        //Nataveni rozmeru tlacitka
        QPushButton* card = new QPushButton(window);
        card->setFixedSize(cardSize);
        card->move(getX() + 259 + x * 83, 70 + getY());
        card->show();

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
    cardLeft->show();

    //mapovani tlacitka se signalem
    cardMapper->setMapping(cardLeft, gameId * 10000 + cardCounter + 1);
    window->connect(cardLeft, SIGNAL(clicked()), cardMapper, SLOT(map()));

    //generovani karet pro balicek
    cardCounter = cardMultiplier*12;
    cardRight = new QPushButton(window);
    //Nataveni rozmeru tlacitka
    cardRight->setFixedSize(cardSize);
    cardRight->move(getX()+90,70+getY());
    cardRight->show();

    //mapovani tlacitka se signalem
    cardMapper->setMapping(cardRight, gameId * 10000 + cardCounter + 1);
    window->connect(cardRight, SIGNAL(clicked()), cardMapper, SLOT(map()));

    cout << "OK" ;
}

void GameBoard::drawBoard()
{
    cout << endl << "draw ";
    for (unsigned int i = 0; i < headerPanel.size(); i++) {
        QPixmap map(headIconsPath.at(i).c_str());
        QIcon icon(map);
        headerPanel.at(i)->setIcon(icon);
        headerPanel.at(i)->setIconSize(map.rect().size());
    }

    //vykreslení karet pro herni sloupce na desce
    for (unsigned int x = 0; x < game->getCoutDeskCols(); x++) {
        ColumnOfCart  *col = game->getDeskColumn(x);
        for (unsigned int y = 0; y < col->size(); y++) {
            //Prirazeni obrazku karty + rub, nastaveni viditelnosti
            if (col->getCart(y)->isHide() == true){
                CardsBoard.at(x)->getByIndex(y)->setIcon(ButtonIcon);
                CardsBoard.at(x)->getByIndex(y)->setIconSize(cardBack.rect().size());
            }
            else {
                string karta;
                switch (col->getCart(y)->getType()) {
                    case Cart::HEART:
                        karta = ":/cards/img/Hearts/"+std::to_string(col->getCart(y)->getNumber()) +".jpg";
                        break;
                    case Cart::SPADES:
                        karta = ":/cards/img/Spades/"+std::to_string(col->getCart(y)->getNumber()) +".jpg";
                        break;
                    case Cart::SQUARE:
                        karta = ":/cards/img/Diamonds/"+std::to_string(col->getCart(y)->getNumber()) +".jpg";
                        break;
                    case Cart::LETTER:
                        karta = ":/cards/img/Crosses/"+std::to_string(col->getCart(y)->getNumber()) +".jpg";
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

    cout << "OK";
}

bool GameBoard::click(unsigned int col, unsigned int row) {
    if (game->activeGame == false) {
        QMessageBox msgBox;
        msgBox.setText("Hra je dohrana");
        msgBox.exec();
        return false;
    } else if (row == 0 && click_count == 0) {
        return false;
    }
    if (click_actual == 0) {
        click_col = col;
        click_count = row;
        click_actual = 1;
    } else if(click_actual == 1) {
        click_actual = 2;
        click_col2 = col;
    }
    cout << endl << "CLICK start" << endl;
    if (col == 12 && click_col != click_col2) {
        click_col = 12;
        click_count = 1;
        click_actual = 1;
    } else if (click_actual == 2) {
        if (click_col < 7) {
            if (click_col == click_col2 && game->getDeskColumn(click_col)->size() == row) {
                for (unsigned int i = 0; i < 4; i++) {
                    if (game->getResultColumn(i)->canPush(game->getDeskColumn(click_col)->getLastCart(), true)) {
                        game->moveCartsDeskToResult(click_col, i);
                        removeButtons(click_col, 1);
                        click_actual = 3;
                        break;
                    }
                }
            } else if (click_col2 < 7) {//ok
                unsigned int count = game->getDeskColumn(click_col)->size() - click_count + 1;
                if (game->moveCartsOnDesk(click_col, count, click_col2)) {
                    removeButtons(click_col, count);
                    createButtons(click_col2);
                    click_actual = 3;
                }
            } else if (click_col2 < 11) {//ok
                if (game->moveCartsDeskToResult(click_col, click_col2 - 7)) {
                    removeButtons(click_col, 1);
                    click_actual = 3;
                }
            }
        } else if (click_col < 11) {
            if (click_col2 < 7) {
                if (game->moveCarts(game->getResultColumn(click_col-7), game->getDeskColumn(click_col2), 1)) {
                    createButtons(click_col2);
                    click_actual = 3;
                }
            } else if (click_col2 < 11) {//ok
                if (game->moveCarts(game->getResultColumn(click_col-7), game->getResultColumn(click_col2-7), 1, true)) {
                    click_actual = 3;
                }
            }
        } else {
            if (click_col == click_col2) {
                if (game->getRotateColumn()->size(true))
                    for (unsigned int i = 0; i < 4; i++) {
                        if (game->getResultColumn(i)->canPush(game->getRotateColumn()->getLastCart(true), true)) {
                            game->moveCartsRotateToResult(i);
                            click_actual = 3;
                            break;
                        }
                    }
            } else if (click_col2 < 7) {//ok
                if (game->moveCartsRotateToDesk(click_col2)) {
                    createButtons(click_col2);
                    click_actual = 3;
                }
            } else if (click_col2 < 11) {//ok
                if (game->moveCartsRotateToResult(click_col2 - 7)) {
                    click_actual = 3;
                }
            }
        }
    }
    cout << "CLICK end" << endl;

    if (click_actual == 3) {
        click_actual = 0;
        return true;
    } else if (click_actual == 2){
        click_actual = 1;
        click_col = col;
        click_count = row;
        return false;
    }
    return false;
}

void GameBoard::removeButtons(unsigned int col, unsigned int count)
{
    ColumnOfButton *column = CardsBoard.at(col);
    for (unsigned int var = 0; var < count; var++) {
        try {
            delete column->popLast();
        } catch (invalid_argument e) {
            break;
        }
    }
}

void GameBoard::createButtons(unsigned int col)
{
    //cout << "CREATE BUTTONS" << endl;
    for (unsigned int i = CardsBoard.at(col)->size(); i < game->getDeskColumn(col)->size(); i++) {
        //cout << "create button" << endl;

        QPushButton *button = new QPushButton(window);

        //Nataveni rozmeru tlacitka
        button->setFixedSize(cardSize);
        if (CardsBoard.at(col)->size())
            button->move(CardsBoard.at(col)->getLast()->pos().x(), CardsBoard.at(col)->getLast()->pos().y() + 20);
        else
            button->move(getX() + 10 + col * 83, getY() + this->marginDeskTop);
        button->show();

        //mapovani tlacitka se signalem
        cardMapper->setMapping(button, gameId * 10000 + col * 100 + i + 1);
        window->connect(button, SIGNAL(clicked()), cardMapper, SLOT(map()));

        CardsBoard.at(col)->push(button);
    }
    //cout << "CREATE STOP" << endl;
}

void GameBoard::printGame(Game *game)
{
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
