#ifndef _BRUTE_FORCE_H
#define _BRUTE_FORCE_H

/*
    Funciones principales.
    Main Functions.
*/

#define SIN_INGRESO -1
#define BRUTE_FORCE 1
#define ABOUT 2
#define EXIT 3

void initBruteForce();
void runBruteForce();
int* makeCities(int nProvision);
void bruteForce(int** adjmatrix, int nProvision, int* cities);
travel* makeRoute(int** adjMatrix, int nProvision, int* cities);
travel* createTravel();
int routeCost(int** adjMatrix, int nProvision, int* cities);
travel* setCurrentTravel(travel* currentTravel, int* route, int cost);

void printCurrent(travel* currentTravel, int nProvision);


#endif