#ifndef _FUNC_MENU_H_
#define _FUNC_MENU_H_
 
/*
    Funciones del Menu.
    Menu Functions.
*/

void showMenu();
void validateOption(int* option, int min, int max);
void cleanScreen();
void pressToContinue();
char* getFileName();
void about();
void menu(int* option, int min, int max);
#endif