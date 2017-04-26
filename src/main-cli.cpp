/** 
 * @file main.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 25, 2017, 1:32 PM
 */

#include <iostream>
#include <stdexcept>
#include "Game.h"
#include "Package.h"

using namespace std;

/**
 * Napíše nápovědu na STDOUT
 */
void printHelp() {
    cout << "HELP" << endl;
    cout << "\t Z jednoho sloupce na druhy sloupec na hracy desce" << endl;
    cout << "\t\t 2-2 -> 3 Vezme dve karty z druheho sloupce a polozi je na treti sloupec" << endl;
    cout << "\t Z rolovaciho balicku na sloupec na hraci desce" << endl;
    cout << "\t\t R -> 3   Vezme kartu z rolovaciho balicku a polozi ho na treti sloupec" << endl;
    cout << "\t Z Rolovaciho balicku na odkladaci polchu" << endl;
    cout << "\t\t R -> S1  Vezme kartu z rolovaciho balicku a odlozi ji na 1. odkladaci sloupec" << endl;
    cout << "\t Z jednodho sloupce na hraci desce na odkladaci sloupec" << endl;
    cout << "\t\t 2 -> S3  Vezme kartu ze sloupce na hraci desce a odlozi ho na odkladaci sloupec" << endl;
    cout << "\t Z odkladaciho balicku na hraci sloupec" << endl;
    cout << "\t\t S2 -> 3  Vezme kartu z 2. odkladaciho balicku a vlozi ji na 3. hraci sloupec" << endl;
    
          
            
}

void printGame(Game *game) {
    cout << "Rolovaci balicek: " << game->rotateColumnToString() << endl;
    cout << "Odklaci baliek 1: " << game->resultColumnToString(0) << endl;
    cout << "Odklaci baliek 2: " << game->resultColumnToString(1) << endl;
    cout << "Odklaci baliek 3: " << game->resultColumnToString(2) << endl;
    cout << "Odklaci baliek 4: " << game->resultColumnToString(3) << endl;

    cout << endl;

    cout << "Hrací sloupce:" << endl;
    unsigned int row = 0;
    while (row < game->getMaxHeightCol()) {
        if (row == 0) {
            for (unsigned int col = 0; col < game->getCoutDeskCols(); col++) {
                cout << "\t " << col + 1 << ".";
            }
            cout << endl;
        }
        for (unsigned int col = 0; col < game->getCoutDeskCols(); col++) {
            try {
                cout << "\t" << game->getCart(col, row);
            } catch (invalid_argument e) {
                cout << "\t    ";
            }
        }
        cout << endl;
        row++;
    }
}

bool handleInput(Game *game, string inputData)  {
    //source
    unsigned int row;
    unsigned int col;
    
}

int main() {
    // pro generování zcela náhodných čísel
    srand(time(NULL));
    
    // vstup od uživatele
    string inputData;
    try {
        Game *game = new Game(6);
        printHelp();
        while(!game->isEnd()) {
            printGame(game);
            inputData.clear();
            cin >> inputData;
            handleInput(game, inputData);
        }
    } catch (exception e) {
        return 1;
    }
    //game->undo();
    return 0;
}
