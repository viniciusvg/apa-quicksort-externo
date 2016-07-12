/* Apenas um test! */
#include "ordenacaoInterna.h"
#include <time.h>
#include <stdlib.h>

int partition(int *v, int esq, int dir)
{
    int i, j;
    int troca;
    
    i = esq;   
 
    for(j = esq + 1; j <= dir; j++)
        if (v[j] < v[esq]) {
            i++;
            troca = v[i];
            v[i] = v[j];
            v[j] = troca;
        }
    troca = v[i];
    v[i] = v[esq];
    v[esq] = troca;

    return i;
}

void quicksort(int *v, int esq, int dir)
{
    int r;

    if(esq < dir)
    {
        r = partition(v, esq, dir);
        quicksort(v, esq, r - 1);
        quicksort(v, r + 1, dir);
    }
}

