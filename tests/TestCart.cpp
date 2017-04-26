/* 
 * File:   TestCart.cpp
 * Author: leo
 *
 * Created on April 26, 2017, 6:34 PM
 */

#include <stdlib.h>
#include <iostream>
#include "Cart.h"

/*
 * Simple C++ Test Suite
 */

void testPushResultCol() {
    Cart *cartA = new Cart(Cart::HEART, 1);
    Cart *cartB = new Cart(Cart::HEART, 2);
    cartA->show();
    cartB->show();

    cout << cartA << " <- " << cartB << " " << (cartA->canPush(cartB, true) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::LETTER);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB, true) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SPADES);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB, true) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SQUARE);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB, true) ? "OK" : "FAIL") << endl;
    
    cartA->setNumber(2);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB, true) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::LETTER);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB, true) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SPADES);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB, true) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SQUARE);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB, true) ? "OK" : "FAIL") << endl;

    cartA->setNumber(3);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB, true) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::LETTER);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB, true) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SPADES);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB, true) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SQUARE);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB, true) ? "OK" : "FAIL") << endl;
    
    
}

void testPushDeskCol() {
        Cart *cartA = new Cart(Cart::HEART, 1);
    Cart *cartB = new Cart(Cart::HEART, 2);
    cartA->show();
    cartB->show();

    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::LETTER);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SPADES);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SQUARE);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    
    cartA->setNumber(2);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::LETTER);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SPADES);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SQUARE);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    
    cartA->setNumber(3);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::LETTER);
    cout << cartA << " <- " << cartB << " " << (cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SPADES);
    cout << cartA << " <- " << cartB << " " << (cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SQUARE);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    
    cartA->setType(Cart::LETTER);
    cout << cartA << " <- " << cartB << " " << (cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::LETTER);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SPADES);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SQUARE);
    cout << cartA << " <- " << cartB << " " << (cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    
    cartA->setType(Cart::SPADES);
    cout << cartA << " <- " << cartB << " " << (cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::LETTER);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SPADES);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SQUARE);
    cout << cartA << " <- " << cartB << " " << (cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    
    cartA->setType(Cart::SQUARE);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::LETTER);
    cout << cartA << " <- " << cartB << " " << (cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SPADES);
    cout << cartA << " <- " << cartB << " " << (cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
    cartB->setType(Cart::SQUARE);
    cout << cartA << " <- " << cartB << " " << (!cartA->canPush(cartB) ? "OK" : "FAIL") << endl;
}

void testNumberAsString() {
     Cart *cartA = new Cart(Cart::HEART, 1);
     cartA->show();
     
     cout << cartA << " == A " << (cartA->getNumberAsString() == "A" ? "OK" : "FAIL") << endl;
     cartA->setNumber(11);
     cout << cartA << " == J " << (cartA->getNumberAsString() == "J" ? "OK" : "FAIL") << endl;
     cartA->setNumber(12);
     cout << cartA << " == Q " << (cartA->getNumberAsString() == "Q" ? "OK" : "FAIL") << endl;
     cartA->setNumber(13);
     cout << cartA << " == K " << (cartA->getNumberAsString() == "K" ? "OK" : "FAIL") << endl;
}

int main(void) {
    testPushResultCol();
    testPushDeskCol();
    testNumberAsString();
    return (EXIT_SUCCESS);
}

