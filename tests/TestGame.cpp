/** 
 * @file Game.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * 
 * @date April 27, 2017, 12:32 AM
 */

#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include "../src/Game.h"

void printGame(Game *game) {
    string leftCol = "";
    string rightCol = "";
    if (!game->getRotateColumn()->size()) 
        leftCol = "X";
    else leftCol = "-";
    if (!game->getRotateColumn()->size(true)) 
        leftCol = "X";
    else leftCol = game->getRotateColumn()->getLastCart(true)->stringRepresentation();
    
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

void testCreateGame() {
    cout << "TestGame - testCreateGame" << endl;
    try {
        Game *game = new Game(1);
        if (game->getCoutDeskCols() != 1) cout << "FAIL countDeskCols" << endl;
        if (game->getCoutDeskCols() != 1) cout << "FAIL countDeskCols" << endl;
        ColumnOfCart *col = game->getResultColumn(0);
        if (col->size() != 0) cout << "FAIL resultCoumn" << endl;
        col = game->getResultColumn(1);
        if (col->size() != 0) cout << "FAIL1 resultCoumn" << endl;
        col = game->getResultColumn(2);
        if (col->size() != 0) cout << "FAIL2 resultCoumn" << endl;
        col = game->getResultColumn(3);
        if (col->size() != 0) cout << "FAIL3 resultCoumn" << endl;
    } catch (invalid_argument e) {
        cout << "FAIL createGame";
    }

    try {
        Game *game = new Game(9);
        if (game->getCoutDeskCols() != 9) cout << "FAIL2 countDeskCols" << endl;
        if (game->getCoutDeskCols() != 9) cout << "FAIL2 countDeskCols" << endl;
    } catch (invalid_argument e) {
        cout << "FAIL2 createGame";
    }

    try {
        Game *game = new Game(10);
        game->getCoutDeskCols();
        cout << "FAIL3 createGame";
    } catch (invalid_argument e) {
    }
}

void testColumnOnDesk() {
    cout << "TestGame - testColumnOnDesk" << endl;
    Game *game = new Game(7);

    if (game->getDeskColumn(0)->getCart(0) != game->getCart(0, 0))
        cout << "FAIL compare" << endl;
}

void testBaseMoves() {
    cout << "TestGame - testBaseMoves" << endl;
    Game *game = new Game(7);

    game->getCart(0, 0)->setNumber(1);
    if (!game->moveCarts(game->getDeskColumn(0), game->getResultColumn(1), 1, true))
        cout << "FAIL move" << endl;

    if (game->moveCarts(game->getDeskColumn(0), game->getResultColumn(1), 1))
        cout << "FAIL2 move" << endl;

    game->getCart(4, 4)->setNumber(6);
    game->getCart(4, 4)->setType(Cart::LETTER);
    game->getCart(5, 2)->setNumber(7);
    game->getCart(5, 3)->setNumber(6);
    game->getCart(5, 4)->setNumber(5);
    game->getCart(5, 5)->setNumber(4);
    game->getCart(5, 2)->setType(Cart::LETTER);
    game->getCart(5, 3)->setType(Cart::HEART);
    game->getCart(5, 4)->setType(Cart::LETTER);
    game->getCart(5, 5)->setType(Cart::HEART);

    if (game->moveCarts(game->getDeskColumn(5), game->getDeskColumn(4), 4))
        cout << "FAIL3 move" << endl;
    if (game->getDeskColumn(4)->size() != 5 or game->getDeskColumn(5)->size() != 6)
        cout << "FAIL size()" << endl;

    game->getCart(4, 4)->setNumber(8);
    game->getCart(4, 4)->setType(Cart::HEART);

    if (!game->getCart(5, 4)->isHide())
        cout << "FAIL hide" << endl;
    game->getCart(5, 4)->show();
    game->getCart(5, 3)->show();
    game->getCart(5, 2)->show();

    if (!game->moveCarts(game->getDeskColumn(5), game->getDeskColumn(4), 4))
        cout << "FAIL4 move" << endl;
}

void testOtherMoves() {
    cout << "TestGame - testOtherMoves" << endl;
    Game *game = new Game(7);

    game->getCart(4, 4)->setNumber(8);
    game->getCart(4, 4)->setType(Cart::HEART);
    game->getCart(5, 2)->setNumber(7);
    game->getCart(5, 3)->setNumber(6);
    game->getCart(5, 4)->setNumber(5);
    game->getCart(5, 5)->setNumber(4);
    game->getCart(5, 2)->setType(Cart::LETTER);
    game->getCart(5, 3)->setType(Cart::HEART);
    game->getCart(5, 4)->setType(Cart::LETTER);
    game->getCart(5, 5)->setType(Cart::HEART);

    game->getCart(5, 4)->show();
    game->getCart(5, 3)->show();
    game->getCart(5, 2)->show();

    if (!game->moveCartsOnDesk(5, 4, 4))
        cout << "FAIL move" << endl;

    if (game->getCart(5, 1)->isHide())
        cout << "FAIL autoShow" << endl;

    game->getCart(5, 1)->setNumber(1);
    game->getCart(5, 1)->setType(Cart::HEART);
    if (!game->moveCartsDeskToResult(5, 1))
        cout << "FAIL moveDeskToResult" << endl;

    if (game->getCart(5, 0)->isHide())
        cout << "FAIL autoShow" << endl;

    if (game->moveCartsDeskToResult(4, 1))
        cout << "FAIL1 moveDeskToResult" << endl;

    game->getRotateColumn()->getLastCart()->setNumber(2);
    game->getRotateColumn()->getLastCart()->setType(Cart::HEART);
    if (!game->moveCartsRotateToResult(1))
        cout << "FAIL moveRotateToResult" << endl;

    if (game->getResultColumn(1)->size() != 2)
        cout << "FAIL sizeResultCol" << endl;

    game->getRotateColumn()->getLastCart()->setNumber(1);
    if (!game->moveCartsRotateToResult(3))
        cout << "FAIL1 moveRotateToResult" << endl;


    game->getRotateColumn()->getLastCart()->setNumber(3);
    game->getRotateColumn()->getLastCart()->setType(Cart::LETTER);
    printGame(game);
    if (!game->moveCartsRotateToDesk(4))
        cout << "FAIL moveRotateToDesk" << endl;

    game->getCart(2, 2)->setNumber(13);
    game->getDeskColumn(0)->popLastCart();
    if (!game->moveCartsOnDesk(2, 1, 0))
        cout << "FAIL moveKing" << endl;
}

int main(void) {
    testCreateGame();
    testColumnOnDesk();
    testBaseMoves();
    testOtherMoves();
    return (EXIT_SUCCESS);
}