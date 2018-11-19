#ifndef _STRUCTS_H
#define _STRUCTS_H
/*

*/
typedef struct mapKC
{
    int nProvision;
    int** adjMatrix;

} mapKC ;

typedef struct travel
{
    int* route;
    int cost;

} travel;

#endif