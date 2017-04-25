/** 
 * @file Cart.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 25, 2017, 2:34 PM
 */

#include <stdexcept>

#include "Cart.h"

Cart::Cart(int type, int number) {
    this->setType(type);
    this->setNumber(number);
}

void Cart::setNumber(int number) {
    if (number < 1 or number > 13) 
        throw std::invalid_argument("Number must be one of {1,2,3,4,5,6,7,8,9,10,11,12,13}");
    this->number = number;
}

void Cart::setType(int type) {
    switch (type) {
        case Cart::HEART:
        case Cart::LETTER:
        case Cart::SPADES:
        case Cart::SQUARE:
            this->type = type;
            break;
        default:
            throw std::invalid_argument("Type must be one of {Cart::SQUARE, Cart::HEART, Cart::LETTER, Cart::SPADES}");
    }
}

