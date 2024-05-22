//
// Created by Amber GUYENOT-COSIO on 21/05/2024.
//
#ifndef STUFF_SINGLEPLAYERGAME_H
#define STUFF_SINGLEPLAYERGAME_H

#include "Utilities.h"


struct MultiplayerGame {
    boolean isHardDifficulty;
    int x;
    int y;
    char** field;       //rows = x, columns = y
    char hand[5][3][3];
    int score1;
};



/**
 * Creates a new single player game
 * @param rows number of rows in the grid
 * @param columns number of columns in the grid
 * @param hardDifficulty is hard difficulty enabled
 */
void loadNewSingleplayerGame(int rows, int columns, boolean hardDifficulty);

#endif //STUFF_SINGLEPLAYERGAME_H
