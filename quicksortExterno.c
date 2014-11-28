#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "vetor.h"
#include "ordenacaoInterna.h"
#define TAM_BUFFER 3

void quicksortExterno(int, int, FILE *, FILE *, FILE *);
void particao(int, int, int*, int*, FILE *, FILE *, FILE *);
void lerSup(FILE *,int *, int *, int *);
void lerInf(FILE *,int *, int *, int *);
void escreverSup(FILE *, int *, int );
void escreverInf(FILE *, int *, int );
void extrairSup(int *, int *, int *);
void extrairInf(int *, int *, int *);
void inserirBuffer(int *, int, int *);


void quicksortExterno(int esq, int dir, FILE *fileLEs, FILE *fileLi, FILE *fileEi)
{
    int i, j;

    if (dir - esq >= 1)
    {
	puts("Chamando Partição");
        particao(esq, dir, &i, &j, fileLEs, fileLi, fileEi);
        printf("Valor de i = %d\n", i);
	printf("Valor de j = %d\n", j);

	if (i - esq < dir - j) 
        {
            quicksortExterno(esq, i, fileLEs, fileLi, fileEi);
            quicksortExterno(j, dir, fileLEs, fileLi, fileEi);
        }
        else 
        {
            quicksortExterno(j, dir, fileLEs, fileLi, fileEi);
            quicksortExterno(esq, i, fileLEs, fileLi, fileEi);
        }
    }
    
    return;
}

void particao(int esq, int dir, int *i, int *j, FILE *fileLEs, FILE *fileLi, FILE *fileEi)
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
                lerInf(fileLi, &li, &ultimo_lido, &ler_sup);

            inserirBuffer(buffer, ultimo_lido, &qtd_buffer);
        }
        else
        { 
            if (ls == es) 
                lerSup(fileLEs, &ls, &ultimo_lido, &ler_sup);
            else if (li == ei)
                lerInf(fileLi, &li, &ultimo_lido, &ler_sup);
            else
                if (ler_sup)
                    lerSup(fileLEs, &ls, &ultimo_lido, &ler_sup);
                else
                    lerInf(fileLi, &li, &ultimo_lido, &ler_sup);
           
	    printf("Valor atual de j = %d", *j);
	    printf("Valor atual de i = %d", *i);	 
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
                escreverInf(fileEi, &ei, ultimo_lido);
            }
            else
                inserirBuffer(buffer, ultimo_lido, &qtd_buffer);

            // Ordenar o buffer neste ponto
            quicksort(buffer, 0, qtd_buffer-1);
            puts("\nMemória interna ordenada!!");
            imprime_vetor(buffer, qtd_buffer);

            if (ei - esq < dir - es)
            { 
                extrairInf(buffer, &ultimo_lido, &qtd_buffer);
                escreverInf(fileEi, &ei, ultimo_lido);
                lim_inf = ultimo_lido;
                
            }
            else
            {
                extrairSup(buffer, &ultimo_lido, &qtd_buffer);
                escreverSup(fileLEs, &es, ultimo_lido);
                lim_sup = ultimo_lido;

            }
        }
    }
    
    while (ei <= es) 
    {
        extrairInf(buffer, &ultimo_lido, &qtd_buffer);
        escreverInf(fileEi, &ei, ultimo_lido);
    }

}

void lerSup(FILE *fileLEs, int *ls, int *ultimo_lido, int *ler_sup) 
{
    fseek(fileLEs,sizeof(int) * (*ls-1), SEEK_SET);
    fread(ultimo_lido, sizeof(int), 1, fileLEs);
    (*ls)--;
    *ler_sup = 0;
}

void lerInf(FILE *fileLi,int *li, int *ultimo_lido, int *ler_sup)
{
    fread(ultimo_lido, sizeof(int), 1, fileLi);
    (*li)++;
    *ler_sup = 1;
}
void escreverSup(FILE *fileLEs, int *es, int ultimo_lido)
{
    fseek(fileLEs, sizeof(int) * (*es-1), SEEK_SET);
    fwrite(&ultimo_lido, sizeof(int), 1, fileLEs);
    (*es)--;
}
void escreverInf(FILE *fileEi, int *ei, int ultimo_lido)
{
    fwrite(&ultimo_lido, sizeof(int), 1, fileEi);
    (*ei)++;
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
}

