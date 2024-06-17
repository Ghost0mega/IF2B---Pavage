#ifndef STUFF_SAVE_H
#define STUFF_SAVE_H
#include "Utilities.h"
#include <sys/stat.h>
/**
 * ensure that the saves directory exists and create it if it doesn't
 */
void ensureSavesDirectoryExists();

/**
 * generate a file path for a save file
 * @param path the path to generate
 */
void generateFilePath(char** path);

/**
 * save a field to a file
 * @param fptr the file to save to
 * @param sizeX
 * @param sizeY size of the grid
 * @param field the grid
 */
void saveField(FILE* fptr, int sizeX, int sizeY, char** field);

/**
 * save a hand to a file
 * @param fptr the file to save to
 * @param hand the hand to save
 */
void saveHand(FILE* fptr, char*** hand);

/**
 * load a field from a file
 * @param fptr the file to load from
 * @param field the field to load into
 * @param sizeX
 * @param sizeY size of the grid
 */
void loadField(FILE* fptr, int sizeX, int sizeY, char*** field);

/**
 * load a hand from a file
 * @param fptr the file to load from
 * @param hand the hand to load into
 */
void loadHand(FILE* fptr, char**** hand);

/**
 * save a singleplayer game to a file in the Saves directory
 * @param isHardDifficulty  true if hard difficulty is enabled
 * @param sizeX
 * @param sizeY size of the grid
 * @param field the grid
 * @param hand the hand of the player
 * @param score the score of the player
 */
void saveSingleplayerGame(boolean isHardDifficulty, int sizeX, int sizeY, char** field, char*** hand, int score);

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
void saveMultiplayerGame(boolean isHardDifficulty, int sizeX, int sizeY, char** field, char*** handPlayer1, char*** handPlayer2, int scorePlayer1, int scorePlayer2, boolean isPlayer1Turn);

#endif //STUFF_SAVE_H
