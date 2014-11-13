#include <stdio.h>
#include "vetor.h"

/*Imprime os elementos de um vetor.
    @v vetor a ser impresso
    @n tamanho do vetor a ser impresso
*/
void imprime_vetor(int *v, int n)
{
    int i;

    for(i = 0; i<n; i++)
        printf("%d ", v[i]);
}

int verifica_ordem(int *v, int n)
{
    int i;
    for(i = 0; i<n-1; i++)
        if(v[i] > v[i+1])
            return 0;
    
    return 1;
}
