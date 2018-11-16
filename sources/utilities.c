#include <stdio.h>
#include <stdlib.h>

int** createMatrix(int n, int m)
{
    int i = 0;
    int** matrix = (int **)calloc(n, sizeof(int *));
                        for (i = 0; i < n; i++)
                        matrix[i] = (int *)calloc(m, sizeof(int));
    if(NULL != matrix)
    {
        return matrix;
    }
    printf("Memoria insuficiente: createMatrix()\n");
    printf("Error: utilities.c\n");
    return NULL;
}

void showMatrix(int n, int m, int** matrix)
{
    if(NULL != matrix && n >= 0 && m >= 0)
    {
        int i = 0;
        for(i = 0; i < n; i++)
        {
            int j = 0;
            for(j = 0; j < m; j++)
            {
                if (matrix[i][j] > 9) 
                {
                    printf("%d  ", matrix[i][j]);
                }
                else
                {
                    printf("%d   ", matrix[i][j]);
                }
            }
            printf("\n");
        }
    }   
}

unsigned long factorial(unsigned long f)
{
    if ( f == 0 ) 
        return 1;
    return(f * factorial(f - 1));
}
