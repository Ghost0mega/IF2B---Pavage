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
 * save a singleplayer game to a file in the Saves directory
 * @param isHardDifficulty  true if hard difficulty is enabled
 * @param sizeX
 * @param sizeY size of the grid
 * @param field the grid
 * @param hand the hand of the player
 * @param score the score of the player
 */
void saveSingleplayerGame(boolean isHardDifficulty, int sizeX, int sizeY, char** field, char*** hand, int score);

#endif //STUFF_SAVE_H
