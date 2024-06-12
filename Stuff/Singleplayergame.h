//
// Created by Amber GUYENOT-COSIO on 21/05/2024.
//
#ifndef STUFF_SINGLEPLAYERGAME_H
#define STUFF_SINGLEPLAYERGAME_H

#include "Utilities.h"


struct SingleplayerGame {
    boolean isHardDifficulty;
    int sizeX;
    int sizeY;
    char** field;       //rows = x, columns = y
    char** hand[5];
    int score;
};



/**
 * Creates a new single player game
 * @param sizeX number of columns in the grid
 * @param sizeX number of rows in the grid
 * @param hardDifficulty is hard difficulty enabled
 */
void newSingleplayerGame(int sizeX, int sizeY, boolean hardDifficulty);

/**
 * Initialise the game
 * @param sizeX number of columns in the grid
 * @param sizeX number of rows in the grid
 */
//void initialiseGrid

#endif //STUFF_SINGLEPLAYERGAME_H
