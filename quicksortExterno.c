#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "vetor.h"
#include "ordenacaoInterna.h"
#define TAM_BUFFER 3

void quicksortExterno(int, int, FILE **, FILE **, int);
void particao(int, int, int*, int*, FILE **, FILE **, int);
void lerSup(FILE **,int *, int *, int *);
void lerInf(FILE **,int *, int *, int *);
void escreverSup(FILE **, int *, int );
void escreverInf(FILE **, int *, int );
void extrairSup(int *, int *, int *, int *, int);
void extrairInf(int *, int *, int *, int *, int);
void inserirBuffer(int *, int, int *, int *);
void ordenarBuffer(int *, int, int, int);

void quicksortExterno(int esq, int dir, FILE **fileLEs, FILE **fileLEi, int tipoOrdenacao)
{
    int i, j;

    if (dir - esq >= 1)
    {
        particao(esq, dir, &i, &j, fileLEs, fileLEi, tipoOrdenacao);

        fflush(*fileLEs);
        fflush(*fileLEi);       
	if (i - esq < dir - j) 
        {
            quicksortExterno(esq, i, fileLEs, fileLEi, tipoOrdenacao);
            quicksortExterno(j, dir, fileLEs, fileLEi, tipoOrdenacao);
        }
        else 
        {
            quicksortExterno(j, dir, fileLEs, fileLEi, tipoOrdenacao);
            quicksortExterno(esq, i, fileLEs, fileLEi, tipoOrdenacao);
        }
    }
    else
        puts("[quicksortExterno] Nada a fazer.");
    
    return;
}

void particao(int esq, int dir, int *i, int *j, FILE **fileLEs, FILE **fileLEi, int tipoOrdenacao)
{
    int lim_inf, lim_sup;
    int ei, es, li, ls;
    int ultimo_lido;  
    int qtd_buffer = 0;
    int ler_sup;
    int ordenado;
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
        if (qtd_buffer < TAM_BUFFER -1) 
        {
            if (ler_sup) 
                lerSup(fileLEs, &ls, &ultimo_lido, &ler_sup);
            else
                lerInf(fileLEi, &li, &ultimo_lido, &ler_sup);

            inserirBuffer(buffer, ultimo_lido, &qtd_buffer, &ordenado);
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
                escreverSup(fileLEs, &es, ultimo_lido);
            }
            else if (ultimo_lido < lim_inf)
            {
                *i = ei;
                escreverInf(fileLEi, &ei, ultimo_lido);
            }
            else
            {
                inserirBuffer(buffer, ultimo_lido, &qtd_buffer, &ordenado);
            
                           
                if (ei - esq < dir - es)
                {
                    extrairInf(buffer, &ultimo_lido, &qtd_buffer, &ordenado, tipoOrdenacao);
                    escreverInf(fileLEi, &ei, ultimo_lido);
                    lim_inf = ultimo_lido;
                }
                else
                {
                    extrairSup(buffer, &ultimo_lido, &qtd_buffer, &ordenado, tipoOrdenacao);
                    escreverSup(fileLEs, &es, ultimo_lido);
                    lim_sup = ultimo_lido;
                }
            }
        }
    }
    
    while (ei <= es) 
    {
        extrairInf(buffer, &ultimo_lido, &qtd_buffer, &ordenado, tipoOrdenacao);
        escreverInf(fileLEi, &ei, ultimo_lido);
    }

}

void lerSup(FILE **fileLEs, int *ls, int *ultimo_lido, int *ler_sup) 
{
    fseek(*fileLEs,sizeof(int) * (*ls-1), SEEK_SET);
    fread(ultimo_lido, sizeof(int), 1, *fileLEs);
    (*ls)--;
    *ler_sup = 0;
}

void lerInf(FILE **fileLEi,int *li, int *ultimo_lido, int *ler_sup)
{
    fseek(*fileLEi, sizeof(int) * (*li-1), SEEK_SET);
    fread(ultimo_lido, sizeof(int), 1, *fileLEi);
    (*li)++;
    *ler_sup = 1;
}
void escreverSup(FILE **fileLEs, int *es, int ultimo_lido)
{

    fseek(*fileLEs, sizeof(int) * (*es-1), SEEK_SET);
    fwrite(&ultimo_lido, sizeof(int), 1, *fileLEs);
    (*es)--;
}
void escreverInf(FILE **fileLEi, int *ei, int ultimo_lido)
{

    fseek(*fileLEi, sizeof(int) * (*ei-1), SEEK_SET);
    fwrite(&ultimo_lido, sizeof(int), 1, *fileLEi);
    (*ei)++;
}
void extrairSup(int *buffer, int *ultimo_lido, int *qtd_buffer, int *ordenado, int tipoOrdenacao)
{
    if (!*ordenado) 
    {
        // Ordenar o buffer neste ponto
        ordenarBuffer(buffer, 0, *qtd_buffer, tipoOrdenacao);
        puts("Memória interna ordenada!\n");
        //imprime_vetor(buffer, *qtd_buffer);
        //puts("\n--------");
        *ordenado = 1;
    }

    *ultimo_lido = buffer[*qtd_buffer - 1];
    (*qtd_buffer)--;

}

void extrairInf(int *buffer, int *ultimo_lido, int *qtd_buffer, int *ordenado, int tipoOrdenacao)
{
    int i;

    if (!*ordenado) 
    {
        // Ordenar o buffer neste ponto
        ordenarBuffer(buffer, 0, *qtd_buffer, tipoOrdenacao);
        puts("Memória interna ordenada!\n");
        //imprime_vetor(buffer, *qtd_buffer);
        //puts("\n--------");
        *ordenado = 1;
    }

    *ultimo_lido = buffer[0];
    for (i = 0; i < *qtd_buffer - 1; i++)
        buffer[i] = buffer[i+1];
    (*qtd_buffer)--;
}

void inserirBuffer(int *buffer, int ultimo_lido, int *qtd_buffer, int *ordenado)
{
    buffer[*qtd_buffer] = ultimo_lido;
    (*qtd_buffer)++;
    *ordenado = 0;
}

void ordenarBuffer(int *buffer, int inicio, int tamanho, int tipoOrdenacao)
{
    switch(tipoOrdenacao)
    {
        case 0:
            puts("[quicksortExterno] Executando o quicksort.");  
            quicksort(buffer, inicio, tamanho - 1);
            break;
        case 1:
            //chamar insertionSort
            puts("Não implementado ainda");
            break;
    }
}
