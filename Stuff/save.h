#ifndef STUFF_SAVE_H
#define STUFF_SAVE_H
#include "Utilities.h"

/**
 * ensure that the saves directory exists and create it if it doesn't
 */
void ensureSavesDirectoryExists();

/**
 * generate a file path for a save file
 * @param path the path to generate
 */
void generateFilePath(char** path);


#endif //STUFF_SAVE_H
