#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <read_file.h>

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

FILE* openFile(char* fileName)
{
    FILE* currentFile = fopen(fileName, "rb");
    if(NULL != currentFile)
    {
        printf("Archivo '%s' abierto\n", fileName);
        return currentFile;
    }
    printf("Error: El archivo '%s' no existe.\n", fileName);
    return NULL;
}

int** readFile(FILE* currentFile)
{
    if(NULL != currentFile)
    {
        int nProvision      = 0;
        fscanf(currentFile, "%d", &nProvision);

        int** adjMatrix     = createAdjMatrix(nProvision);
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
            showAdjMatrix(nProvision, adjMatrix);
        #endif
        return adjMatrix;
    }
    return NULL;
}

int** createAdjMatrix(int nProvision)
{
    int i = 0;
    int** adjMatrix = (int **)calloc(nProvision, sizeof(int *));
                        for (i = 0; i < nProvision; i++)
                        adjMatrix[i] = (int *)calloc(nProvision, sizeof(int));
    if(NULL != adjMatrix)
    {
        return adjMatrix;
    }
    printf("Memoria insuficiente: createAdjMatrix()\n");
    printf("Error: read_file.c\n");
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

void showAdjMatrix(int nProvision, int** adjMatrix)
{
    if(NULL != adjMatrix && nProvision >= 0)
    {
        int i = 0;
        for(i = 0; i < nProvision; i++)
        {
            int j = 0;
            for(j = 0; j < nProvision; j++)
            {
                if (adjMatrix[i][j] > 9) 
                {
                    printf("%d  ", adjMatrix[i][j]);
                }
                else
                {
                    printf("%d   ", adjMatrix[i][j]);
                }
            }
            printf("\n");
        }
    }   
}

int closeFile(FILE* file, char* fileName)
{
    if (NULL != file && NULL != fileName) 
    {
        if(0 == fclose(file))
        {
            printf("Archivo '%s' cerrado.\n", fileName);
            return SUCCESS;
        }
    }
    printf("Error al cerrar el archivo '%s'.\n", fileName);
    return ERROR_CLOSE;
}

int** getAdjMatrixFromFile()
{
    char* fileName = getFileName();
    if(NULL != fileName)
    {
        FILE* currentFile = openFile(fileName);
        if(NULL != currentFile)
        {
            int** adjMatrix = readFile(currentFile);
            if(NULL != adjMatrix)
            {
                int status = closeFile(currentFile, fileName);
                if(SUCCESS == status)
                {
                    free(fileName);
                    return adjMatrix;
                }
                #ifdef DEBUG
                    printf("No es posible cerrar el archivo '%s'", fileName);
                #endif
                free(adjMatrix);
            }
            #ifdef DEBUG
                printf("No es posible leer una matriz de adyacencia");
            #endif
        }
        #ifdef DEBUG
            printf("No es posible abrir el archivo '%s'", fileName);
        #endif
        free(fileName);
    }
    return NULL;
}