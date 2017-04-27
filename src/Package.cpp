/** 
 * @file Package.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 25, 2017, 2:54 PM
 */

#include <stdexcept>
#include <vector>
#include <cstdlib>

#include "Package.h"
#include "Cart.h"

Package::Package() {
    this->generateCards();
    this->mix();
}

void Package::generateCards() {
    for (int i = 1; i <= 13; i++) {
        this->carts.insert(this->carts.end(), new Cart(Cart::HEART, i));
        this->carts.insert(this->carts.end(), new Cart(Cart::SPADES, i));
        this->carts.insert(this->carts.end(), new Cart(Cart::LETTER, i));
        this->carts.insert(this->carts.end(), new Cart(Cart::SQUARE, i));
    }
}

void Package::mix() {
    unsigned int random;
    vector<unsigned int> mixKeys;
    for (unsigned int i = 0; i < this->carts.size(); i++) {
        do {
            random = rand() % this->carts.size();
        } while (this->inArray(random, mixKeys));
        mixKeys.insert(mixKeys.end(), random);
    }


    vector<Cart*> newCarts;
    for (unsigned int i = 0; i < mixKeys.size(); i++) {
        newCarts.insert(newCarts.end(), this->carts.at(mixKeys.at(i)));
    }
    this->carts.erase(this->carts.begin());
    this->carts = newCarts;
}

bool Package::inArray(unsigned int value, std::vector<unsigned int> data) {
    for (unsigned int i = 0; i < data.size(); i++) {
        if (data.at(i) == value)
            return true;
    }
    return false;

}

Cart *Package::getCart() {
    if (this->carts.empty())
        throw invalid_argument("Žádné další karty");
    Cart *temp = this->carts.back();
    this->carts.pop_back();
    return temp;
}