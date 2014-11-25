/*Programa para testar o funcionamento dos algoritmos
de ordenação interna*/

#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include "ordenacaoInterna.h"
#define TAM 1000000

int main(int argc, char * argv[])
{   
    int escolha = 0;
    int vetor[TAM];
    gerar_numeros(vetor,TAM);
    int cp_vetor[TAM];

    printf("\nVetor a ser ordenado: ");
    imprime_vetor(vetor, TAM);
    copia_vetor(vetor, cp_vetor, TAM);
    printf("\nEscolha o algoritmo de ordenacao a ser testado:\n");
    printf("1 - Todos\n");
    printf("2 - Insertion sort\n");
    printf("3 - Quicksort\n");
    printf("4 - Insertion sort (Busca Binária)\n");
    printf("Escolha: ");
    scanf("%d", &escolha);
    switch(escolha)
    {
        case 1:
            /* Quicksort */
            printf("Quicksort...");
            quicksort(cp_vetor, 0, TAM-1);

            if(verifica_ordem(cp_vetor, TAM))
                printf("ordenado ");
            else
                printf("nãoordenado");

            printf("\n");
 
            /* recupera vetor desordenado */ 
            copia_vetor(vetor, cp_vetor, TAM);
            
            /* Insertion Sort*/
            printf("Insertion sort...");
            insertionSort(cp_vetor, TAM);

            if(verifica_ordem(cp_vetor, TAM))
                printf("ordenado ");
            else
                printf("não ordena ");

            printf("\n");

             /* recupera vetor desordenado */ 
            copia_vetor(vetor, cp_vetor, TAM);
 
            /* Insertion Sort (BB)*/
            printf("Insertion sort (BB)...");

            insertionSortBB(cp_vetor, TAM);

            if(verifica_ordem(cp_vetor, TAM))
                printf("ordenado ");
            else
                printf("não ordena ");

            printf("\n");

            break;
        case 2:
            printf("Insertion sort...");
             
            insertionSort(cp_vetor, TAM);

            if(verifica_ordem(cp_vetor, TAM))
                printf("ordenado ");
            else
                printf("não ordena ");

            printf("\n");

            break;
        case 3:
            printf("Quicksort...");
            quicksort(cp_vetor, 0, TAM-1);

            if(verifica_ordem(cp_vetor, TAM))
                printf("ordenado ");
            else
                printf("não ordenao ");

            printf("\n");        

            break;
        
        case 4:
            printf("Insertion sort (BB)...");
            
            insertionSortBB(cp_vetor, TAM);

            if(verifica_ordem(cp_vetor, TAM))
                printf("ordenado ");
            else
                printf("não ordena ");
    
            printf("\n");
            
            break;

         default:
            printf("nenhum\n");
            break;
    }

    return 0;

}
