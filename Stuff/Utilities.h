//
// Original code made by Nicolas GAUD during a lecture
// Edited by Amber GUYENOT-COSIO

#ifndef STUFF_UTILITIES_H
#define STUFF_UTILITIES_H

#include <stdlib.h>
#include <stdio.h>

/**
 * Used to create and initialize a matrix having lineNumber lines and columnNumber columns of zero
 * @param lineNumber - number of lines
 * @param columnNumber - number of columns
 * @return the newly initialized matrix
 */
float** createAndInitializeMatrix (int lineNumber, int columnNumber);

/**
 * Allow the user to fill in the content of the specified matrix.
 * @param lineNumber - number of lines
 * @param columnNumber - number of columns
 * @param a matrix [lineNumber X columnNumber] filled from user inputs, it will be modified by this function (by address parameter passing)
 */
void fillInMatrix (int lineNumber, int columnNumber, float*** matrix);

/**
 * Compute the multiplication between two matrices A and B
 * @param lineNumberA - number of lines of the first matrix
 * @param columnNumberA - number of columns of the first matrix
 * @param matrixA - the matrix [lineNumberA X columnNumberA] as first operand of the multiplication
 * @param lineNumberB - number of lines of the second matrix
 * @param columnNumberB - number of columns of the second matrix
 * @param matrixB - the matrix [lineNumberB X columnNumberB] as second operand of the multiplication
 * @return a matrix correspodnign to the multiplication of matrixA x matrixB
 */
float** matricesMultiplication (int lineNumberA, int columnNumberA, float** matrixA, int lineNumberB, int columnNumberB, float** matrixB);

/**
 * Print the content of the specified matrix
 * @paramlineNumber - number of lines
 * @paramcolumnNumber - number of columns
 * @param matrix - the matrix [lineNumber X columnNumber] to print
 */
void printMatrix (int lineNumber, int columnNumber, float** matrix);

/**
 * Free the the content of the specified matrix
 * @paramlineNumber - number of lines
 * @param matrix - the matrix to free, it will be modified by this function (by address parameter passing)
 */
void freeMatrix (int lineNumber, float*** matrix);

#endif //STUFF_UTILITIES_H
