/** 
 * @file ColumnOfCart.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 25, 2017, 2:53 PM
 */

#include <vector>
#include <stdexcept>

#include "ColumnOfCart.h"

using namespace std;

ColumnOfCart::ColumnOfCart() {
    this->index = 0;
}

void ColumnOfCart::addCart(Cart* cart) {
    this->carts.insert(this->carts.end(), cart);
}

void ColumnOfCart::rotate(int num) {
    for (int i = 0; i < num; i++) {
        this->rotateOne();
    }
}

void ColumnOfCart::rotateOne() {
    this->index = this->index + 1 % this->carts.size();
}

Cart *ColumnOfCart::getCart(unsigned int index) {
    if (this->carts.empty() || this->carts.size() <= index )
        throw invalid_argument("Prazdný sloupec");
    Cart *temp = this->carts.at(index);
    //this->carts.pop_back();
    return temp;
}

