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

    string getNumberAsString() {
        switch (this->number) {
            case 1:
                return "A";
            case 11:
                return "J";
            case 12:
                return "Q";
            case 13:
                return "K";
            default: return to_string(this->number);
        }
    }

    /**
     * @return Typ karty
     */
    int getType() {
        return this->type;
    };

    /**
     * Otočí kartu lícem nahoru
     */
    void show() {
        this->isHidden = 0;
    }

    /**
     * Otočí kartu rubem nahoru
     */
    void hide() {
        this->isHidden = 1;
    }

    /**
     * Ověří zda může danou kartu položit na tuto
     * 
     * @param resultCol Jedná se o odkládací sloupec
     * @return Úspěch operace
     */
    bool canPush(Cart *cart, bool resultCol = false) {
        if (!((!resultCol and this->number == cart->getNumber() + 1) or (resultCol and this->number + 1 == cart->getNumber())))
            return false;
        switch (this->type) {
            case Cart::HEART:
            case Cart::SQUARE:
                if (!((!resultCol and (cart->getType() == Cart::LETTER || cart->getType() == Cart::SPADES)) or (resultCol and this->type == cart->getType())))
                    return false;
                break;
            case Cart::LETTER:
            case Cart::SPADES:
                if (!((!resultCol and (cart->getType() == Cart::HEART || cart->getType() == Cart::SQUARE)) or (resultCol and this->type == cart->getType())))
                    return false;
                break;
        }
        return true;
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
        string type;
        switch (this->type) {
            case Cart::HEART:
                type = "\u2665";
                break;
            case Cart::LETTER:
                type = "\u2660";
                break;
            case Cart::SPADES:
                type = "\u2663";
                break;
            default:
                type = "\u2666";
        }
        return (this->isHidden) ? "---" : this->getNumberAsString() + type;
    }
private:
    int type;
    int number;
    int isHidden;

};

#endif /* CART_H */

