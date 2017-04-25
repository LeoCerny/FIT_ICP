/** 
 * @file Package.h
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 25, 2017, 2:54 PM
 */

#ifndef PACKAGE_H
#define PACKAGE_H

#include "Cart.h"

class Package {
public:
    Package();
    /**
     * Vytvoří balíček karet
     */
    void generateCards();
    
    /**
     * Zamíchá karty v balíčku
     */
    void mix();
    
    /**
     * Vrátí kartu z vrcholu balíčku
     * @return Poslední karta v poli karet
     */
    Cart *getCart();
    
private:
    std::vector <Cart*> carts;
    
    /**
     * Vyhledá hodnotu v zadaném vektoru
     * 
     * @param value
     * @param data
     * @return 
     */
    bool inArray(int value, std::vector<int> data);
};

#endif /* PACKAGE_H */

