/** 
 * @file Package.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 25, 2017, 2:54 PM
 */

#include <vector>
#include <stdexcept>
#include <cstdlib>

#include "Package.h"
#include "Cart.h"

Package::Package() {
    this->generateCards();
    this->mix();
}

void Package::generateCards() {
    this->carts.erase(this->carts.begin());
    for (int i = 1; i <= 13; i++) {
        this->carts.insert(this->carts.end(), new Cart(Cart::HEART, i));
        this->carts.insert(this->carts.end(), new Cart(Cart::SPADES, i));
        this->carts.insert(this->carts.end(), new Cart(Cart::LETTER, i));
        this->carts.insert(this->carts.end(), new Cart(Cart::SQUARE, i));
    }
}

void Package::mix() {
    unsigned int random;
    std::vector<int> mixKeys;
    for (int i = 0; i < 32; i++) {
        do {
            random = std::rand() % 32;
        } while (this->inArray(random, mixKeys));
        mixKeys.insert(mixKeys.end(), random);
    }
    
    std::vector<Cart*> newCarts;
    for (unsigned int i = 0; i < mixKeys.size(); i++) {
        newCarts.insert(newCarts.end(), this->carts.at(mixKeys.at(i)));
    }
    this->carts.erase(this->carts.begin());
    this->carts = newCarts;

}

bool Package::inArray(int value, std::vector<int> data) {
    for (unsigned int i = 0; i < data.size(); i++) {
        if (data.at(i) == value)
            return true;
    }
    return false;

}

Cart *Package::getCart() {
    if (this->carts.empty())
        throw std::invalid_argument("No carts");
    return this->carts.back();
}