#include "save.h"

/**
 * ensure that the saves directory exists and create it if it doesn't
 */
void ensureSavesDirectoryExists() {
    struct stat st = {0};
    if (stat("Saves", &st) == -1) {
        mkdir("Saves");
    }
}

/**
 * generate a file path for a save file according to the user's input
 * @param path the path to generate
 */
void generateFilePath(char** path) {
    char name[20];
    printf("Please enter the name of the save file : \n");
    do {
        fflush(stdin);
        scanf("%s", name);
        if (strlen(name) > 20) {
            fprintf(stderr, "ERROR: The name is too long, please enter a name with less than 20 characters\n");
        }
    } while (strlen(name) > 20);
    sprintf(*path, "Saves/%s.txt", name);
}

/**
 * save a singleplayer game to a file in the Saves directory
 * @param isHardDifficulty  true if hard difficulty is enabled
 * @param sizeX
 * @param sizeY size of the grid
 * @param field the grid
 * @param hand the hand of the player
 * @param score the score of the player
 */
void saveSingleplayerGame(boolean isHardDifficulty, int sizeX, int sizeY, char** field, char*** hand, int score) {

}