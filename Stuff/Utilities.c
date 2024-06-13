// Original code made by Nicolas GAUD during a lecture
// Edited by Amber GUYENOT-COSIO

#include "Utilities.h"


/**
 * Used to create and initialize a matrix having lineNumber lines and columnNumber columns of zero
 * @param sizeX - number of columns
 * @param sizeY - number of lines
 * @return the newly initialized matrix
 */
char** createAndInitializeMatrix (int sizeX, int sizeY) {
    int x,y;

    char** matrix = (char**) malloc(sizeX * sizeof(char*));
    if (matrix != NULL) {/* Be sure that the memory allocation was effectively successful */
        for (x=0; x<sizeX; x++) {
            matrix[x] = (char*) malloc(sizeY * sizeof (char));
            if (matrix[x] != NULL) {/* Be sure that the memory allocation was effectively successful */
                for (y=0; y<sizeY ; y++) {
                    matrix[x][y]='3';
                }
            } else {
                fprintf(stderr, "ERROR: Error during the initialization of the %d line of the matrix. You probably requested a over the bit limit of %d\n", x, INT_MAX);
            }
        }
    } else {
        fprintf(stderr, "ERROR: Error during the initialization of the matrix. You probably requested a over the bit limit of %d\n", INT_MAX);
    }

    return matrix;
}


/**
 * Check if the space is available inside an array.
 * @param tab the array to check in
 * @param x
 * @param y
 * @return TRUE if the space is available TRUE, FALSE if theres already something else
 */
boolean checkIfSpaceIsEmpty (char** tab, int x, int y) {
    if (tab[x][y] == '3') {
        return TRUE;
    }
    return FALSE;
}


/**
 * will use rng to make a new tile inside the given matrix
 * @param tile the tile to be initialized
 * @param isHardDifficulty if false 1 letter and 1-3 numbers ,if true 2 letters and 2-4 numbers
 * @param isMultiplayer
 * @param isPlayer1 relevant only in multiplayer changes polarity of numbers and letters
 */
void initializeTile (char*** tile, boolean isHardDifficulty, boolean isMultiplayer, boolean isPlayer1) {
    for (int i = 0; i < 3; i++) {            //emptying everything
        for (int j = 0; j < 3; j++) {
            (*tile)[i][j] = '3';
        }
    }
    int howManyNumbers = isHardDifficulty ? rand() % 2 + 2 /*2 a 4*/ : rand() % 2 + 1/*1 a 3*/;        //Faire recherches sur operateurs ternaires
    int x, y;
    boolean placed = FALSE;
    for (int i = 0; i < (isHardDifficulty ? 2 : 1); i++) {
        do {
            x = rand() % 3;
            y = rand() % 3;
            if (checkIfSpaceIsEmpty(*tile, x, y)) {
                placed = TRUE;
                if (isMultiplayer) {
                    (*tile)[x][y] = isPlayer1 ? (char)(rand() % 2 + 65) : (char)(rand() % 2 + 88);
                } else {
                    (*tile)[x][y] = (char) (rand() % 26 + 65);
                }
            }
        } while (!placed);
        placed = FALSE;
    }
    for (int j = 0; j < howManyNumbers; j++) {
        do {
            x = rand() % 3;
            y = rand() % 3;
            if (checkIfSpaceIsEmpty(*tile, x, y)) {
                placed = TRUE;
                (*tile)[x][y] = !isPlayer1 ? (char)(rand() % 3 + 48) : (char)(rand() % 3 + 52);
            }
        } while (!placed);
        placed = FALSE;
    }
}

char* interpretChar (char n) {
    char *output = (char *) malloc(sizeof(char) * 2);
    output[1] = '\0';
    switch (n) {
        default:
            output[0] = n;
            break;
        case '0':
            strcpy(output, "-3");
            break;
        case '1':
            strcpy(output, "-2");
            break;
        case '2':
            strcpy(output, "-1");
            break;
        case '3':
            output[0] = ' ';
            break;
        case '4':
            output[0] = '1';
            break;
        case '5':
            output[0] = '2';
            break;
        case '6':
            output[0] = '3';
            break;
    }
    return output;
}

/**
 * Prints the tile array that has the hand data
 * @param isPlayer1 to show the correct text in the header
 * @param hand the current player's hand
 */
void printHand (boolean isPlayer1, char*** hand) {
    printf(" --------------------------- %s --------------------------- \n", isPlayer1 ? "PLAYER 1'S HAND" : "PLAYER 2'S HAND");
    printf("Tile 1 :\tTile 2 :\tTile 3 :\tTile 4 :\tTile 5 :\n");
    for (int y = 0; y < 3; y++) {           //lines last to be able to optimize the space
        for (int i = 0; i < 5; i++) {
            printf("[");
            for (int x = 0; x < 2; x++) {
                printf("%s, ", interpretChar(hand[i][x][y]));
            }
            printf("%s]\t", interpretChar(hand[i][2][y]));
        }
        printf("\n");
    }
    printf(" ----------------------------------------------------------------------- \n");
}

/**
 * Print the content of the specified matrix
 * @param sizeX - number of columns
 * @param sizeY - number of lines
 * @param matrix - the matrix [lineNumber X columnNumber] to print
 */
void printLevel (int sizeX, int sizeY, char** matrix) {
    int x;
    int y;
    printf("\n ---------------------------- Current board ---------------------------- \n");
    printf("\t ");
    for (int i = 1; i <= sizeX; i++){
        printf("%d%s", i, i > 9 ? " " : "  ");      //to keep it aligned
    }
    printf("\n");
    for(y=0; y<sizeY; y++) {
        printf("     %c\t[", y + 'A');
        for (x=0; x<sizeX-1; x++) {
            char* content = interpretChar(matrix[x][y]);
            printf("%s, ", content);
            free(content);
        }
        char* content = interpretChar(matrix[x][y]);
        printf("%s] \n",content);
        free(content);
    }
    printf(" ----------------------------------------------------------------------- \n");
}


/**
 * will print the current state of the game
 * @param isPlayer1Turn to show the correct text in the header
 * @param level matrix storing the level data
 * @param sizeXlevel number of columns
 * @param sizeYlevel number of lines
 * @param hand the current player's hand
 * @param scorePlayer1
 * @param scorePlayer2 set to -1 if single-player game
 */
void printTurn (boolean isPlayer1Turn, char** level, int sizeXlevel, int sizeYlevel, char*** hand, int scorePlayer1, int scorePlayer2) {
    printLevel(sizeXlevel,sizeYlevel,level);
    printf("PLAYER %c'S TURN\t\t\t\t\t\t", isPlayer1Turn ? '1' : '2');
    if (scorePlayer2 != -1) {
        printf("SCORE : %d | %d\n", scorePlayer1, scorePlayer2);
    } else {
        printf("SCORE : %d\n", scorePlayer1);
    }
    printHand(isPlayer1Turn,hand);
}

/**
 * Free the the content of the specified matrix
 * @param sizeX - number of columns
 * @param matrix - the matrix to free, it will be modified by this function (by address parameter passing)
 */
void freeMatrix (int sizeX, char*** matrix) {
    if (*matrix!= NULL) {
        for (int x = 0; x < sizeX; x++) {
            if ((*matrix)[x] != NULL) {
                free((*matrix)[x]);
                (*matrix)[x] = NULL;
            }
        }
        free(*matrix);
        *matrix = NULL;
    }
}

/**
 * Free the the content of the specified matrix
 * @param sizeZ - number of superpositions
 * @param sizeX - number of columns
 * @param matrix - the matrix to free, it will be modified by this function (by address parameter passing)
 */
void free3dMatrix (int sizeZ, int sizeX, char**** matrix) {
    for (int i = 0; i < sizeZ; i++) {
        for (int x = 0; x < sizeX; x++) {
            free((*matrix)[i][x]);
            (*matrix)[i][x] = NULL;
        }
        free((*matrix)[i]);
        (*matrix)[i] = NULL;
    }
    free(*matrix);
    *matrix = NULL;
}