#include "MultiplayerGame.h"



/**
 * The main loop of the multiplayer game
 * @param game the game to play
 */
void multiplayerGameLoop(MultiplayerGame* game) {

    boolean player1gaveUp = FALSE;
    boolean player2gaveUp = FALSE;
    boolean gameIsOver = FALSE;
    do {
        if (game->isPlayer1Turn) {
            printTurn(TRUE, game->field, game->sizeX, game->sizeY, game->handPlayer1, game->scorePlayer1, game->scorePlayer2);
            game->scorePlayer1 = playerTurn(&game->field, game->sizeX, game->sizeY, game->handPlayer1, game->scorePlayer1, TRUE, game->isHardDifficulty, TRUE, TRUE);
            if (game->scorePlayer1 < 0) {
                player1gaveUp = TRUE;
                game->scorePlayer1 = game->scorePlayer1 * -1;
            }
            game->isPlayer1Turn = player2gaveUp ? TRUE : FALSE;
        } else {
            printTurn(FALSE, game->field, game->sizeX, game->sizeY, game->handPlayer2, game->scorePlayer2, game->scorePlayer1);
            game->scorePlayer2 = playerTurn(&game->field, game->sizeX, game->sizeY, game->handPlayer2, game->scorePlayer2, TRUE, game->isHardDifficulty, TRUE, FALSE);
            if (game->scorePlayer2 < 0) {
                player2gaveUp = TRUE;
                game->scorePlayer2 = game->scorePlayer2 * -1;
            }
            game->isPlayer1Turn = player1gaveUp ? FALSE : TRUE;
        }
        if (player1gaveUp && player2gaveUp) {
            gameIsOver = TRUE;
            printf("Both players either gave up or couldn't place any more tiles, the game is over.\n");
        }
    } while (!gameIsOver);
    if (game->scorePlayer1 > game->scorePlayer2) {
        printf("Player 1 wins with a score of %d over %d\n", game->scorePlayer1, game->scorePlayer2);
    } else if (game->scorePlayer1 < game->scorePlayer2) {
        printf("Player 2 wins with a score of %d over %d\n", game->scorePlayer2, game->scorePlayer1);
    } else {
        printf("It's a draw!\n");
    }
}


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
    multiplayerGameLoop(&game);
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