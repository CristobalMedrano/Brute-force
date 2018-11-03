/*
	Autor/Author: Cristobal Medrano Alvarado.
	Funciones asociadas al menu.
	Functions associated with the menu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <menu.h>

void showMenu()
{
    printf("***------------------------------***\n");
    printf("**                                **\n");
    printf("*            Reino Clover          *\n");
    printf("*            Version 0.0           *\n");
    printf("**                                **\n");
    printf("***------------------------------***\n");
    printf("\n");
    printf("1.- Obtener ruta minima de recursos.\n");
    printf("2.- Acerca de.\n");
    printf("3.- Salir.\n\n");
    printf("Ingrese la opcion deseada: ");
}

void validateMenuOption(int* option, int min, int max)
{
    do
    {
        fflush(stdin);
        if ((scanf("%d", option) == 0) || (*option < min || *option > max))
        {
            while (getchar() != '\n');
            printf("Error. Ingrese una opcion valida: ");
            fflush(stdin);
        }
         
    } while (*option < min || *option > max);
}
  
void cleanScreen()
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif
 
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void pressToContinue()
{
    fflush(stdin);
    printf("\nPresione intro para continuar...");
    getchar();
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        getchar();
    #endif      
}
  
char* getFileName()
{
    printf("Ingrese el nombre del archivo: ");
    char file[256];
	char* filename = (char*)malloc(sizeof(char)*256);
    fflush(stdin);
    scanf("%s", file);
    fflush(stdin);
    strcpy(filename, file);
    return filename;
}
 
void about()
{
	cleanScreen();
    printf("Reino Clover (Lab 1: Fuerza Bruta - Algoritmos Avanzados).\n\n");
    printf("Nombre: Cristobal Nicolas Medrano Alvarado.\n");
    printf("Rut: 19.083.864-1\n");
    printf("Correo: cristobal.medrano@usach.cl\n");
	pressToContinue();
}

void menu(int* option, int min, int max)
{
	cleanScreen();
	showMenu();
	validateMenuOption(option, min, max);
}