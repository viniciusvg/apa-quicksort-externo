#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "vetor.h"

/*Imprime os elementos de um vetor.
    @v vetor a ser impresso
    @n tamanho do vetor a ser impresso
*/
void imprime_vetor(int *v, int tam)
{
    int i;

    for (i = 0; i < tam; i++)
        printf("%d ", v[i]);
    
    return;
}

int verifica_ordem(int *v, int tam)
{
    int i;
    for (i = 0; i < tam-1; i++)
        if (v[i] > v[i+1])
            return 0;
    
    return 1;
}

void copia_vetor(int *src, int *dst, int tam)
{
    int i;

    for (i = 0; i < tam; i++)
        dst[i] = src[i];

    return;
}


void gerar_numeros(int *v, int tam)
{
    int r,i;
    srand(time(NULL));
    for(i=0;i<tam;i++){ 
        v[i] = rand();    
    }
    return;
}
