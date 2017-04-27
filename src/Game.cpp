/** 
 * @file Game.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 26, 2017, 1:03 AM
 */



#include <stdexcept>

#include "Game.h"
#include "Package.h"

Game::Game(unsigned int countDeskCols) {
    this->countDeskCols = countDeskCols;
    if (this->countDeskCols > 9)
        throw invalid_argument("Maximalní počet sloupců na herní ploše může být 9");
    this->rotateColumn = new ColumnOfCart;
    this->createGame();
}

void Game::createGame() {
    Package *package = new Package();
    unsigned int i = 0;
    ColumnOfCart *col;
    while (i < this->countDeskCols) {
        col = new ColumnOfCart();
        for (unsigned int x = 0; x < i + 1; x++) {
            col->addCart(package->getCart());
        }
        col->getLastCart()->show();
        this->desk.insert(this->desk.end(), col);
        i++;
    }

    for (int i = 0; i < 4; i++) {
        this->results.insert(this->results.end(), new ColumnOfCart);
    }
    while (!package->isEmpty()) {
        Cart *cart2 = package->getCart();
        cart2->show();
        this->rotateColumn->addCart(cart2);
    }
}

bool Game::moveCarts(ColumnOfCart *src, ColumnOfCart *dest, unsigned int count, bool resultCol) {
    unsigned int i;
    ColumnOfCart *temp = new ColumnOfCart;
    for (i = 0; i < count; i++) {
        try {
            if (src->getLastCart()->isHide()) break;
            temp->addCart(src->popLastCart());
        } catch (invalid_argument e) {
        }
    }

    bool continueVar = false;
    if (temp->size() != 0) {
        continueVar = dest->canPush(temp->getLastCart(), resultCol);
    }

    i = temp->size();
    if (continueVar == true) {
        while (i > 0) {
            i--;
            dest->addCart(temp->popLastCart());
        }
        return true;
    } else {
        while (i > 0) {
            i--;
            src->addCart(temp->popLastCart());
        }
        return false;
    }
}

string Game::resultColumnToString(unsigned int index) {
    if (index + 1 > this->results.size())
        throw invalid_argument("Neplatný index sloupce");
    try {
        return this->results.at(index)->getLastCart()->stringRepresentation();
    } catch (invalid_argument e) {
        return "prazdny";
    }
}

unsigned int Game::getMaxHeightCol() {
    unsigned int max = 0;
    for (unsigned int i = 0; i < this->desk.size(); i++) {
        if (max < this->desk.at(i)->size())
            max = this->desk.at(i)->size();
    }
    return max;
}

ColumnOfCart *Game::getDeskColumn(unsigned int index) {
    if (this->desk.size() <= index)
        throw invalid_argument("Neexistují sloupec na hrací desce");
    return this->desk.at(index);
}

ColumnOfCart *Game::getResultColumn(unsigned int index) {
    if (this->results.size() <= index)
        throw invalid_argument("Neexistují odkládací sloupec");
    return this->results.at(index);
}

bool Game::moveCartsOnDesk(unsigned int srcCol, unsigned int count, unsigned int destCol) {
    ColumnOfCart *src = this->getDeskColumn(srcCol);
    ColumnOfCart *dest = this->getDeskColumn(destCol);

    if (this->moveCarts(src, dest, count)) {
        try {
            src->getLastCart()->show();
        } catch (invalid_argument e) {

        }
        return true;
    } else return false;
}

bool Game::moveCartsDeskToResult(unsigned int srcCol, unsigned int destCol) {
    ColumnOfCart *src = this->getDeskColumn(srcCol);
    ColumnOfCart *dest = this->getResultColumn(destCol);

    if (this->moveCarts(src, dest, 1, true)) {
        try {
            src->getLastCart()->show();
        } catch (invalid_argument e) {
        }
        return true;
    } else return false;
}

void Game::save() {
}

void Game::undo() {
}