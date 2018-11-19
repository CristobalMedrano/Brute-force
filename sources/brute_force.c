#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <brute_force.h>
#include <menu.h>
#include <files.h>
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
        travel* minTravel = bruteForce(currentMapKC->adjMatrix, currentMapKC->nProvision, cities);
        saveFile(minTravel, "salida.out", currentMapKC->nProvision);
        free(minTravel->route);
        free(minTravel);
        free(cities);        
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
        }
        return cities;
    }
    return NULL;
    
}


travel* makeRoute(int** adjMatrix, int nProvision, int* cities)
{
    if(NULL != cities)
    {
        int* route = copyRoutetoMemory(cities, nProvision);
        travel* currentTravel   = createTravel();
        int currentRouteCost    = routeCost(adjMatrix, nProvision, route); 
        currentTravel           = setCurrentTravel(currentTravel, route, currentRouteCost);
        return currentTravel;
    }
    return NULL;
}

int* copyRoutetoMemory(int* cities, int nProvision)
{
    int* route = (int*)malloc(sizeof(int)*nProvision);
    
    
    if (NULL != route) 
    {
        int i;
        for(i = 0; i < nProvision; i++)
        {
            route[i] = cities[i];
        }
        return route;
    }
    return NULL;   
}

/* Inicializa un viaje vacio*/
travel* createTravel()
{
    travel* newTravel = (travel*)malloc(sizeof(travel));
    if(NULL != newTravel)
    {
        newTravel->route    = NULL;
        newTravel->cost     = 0;
        return newTravel;
    }
    printf("Memoria insuficiente: createTravel()\n");
    printf("Error: brute_force.c\n");
    return NULL;
}

/*Funcion que calcula el coste de una ruta*/
int routeCost(int** adjMatrix, int nProvision, int* route)
{
    int cost        = 2;
    int i           = 0;
    int startCity   = 0;
    int endCity     = 0;

    for(i = 1; i < nProvision; i++) 
    {
        startCity   = route[i-1];
        endCity     = route[i];
        cost        = adjMatrix[startCity][endCity] + cost;
    }
    return cost;
}

/* Guarda el viaje actual, el cual contiene una ruta y su costo*/
travel* setCurrentTravel(travel* currentTravel, int* route, int cost)
{
    if(NULL != currentTravel)
    {
        currentTravel->route    = route;
        currentTravel->cost     = cost;
        return currentTravel;
    }
    return NULL;
}

/* Crea las permutaciones a partir de una lista de ciudades*/
int* makePermutation(int* cities)
{
    int j   = 0;
    int i   = 1;
    int aux = 0;

    while(cities[i] < cities[i-1])
    {
        i++;
    }
    while(cities[j] > cities[i])
    {
        j++;
    }
    
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
    return cities;
}

/*
    Entrada: una matriz de adjacencia, la cantidad de recursos y un listado de ciudades.
    Procedimiento: se calculan las n! permutaciones del problema, donde n es la cantidad de ciudades a permutar,
                Por cada permutacion se calcula el costo de la ruta recorrida y se almacena en una lista de viajes(travels).
                Finalmente se ordena la lista de viajes de menor a mayor y se entrega el primer elemento.
    Salida: puntero a la estructura travel que contiene la ruta y el coste de realizarla.
*/
travel* bruteForce(int** adjMatrix, int nProvision, int* cities)
{
    printf("Ejecutando fuerza bruta...\n");
    int fact = factorial(nProvision);
    travel** travels = (travel**)malloc(sizeof(travel*)*fact*2);
    int y = 0;
    
    while (y != fact)
    {
        travels[y] = makeRoute(adjMatrix, nProvision, cities);
        #ifdef DEBUG
            printf("%d/%d\n", y+1, fact);
        #endif
        printCurrent(travels[y], nProvision);
        cities = makePermutation(cities);
        y++;
    }
    #ifdef DEBUG
        printf("\n\n");
    #endif
    //travels = quickSort(travels, 0, fact);
    printf("Filtrando resultados...\n");
    travels = bubbleSort(travels, fact);
    printf("Resultado encontrado.\n");

    #ifdef DEBUG
        int k;
        printf("min cost: %d -> route: ",travels[0]->cost);
        for(k = 0; k < nProvision; k++)
        {
            printf(" %d ", travels[0]->route[k]);
        }
        printf("\n");
    #endif
    printf("Fuerza bruta terminada.\n");
    #ifdef DEBUG
        printf("Liberando recursos utilizados...\n");
    #endif
    int l;
    for(l = 1; l < fact; l++)
    {
        free(travels[l]->route); 
        free(travels[l]);      
    }
    return travels[0];
}

/*
    Entrada: dato de tipo travel, que contiene una ruta y su coste; ademas el numero de recursos.
    Procedimiento: por cada permutacion, muestra por pantalla el resultado de su coste junto con su ruta.
    Salida: no posee.
*/
void printCurrent(travel* currentTravel, int nProvision)
{
    #ifdef DEBUG
        fflush(stdin);
        int k = 0;

        printf("Ruta actual: ");
        for (k = 0; k < nProvision; k++)
        {
            printf("%d", currentTravel->route[k]);
        }
        printf(" - Coste de ruta: %d\n", currentTravel->cost);
        printf("Presione intro para continuar...");
        getchar();
        #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
            getchar();
        #endif   
        fflush(stdin); 
    #endif
}