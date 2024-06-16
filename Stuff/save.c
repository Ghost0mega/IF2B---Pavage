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