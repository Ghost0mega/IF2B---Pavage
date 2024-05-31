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
 * will use rng to make a new tile inside the given matrix
 * @param tile the tile to be initialized
 * @param isHardDifficulty if false 1 letter and 1-3 numbers ,if true 2 letters and 2-4 numbers
 * @param isMultiplayer
 * @param isPlayer1 relevant only in multiplayer changes polarity of numbers and letters
 */
void initializeTile (char* tile[3][3], boolean isHardDifficulty, boolean isMultiplayer, boolean isPlayer1) {
    for (int i = 0; i < 3; i++) {            //emptying everything
        for (int j = 0; j < 3; j++) {
            (*tile)[i][j] = '0';
        }
    }
    int howManySpacesToFill = isHardDifficulty ? rand() % 2 + 2 /*2 a 4 + 2lettres*/ : rand() % 2 + 1/*1 a 3*/ /*+ 1lettres*/;        //Faire recherches sur operateurs ternaires
    int pos[2];
    for (int i = 0; i < (isHardDifficulty ? 2 : 1); i++) {
        pos[0] = rand()%3;
    }
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

    printf("\n ------------------ Current board ------------------ \n\n");

    for(l=0; l<lineNumber; l++) {
        printf("\t[");
        for (c=0; c<columnNumber; c++) {
            printf("%c ", matrix[l][c]);
        }
        printf("] \n");
    }

    printf("\n --------------------------------------------------- \n");
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
