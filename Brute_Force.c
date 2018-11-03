#include <stdio.h>
#include <stdlib.h>
#include <brute_force.h>
#include <menu.h>

int main(int argc, char const *argv[])
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
    return 0;
}

void initBruteForce()
{

}
