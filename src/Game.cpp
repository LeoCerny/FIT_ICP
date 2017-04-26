/** 
 * @file Game.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 26, 2017, 1:03 AM
 */



#include <stdexcept>

#include "Package.h"
#include "Game.h"

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
    Cart *cart;
    while (i < this->countDeskCols) {
        col = new ColumnOfCart();
        for (unsigned int x = 0; x < i + 1; x++) {
            cart = package->getCart();
            col->addCart(cart);
        }
        cart->show();
        this->desk.insert(this->desk.end(), col);
        i++;
    }

    for (int i = 0; i < 4; i++) {
        this->results.insert(this->results.end(), new ColumnOfCart);
    }

    while (!package->isEmpty()) {
        this->rotateColumn->addCart(package->getCart());
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

void Game::save() {
}

void Game::undo() {
}