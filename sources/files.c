#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <structs.h>
#include <utilities.h>
#include <files.h>

char* getFileName()
{
    printf("Ingrese el nombre del archivo: ");
    char    file[256];
	char*   filename = (char*)malloc(sizeof(char)*256);
    
    if (NULL != filename) 
    {
        fflush(stdin);
        scanf("%s", file);
        fflush(stdin);
        strcpy(filename, file);
        return filename;
    }    
    printf("Memoria insuficiente: getFileName()\n");
    printf("Error: read_file.c\n");
    return NULL;
}

FILE* openFile(char* fileName, char* type)
{
    FILE* currentFile = fopen(fileName, type);
    if(NULL != currentFile)
    {
        #ifdef DEBUG
            printf("Archivo '%s' abierto\n", fileName);
        #endif
        return currentFile;
    }
    printf("Error: El archivo '%s' no existe.\n", fileName);
    return NULL;
}

mapKC* readFile(FILE* currentFile)
{
    if(NULL != currentFile)
    {
        int nProvision      = 0;
        fscanf(currentFile, "%d", &nProvision);

        mapKC* newMapKC     = createMapKindomClover();
        int** adjMatrix     = createMatrix(nProvision, nProvision);

        if (NULL != adjMatrix && NULL != newMapKC) 
        {
            int originCity      = 0;
            int destinationCity = 0;
            int cost            = 0;

            while(0 == feof(currentFile))
            {
                fscanf(currentFile, "%d", &originCity);
                fscanf(currentFile, "%d", &destinationCity);
                fscanf(currentFile, "%d", &cost);
                adjMatrix = setAdjMatrix(adjMatrix, originCity, destinationCity, cost);
            }
            #ifdef DEBUG
                showMatrix(nProvision, nProvision, adjMatrix);
            #endif

            newMapKC = setMapKingdomClover(newMapKC, adjMatrix, nProvision);
            return newMapKC;
        }
    }
    return NULL;
}

mapKC* createMapKindomClover()
{
    mapKC* newMapKC = (mapKC*)malloc(sizeof(mapKC));
    if(NULL != newMapKC)
    {
        newMapKC->adjMatrix = NULL;
        newMapKC->nProvision = 0;
        return newMapKC;
    }
    printf("Memoria insuficiente: createMapKindomClover()\n");
    printf("Error: read_file.c\n");
    return NULL;
}

mapKC* setMapKingdomClover(mapKC* currentMapMC, int** adjMatrix, int nProvision)
{
    if(NULL != currentMapMC)
    {
        currentMapMC->adjMatrix = adjMatrix;
        currentMapMC->nProvision = nProvision;
        return currentMapMC;
    }
    return NULL;
}

int** setAdjMatrix(int** adjMatrix, int originCity, int destinationCity, int cost)
{
    if (NULL != adjMatrix) 
    {
        adjMatrix[originCity-1][destinationCity-1] = cost;
        adjMatrix[destinationCity-1][originCity-1] = cost;
        return adjMatrix;
    }
    return NULL;
}

int closeFile(FILE* file, char* fileName)
{
    if (NULL != file && NULL != fileName) 
    {
        if(0 == fclose(file))
        {
            #ifdef DEBUG
                printf("Archivo '%s' cerrado.\n", fileName);
            #endif
            return SUCCESS;
        }
    }
    printf("Error al cerrar el archivo '%s'.\n", fileName);
    return ERROR_CLOSE;
}

mapKC* getMapKC()
{
    char* fileName = getFileName();
    if(NULL != fileName)
    {
        FILE* currentFile = openFile(fileName, "rb");
        if(NULL != currentFile)
        {
            mapKC* currentMapKC = readFile(currentFile);
            if(NULL != currentMapKC)
            {
                int status = closeFile(currentFile, fileName);
                if(SUCCESS == status)
                {
                    free(fileName);
                    printf("\nArchivo cargado correctamente.\n");
                    return currentMapKC;
                }
                #ifdef DEBUG
                    printf("No es posible cerrar el archivo '%s'\n", fileName);
                #endif
                free(currentMapKC->adjMatrix);
                free(currentMapKC);
            }
            #ifdef DEBUG
                printf("No es posible leer una matriz de adyacencia\n");
            #endif
        }
        #ifdef DEBUG
            printf("No es posible abrir el archivo '%s'\n", fileName);
        #endif
        free(fileName);
    }
    return NULL;
}

void saveFile(travel* currentTravel, char* fileName, int n)
{
    FILE* newFile = openFile(fileName, "wb");
    if (NULL != newFile) 
    {
        fprintf(newFile, "%d\n", currentTravel->cost);
        int i;
        
        fprintf(newFile, "0-");
        for(i = 0; i < n; i++)
        {   
            if (i < n - 1) {
                fprintf(newFile, "%d-", currentTravel->route[i]+1);
            }
            
            if (i == (n - 1))
            {
                fprintf(newFile, "%d", currentTravel->route[i]+1);
                fprintf(newFile, "-0");
            }
           
        }
        printf("Archivo solucion creado correctamente.\n");      
        closeFile(newFile, fileName);  
    }
    
}
