/* 
 * File:   TestColumnOfCart.cpp
 * Author: leo
 *
 * Created on April 26, 2017, 11:10 PM
 */

#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include "../src/Cart.h"
#include "../src/ColumnOfCart.h"

void testAddCart() {
    cout << "TestColumnOfCart - addCart" << endl;
    ColumnOfCart *col = new ColumnOfCart;
    col->addCart(new Cart(Cart::HEART, 1));
}

void testGetLastCart() {
    cout << "TestColumnOfCart - addCart" << endl;
    ColumnOfCart *col = new ColumnOfCart;
    col->addCart(new Cart(Cart::HEART, 1));
    col->addCart(new Cart(Cart::HEART, 2));
    col->addCart(new Cart(Cart::HEART, 3));
    Cart *cart = col->getLastCart();
    if (cart->getNumber() != 3 or cart->getType() != Cart::HEART)
        cout << "FAIL1" << endl;
    col->addCart(new Cart(Cart::SPADES, 1));
    col->addCart(new Cart(Cart::SPADES, 2));
    col->addCart(new Cart(Cart::SPADES, 11));

    cart = col->getLastCart();
    if (cart->getNumber() != 11 or cart->getType() != Cart::SPADES)
        cout << "FAIL2" << endl;
}

void testGetCartByIndex() {
    cout << "TestColumnOfCart - getCartByIndex" << endl;
    ColumnOfCart *col = new ColumnOfCart;
    col->addCart(new Cart(Cart::HEART, 1));
    col->addCart(new Cart(Cart::HEART, 2));
    col->addCart(new Cart(Cart::HEART, 3));
    col->addCart(new Cart(Cart::SPADES, 1));
    col->addCart(new Cart(Cart::SPADES, 2));
    col->addCart(new Cart(Cart::SPADES, 11));

    Cart *cart = col->getCart(3);
    if (cart->getNumber() != 1 or cart->getType() != Cart::SPADES)
        cout << "FAIL" << endl;
}

void testPopCart() {
    cout << "TestColumnOfCart - testPopCart" << endl;
    ColumnOfCart *col = new ColumnOfCart;
    col->addCart(new Cart(Cart::HEART, 1));
    col->addCart(new Cart(Cart::SPADES, 2));
    col->addCart(new Cart(Cart::SPADES, 11));

    if (col->size() != 3)
        cout << "FAIL size()" << endl;
    Cart *cart = col->popLastCart();

    if (col->size() != 2 or cart->getNumber() != 11 or cart->getType() != Cart::SPADES)
        cout << "FAIL pop1" << endl;
    cart = col->popLastCart();
    if (col->size() != 1 or cart->getNumber() != 2 or cart->getType() != Cart::SPADES)
        cout << "FAIL pop2" << endl;
    cart = col->popLastCart();
    if (col->size() != 0 or cart->getNumber() != 1 or cart->getType() != Cart::HEART)
        cout << "FAIL pop3" << endl;

    try {
        col->getLastCart();
        cout << "FAIL getLastCart()" << endl;
    } catch (invalid_argument e) {
    }
    try {
        col->popLastCart();
        cout << "FAIL popLastCart()" << endl;
    } catch (invalid_argument e) {
    }
}

void testRotate() {
    cout << "TestColumnOfCart - rotate" << endl;
    ColumnOfCart *col = new ColumnOfCart;
    col->addCart(new Cart(Cart::HEART, 1));
    col->addCart(new Cart(Cart::HEART, 2));
    col->addCart(new Cart(Cart::HEART, 3));
    col->addCart(new Cart(Cart::SPADES, 1));
    col->addCart(new Cart(Cart::SPADES, 2));
    col->addCart(new Cart(Cart::SPADES, 11));

    Cart *cart = col->getLastCart();
    if (col->size() != 6 or cart->getNumber() != 11 or cart->getType() != Cart::SPADES)
        cout << "FAIL1 rotateOne()" << endl;

    col->rotateOne();
    cart = col->getLastCart();
    if (col->size() != 6 or cart->getNumber() != 1 or cart->getType() != Cart::HEART)
        cout << "FAIL2 rotateOne()" << endl;

    col->rotateOne();
    cart = col->getLastCart();
    if (col->size() != 6 or cart->getNumber() != 2 or cart->getType() != Cart::HEART)
        cout << "FAIL3 rotateOne()" << endl;
    col->rotateOne();
    cart = col->getLastCart();
    if (col->size() != 6 or cart->getNumber() != 3 or cart->getType() != Cart::HEART)
        cout << "FAIL4 rotateOne()" << endl;
    col->rotateOne();
    cart = col->getLastCart();
    if (col->size() != 6 or cart->getNumber() != 1 or cart->getType() != Cart::SPADES)
        cout << "FAIL5 rotateOne()" << endl;
    col->rotateOne();
    cart = col->getLastCart();
    if (col->size() != 6 or cart->getNumber() != 2 or cart->getType() != Cart::SPADES)
        cout << "FAIL6 rotateOne()" << endl;
    col->rotateOne();
    cart = col->getLastCart();
    if (col->size() != 6 or cart->getNumber() != 11 or cart->getType() != Cart::SPADES)
        cout << "FAIL7 rotateOne()" << endl;
    cart = col->popLastCart();
    if (col->size() != 5 or cart->getNumber() != 11 or cart->getType() != Cart::SPADES)
        cout << "FAIL pop" << endl;
    cart = col->getLastCart();
    if (col->size() != 5 or cart->getNumber() != 2 or cart->getType() != Cart::SPADES)
        cout << "FAIL getLast" << endl;
}

int main(void) {
    testAddCart();
    testGetLastCart();
    testGetCartByIndex();
    testPopCart();
    testRotate();

    return (EXIT_SUCCESS);
}

