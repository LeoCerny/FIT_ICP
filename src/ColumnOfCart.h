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
    void addCart(Cart *cart) {
        this->carts.insert(this->carts.end(), cart);
    }

    Cart *getLastCart() {
        return this->getCart(this->carts.size() - 1);
    };
    /**
     * Vráti kartu na určité pozici
     * 
     * @param index
     * @return Karta
     */
    Cart *getCart(unsigned int index);

    /**
     * Vráti poslední kartu ve sloupci a odebere ji
     * 
     * @return Posední karta
     */
    Cart *popLastCart() {
        Cart *cart = this->getLastCart();
        this->carts.pop_back();
        return cart;
    }

    /**
     * @return Počet karet
     */
    unsigned int size() {
        return this->carts.size();
    }

    /**
     * Provede rotaci sloupce
     */
    void rotateOne() {
        rotate(this->carts.begin(), this->carts.begin() + 1, this->carts.end());
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

private:
    vector<Cart*> carts;


};

#endif /* COLUMNOFCART_H */

