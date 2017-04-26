/** 
 * @file Cart.h
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 25, 2017, 2:34 PM
 */

#ifndef CART_H
#define CART_H

#include <iostream>

using namespace std;

class Cart {
public:
    static const int SPADES = 0;
    static const int HEART = 1;
    static const int LETTER = 2;
    static const int SQUARE = 3;

    /**
     * 
     * @param type Typ karty
     * @param number Číslo karty
     */
    Cart(int type, int number);

    /**
     * Nastaví číslo karty a provede validaci
     * 
     * @param number
     * @throw std::invalid_argument
     */
    void setNumber(int number);

    /**
     * Nastaví druh kraty a provede validaci
     * 
     * @param type
     * @throw std::invalid_argument
     */
    void setType(int type);

    /**
     * @return Číslo karty
     */
    int getNumber() {
        return this->number;
    };

    /**
     * @return Typ karty
     */
    int getType() {
        return this->type;
    };

    /**
     * Otočí kartu lícem nahoru
     */
    void show() { this->isHidden = 0; }

    /**
     * Otočí kartu rubem nahoru
     */
    void hide() {
        this->isHidden = 1;
    }

    friend ostream& operator<<(std::ostream &strm, Cart *cart) {
        strm << cart->stringRepresentation();
        return strm;
    }

    /**
     * Vratí textovou reprezetaci karty
     * 
     * @return Textová reprezentace
     */
    string stringRepresentation() {
        return (this->isHidden) ? "---" : to_string(this->number) + "-" + to_string(this->type);
    }
private:
    int type;
    int number;
    int isHidden;

};

#endif /* CART_H */

