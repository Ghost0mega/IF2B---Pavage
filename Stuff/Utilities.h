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
 * @param sizeX - number of columns
 * @param sizeY - number of lines
 * @return the newly initialized matrix
 */
char** createAndInitializeMatrix (int sizeX, int sizeY);

/**
 * Check if the space is available inside an array.
 * @param tab the array to check in
 * @param x
 * @param y
 * @return TRUE if the space is available TRUE, FALSE if theres already something else
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
 * Prints a tile array
 * @param isPlayer1 to show the correct text in the header
 * @param hand the current player's hand
 */
void printHand (boolean isPlayer1, char*** hand);

/**
 * Print the content of the specified matrix
 * @param sizeX - number of columns
 * @param sizeY - number of lines
 * @param matrix - the matrix [lineNumber X columnNumber] to print
 */
void printLevel (int sizeX, int sizeY, char** matrix);

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
void printTurn (boolean isPlayer1Turn, char** level, int sizeXlevel, int sizeYlevel, char*** hand, int scorePlayer1, int scorePlayer2);

/**
 * will edit anchorX and anchorY to feature the coordinates of the first letter in the tile
 * @param tile
 * @param anchorX
 * @param anchorY
 */
void locateTileAnchor(char** tile, int* anchorX, int* anchorY);

/**
 * will place the tile in the level using the anchor coordinates
 * @param level the array that will receive the tile
 * @param tile the tile to place
 * @param anchorLevelX x level to place tile anchor in
 * @param anchorLevelY y level to place tile anchor in
 * @param anchorTileX internal x level of tile anchor
 * @param anchorTileY internal y level of tile anchor
 */
void placeTile (char*** level, char** tile, int anchorLevelX, int anchorLevelY, int anchorTileX, int anchorTileY);

/**
 * allows a player to play their turn
 * @param level the current level
 * @param sizeX
 * @param sizeY The dimensions of the level
 * @param hand the current player's hand
 * @param score the current player's score
 * @param isFirstTurn used for the rule exception at first turn
 * @param isHardMode the difficulty of the current game
 * @return the player's score at the end of the turn, if they give up the function will return score * -1
 */
int playerTurn (char*** level, int sizeX, int sizeY, char*** hand, int score, boolean isFirstTurn, boolean isHardMode);

/**
 * Free the the content of the specified matrix
 * @param sizeX - number of columns
 * @param matrix - the matrix to free, it will be modified by this function (by address parameter passing)
 */
void freeMatrix (int sizeX, char*** matrix);

/**
 * Free the the content of the specified matrix
 * @param sizeZ - number of superpositions
 * @param sizeX - number of columns
 * @param matrix - the matrix to free, it will be modified by this function (by address parameter passing)
 */
void free3dMatrix (int sizeZ, int sizeX, char**** matrix);
#endif //STUFF_UTILITIES_H
