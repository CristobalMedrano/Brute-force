#ifndef _READ_FILE_H
#define _READ_FILE_H

/*
    Funciones de lectura.
    Read Functions.
*/
#define SUCCESS 0
#define ERROR_CLOSE -1

char* getFileName();
FILE* openFile(char* fileName, char* type);
mapKC* readFile(FILE* currentFile);
mapKC* createMapKindomClover();
mapKC* setMapKingdomClover(mapKC* currentMapMC, int** adjMatrix, int nProvision);
int** setAdjMatrix(int** adjMatrix, int originCity, int destinationCity, int cost);
int closeFile(FILE* file, char* fileName);
mapKC* getMapKC();

void saveFile(travel* currentTravel, char* fileName, int n);

#endif