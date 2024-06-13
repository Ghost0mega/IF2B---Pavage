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
    printTurn(TRUE, game.field, game.sizeX, game.sizeY, game.hand, game.score, -1);


    //free everything
    free3dMatrix(5,3,&game.hand);
    freeMatrix(sizeX,&game.field);

}