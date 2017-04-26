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
#include "Cart.h"

using namespace std;

class ColumnOfCart {
public:
    ColumnOfCart();
    void addCart(Cart *cart);
    void rotate(int num);
    Cart *getLastCart() { return this->getCart(this->carts.size() - 1); };
    Cart *getCart(unsigned int index);
    unsigned int size() { return this->carts.size(); }
private:
    vector<Cart*> carts;
    unsigned int index;
    void rotateOne();
};

#endif /* COLUMNOFCART_H */

