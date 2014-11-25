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
    int j, chave, i, inicio, fim, meio, flag, x, temp,index;
    for(j=1; j < tam; j++){
        chave = v[j];
        i = j - 1;
        inicio = 0;
        fim = j;
        flag = 0;
        meio = (int)((inicio+fim)/2);
        while(inicio < fim){
            if(chave < v[meio]){
                fim = meio - 1;
                flag = 1; 
            }else{
                inicio = meio + 1;
            }
            meio = (int)((inicio+fim)/2);
        }
        x=j;
       
        if(flag == 1 && (v[meio] < chave))
            index = meio + 1;
        else
            index = meio;
 
        while(x != index){
            v[x] = v[x-1];
            x = x-1;
        }
        v[index] = chave;
    }
}

