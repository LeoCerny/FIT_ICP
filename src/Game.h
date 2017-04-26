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
#include "ColumnOfCart.h"

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
    unsigned int getCoutDeskCols() { return this->countDeskCols; }
    
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
    string rotateColumnToString() { return this->rotateColumn->getLastCart()->stringRepresentation(); }
    
    /**
     * @return Textová reprezentace odkládacího místa balíčku
     */
    string resultColumnToString(unsigned int index);
    
    /**
     * Vrací kartu na určité pozici
     * 
     * @param index
     * @param row
     * @return Hrací karta
     */
    Cart *getCart(unsigned int index, unsigned int row) { return this->getDeskColumn(index)->getCart(row); }
    
    bool isEnd() { return false; }
private:
    ColumnOfCart *rotateColumn;
    vector<ColumnOfCart*> results;
    vector<ColumnOfCart*> desk;
    unsigned int countDeskCols;
    
    
    /**
     * Vygeneruje hru
     */
    void createGame();
    
    /**
     * @param index
     * @return Hrací sloupec
     */
    ColumnOfCart *getDeskColumn(unsigned int index);
};

#endif /* GAME_H */

