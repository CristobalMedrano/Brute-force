#ifndef _READ_FILE_H
#define _READ_FILE_H

/*
    Funciones de lectura.
    Read Functions.
*/
#define SUCCESS 0
#define ERROR_CLOSE -1

char* getFileName();
FILE* openFile(char* fileName);
int** readFile(FILE* currentFile);
int** createAdjMatrix(int nProvision);
int** setAdjMatrix(int** adjMatrix, int originCity, int destinationCity, int cost);
void showAdjMatrix(int nProvision, int** adjMatrix);
int closeFile(FILE* file, char* fileName);
int** getAdjMatrixFromFile();

#endif