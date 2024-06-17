#include "MultiplayerGame.h"



/**
 * The main loop of the multiplayer game
 * @param game the game to play
 */
void multiplayerGameLoop(MultiplayerGame* game) {

    boolean player1gaveUp = FALSE;
    boolean player2gaveUp = FALSE;
    boolean gameIsOver = FALSE;
    boolean hasSaved = FALSE;
    boolean isFirstTurn = TRUE;
    do {
        if (game->isPlayer1Turn) {
            if (!canPlayerPlay(game->field, game->sizeX, game->sizeY, game->handPlayer1) && !isFirstTurn) {
                printf("Player 1 couldn't place any more tiles, game over.\n");
                player1gaveUp = TRUE;
            } else {
                printTurn(TRUE, game->field, game->sizeX, game->sizeY, game->handPlayer1, game->scorePlayer1,
                          game->scorePlayer2);
                game->scorePlayer1 = playerTurn(&game->field, game->sizeX, game->sizeY, game->handPlayer1,
                                                game->scorePlayer1, isFirstTurn, game->isHardDifficulty, TRUE, TRUE);
                if (game->scorePlayer1 < 0) {
                    player1gaveUp = TRUE;
                    game->scorePlayer1 = game->scorePlayer1 * -1;
                }
            }
            game->isPlayer1Turn = player2gaveUp ? TRUE : FALSE;
            if (game->scorePlayer1 > 1000) {
                hasSaved = TRUE;
                game->scorePlayer1 = game->scorePlayer1 - 1000;
            }
        } else {
            if (!canPlayerPlay(game->field, game->sizeX, game->sizeY, game->handPlayer2) && !isFirstTurn) {
                printf("Player 2 couldn't place any more tiles, game over.\n");
                player2gaveUp = TRUE;
            } else {
                printTurn(FALSE, game->field, game->sizeX, game->sizeY, game->handPlayer2, game->scorePlayer2,
                          game->scorePlayer1);
                game->scorePlayer2 = playerTurn(&game->field, game->sizeX, game->sizeY, game->handPlayer2,
                                                game->scorePlayer2, isFirstTurn, game->isHardDifficulty, TRUE, FALSE);
                if (game->scorePlayer2 < 0) {
                    player2gaveUp = TRUE;
                    game->scorePlayer2 = game->scorePlayer2 * -1;
                }
            }
            game->isPlayer1Turn = player1gaveUp ? FALSE : TRUE;
            if (game->scorePlayer2 > 1000) {
                hasSaved = TRUE;
                game->scorePlayer2 = game->scorePlayer2 - 1000;
            }
        }
        if (player1gaveUp && player2gaveUp) {
            gameIsOver = TRUE;
            printf("Both players either gave up or couldn't place any more tiles, the game is over.\n");
        }
        isFirstTurn = FALSE;
    } while (!gameIsOver && !hasSaved);
    if (!gameIsOver) {
        printf("saving game...\n");
        saveMultiplayerGame(game->isHardDifficulty, game->sizeX, game->sizeY, game->field, game->handPlayer1,
                            game->handPlayer2, game->scorePlayer1, game->scorePlayer2, game->isPlayer1Turn);
        printf("Game saved, returning to main menu\n");
    } else {
        if (game->scorePlayer1 > game->scorePlayer2) {
            printf("Player 1 wins with a score of %d over %d\n", game->scorePlayer1, game->scorePlayer2);
        } else if (game->scorePlayer1 < game->scorePlayer2) {
            printf("Player 2 wins with a score of %d over %d\n", game->scorePlayer2, game->scorePlayer1);
        } else {
            printf("It's a draw!\n");
        }
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

/**
 * Load and play multiplayer game from a file
 * @param game the game to load into
 * @param path the path to the save file
 */
void loadMultiplayerGame(char* path) {
    printf("Attempting to load multiplayer game from %s\n", path);
    FILE* fptr = fopen(path, "r");
    if (fptr == NULL) {
        fprintf(stderr, "ERROR: Couldn't open the file\n");
        return;
    }
    printf(" - File opened\n");
    char* type = (char*)malloc(sizeof(char)*20);
    fscanf(fptr, "%s\n", type);
    if (strcmp(type, "Multiplayer") != 0) {
        fprintf(stderr, "ERROR: The file is not a multiplayer save file\n");
        free(type);
        fclose(fptr);
        return;
    }
    printf(" - File is valid\n");
    free(type);

    boolean isHardDifficulty;
    fscanf(fptr, "%d\n", &isHardDifficulty);
    int scorePlayer1;
    fscanf(fptr, "%d\n", &scorePlayer1);
    int scorePlayer2;
    fscanf(fptr, "%d\n", &scorePlayer2);
    int sizeX;
    fscanf(fptr, "%d\n", &sizeX);
    int sizeY;
    fscanf(fptr, "%d\n", &sizeY);
    printf(" - Basic file data loaded\n");

    MultiplayerGame game = {
            .sizeX = sizeX,
            .sizeY = sizeY,
            .isHardDifficulty = isHardDifficulty,
            .field = createAndInitializeMatrix(sizeX,sizeY),
            .handPlayer1 = (char***)malloc(sizeof(char)*5*3*3),
            .handPlayer2 = (char***)malloc(sizeof(char)*5*3*3),
            .scorePlayer1 = scorePlayer1,
            .scorePlayer2 = scorePlayer2
    };
    printf(" - Game structure initialized\n");
    loadField(fptr, sizeX, sizeY, &game.field);
    printf(" - Field loaded\n");

    for (int i = 0; i < 5; i++) {
    game.handPlayer1[i] = createAndInitializeMatrix(3,3);
    game.handPlayer2[i] = createAndInitializeMatrix(3,3);
    }
    printf(" - Hands initialized\n");
    loadHand(fptr, &game.handPlayer1);
    loadHand(fptr, &game.handPlayer2);
    printf(" - Hands loaded\n");
    fclose(fptr);
    printf("Game loaded, starting game...\n");
    multiplayerGameLoop(&game);

    //free everything
    free3dMatrix(5,3,&game.handPlayer1);
    free3dMatrix(5,3,&game.handPlayer2);
    freeMatrix(sizeX,&game.field);
}