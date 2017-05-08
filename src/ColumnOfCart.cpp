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

Cart *ColumnOfCart::getCart(unsigned int index, bool right) {
    if ((right == false && (this->cartsLeft.empty() || this->cartsLeft.size() <= index)) || (right && (this->cartsRight.empty() || this->cartsRight.size() <= index)))
        throw invalid_argument("Prazdný sloupec");
    if (right)
        return this->cartsRight.at(index);
    return this->cartsLeft.at(index);
}

