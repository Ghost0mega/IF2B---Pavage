#include "save.h"

/**
 * ensure that the saves directory exists and create it if it doesn't
 */
void ensureSavesDirectoryExists() {
    struct stat st = {0};
    if (stat("Saves", &st) == -1) {
        printf("Saves directory doesn't exist, creating it...\n");
        mkdir("Saves");
        printf("Done\n");
    }
}

/**
 * generate a file path for a save file according to the user's input
 * @param path the path to generate
 */
void generateFilePath(char** path) {
    char name[20];
    printf("Please enter the name of the save file : \n");
    do {
        fflush(stdin);
        scanf("%s", name);
        if (strlen(name) > 20) {
            fprintf(stderr, "ERROR: The name is too long, please enter a name with less than 20 characters\n");
        } else if (strlen(name) == 0) {
            fprintf(stderr, "ERROR: The name is too short, please enter a name with at least 1 character\n");
        } else {
            printf("The name of the save file is : %s\n", name);
        }
    } while (strlen(name) > 20);
    *path = malloc(strlen("./Saves/") + strlen(name) + strlen(".txt") + 1);  // allocate memory for path
    if (*path == NULL) {
        fprintf(stderr, "ERROR: Couldn't allocate memory for path\n");
        return;
    }
    sprintf(*path, "./Saves/%s.txt", name);
}

/**
 * save a field to a file
 * @param fptr the file to save to
 * @param sizeX
 * @param sizeY size of the grid
 * @param field the grid
 */
void saveField(FILE* fptr, int sizeX, int sizeY, char** field) {
    fprintf(fptr, "%d\n", sizeX);
    fprintf(fptr, "%d\n", sizeY);
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            fprintf(fptr, "%c", field[i][j]);
        }
    }
    fprintf(fptr, "\n");
}

/**
 * save a hand to a file
 * @param fptr the file to save to
 * @param hand the hand to save
 */
void saveHand(FILE* fptr, char*** hand) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                fprintf(fptr, "%c", hand[i][j][k]);
            }
            fprintf(fptr, "\n");
        }
        fprintf(fptr, "\n");
    }
}

/**
 * load a field from a file
 * @param fptr the file to load from
 * @param field the field to load into
 * @param sizeX
 * @param sizeY size of the grid
 */
void loadField(FILE* fptr, int sizeX, int sizeY, char*** field) {
        char temp;
        for (int i = 0; i < sizeX; i++) {
            for (int j = 0; j < sizeY; j++) {
                printf(" - Reading character for field[%d][%d]\n", i, j);
                fscanf(fptr, "%c", field[i][j]);
                printf(" - Read character: %c\n", *field[i][j]);
            }
//            fscanf(fptr, "%c", &temp);  // read and discard the newline character
        }
}

/**
 * load a hand from a file
 * @param fptr the file to load from
 * @param hand the hand to load into
 */
void loadHand(FILE* fptr, char**** hand) {
    char temp;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                fscanf(fptr, "%c", hand[i][j][k]);
            }
            fscanf(fptr, "%c", &temp);  // read and discard the newline character
        }
    }
}

/**
 * save a singleplayer game to a file in the Saves directory
 * @param isHardDifficulty  true if hard difficulty is enabled
 * @param sizeX
 * @param sizeY size of the grid
 * @param field the grid
 * @param hand the hand of the player
 * @param score the score of the player
 */
void saveSingleplayerGame(boolean isHardDifficulty, int sizeX, int sizeY, char** field, char*** hand, int score) {
    ensureSavesDirectoryExists();
    char* path;
    generateFilePath(&path);
    FILE* fptr = fopen(path, "w");  //open the file in write mode
    if (fptr == NULL) {
        fprintf(stderr, "ERROR: Couldn't open the file\n");
        return;
    }
    fprintf(fptr, "Singleplayer\n");
    fprintf(fptr, "%d\n", isHardDifficulty);
    fprintf(fptr, "%d\n", score);
    saveField(fptr, sizeX, sizeY, field);
    saveHand(fptr, hand);
    fclose(fptr);
    free(path);
}

/**
 * save a multiplayer game to a file in the Saves directory
 * @param isHardDifficulty  true if hard difficulty is enabled
 * @param sizeX
 * @param sizeY size of the grid
 * @param field the grid
 * @param handPlayer1 the hand of player 1
 * @param handPlayer2 the hand of player 2
 * @param scorePlayer1 the score of player 1
 * @param scorePlayer2 the score of player 2
 * @param isPlayer1Turn true if it's player 1's turn
 */
void saveMultiplayerGame(boolean isHardDifficulty, int sizeX, int sizeY, char** field, char*** handPlayer1, char*** handPlayer2, int scorePlayer1, int scorePlayer2, boolean isPlayer1Turn) {
    ensureSavesDirectoryExists();
    char* path;
    generateFilePath(&path);
    FILE* fptr = fopen(path, "w");  //open the file in write mode
    if (fptr == NULL) {
        fprintf(stderr, "ERROR: Couldn't open the file\n");
        return;
    }
    fprintf(fptr, "Multiplayer\n");
    fprintf(fptr, "%d\n", isHardDifficulty);
    fprintf(fptr, "%d\n", scorePlayer1);
    fprintf(fptr, "%d\n", scorePlayer2);
    fprintf(fptr, "%d\n", isPlayer1Turn);
    saveField(fptr, sizeX, sizeY, field);
    saveHand(fptr, handPlayer1);
    saveHand(fptr, handPlayer2);
    fclose(fptr);
    free(path);
}