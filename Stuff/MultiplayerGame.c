#include "MultiplayerGame.h"


/**
 * Creates a new multiplayer game
 * @param sizeX number of columns in the grid
 * @param sizeY number of rows in the grid
 * @param hardDifficulty is hard difficulty enabled
 */
void newMultiplayerGame(int sizeX, int sizeY, boolean hardDifficulty) {
    printf("Multiplayer | Rows : %d | Columns : %d | HardDifficulty : %s\n", sizeY, sizeX, hardDifficulty ? "true" : "false");
    MultiplayerGame game = {        //init the main structure
            .sizeX = sizeX,
            .sizeY = sizeY,
            .isHardDifficulty = hardDifficulty,
            .field = createAndInitializeMatrix(sizeX,sizeY),
            .handPlayer1 = (char***)malloc(sizeof(char)*5*3*3),
            .handPlayer2 = (char***)malloc(sizeof(char)*5*3*3),
            .isPlayer1Turn = rand()%2,
            .scorePlayer1 = 0,
            .scorePlayer2 = 0
    };
    for (int i = 0; i < 5; i++) {       //Init the players' hand
        game.handPlayer1[i] = createAndInitializeMatrix(3,3);
        game.handPlayer2[i] = createAndInitializeMatrix(3,3);

        initializeTile(&game.handPlayer1[i], hardDifficulty, TRUE, TRUE);
        initializeTile(&game.handPlayer2[i], hardDifficulty, TRUE, FALSE);
    }
    printTurn(TRUE, game.field, game.sizeX, game.sizeY, game.handPlayer1, game.scorePlayer1, game.scorePlayer2);
    playerTurn(&game.field, game.sizeX, game.sizeY, game.handPlayer1, game.scorePlayer1, TRUE, TRUE);
    printTurn(FALSE, game.field, game.sizeX, game.sizeY, game.handPlayer2, game.scorePlayer1, game.scorePlayer2);
    /*
    printLevel(sizeX,sizeY,game.field);
    printHand(TRUE, game.handPlayer1);
    printHand(FALSE, game.handPlayer2);
    */
//free everything
    free3dMatrix(5,3,&game.handPlayer1);
    free3dMatrix(5,3,&game.handPlayer2);
    freeMatrix(sizeX,&game.field);
}