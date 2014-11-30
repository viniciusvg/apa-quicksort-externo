#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "vetor.h"
#include "ordenacaoInterna.h"
#define TAM_BUFFER 3

void quicksortExterno(int, int, FILE **, FILE **);
void particao(int, int, int*, int*, FILE **, FILE **);
void lerSup(FILE **,int *, int *, int *);
void lerInf(FILE **,int *, int *, int *);
void escreverSup(FILE **, int *, int );
void escreverInf(FILE **, int *, int );
void extrairSup(int *, int *, int *);
void extrairInf(int *, int *, int *);
void inserirBuffer(int *, int, int *);


void quicksortExterno(int esq, int dir, FILE **fileLEs, FILE **fileLEi)
{
    int i, j;

    if (dir - esq >= 1)
    {
	puts("Chamando Partição");
        puts("--------------------------");
        particao(esq, dir, &i, &j, fileLEs, fileLEi);
        puts("--------Fim Partição------");

       
        printf("Valor de i = %d\n", i);
	printf("Valor de j = %d\n", j);
	if (i - esq < dir - j) 
        {
            quicksortExterno(esq, i, fileLEs, fileLEi);
            quicksortExterno(j, dir, fileLEs, fileLEi);
        }
        else 
        {
            quicksortExterno(j, dir, fileLEs, fileLEi);
            quicksortExterno(esq, i, fileLEs, fileLEi);
        }
    }
    else
        puts("[quicksort] Nada a fazer.");
    
    return;
}

void particao(int esq, int dir, int *i, int *j, FILE **fileLEs, FILE **fileLEi)
{
    int lim_inf, lim_sup;
    int ei, es, li, ls;
    int ultimo_lido;  
    int qtd_buffer = 0;
    int ler_sup;

    int buffer[TAM_BUFFER];

    lim_inf = INT_MIN;
    lim_sup = INT_MAX;
    ler_sup = 1;
    
    *i = esq - 1;
    *j = dir + 1;

    /*Alinha ponteiros de leitura e escrita aqui:
        Li e Ei <- começam em esq
        Ls e Es <- comecma em dir
    */

    li = esq; 
    ei = esq;
    ls = dir; 
    es = dir;

    while (li <=ls)
    {
        printf("Qtd_buffer = %d\n", qtd_buffer);
        if (qtd_buffer < TAM_BUFFER -1) 
        {
            if (ler_sup) 
                lerSup(fileLEs, &ls, &ultimo_lido, &ler_sup);
            else
                lerInf(fileLEi, &li, &ultimo_lido, &ler_sup);

            inserirBuffer(buffer, ultimo_lido, &qtd_buffer);
        }
        else
        { 
            if (ls == es) 
                lerSup(fileLEs, &ls, &ultimo_lido, &ler_sup);
            else if (li == ei)
                lerInf(fileLEi, &li, &ultimo_lido, &ler_sup);
            else
                if (ler_sup)
                    lerSup(fileLEs, &ls, &ultimo_lido, &ler_sup);
                else
                    lerInf(fileLEi, &li, &ultimo_lido, &ler_sup);
           
            if (ultimo_lido > lim_sup)
            {
                *j = es;
		printf("Valor de j alterado para %d\n", *j);
                escreverSup(fileLEs, &es, ultimo_lido);
            }
            else if (ultimo_lido < lim_inf)
            {
                *i = ei;
		printf("Valor de i alterado para %d\n", *i);
                escreverInf(fileLEi, &ei, ultimo_lido);
            }
            else
            {
                inserirBuffer(buffer, ultimo_lido, &qtd_buffer);
            
                // Ordenar o buffer neste ponto
                quicksort(buffer, 0, qtd_buffer-1);
                puts("\nMemória interna ordenada!!");
                imprime_vetor(buffer, qtd_buffer);
                puts("\n--------");
           
                if (ei - esq < dir - es)
                {
                    extrairInf(buffer, &ultimo_lido, &qtd_buffer);
                    escreverInf(fileLEi, &ei, ultimo_lido);
                    lim_inf = ultimo_lido;
                    printf("Valor do lim_inf = %d\n", lim_inf);
                }
                else
                {
                    extrairSup(buffer, &ultimo_lido, &qtd_buffer);
                    escreverSup(fileLEs, &es, ultimo_lido);
                    lim_sup = ultimo_lido;
                    printf("Valor do lim_sup = %d\n", lim_sup);
                }
            }
        }
    }
    
    while (ei <= es) 
    {
        extrairInf(buffer, &ultimo_lido, &qtd_buffer);
        escreverInf(fileLEi, &ei, ultimo_lido);
    }

}

void lerSup(FILE **fileLEs, int *ls, int *ultimo_lido, int *ler_sup) 
{
    fseek(*fileLEs,sizeof(int) * (*ls-1), SEEK_SET);
    fread(ultimo_lido, sizeof(int), 1, *fileLEs);
    (*ls)--;
    printf("Valor de ls: %d\n", *ls);
    *ler_sup = 0;
}

void lerInf(FILE **fileLEi,int *li, int *ultimo_lido, int *ler_sup)
{
    fseek(*fileLEi, sizeof(int) * (*li-1), SEEK_SET);
    fread(ultimo_lido, sizeof(int), 1, *fileLEi);
    (*li)++;
    printf("Valor de li: %d\n", *li);
    *ler_sup = 1;
}
void escreverSup(FILE **fileLEs, int *es, int ultimo_lido)
{

    printf("Inserindo em A2: %d\n", ultimo_lido);  
    fseek(*fileLEs, sizeof(int) * (*es-1), SEEK_SET);
    fwrite(&ultimo_lido, sizeof(int), 1, *fileLEs);
    (*es)--;
    printf("Valor de es: %d\n\n", *es);
}
void escreverInf(FILE **fileLEi, int *ei, int ultimo_lido)
{

    printf("Inserindo em A1: %d\n", ultimo_lido);  
    fseek(*fileLEi, sizeof(int) * (*ei-1), SEEK_SET);
    fwrite(&ultimo_lido, sizeof(int), 1, *fileLEi);
    (*ei)++;
    printf("Valor de ei: %d\n\n", *ei);
}
void extrairSup(int *buffer, int *ultimo_lido, int *qtd_buffer)
{
    *ultimo_lido = buffer[*qtd_buffer - 1];
    (*qtd_buffer)--;

}

void extrairInf(int *buffer, int *ultimo_lido, int *qtd_buffer)
{
    int i;

    *ultimo_lido = buffer[0];
    for (i = 0; i < *qtd_buffer - 1; i++)
        buffer[i] = buffer[i+1];
    (*qtd_buffer)--;
}

void inserirBuffer(int *buffer, int ultimo_lido, int *qtd_buffer)
{
    buffer[*qtd_buffer] = ultimo_lido;
    (*qtd_buffer)++;
    printf("Inserindo no buffer: %d\n\n", ultimo_lido);
}

