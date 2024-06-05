// Original code made by Nicolas GAUD during a lecture
// Edited by Amber GUYENOT-COSIO

#include "Utilities.h"


/**
 * Used to create and initialize a matrix having lineNumber lines and columnNumber columns of zero
 * @param lineNumber - number of lines
 * @param columnNumber - number of columns
 * @return the newly initialized matrix
 */
char** createAndInitializeMatrix (int lineNumber, int columnNumber) {
    int l,c;

    char** matrix = (char**) malloc(lineNumber * sizeof(char*));
    if (matrix != NULL) {/* Be sure that the memory allocation was effectively successful */
        for (l=0; l<lineNumber; l++) {
            matrix[l] = (char*) malloc(columnNumber * sizeof (char));
            if (matrix[l] != NULL) {/* Be sure that the memory allocation was effectively successful */
                for (c=0; c<columnNumber ; c++) {
                    matrix[l][c]='0';
                }
            } else {
                fprintf(stderr, "ERROR: Error during the initialization of the %d line of the matrix. You probably requested a over the bit limit of %d\n", l, INT_MAX);
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
 * @return TRUE if the space is available '0', FALSE if theres already something else
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
    int howManyNumbers = isHardDifficulty ? rand() % 2 + 2 /*2 a 4 + 2lettres*/ : rand() % 2 + 1/*1 a 3*/ /*+ 1lettres*/;        //Faire recherches sur operateurs ternaires
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
                (*tile)[x][y] = !isPlayer1 ? (char)(rand() % 2 + 49) : (char)(rand() % 2 + 52);
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
            output[0] = '0';
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
 * Print the content of the specified matrix
 * @param lineNumber - number of lines
 * @param columnNumber - number of columns
 * @param matrix - the matrix [lineNumber X columnNumber] to print
 */
void printLevel (int lineNumber, int columnNumber, char** matrix) {
    int l;
    int c;
    printf("\n ------------------ Current board ------------------ \n");

    for(l=0; l<lineNumber; l++) {
        printf("\t[");
        for (c=0; c<columnNumber-1; c++) {
            char * content = interpretChar(matrix[l][c]);
            printf("%s, ", content);
            free(content);
        }
        char* content = interpretChar(matrix[l][c]);
        printf("%s] \n",content);
        free(content);
    }
    printf(" --------------------------------------------------- \n");
}


/**
 * Free the the content of the specified matrix
 * @param lineNumber - number of lines
 * @param matrix - the matrix to free, it will be modified by this function (by address parameter passing)
 */
void freeMatrix (int lineNumber, char*** matrix) {
    if (*matrix!= NULL) {
        for (int l = 0; l < lineNumber; l++) {
            if ((*matrix)[l] != NULL) {
                free((*matrix)[l]);
                (*matrix)[l] = NULL;
            }
        }
        free(*matrix);
        *matrix = NULL;
    }
}
