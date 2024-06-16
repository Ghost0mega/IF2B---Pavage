#ifndef STUFF_MULTIPLAYERGAME_H
#define STUFF_MULTIPLAYERGAME_H
#include "Utilities.h"
#include "save.h"

typedef struct MultiplayerGame {
    boolean isHardDifficulty;
    int sizeX;
    int sizeY;
    char** field;           //rows = x, columns = y
    char*** handPlayer1;
    char*** handPlayer2;
    int scorePlayer1;
    int scorePlayer2;
    boolean isPlayer1Turn;  //false = is player 2's turn
} MultiplayerGame;

/**
 * The main loop of the multiplayer game
 * @param game the game to play
 */
void multiplayerGameLoop(MultiplayerGame* game);

/**
 * Creates a new multiplayer game
 * @param sizeX number of columns in the grid
 * @param sizeY number of rows in the gridd
 * @param hardDifficulty is hard difficulty enabled
 */
void newMultiplayerGame(int sizeX, int sizeY, boolean hardDifficulty);
#endif //STUFF_MULTIPLAYERGAME_H