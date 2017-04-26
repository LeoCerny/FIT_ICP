/** 
 * @file Package.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * 
 * @date April 27, 2017, 12:02 AM
 */

#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include "../src/Package.h"
#include "../src/Cart.h"

void testGetCart() {
    cout << "TestPackage - testGetCart" << endl;
    Package *package = new Package;
    if (package->isEmpty())
        cout << "FAIL isEmpty()" << endl;

    unsigned int count = 0;
    try {
        while (true) {
            package->getCart();
            count++;
        }
        cout << "FAIL1 count" << endl;
    } catch (invalid_argument e) {
        if (count != 4 * 13)
            cout << "FAIL2 count" << endl;
        if (!package->isEmpty())
            cout << "FAIL2 isEmpty()" << endl;
    }
}

int main(void) {
    testGetCart();
    return (EXIT_SUCCESS);
}