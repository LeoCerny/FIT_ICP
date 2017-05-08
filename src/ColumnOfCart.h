/** 
 * @file ColumnOfCart.h
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 25, 2017, 2:53 PM
 */

#ifndef COLUMNOFCART_H
#define COLUMNOFCART_H

#include <vector>
#include <algorithm>
#include "Cart.h"

using namespace std;

class ColumnOfCart {
public:

    /**
     * Pridá kartu do sloupce
     * @param cart
     */
    void addCart(Cart *cart, bool right = false) {
        if (right)
            this->cartsRight.insert(this->cartsRight.end(), cart);
        else
            this->cartsLeft.insert(this->cartsLeft.end(), cart);
    }

    /**
     * Vráti poslední kartu v levem nebo pravem baličku
     * 
     * @param right
     * @return Poslední karta
     */
    Cart *getLastCart(bool right = false) {
        if (right)
            return this->getCart(this->cartsRight.size() - 1, true);
        return this->getCart(this->cartsLeft.size() - 1);
    };
    /**
     * Vráti kartu na určité pozici
     * 
     * @param index
     * @return Karta
     */
    Cart *getCart(unsigned int index, bool right = false);

    /**
     * Vráti poslední kartu ve sloupci a odebere ji
     * 
     * @return Posední karta
     */
    Cart *popLastCart(bool right = false) {
        Cart *cart;
        if (right) {
            cart = this->getLastCart(true);
            this->cartsRight.pop_back();
        } else {
            cart = this->getLastCart();
            this->cartsLeft.pop_back();
        }
        return cart;
    }

    /**
     * @return Počet karet
     */
    unsigned int size(bool right = false) {
        if (right)
            return this->cartsRight.size();
        return this->cartsLeft.size();
    }

    /**
     * Provede rotaci sloupce
     */
    void rotateOne() {
        if (size() > 0) {
            Cart *cart = popLastCart();
            addCart(cart, true);
            getLastCart(true)->show();
        } else if (size(true)) {
            while (size(true) > 0) {
                Cart *cart = popLastCart(true);
                addCart(cart);
                getLastCart()->hide();
            }
        }
    }

    bool canPush(Cart *cart, bool resultCol) {
        if (this->size() == 0) {
            if (resultCol)
                return cart->getNumberAsString() == "A";
            else
                return cart->getNumberAsString() == "K";
        } else {
            return this->getLastCart()->canPush(cart, resultCol);
        }
    }
    
    bool findCart(Cart *cart) {
        for (Cart *x : cartsLeft) {
            if (x == cart)
                return true;
        }
        return false;
    }

private:
    vector<Cart*> cartsLeft;
    vector<Cart*> cartsRight;
};

#endif /* COLUMNOFCART_H */

