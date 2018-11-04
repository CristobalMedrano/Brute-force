#include <stdio.h>
#include <stdlib.h>
#include <brute_force.h>
#include <menu.h>
#include <read_file.h>

void initMenu()
{
    int option;
    do
    {
        option = SIN_INGRESO;
        menu(&option, 1, 3);
 
        switch(option)
        {
            case BRUTE_FORCE: 
                initBruteForce();
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

void initBruteForce()
{
    getDataFile();
}

int main(int argc, char const *argv[])
{
    initMenu();
    return 0;
}