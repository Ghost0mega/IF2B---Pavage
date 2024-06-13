#include <stdio.h>
#include "Utilities.h"
#include "Singleplayergame.h"
#include "MultiplayerGame.h"
#define testMode 0

/**
 * Asks the user what parameters they want for the start of their game and calls the appropriate function
 * @param type if type = 1 single player game | if type = 2 multiplayer game
 */
void newGame(boolean isMultiplayer) {
    boolean isHardDifficulty = FALSE;
    int sizeX = 0;
    int sizeY = 0;
    boolean proceed = FALSE;
    char input[10];
    printf("Do you wish to play the game in hard mode ( y / n ) ?\n");
    do {
        fflush(stdin);
        scanf("%s", input);
        input[0] = toupper(input[0]);
        switch (input[0]) {
            default:
                fprintf(stderr, "ERROR: Invalid input please use 'y' for yes and 'n' for no\n");
                break;
            case 'Y':
                printf("Game set to hard mode.\n");
                isHardDifficulty = TRUE;
                proceed = TRUE;
                break;
            case 'N':
                printf("Game set to normal mode.\n");
                proceed = TRUE;
                break;
        }
    } while (!proceed);
    proceed = FALSE;
    printf("How wide do you wish the level to be ( min 6 ) ?\n");
    do{
        fflush(stdin);
        scanf("%s", input);
        sizeX = atoi(input);        //atoi works bc we always want a value above 3 anyway
        if (sizeX < 6) {
            fprintf(stderr, "ERROR: Invalid input please use a decimal number over 6\n");
        } else {
            proceed = TRUE;
        }
    } while (!proceed);
    proceed = FALSE;
    printf("How tall do you wish the level to be ( min 3 ) ?\n");
    do{
        fflush(stdin);
        scanf("%s", input);
        sizeY = atoi(input);        //atoi works bc we always want a value above 3 anyway
        if (sizeY < 3) {
            fprintf(stderr, "ERROR: Invalid input please use a decimal number over 3\n");
        } else {
            proceed = TRUE;
        }
    } while (!proceed);

    if (isMultiplayer) {
        newMultiplayerGame(sizeX, sizeY, isHardDifficulty);
    } else {
        newSingleplayerGame(sizeX, sizeY, isHardDifficulty);
    }
}

int main(int argc, char** argv) {
    printf("'Pavage' by Thomas Meyer, Elven Bosc--Charles and Amber Guyenot-cosio\nRepo : https://github.com/Ghost0mega/IF2B-Pavage\n\n"); //test
#if testMode
//tile initialization test
    srand(time(0));
    int iterations = 5;
    for (int i = 0; i < iterations; i++) {
        newSingleplayerGame(15,10,TRUE);
        /*
        char **handtest = createAndInitializeMatrix(3, 3);
        initializeTile(&handtest, TRUE, TRUE, FALSE);
        printLevel(3, 3, handtest);
         */
    }

#else
    char input[10];
    boolean exit = FALSE;
    boolean proceed = FALSE;
    boolean skip; //Could be deleted but i dont wanna spend 20 mins switching if statements around
    int menuPos = 0;
    do {
        skip = FALSE;
        switch (menuPos) {
            default:        //should stay inaccessible
                fprintf(stderr, "ERROR: menuPos %d is not a valid value! resetting menuPos to 0\n", menuPos);
                menuPos = 0;
                break;
            case 0:
                printf("MAIN MENU :\n 1 - start new game\n 2 - load game\n 3 - quit\n");
                break;
            case 1:
                printf("NEW GAME :\n 1 - Single-player\n 2 - Duo match\n 3 - Back\n");
                break;
            case 11:
                printf("CREATING NEW SINGLE-PLAYER MATCH :\n");
                break;
            case 12:
                printf("CREATING NEW DUO MATCH :\n");
                break;
        }

        if (menuPos == 0) {     //MAIN MENU
            proceed = FALSE;
            do {
                fflush(stdin);
                scanf("%s", input);
                switch (input[0]) {
                    default:
                        fprintf(stderr, "ERROR: Invalid input please use the index of an existing option\n");
                        break;
                    case '1':     //NEW GAME
                        menuPos = 1;
                        skip = TRUE;
                        proceed = TRUE;
                        break;
                    case '2':     //LOAD GAME
                        fprintf(stderr, "Not implemented yet\n");
                        menuPos = 0;
                        skip = TRUE;
                        proceed = FALSE;
                        //menuPos = 2;
                        //proceed = TRUE;
                        break;
                    case '3':     //QUIT
                        printf("Goodbye.");
                        proceed = TRUE;
                        exit = TRUE;
                }
            } while (!proceed);
        }

        if (menuPos == 1 && !skip) {     //NEW GAME
            proceed = FALSE;
            do {
                fflush(stdin);
                scanf("%s", input);
                switch (input[0]) {
                    default:
                        fprintf(stderr, "ERROR: Invalid input please use the index of an existing option\n");
                        break;
                    case '1':     //SINGLEPLAYER
                        menuPos = 11;
                        skip = TRUE;
                        proceed = TRUE;
                        break;
                    case '2':     //MULTIPLAYER
                        menuPos = 12;
                        skip = TRUE;
                        proceed = TRUE;
                        break;
                    case '3':     //RETURN TO MAIN MENU
                        printf("Returning to main menu.\n\n");
                        menuPos = 0;
                        proceed = TRUE;
                }
            } while (!proceed);
        }

        if (menuPos == 11 && !skip) {     //CREATING NEW SINGLE-PLAYER GAME
            newGame(FALSE);
            printf("Returning to main menu.\n\n");
            menuPos = 0;
        }

        if (menuPos == 12 && !skip) {    //CREATING NEW MULTI-PLAYER GAME
            newGame(TRUE);
            printf("Returning to main menu.\n\n");
            menuPos = 0;
        }
    } while (!exit);
#endif
    return EXIT_SUCCESS;
}
