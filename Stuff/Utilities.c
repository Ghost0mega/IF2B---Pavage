//
// Created by sguye on 21/05/2024.
//

#include "Utilities.h"


/**
 * Used to create and initialize a matrix having lineNumber lines and columnNumber columns of zero
 * @param lineNumber - number of lines
 * @param columnNumber - number of columns
 * @return the newly initialized matrix
 */
float** createAndInitializeMatrix (int lineNumber, int columnNumber) {
    int l,c;

    float** matrix = (float**) malloc(lineNumber * sizeof(float*));
    if (matrix != NULL) {/* Be sure that the memory allocation was effectively successful */
        for (l=0; l<lineNumber; l++) {
            matrix[l] = (float*) malloc(columnNumber * sizeof (float));
            if (matrix[l] != NULL) {/* Be sure that the memory allocation was effectively successful */
                for (c=0; c<columnNumber ; c++) {
                    matrix[l][c]=0;
                }
            } else {
                fprintf(stderr, "ERROR: Error during the initialization of the %d line of the matrix. You probably request a size too big \n", l);
            }
        }
    } else {
        fprintf(stderr, "ERROR: Error during the initialization of the matrix. You probably request a size too big \n");
    }

    return matrix;
}


/**
 * Allow the user to fill in the content of the specified matrix.
 * @param lineNumber - number of lines
 * @param columnNumber - number of columns
 * @return a matrix [lineNumber X columnNumber] filled from user inputs, it will be modified by this function (by address parameter passing)
 */
void fillInMatrix (int lineNumber, int columnNumber, float*** matrix) {
    int l = 0;
    int c = 0;
    char mastring[20];
    for (l=0; l< lineNumber ; l++) {
        for (c=0; c<columnNumber ; c++) {
            //printf("\nPlease enter the value for the matrix element at the %d th line and the %d th column\n",l+1,c+1);
            //scanf("%f",&((*matrix)[l][c])); /* Normally I should verify that the user input is effectively a float, as we have done in the main for the command line parameter */

            do {
                printf("\nPlease enter the value for the matrix element at the %d th line and the %d th column\n",l+1,c+1);
                scanf("%s",mastring);
                fflush(stdin);
            } while((sscanf(mastring, "%f", &((*matrix)[l][c])) == EOF) || ((*matrix)[l][c]<=0));


        }
    }
}

/**
 * Compute the multiplication between two matrices A and B
 * @param lineNumberA - number of lines of the first matrix
 * @param columnNumberA - number of columns of the first matrix
 * @param matrixA - the matrix [lineNumberA X columnNumberA] as first operand of the multiplication
 * @param lineNumberB - number of lines of the second matrix
 * @param columnNumberB - number of columns of the second matrix
 * @param matrixB - the matrix [lineNumberB X columnNumberB] as second operand of the multiplication
 * @return a matrix correspodnign to the multiplication of matrixA x matrixB
 */
float** matricesMultiplication (int lineNumberA, int columnNumberA, float** matrixA, int lineNumberB, int columnNumberB, float** matrixB) {
    int l = 0;
    int c = 0;
    int k = 0;
    float** matrix = NULL;

    if (columnNumberA==lineNumberB) {
        matrix = (float**) malloc(lineNumberA*sizeof(float*));
        if (matrix != NULL) {/* Be sure that the memory allocation was effectively successful */
            for (l=0; l<lineNumberA ; l++) {
                matrix[l] = (float*) malloc(columnNumberB * sizeof(float));
                if (matrix[l] != NULL) {/* Be sure that the memory allocation was effectively successful */
                    for (c=0; c<columnNumberB ; c++) {
                        matrix[l][c] = 0;
                        for(k=0; k<columnNumberA; k++) {
                            matrix[l][c] = matrix[l][c] + matrixA[l][k] * matrixB[k][c];
                        }
                    }
                } else {
                    fprintf(stderr, "ERROR: Error during the initialization of the %d line of the matrix. You probably request a size too big \n", l);
                    for (int i=0; i<l-1 ; i++) {
                        free(matrix[i]);
                    }
                    free(matrix);
                    matrix = NULL;
                }
            }
        } else {
            fprintf(stderr, "ERROR: Error during the initialization of the matrix. You probably request a size too big \n");
        }
    } else {
        fprintf(stderr, "ERROR:Incompatible matrix size \n");
    }
    return matrix;
}

/**
 * Print the content of the specified matrix
 * @param lineNumber - number of lines
 * @param columnNumber - number of columns
 * @param matrix - the matrix [lineNumber X columnNumber] to print
 */
void printMatrix (int lineNumber, int columnNumber, float** matrix) {
    int l = 0;
    int c = 0;

    printf("\n ------------------ Matrix content  ------------------ \n\n");

    for(l=0; l<lineNumber; l++) {
        printf("\t[");
        for (c=0; c<columnNumber; c++) {
            printf("%f ", matrix[l][c]);
        }
        printf("] \n");
    }

    printf("\n ---------------------------------------------------- \n");
}


/**
 * Free the the content of the specified matrix
 * @param lineNumber - number of lines
 * @param matrix - the matrix to free, it will be modified by this function (by address parameter passing)
 */
void freeMatrix (int lineNumber, float*** matrix) {
    int l = 0;
    if (*matrix!= NULL) {
        for (l=0; l<lineNumber; l++) {
            if ((*matrix)[l] != NULL) {
                free((*matrix)[l]);
                (*matrix)[l] = NULL;
            }
        }
        free(*matrix);
        *matrix = NULL;
    }
}
