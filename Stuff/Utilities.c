//
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
                    matrix[l][c]='\0';
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
 * Print the content of the specified matrix
 * @param lineNumber - number of lines
 * @param columnNumber - number of columns
 * @param matrix - the matrix [lineNumber X columnNumber] to print
 */
void printMatrix (int lineNumber, int columnNumber, char** matrix) {
    int l = 0;
    int c = 0;

    printf("\n ------------------ Matrix content  ------------------ \n\n");

    for(l=0; l<lineNumber; l++) {
        printf("\t[");
        for (c=0; c<columnNumber; c++) {
            printf("%c ", matrix[l][c]);
        }
        printf("] \n");
    }

    printf("\n ---------------------------------------------------- \n");
}


/**
 * Free the the content of the specified matrix
 * @param lineNumber - number of lines
 * @param matrix - the matrix to free, it will be modified by this function (by address parameter passing)
 */
void freeMatrix (int lineNumber, char*** matrix) {
    int l = 0;
    if (*matrix!= NULL) {
        for (l=0; l<lineNumber; l++) {
            if ((*matrix)[l] != NULL) {
                free((*matrix)[l]);
                (*matrix)[l] = NULL;
            }
        }
        free(*matrix);
        *matrix = NULL;
    }
}
