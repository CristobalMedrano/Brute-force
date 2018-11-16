#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <brute_force.h>
#include <menu.h>
#include <read_file.h>
#include <utilities.h>

void initBruteForce()
{
    int option;
    do
    {
        option = SIN_INGRESO;
        menu(&option, 1, 3);
 
        switch(option)
        {
            case BRUTE_FORCE:
                runBruteForce();
                pressToContinue();
                break;
  
            case ABOUT:
                about();
                break;
 
            case EXIT:
                printf("Programa finalizado.\n");
                break;
        }

    }while(option != EXIT);
}

void runBruteForce()
{
    mapKC* currentMapKC = getMapKC();
    if(NULL != currentMapKC)
    {
        int* cities = makeCities(currentMapKC->nProvision);
        bruteForce(currentMapKC->adjMatrix, currentMapKC->nProvision, cities);
    }
}

int* makeCities(int nProvision)
{
    int* cities = (int*)malloc(sizeof(int)*nProvision);
    
    if (NULL != cities) 
    {   
        int i;
        for(i = 0; i < nProvision; i++)
        {
            cities[i] = i;
            printf("city: %d\n", cities[i]);
        }
        return cities;
    }
    return NULL;
    
}

travel* createTravel()
{
    travel* newTravel = (travel*)malloc(sizeof(travel));
    if(NULL != newTravel)
    {
        newTravel->route = NULL;
        newTravel->cost = 0;
        return newTravel;
    }
    printf("Memoria insuficiente: createTravel()\n");
    printf("Error: brute_force.c\n");
    return NULL;
}

travel* setCurrentTravel(travel* currentTravel, int* route, int cost)
{
    if(NULL != currentTravel)
    {
        currentTravel->route = route;
        currentTravel->cost = cost;
        return currentTravel;
    }
    return NULL;
}

void bruteForce(int** adjmatrix, int nProvision, int* cities)
{
    int fact = factorial(nProvision);
    travel* travels[fact];
    int* route = (int*)malloc(sizeof(int)*nProvision);
    int i   = 0;
    int j   = 0;
    int y   = 0;
    int aux = 0;
    while (y != fact)
    {
        travel* currentTravel = createTravel();
        int k = 0;
        for (k = 0; k < nProvision; k++)
        {
            route[k] = cities[k];
        }
        currentTravel = setCurrentTravel(currentTravel, route, 0);
        printCurrent(currentTravel, nProvision);
        travels[y] = currentTravel;

        /*printf("secuencia actual: ");
        for (k = 0; k < nProvision; k++)
        {
            printf("%d", travels[y]->route[k]);
        }*/

        j = 0 ;
        i = 1 ;
        while(cities[i] < cities[i-1]) i++;
        while(cities[j] > cities[i]) j++;
        aux=cities[j];
        cities[j]=cities[i];
        cities[i]=aux;
        i--;      

        for(j = 0; j < i; i--, j++)
        {
            aux = cities[i];
            cities[i] = cities[j];
            cities[j] = aux;
        }
        y++;
    }
}

void printCurrent(travel* currentTravel, int nProvision)
{
    printf("\n");
    #ifdef DEBUG
        fflush(stdin);
        int k = 0;

        printf("Ruta actual: ");
        for (k = 0; k < nProvision; k++)
        {
            printf("%d", currentTravel->route[k]);
        }
        printf("- Coste de ruta: %d\n", currentTravel->cost);
        printf("Presione intro para continuar...");
        getchar();
        #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
            getchar();
        #endif   
        fflush(stdin); 
    #endif
}