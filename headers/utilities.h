#ifndef _UTILITIES_H
#define _UTILITIES_H

int** createMatrix(int n, int m);
void showMatrix(int n, int m, int** matrix);
unsigned long factorial(unsigned long f);

// QuickSort
travel** quickSort(travel** ints, int start, int end);
int searchPivot(travel** ints, int start, int end);
int makePartition(travel** ints, int start, int end, int indexPivot);
travel** makeSwap(travel** ints, int i, int j);
travel** bubbleSort(travel** travels, int n);

// End QuickSort
#endif