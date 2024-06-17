#include "Singleplayergame.h"

/**
 * The main loop of the single player game
 * @param game the game to play
 */
void singleplayerGameLoop(Singleplayergame* game) {
    boolean gameIsOver = FALSE;
    boolean gaveUp = FALSE;
    boolean hasSaved = FALSE;
    boolean isFirstTurn = TRUE;
    do {
        if (!canPlayerPlay(game->field, game->sizeX, game->sizeY, game->hand) && !isFirstTurn) {    //if the player can't play
            gaveUp = TRUE;
        } else {
            printTurn(TRUE, game->field, game->sizeX, game->sizeY, game->hand, game->score, -1);
            game->score = playerTurn(&game->field, game->sizeX, game->sizeY, game->hand, game->score, isFirstTurn,game->isHardDifficulty, FALSE, TRUE);
            if (game->score < 0) {  //if the player has negative points -> they gave up
                gaveUp = TRUE;
                game->score = game->score * -1;
            }
            if (game->score > 1000) {   //if the player has more than 1000 points(technically achievable with absurd grid sizes but let's ignore that) -> save the game
                hasSaved = TRUE;
                game->score = game->score - 1000;
            }
        }
        if (gaveUp) {
            gameIsOver = TRUE;
            printf("You either gave up or couldn't place any more tiles, the game is over.\n");
        }
        isFirstTurn = FALSE;
    } while (!gameIsOver && !hasSaved);
//    printf("You finished the game with a score of %d\n", game->score);
    if (!gameIsOver) {
        printf("saving game...\n");
        saveSingleplayerGame(game->isHardDifficulty, game->sizeX, game->sizeY, game->field, game->hand, game->score);
        printf("Game saved, returning to main menu\n");
    } else {
        printf("Game over, score : %d\n", game->score);
    }
}

/**
 * Creates a new single player game
 * @param sizeX number of columns in the grid
 * @param sizeY number of rows in the grid
 * @param hardDifficulty is hard difficulty enabled
 */
void newSingleplayerGame(int sizeX, int sizeY, boolean hardDifficulty) {
//    printf("Singleplayer | Rows : %d | Columns : %d | HardDifficulty : %s\n", sizeY, sizeX, hardDifficulty ? "true" : "false");

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

/**
 * Load and play singleplayer game from a file
 * @param path the path to the save file
 */
void loadSingleplayerGame(char* path) {
    printf("Attempting to load singleplayer game from %s\n", path);
    FILE* fptr = fopen(path, "r");
    if (fptr == NULL) {
        fprintf(stderr, "ERROR: Couldn't open the file\n");
        return;
    }
    printf(" - File opened\n");
    char* type = (char*)malloc(sizeof(char)*20);
    fscanf(fptr, "%s\n", type);
    if (strcmp(type, "Singleplayer") != 0) {
        fprintf(stderr, "ERROR: The file is not a singleplayer save file\n");
        free(type);
        fclose(fptr);
        return;
    }
    printf(" - File is valid\n");
    free(type);

    boolean isHardDifficulty;
    fscanf(fptr, "%d\n", &isHardDifficulty);
    int score;
    fscanf(fptr, "%d\n", &score);
    int sizeX;
    fscanf(fptr, "%d\n", &sizeX);
    int sizeY;
    fscanf(fptr, "%d\n", &sizeY);
    printf(" - Basic file data loaded\n");

    Singleplayergame game = {
            .sizeX = sizeX,
            .sizeY = sizeY,
            .isHardDifficulty = isHardDifficulty,
            .field = createAndInitializeMatrix(sizeX,sizeY),
            .hand = (char***)malloc(sizeof(char)*5*3*3),
            .score = 0
    };
    printf(" - Game structure initialized\n");
    loadField(fptr, sizeX, sizeY, &game.field);
    printf(" - Field loaded\n");

    for (int i = 0; i < 5; i++) {
        game.hand[i] = createAndInitializeMatrix(3, 3);
    }
    printf(" - Hand initialized\n");
    loadHand(fptr, &game.hand);
    printf(" - Hand loaded\n");
    fclose(fptr);
    printf("Game loaded, starting game...\n");
    singleplayerGameLoop(&game);

    //free everything
    free3dMatrix(5,3,&game.hand);
    freeMatrix(sizeX,&game.field);
}