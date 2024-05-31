#include <stdio.h>
#include "Utilities.h"
#include "Singleplayergame.h"
#include "MultiplayerGame.h"

/**
 * Asks the user what parameters they want for the start of their game and calls the appropriate function
 * @param type if type = 1 single player game | if type = 2 multiplayer game
 */
void newGame(boolean isMultiplayer) {
    int rows = 0;
    int columns = 0;
    boolean hardMode = FALSE;
    boolean letsGo = FALSE;
    char input[10];

    printf("Please input the number of rows you wish to have in your game.\n");
    do {
        fflush(stdin);
        scanf("%s", input);
        rows = atoi(input);
        if (rows < 3) { fprintf(stderr, "ERROR: Invalid input please use a decimal number over 3\n"); }
    } while (rows < 3);

    printf("Please input the number of columns you wish to have in your game.\n");
    do {
        fflush(stdin);
        scanf("%s", input);
        columns = atoi(input);
        if (columns < 6) { fprintf(stderr, "ERROR: Invalid input please use a decimal number over 6\n"); }
    } while (columns < 6);

    printf("Do you wish to play the game in hard mode ( y / n ) ?\n");
    do {
        fflush(stdin);
        scanf("%s", input);
        input[0] = toupper(input[0]);
        switch (input[0]) {
            default:
                fprintf(stderr, "ERROR: Invalid input please use a decimal number\n");
                break;
            case 'Y':
                hardMode = TRUE;
                letsGo = TRUE;
                break;
            case 'N':
                letsGo = TRUE;
        }
    } while (!letsGo);
    if (isMultiplayer) {
        loadNewMultiplayerGame(rows, columns, hardMode);
    } else {
        loadNewSingleplayerGame(rows, columns, hardMode);
    }
}

int main(void) {
    printf("'Pavage' by Thomas Meyer, Elven Bosc--Charles and Amber Guyenot-cosio\nRepo : https://github.com/Ghost0mega/IF2B-Pavage\n\n"); //test
    char input[10];
    boolean exit = FALSE;
    do {
        mainmenu:
        printf("MAIN MENU :\n 1 - start new game\n 2 - load game\n 3 - quit\n\nTip : input the index of each option in the console to navigate through them and type 'help' if you are in a pickle\n");
        mainmenu1:
        fflush(stdin);
        scanf("%s", input);

        switch (input[0]) {
            default:
                fprintf(stderr, "ERROR: Invalid input please use the index of an existing option\n");
                goto mainmenu1;

            case '1':
                printf("NEW GAME :\n 1 - Singleplayer\n 2 - Duo match\n 3 - Back\n");
            newgamemenu:
                fflush(stdin);
                scanf("%s", input);
                switch (input[0]) {
                    default:
                        fprintf(stderr, "ERROR: Invalid input please use 'y' for yes and 'n, for no.\n");
                        goto newgamemenu;
                    case '1':
                        newGame(FALSE);
                        printf("Returning to main menu.\n\n");
                        goto mainmenu;
                    case '2':
                        newGame(TRUE);
                        printf("Returning to main menu.\n\n");
                        goto mainmenu;
                    case '3':
                        printf("Returning to main menu.\n\n");
                        goto mainmenu;
                }

            case '2':
                fprintf(stderr, "Not implemented yet\n");
                goto mainmenu1;

            case '3':
                printf("Goodbye.");
                exit = TRUE;
        }
    } while (!exit);
    return EXIT_SUCCESS;
}
