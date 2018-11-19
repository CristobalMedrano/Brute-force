#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <utilities.h>

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

travel** quickSort(travel** travels, int start, int end)
{
   if (start < end) 
    {
        int indexPivot = searchPivot(travels, start, end);
        printf("indexPivot %d\n", indexPivot);
        int cut = makePartition(travels, start, end, indexPivot);
        printf("cut %d", cut);
        travels = quickSort(travels, start, cut - 1);
        travels = quickSort(travels, cut + 1, end);
        return travels;
    }
    return travels;
}

int searchPivot(travel** travels, int start, int end)
{
    int i = 0;
    for(i = start + 1; i < end; i++)
    {
        if (travels[i]->cost > travels[start]->cost)
        {
            return i;
        }
        if(travels[i]->cost < travels[start]->cost)
        {
            return start;            
        }
    }
    return end;
    
}

int makePartition(travel** travels, int start, int end, int indexPivot)
{
    int pivot = travels[indexPivot]->cost;
    printf("pivot %d\n", pivot);
    travels = makeSwap(travels, indexPivot, end);
    indexPivot  = end;   
    printf("indexpivot %d\n", indexPivot);

    int left    = start;
    int right   = end - 1;
    do
    {
        travels = makeSwap(travels, left, right);

        while(travels[left]->cost < pivot)
        {
            left++;
        } 
        while(travels[right]->cost >= pivot)
        {
            right--;
        }
    } while (left < right);
    
    travels  =  makeSwap(travels,  left,  indexPivot);

    return left;
}

travel** makeSwap(travel** travels, int i, int j)
{    
    travel* costAux;

    if (i != j) 
    {
        costAux = travels[i];
        travels[i]  = travels[j];
        travels[j]  = costAux;
    }
    return travels;
}

travel** bubbleSort(travel** travels, int n)
{
    int i;
    for(i = n; i > 1; i--)
    {
        int j;
        for(j = 0; j < i - 1; j++)
        {
            if (travels[j]->cost > travels[j + 1]->cost)
            {
                travels = makeSwap(travels, j, j + 1);
            }   
        }
    }  
    return travels;
}