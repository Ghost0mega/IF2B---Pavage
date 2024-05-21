#include <stdio.h>
#include "Utilities.h"


int main(void) {
    printf("'Pavage' by Thomas Meyer and Amber Guyenot-cosio\n\n\n"); //test
    char input[10];
    boolean exit = FALSE;
    do {
        mainmenu:
        printf("MAIN MENU :\n 1 - start new game\n 2 - load game\n 3 - quit\n\nTip : input the index of each option in the console to navigate through them and type 'help' if you are in a pickle\n");
        mainmenu1:
        scanf("%s", input);

        switch (input[0]) {
            default:
                fprintf(stderr, "ERROR: Invalid input please use the index of an existing option\n");
                goto mainmenu1;

            case '1':
                printf("NEW GAME :\n 1 - Singleplayer\n 2 - Duo match\n 3 - Back\n");
            newgamemenu:
                input[0] = '\0';
                scanf("%s", input);
                switch (input[0]) {
                    default:
                        fprintf(stderr, "ERROR: Invalid input please use the index of an existing option\n");
                        goto newgamemenu;
                    case '1':
                        fprintf(stderr, "Not implemented yet\n");
                        goto mainmenu;
                    case '2':
                        fprintf(stderr, "Not implemented yet\n");
                        goto mainmenu;
                    case '3':
                        printf("Going back to main menu\n\n");
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
