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
    //Verif
    printLevel(sizeX,sizeY,game.field);
    printf("PLAYER 1\n");
    for (int i = 0; i < 5; i++){
        printLevel(3,3,game.handPlayer1[i]);
    }
    printf("PLAYER 2\n");
    for (int i = 0; i < 5; i++){
        printLevel(3,3,game.handPlayer2[i]);
    }

//free everything
    for (int i = 0; i < 5; i++) {
        for (int x = 0; x < 3; x++) {
            free(game.handPlayer1[i][x]);
            game.handPlayer1[i][x] = NULL;
        }
        free(game.handPlayer1[i]);
        game.handPlayer1[i] = NULL;
    }
    free(game.handPlayer1);
    game.handPlayer1 = NULL;

    for (int i = 0; i < 5; i++) {
        for (int x = 0; x < 3; x++) {
            free(game.handPlayer2[i][x]);
            game.handPlayer2[i][x] = NULL;
        }
        free(game.handPlayer2[i]);
        game.handPlayer2[i] = NULL;
    }
    free(game.handPlayer2);
    game.handPlayer2 = NULL;

    freeMatrix(sizeX,&game.field);
}