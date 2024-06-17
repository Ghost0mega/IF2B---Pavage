#ifndef STUFF_SINGLEPLAYERGAME_H
#define STUFF_SINGLEPLAYERGAME_H

#include "Utilities.h"
#include "save.h"

typedef struct {
    boolean isHardDifficulty;
    int sizeX;
    int sizeY;
    char** field;       //rows = x, columns = y
    char*** hand;
    int score;
} Singleplayergame;

/**
 * The main loop of the single player game
 * @param game the game to play
 */
void singleplayerGameLoop(Singleplayergame* game);

/**
 * Creates a new single player game
 * @param sizeX number of columns in the grid
 * @param sizeY number of rows in the grid
 * @param hardDifficulty is hard difficulty enabled
 */
void newSingleplayerGame(int sizeX, int sizeY, boolean hardDifficulty);

/**
 * Load and play singleplayer game from a file
 * @param path the path to the save file
 */
void loadSingleplayerGame(char* path);
#endif //STUFF_SINGLEPLAYERGAME_H
