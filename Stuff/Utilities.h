// Original code made by Nicolas GAUD during a lecture
// Edited by Amber GUYENOT-COSIO

#ifndef STUFF_UTILITIES_H
#define STUFF_UTILITIES_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

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
 * Check if the space is available inside an array.
 * @param tab the array to check in
 * @param x
 * @param y
 * @return TRUE if the space is available '0', FALSE if theres already something else
 */
boolean checkIfSpaceIsEmpty (char** tab, int x, int y);

/**
 * will use rng to make a new tile inside the given matrix
 * @param tile the tile to be initialized
 * @param isHardDifficulty if false 1 letter and 1-3 numbers ,if true 2 letters and 2-4 numbers
 * @param isMultiplayer
 * @param isPlayer1 relevant only in multiplayer changes polarity of numbers and letters
 */
void initializeTile (char*** tile, boolean isHardDifficulty, boolean isMultiplayer, boolean isPlayer1);

/**
 * will return the correct input to show the player
 * @param n
 * @return what is to be shown
 */
char* interpretChar (char n);

/**
 * Print the content of the specified matrix
 * @paramlineNumber - number of lines
 * @paramcolumnNumber - number of columns
 * @param matrix - the matrix [lineNumber X columnNumber] to print
 */
void printLevel (int lineNumber, int columnNumber, char** matrix);

/**
 * Free the the content of the specified matrix
 * @paramlineNumber - number of lines
 * @param matrix - the matrix to free, it will be modified by this function (by address parameter passing)
 */
void freeMatrix (int lineNumber, char*** matrix);

#endif //STUFF_UTILITIES_H
