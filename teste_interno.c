/*Programa para testar o funcionamento dos algoritmos
de ordenação interna*/

#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include "ordenacaoInterna.h"
#define TAM 5

int main(void)
{
    
    int escolha = 0;

    int vetor[TAM] = {9, 2, 3, 4, 11};
    int cp_vetor[TAM];

    printf("\nVetor a ser ordenado: ");
    imprime_vetor(vetor, TAM);

    printf("\nEscolha o algoritmo de ordenacao a ser testado:\n");
    printf("1 - Todos\n");
    printf("2 - Insertion sort\n");
    printf("3 - Quicksort\n");

    scanf("%d", &escolha);

    printf("Escolha: ");
    switch(escolha)
    {
        case 1:
            printf("todos.\n");
            
            copia_vetor(vetor, cp_vetor, TAM);
            
            quicksort(cp_vetor, 0, TAM-1);
            imprime_vetor(cp_vetor, TAM);

            if(verifica_ordem(cp_vetor, TAM))
                puts("Esta ordenado");
            else
                puts("Vetor nao ordenado");
            break;
        case 2:
            printf("insertion sort.\n");
            break;
        case 3:
            printf("quicksort\n");
            break;
        default:
            printf("nenhum\n");
            break;
    }

    return 0;

}
