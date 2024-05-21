//
// Original code made by Nicolas GAUD during a lecture
// Edited by Amber GUYENOT-COSIO

#ifndef STUFF_UTILITIES_H
#define STUFF_UTILITIES_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef enum {
    FALSE = 0,
    TRUE = 1
} boolean;


/**
 * Used to create and initialize a matrix having lineNumber lines and columnNumber columns of zero
 * @param lineNumber - number of lines
 * @param columnNumber - number of columns
 * @return the newly initialized matrix
 */
char** createAndInitializeMatrix (int lineNumber, int columnNumber);

/**
 * Print the content of the specified matrix
 * @paramlineNumber - number of lines
 * @paramcolumnNumber - number of columns
 * @param matrix - the matrix [lineNumber X columnNumber] to print
 */
void printMatrix (int lineNumber, int columnNumber, char** matrix);

/**
 * Free the the content of the specified matrix
 * @paramlineNumber - number of lines
 * @param matrix - the matrix to free, it will be modified by this function (by address parameter passing)
 */
void freeMatrix (int lineNumber, char*** matrix);

#endif //STUFF_UTILITIES_H
