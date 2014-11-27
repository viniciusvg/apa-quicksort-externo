#include <stdlib.h>
#include <limits.h>

void quicksort_externo(int, int);
void particao(int, int, int*, int*);
int lerSup(Descritor e ls, int *);
int lerInf(Descritor e li, int *);
void escreverSup(Descritor e es, int);
void escreverInf(Descritor e ei, int);
int extrairSup(int *);
int extrairInf(int *);
void inserirBuffer(int *, int);


void quicksort_externo(int esq, int dir)
{
    int i, j;

    if (dir - esq >= 1)
    {
        particao(esq, dir, &i, &j);
        if (i - esq < dir - j) 
        {
            quicksort_externo(esq, i);
            quicksort_externo(j, dir);
        }
        else 
        {
            quicksort_externo(j, dir);
            quicksort_externo(esq, i);
        }
    }
    
    return;
}

void particao(int esq, int dir, int *i, int *j)
{
    int linf, lsup;
    int ei, es, li, ls;
    int ultimo_lido;  
    int qtd_buffer;
    int ler_sup;

    int buffer[3];

    linf = INT_MIN;
    lsup = INT_MAX;
    let_sup = 1;


    /*Alinha ponteiros de leitura e escrita aqui:
        Li e Ei <- começam em esq
        Ls e Es <- comecma em dir
    */

    li = ei = esq;
    ls = es = dir;

    while (li <=ls)
    {
        if (qtd_buffer < tam_buffer -1) 
        {
            if (ler_sup) {
                lerSup(Descritor, &ls, &ultimo_lido);
                ler_sup = 0;
            }
            else
            {
                lerInf(Descritor, &li, &ultimo_lido);
                ler_sup = 1;
            }

            inserirBuffer(buffer, ultimo_lido, &tam_buffer);
        }
        else

    }

}


