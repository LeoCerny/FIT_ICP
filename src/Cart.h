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
        this->isHidden = false;
    }

    /**
     * Otočí kartu rubem nahoru
     */
    void hide() {
        this->isHidden = true;
    }

    /**
     * @return Je rubem nahoře
     */
    bool isHide() {
        return this->isHidden;
    }

    /**
     * Ověří zda může danou kartu položit na tuto
     * 
     * @param resultCol Jedná se o odkládací sloupec
     * @return Úspěch operace
     */
    bool canPush(Cart *cart, bool resultCol = false) {
        if (resultCol) {
            return (cart->type == type && cart->getNumber() == number + 1);
        } else {
            switch (type) {
                case Cart::HEART:
                case Cart::SQUARE:
                    return ((cart->getType() == Cart::LETTER || cart->getType() == Cart::SPADES) and (number == cart->getNumber() + 1));
                case Cart::LETTER:
                case Cart::SPADES:
                    return ((cart->getType() == Cart::HEART || cart->getType() == Cart::SQUARE) and (number == cart->getNumber() + 1));
            }
        }

        return false;
    }

    friend ostream& operator<<(std::ostream &strm, Cart *cart) {
        strm << cart->stringRepresentation();
        return strm;
    }

    bool operator==(Cart *cart) {
        return (this->number == cart->getNumber() and this->type == cart->getType() and this->isHidden == cart->isHide());
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
            case Cart::SPADES:
                type = "\u2660";
                break;
            case Cart::LETTER:
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
    bool isHidden;

};

#endif /* CART_H */

