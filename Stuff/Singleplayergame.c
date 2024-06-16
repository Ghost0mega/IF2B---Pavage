#include "Singleplayergame.h"

/**
 * The main loop of the single player game
 * @param game the game to play
 */
void singleplayerGameLoop(Singleplayergame* game) {
    boolean gameIsOver = FALSE;
    boolean gaveUp = FALSE;
    boolean isFirstTurn = TRUE;
    do {
        printTurn(TRUE, game->field, game->sizeX, game->sizeY, game->hand, game->score, -1);
        game->score = playerTurn(&game->field, game->sizeX, game->sizeY, game->hand, game->score, isFirstTurn, game->isHardDifficulty, FALSE, TRUE);
        if (game->score < 0) {
            gaveUp = TRUE;
            game->score = game->score * -1;
        }
        if (gaveUp) {
            gameIsOver = TRUE;
            printf("You either gave up or couldn't place any more tiles, the game is over.\n");
        }
        isFirstTurn = FALSE;
    } while (!gameIsOver);
    printf("You finished the game with a score of %d\n", game->score);
}

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
            .hand = (char***)malloc(sizeof(char)*5*3*3),
            .score = 0
    };

    for (int i = 0; i < 5; i++) {
        game.hand[i] = createAndInitializeMatrix(3,3);
        initializeTile(&game.hand[i],hardDifficulty,FALSE,TRUE);
    }
    singleplayerGameLoop(&game);

    //free everything
    free3dMatrix(5,3,&game.hand);
    freeMatrix(sizeX,&game.field);

}