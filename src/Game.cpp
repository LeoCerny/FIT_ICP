/** 
 * @file Game.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 26, 2017, 1:03 AM
 */



#include <stdexcept>
#include <fstream>
#include <sstream>
#include <regex>

#include "Game.h"
#include "Package.h"

Game::Game(unsigned int countDeskCols, bool autoInit) {
    this->countDeskCols = countDeskCols;
    if (this->countDeskCols > 9)
        throw invalid_argument("Maximalní počet sloupců na herní ploše může být 9");
    this->rotateColumn = new ColumnOfCart;
    if (autoInit)
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
        this->rotateColumn->addCart(cart2);
    }

}

bool Game::moveCarts(ColumnOfCart *src, ColumnOfCart *dest, unsigned int count, bool resultCol) {
    addMove();
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
        if (getMaxHeightCol() == 0)
            activeGame = false;
        return true;
    } else return false;
}

bool Game::save(string path) {
    if (!ofstream(path.c_str())) {
        return false;
    }

    ofstream file(path);

    for (unsigned int i = 0; i < rotateColumn->size(); i++) {
        file << rotateColumn->getCart(i)->save();
        file << " ";
    }
    file << endl;

    for (unsigned int i = 0; i < rotateColumn->size(true); i++) {
        file << rotateColumn->getCart(i, true)->save();
        file << " ";
    }
    file << endl;

    for (unsigned int i = 0; i < results.size(); i++) {
        for (unsigned int x = 0; x < results.at(i)->size(); x++) {
            file << results.at(i)->getCart(x)->save();
            file << " ";
        }
        file << endl;
    }

    for (unsigned int i = 0; i < desk.size(); i++) {
        for (unsigned int x = 0; x < desk.at(i)->size(); x++) {
            file << desk.at(i)->getCart(x)->save();
            file << " ";
        }
        file << endl;
    }

    file.close();
    return true;
}

bool Game::load(string path) {
    if (!ifstream(path.c_str())) {
        return false;
    }
    ifstream file(path);

    string line;
    unsigned int index = 0;
    regex reg("([0-9]+)-([0-9]+)-([0-9]+)");
    smatch match;
    ColumnOfCart *col;
    while(getline(file, line)) {
        switch (index) {
        case 0://rotate left
            rotateColumn = new ColumnOfCart;
            while (regex_search(line, match, reg)) {
                Cart *cart = new Cart(atoi(match.str(1).c_str()), atoi(match.str(2).c_str()));
                if (atoi(match.str(3).c_str()) == 0)
                    cart->show();
                rotateColumn->addCart(cart);
                line = match.suffix().str();
            }
            break;
        case 1:
            while (regex_search(line, match, reg)) {
                Cart *cart = new Cart(atoi(match.str(1).c_str()), atoi(match.str(2).c_str()));
                if (atoi(match.str(3).c_str()) == 0)
                    cart->show();
                rotateColumn->addCart(cart, true);
                line = match.suffix().str();
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            col = new ColumnOfCart();
            while (regex_search(line, match, reg)) {
                Cart *cart = new Cart(atoi(match.str(1).c_str()), atoi(match.str(2).c_str()));
                if (atoi(match.str(3).c_str()) == 0)
                    cart->show();
                col->addCart(cart);
                line = match.suffix().str();
            }
            results.push_back(col);
            break;
        default:
            col = new ColumnOfCart();
            while (regex_search(line, match, reg)) {
                Cart *cart = new Cart(atoi(match.str(1).c_str()), atoi(match.str(2).c_str()));
                if (atoi(match.str(3).c_str()) == 0)
                    cart->show();
                col->addCart(cart);
                line = match.suffix().str();
            }
            desk.insert(desk.end(), col);
            break;
        }
        index++;
    }
    return true;
}

void Game::addMove() {
    string move;
    for (unsigned int i = 0; i < rotateColumn->size(); i++) {
        move += rotateColumn->getCart(i)->save();
        move += " ";
    }
    move += "\n";

    for (unsigned int i = 0; i < rotateColumn->size(true); i++) {
        move += rotateColumn->getCart(i, true)->save();
        move += " ";
    }
    move += "\n";
    for (unsigned int i = 0; i < results.size(); i++) {
        for (unsigned int x = 0; x < results.at(i)->size(); x++) {
            move += results.at(i)->getCart(x)->save();
            move += " ";
        }
        move += "\n";
    }

    for (unsigned int i = 0; i < desk.size(); i++) {
        for (unsigned int x = 0; x < desk.at(i)->size(); x++) {
            move += desk.at(i)->getCart(x)->save();
            move += " ";
        }
        move += "\n";
    }
    this->moves.push_back(move);
}

void Game::undo() {
    if (moves.size() == 0)
        return;
    string line;

    while (results.size())
        results.pop_back();
    while(desk.size())
        desk.pop_back();

    istringstream file(moves.at(moves.size()-1));
    moves.pop_back();

    unsigned int index = 0;

    regex reg("([0-9]+)-([0-9]+)-([0-9]+)");
    smatch match;
    ColumnOfCart *col;
    while(getline(file, line)) {
        switch (index) {
        case 0://rotate left
            rotateColumn = new ColumnOfCart;
            while (regex_search(line, match, reg)) {
                Cart *cart = new Cart(atoi(match.str(1).c_str()), atoi(match.str(2).c_str()));
                if (atoi(match.str(3).c_str()) == 0)
                    cart->show();
                rotateColumn->addCart(cart);
                line = match.suffix().str();
            }
            break;
        case 1:
            while (regex_search(line, match, reg)) {
                Cart *cart = new Cart(atoi(match.str(1).c_str()), atoi(match.str(2).c_str()));
                if (atoi(match.str(3).c_str()) == 0)
                    cart->show();
                rotateColumn->addCart(cart, true);
                line = match.suffix().str();
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            col = new ColumnOfCart();
            while (regex_search(line, match, reg)) {
                Cart *cart = new Cart(atoi(match.str(1).c_str()), atoi(match.str(2).c_str()));
                if (atoi(match.str(3).c_str()) == 0)
                    cart->show();
                col->addCart(cart, true);
                line = match.suffix().str();
            }
            results.push_back(col);
            break;
        default:
            col = new ColumnOfCart();
            while (regex_search(line, match, reg)) {
                Cart *cart = new Cart(atoi(match.str(1).c_str()), atoi(match.str(2).c_str()));
                if (atoi(match.str(3).c_str()) == 0)
                    cart->show();
                col->addCart(cart);
                line = match.suffix().str();
            }
            desk.insert(desk.end(), col);
            break;
        }
        index++;
    }
}
