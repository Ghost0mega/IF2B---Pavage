#ifndef STUFF_MULTIPLAYERGAME_H
#define STUFF_MULTIPLAYERGAME_H
#include "Utilities.h"

struct MultiplayerGame {
    boolean isHardDifficulty;
    int x;
    int y;
    char** field;           //rows = x, columns = y
    char** handPlayer1[5];
    char** handPlayer2[5];
    int scorePlayer1;
    int scorePlayer2;
    boolean isPlayer1Turn;  //false = is player 2's turn
};

/**
 * Creates a new multiplayer game
 * @param rows number of rows in the grid
 * @param columns number of columns in the grid
 * @param hardDifficulty is hard difficulty enabled
 */
void loadNewMultiplayerGame(int rows, int columns, boolean hardDifficulty);
#endif //STUFF_MULTIPLAYERGAME_H
