/** 
 * @file TestCart.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * 
 * @date April 26, 2017, 6:34 PM
 */

#include <stdlib.h>
#include <iostream>
#include "../src/Cart.h"

void testPushResultCol() {
    cout << "TestCart - testPushResultCol" << endl;
    Cart *cartA = new Cart(Cart::HEART, 1);
    Cart *cartB = new Cart(Cart::HEART, 2);
    cartA->show();
    cartB->show();

    if (!cartA->canPush(cartB, true))
        cout << "FAIL1" << endl;
    cartB->setType(Cart::LETTER);
    if (cartA->canPush(cartB, true))
        cout << "FAIL2" << endl;
    cartB->setType(Cart::SPADES);
    if (cartA->canPush(cartB, true))
        cout << "FAIL3" << endl;
    cartB->setType(Cart::SQUARE);
    if (cartA->canPush(cartB, true))
        cout << "FAIL4" << endl;

    cartA->setNumber(2);
    cartB->setType(Cart::HEART);
    if (cartA->canPush(cartB, true))
        cout << "FAIL5" << endl;
    cartB->setType(Cart::LETTER);
    if (cartA->canPush(cartB, true))
        cout << "FAIL6" << endl;
    cartB->setType(Cart::SPADES);
    if (cartA->canPush(cartB, true))
        cout << "FAIL7" << endl;
    cartB->setType(Cart::SQUARE);
    if (cartA->canPush(cartB, true))
        cout << "FAIL8" << endl;

    cartA->setNumber(3);
    cartB->setType(Cart::HEART);
    if (cartA->canPush(cartB, true))
        cout << "FAIL9" << endl;
    cartB->setType(Cart::LETTER);
    if (cartA->canPush(cartB, true))
        cout << "FAIL10" << endl;
    cartB->setType(Cart::SPADES);
    if (cartA->canPush(cartB, true))
        cout << "FAIL11" << endl;
    if (cartA->canPush(cartB, true))
        cout << "FAIL12" << endl;	
    cartB->setType(Cart::SQUARE);
    if (cartA->canPush(cartB, true))
        cout << "FAIL13" << endl;
}

void testPushDeskCol() {
    cout << "TestCart - testPushDeskCol" << endl;
    Cart *cartA = new Cart(Cart::HEART, 1);
    Cart *cartB = new Cart(Cart::HEART, 2);
    cartA->show();
    cartB->show();

    if (cartA->canPush(cartB)) cout << "FAIL1" << endl;
    cartB->setType(Cart::LETTER);
    if (cartA->canPush(cartB)) cout << "FAIL2" << endl;
    cartB->setType(Cart::SPADES);
    if (cartA->canPush(cartB)) cout << "FAIL3" << endl;
    cartB->setType(Cart::SQUARE);
    if (cartA->canPush(cartB)) cout << "FAIL4" << endl;

    cartA->setNumber(2);
    if (cartA->canPush(cartB)) cout << "FAIL5" << endl;
    cartB->setType(Cart::LETTER);
    if (cartA->canPush(cartB)) cout << "FAIL6" << endl;
    cartB->setType(Cart::SPADES);
    if (cartA->canPush(cartB)) cout << "FAIL7" << endl;
    cartB->setType(Cart::SQUARE);
    if (cartA->canPush(cartB)) cout << "FAIL8" << endl;

    cartA->setNumber(3);
    if (cartA->canPush(cartB)) cout << "FAIL9" << endl;
    cartB->setType(Cart::LETTER);
    if (!cartA->canPush(cartB)) cout << "FAIL10" << endl;
    cartB->setType(Cart::SPADES);
    if (!cartA->canPush(cartB)) cout << "FAIL11" << endl;
    cartB->setType(Cart::SQUARE);
    if (cartA->canPush(cartB)) cout << "FAIL12" << endl;

    cartA->setType(Cart::LETTER);
    if (!cartA->canPush(cartB)) cout << "FAIL13" << endl;
    cartB->setType(Cart::LETTER);
    if (cartA->canPush(cartB)) cout << "FAIL14" << endl;
    cartB->setType(Cart::SPADES);
    if (cartA->canPush(cartB)) cout << "FAIL15" << endl;
    cartB->setType(Cart::SQUARE);
    if (!cartA->canPush(cartB)) cout << "FAIL16" << endl;

    cartA->setType(Cart::SPADES);
    if (!cartA->canPush(cartB)) cout << "FAIL17" << endl;
    cartB->setType(Cart::LETTER);
    if (cartA->canPush(cartB)) cout << "FAIL18" << endl;
    cartB->setType(Cart::SPADES);
    if (cartA->canPush(cartB)) cout << "FAIL19" << endl;
    cartB->setType(Cart::SQUARE);
    if (!cartA->canPush(cartB)) cout << "FAIL20" << endl;

    cartA->setType(Cart::SQUARE);
    if (cartA->canPush(cartB)) cout << "FAIL21" << endl;
    cartB->setType(Cart::LETTER);
    if (!cartA->canPush(cartB)) cout << "FAIL22" << endl;
    cartB->setType(Cart::SPADES);
    if (!cartA->canPush(cartB)) cout << "FAIL23" << endl;
    cartB->setType(Cart::SQUARE);
    if (cartA->canPush(cartB)) cout << "FAIL24" << endl;
}

void testNumberAsString() {
    Cart *cartA = new Cart(Cart::HEART, 1);
    cartA->show();

    if (cartA->getNumberAsString() != "A") cout << "FAIL A" << endl;
    cartA->setNumber(11);
    if (cartA->getNumberAsString() != "J") cout << "FAIL J" << endl;
    cartA->setNumber(12);
    if (cartA->getNumberAsString() != "Q") cout << "FAIL Q" << endl;
    cartA->setNumber(13);
    if (cartA->getNumberAsString() != "K") cout << "FAIL K" << endl;
}

int main(void) {
    testPushResultCol();
    testPushDeskCol();
    testNumberAsString();
    return (EXIT_SUCCESS);
}

