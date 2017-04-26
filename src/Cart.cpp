/** 
 * @file Cart.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 25, 2017, 2:34 PM
 */

#include <stdexcept>

#include "Cart.h"

using namespace std;

Cart::Cart(int type, int number) {
    this->setType(type);
    this->setNumber(number);
    this->hide();
}

void Cart::setNumber(int number) {
    if (number < 1 or number > 13) 
        throw invalid_argument("Číslo musí být jedno z {1,2,3,4,5,6,7,8,9,10,11,12,13}");
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
            throw invalid_argument("Typ musí být jeden z {Cart::SQUARE, Cart::HEART, Cart::LETTER, Cart::SPADES}");
    }
}





