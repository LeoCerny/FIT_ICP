/** 
 * @file main.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 25, 2017, 1:32 PM
 */

#include <iostream>
#include <stdexcept>
#include <regex>
#include "Game.h"
#include "Package.h"

using namespace std;

Game *game;
/**
 * Napíše nápovědu na STDOUT
 */
void printHelp() {
    cout << "\thelp - napoveda" << endl;
    cout << "\tnew - nova hra" << endl;
    cout << "\tsave path - ulozi hru" << endl;
    cout << "\tload path - nacte hru" << endl;
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
    cout << "\trotate - provede rotaci balicku" << endl;
}

void printGame(Game *game) {
    string leftCol = "";
    string rightCol = "";
    if (!game->getRotateColumn()->size()) 
        leftCol = "X";
    else leftCol = "-";
    if (!game->getRotateColumn()->size(true)) 
        rightCol = "X";
    else rightCol = game->getRotateColumn()->getLastCart(true)->stringRepresentation();
    
    cout << "Rolovaci balicek: " << leftCol << " " << rightCol << endl;
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

bool parseInput(Game *game, string input) {
    smatch match;
    bool error = false;
    regex expr1("^([1-9])-([1-9][0-9]{0,2})->([1-9])$");
    regex expr2("^R->([1-9])$");
    regex expr3("^R->S([1-4])$");
    regex expr4("^([1-9])->S([1-4])$");
    regex expr5("^S([1-4])->([1-9])$");

    if (regex_match(input, expr1)) {
        regex_search(input, match, expr1);
        if (!game->moveCartsOnDesk((unsigned int) stoul(match[1]) - 1, (unsigned int) stoul(match[2]), (unsigned int) stoul(match[3]) - 1))
            cout << endl << "CHYBA: Nepovolený tah" << endl;
    } else if (regex_match(input, expr2)) {
        regex_search(input, match, expr2);
        if (!game->moveCartsRotateToDesk((unsigned int) stoul(match[1]) - 1))
            cout << endl << "CHYBA: Nepovolený tah" << endl;
    } else if (regex_match(input, expr3)) {
        regex_search(input, match, expr3);
        if (!game->moveCartsRotateToResult((unsigned int) stoul(match[1]) - 1))
            cout << endl << "CHYBA: Nepovolený tah" << endl;
    } else if (regex_match(input, expr4)) {
        regex_search(input, match, expr4);
        if (!game->moveCartsDeskToResult((unsigned int) stoul(match[1]) - 1, (unsigned int) stoul(match[2]) - 1))
            cout << endl << "CHYBA: Nepovolený tah" << endl;
    } else if (regex_match(input, expr5)) {
        regex_search(input, match, expr5);
    } else return false;
    return true;
}

bool handleInput(string inputData) {
    string path;
        
    if (inputData == "help") {
        printHelp();
    } else if (inputData == "rotate") {
        game->rotate();
        return true;
    } else if (inputData == "new") {
        game = new Game(7);
        return true;
    } else if (inputData == "undo") {
        game->undo();
        return true;
    } else if (inputData == "load") {
        cout << endl << "PATH:";
        path.clear();
        game = new Game(7, false);
        cin >> path;
        if (game->load(path)) {
            cout << "OK - nahrano" << endl;
        } else cout << "CHYBA - nepodarilo se soubor nahrat" << endl;
        return true;
    } else if (inputData == "save") {
        cout << endl << "PATH:";
        path.clear();
        cin >> path;
        if (game->save(path)) {
            cout << "OK - ulozeno" << endl;
        } else cout << "CHYBA - nepodarilo se hru ulozit" << endl;
        return true;
    } else
        return parseInput(game, inputData);
}

int main() {
    // pro generování zcela náhodných čísel
    srand(time(NULL));

    // vstup od uživatele
    string inputData;
    try {
        game = new Game(7);
        printHelp();
        while (!game->isEnd()) {
            printGame(game);
            inputData.clear();
            cin >> inputData;
            if (!handleInput(inputData)) {
                cout << "no" << endl;
            }
        }
        cout << endl << endl << "KONEC HRY" << endl;
    } catch (exception e) {
        return 1;
    }
    return 0;
}
