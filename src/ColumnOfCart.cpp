/** 
 * @file ColumnOfCart.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 25, 2017, 2:53 PM
 */

#include <vector>
#include <stdexcept>

#include "ColumnOfCart.h"

using namespace std;

Cart *ColumnOfCart::getCart(unsigned int index) {
    if (this->carts.empty() || this->carts.size() <= index )
        throw invalid_argument("Prazdný sloupec");
    return this->carts.at(index);
}

