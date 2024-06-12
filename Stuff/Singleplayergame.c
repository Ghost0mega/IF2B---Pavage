//
// Created by Amber GUYENOT-COSIO on 21/05/2024.
//

#include "Singleplayergame.h"

/**
 * Creates a new single player game
 * @param sizeX number of columns in the grid
 * @param sizeY number of rows in the grid
 * @param hardDifficulty is hard difficulty enabled
 */
void newSingleplayerGame(int sizeX, int sizeY, boolean hardDifficulty) {
    printf("Singleplayer | Rows : %d | Columns : %d | HardDifficulty : %s\n", sizeY, sizeX, hardDifficulty ? "true" : "false");

    Singleplayergame game = {
            .sizeX = sizeX,
            .sizeY = sizeY,
            .isHardDifficulty = hardDifficulty,
            .field = createAndInitializeMatrix(sizeX,sizeY),
            .hand = (char***) malloc(sizeof(char)*5*3*3),
            .score = 0
    };

    for (int i = 0; i < 5; i++) {
        game.hand[i] = createAndInitializeMatrix(3,3);
        initializeTile(&game.hand[i],hardDifficulty,FALSE,TRUE);
    }

    //free everything
    for (int i = 0; i < 5; i++) {
        for (int x = 0; x < 3; x++) {
            free(game.hand[i][x]);
            game.hand[i][x] = NULL;
        }
        free(game.hand[i]);
        game.hand[i] = NULL;
    }
    free(game.hand);
    game.hand = NULL;
    freeMatrix(sizeX,&game.field);

}