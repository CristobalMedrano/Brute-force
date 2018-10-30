#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    #ifdef DEBUG
        printf("debug_mode");
    #endif
    printf("brute_force");
    return 0;
}
