#include "ordenacaoInterna.h"
#include <time.h>
#include <stdlib.h>

void insertionSort(int *v, int tam)
{
    int j, chave, i;
    for(j=1; j < tam; j++){
        chave = v[j];
        i = j - 1;
        while(i>=0 && v[i]>chave){
            v[i+1] = v[i];
            i--;
        }
        v[i+1] = chave;
    }
}


void insertionSortBB(int *v, int tam)
{
    int j, chave, i, inicio, fim, meio, achou, x;
    for(j=1; j < tam; j++){
        chave = v[j];
        i = j - 1;
        inicio = 0;
        fim = tam;
        meio = (int)(inicio+fim/2); /* parte inteira */
        while(inicio <= fim && achou == 0){
            if(v[meio] == chave){
                achou = 1;
            }else{ 
                if(chave < v[meio])
                    fim = meio - 1;
                else
                    inicio = meio + 1;
                meio = (int)(inicio+fim/2);
            }   
        }
        x=j;
        while((x-1) != meio)
            v[x] = v[--x];
        if(achou = 0)
            v[meio] = chave;
        else
            v[meio+1] = chave;   
    }
}

