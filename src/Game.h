/** 
 * @file Game.h
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 26, 2017, 1:03 AM
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <stdexcept>
#include "ColumnOfCart.h"
#include "Cart.h"

using namespace std;

class Game {
public:
    /**
     * @param countDeskCols Počet sloupců s kartami na hrací ploše
     */
    Game(unsigned int countDeskCols);

    /**
     * @return Počet sloupců karet na hrací desce
     */
    unsigned int getCoutDeskCols() {
        return this->countDeskCols;
    }

    /**
     * @return Maximální výšku sloupců
     */
    unsigned int getMaxHeightCol();
    /**
     * Uloží rozehranou hru
     */
    void save();

    /**
     * Vratí tah zpět
     */
    void undo();

    /**
     * @return Textová reprezentace rolovacího balíčku
     */
    string rotateColumnToString() {
        return this->rotateColumn->getLastCart()->stringRepresentation();
    }

    /**
     * @return Textová reprezentace odkládacího místa balíčku
     */
    string resultColumnToString(unsigned int index);

    /**
     * Vrací kartu na určité pozici v hracím sloupci
     * 
     * @param index
     * @param row
     * @return Hrací karta
     */
    Cart *getCart(unsigned int index, unsigned int row) {
        return this->getDeskColumn(index)->getCart(row);
    }

    /**
     * @return Konec hry?
     */
    bool isEnd() {
        return false;
    }

    /**
     * Přesune několik karet ze zdrojového sloupce na cílový
     * 
     * @param srcCol Zdrojový sloupec
     * @param count  Počet karet
     * @param destCol Cílový sloupec
     * @return Úspěch
     */
    bool moveCartsOnDesk(unsigned int srcCol, unsigned int count, unsigned int destCol);

    /**
     * Přesune kartu z hrací desky na odkládací sloupec
     * 
     * @param srcCol
     * @param destCol
     * @return 
     */
    bool moveCartsDeskToResult(unsigned int srcCol, unsigned int destCol);

    /**
     * Přesune kartu z rotujícího balíčku na hrací desku
     * 
     * @param destCol
     * @return 
     */
    bool moveCartsRotateToDesk(unsigned int destCol) {
        ColumnOfCart *dest = this->getDeskColumn(destCol);
        if (dest->canPush(this->rotateColumn->getLastCart(true), false)) {
            dest->addCart(this->rotateColumn->popLastCart(true));
            return true;
        }
        return false;
    }

    /**
     * Přesune kartu z rotujícího balíčku na odkládací sloupec
     * 
     * @param srcCol
     * @param destCol
     * @return 
     */
    bool moveCartsRotateToResult(unsigned int destCol) {
        ColumnOfCart *dest = this->getResultColumn(destCol);
        if (dest->canPush(this->rotateColumn->getLastCart(true), true)) {
            dest->addCart(this->rotateColumn->popLastCart(true));
            return true;
        }
        return false;
    }

    /**
     * Přesune určitý počet karet ze zdrojového sloupce na cílový
     * 
     * @param src Zdrojový sloupec
     * @param dest Cílový sloupec
     * @param count Pošet karet k přesunutí
     * @param resultCol Jedná se o odkládací sloupec
     * @return 
     */
    bool moveCarts(ColumnOfCart *src, ColumnOfCart *dest, unsigned int count, bool = false);

    /**
     * Provede rotaci rotačního sloupce
     */
    void rotate() {

        this->rotateColumn->rotateOne();
    }

    /**
     * Vrátí hrací sloupec podle indexu
     * 
     * @param index
     * @return Hrací sloupec
     */
    ColumnOfCart *getDeskColumn(unsigned int index);

    /**
     * Vráti odkládací sloupec podle indexu
     * 
     * @param index
     * @return Odkládací sloupec
     */
    ColumnOfCart *getResultColumn(unsigned int index);

    /**
     * @return Rotující sloupec
     */
    ColumnOfCart *getRotateColumn() {
        return this->rotateColumn;
    }
private:
    ColumnOfCart *rotateColumn;
    vector<ColumnOfCart*> results;
    vector<ColumnOfCart*> desk;
    unsigned int countDeskCols;


    /**
     * Vygeneruje hru
     */
    void createGame();


};

#endif /* GAME_H */

