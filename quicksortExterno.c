#include <stdlib.h>
#include <limits.h>

void quicksort_externo(int, int);
void particao(int, int, int*, int*);
int lerSup(Descritor e ,int *, int *, int *);
int lerInf(Descritor e ,int *, int *, int *);
void escreverSup(Descritor e, int *, int );
void escreverInf(Descritor e, int *, int );
int extrairSup(int *, int *, int *);
int extrairInf(int *, int *, int *);
void inserirBuffer(int *, int, int *);


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
    int lim_inf, lim_sup;
    int ei, es, li, ls;
    int ultimo_lido;  
    int qtd_buffer;
    int ler_sup;

    int buffer[3];

    lim_inf = INT_MIN;
    lim_sup = INT_MAX;
    ler_sup = 1;


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
            if (ler_sup) 
                lerSup(Descritor, &ls, &ultimo_lido, &ler_sup);
            else
                lerInf(Descritor, &li, &ultimo_lido, &ler_sup);

            inserirBuffer(buffer, ultimo_lido, &tam_buffer);
        }
        else
        { 
            if (ls == es) 
                lerSup(Desc, &ls, &ultimo_lido, &ler_sup);
            else if (li == ei)
                lerInf(Desc, &li, &ultimo_lido, &ler_sup);
            else
                if (ler_sup)
                    lerSup(Desc, &ls, &ultimo_lido, &ler_sup);
                else
                    lerInf(Desc, &li, &ultimo_lido, &ler_sup);
            
            if (ultimo_lido > lim_sup)
            {
                j = es;
                escreverSup(fdesc, &es, ultimo_lido);
            }
            else if (ultimo_lido < lim_inf)
            {
                i = ei;
                escreverInf(fdesc, &ei, ultimo_lido);
            }
            else
                inserirBuffer(buffer, ultimo_lido, &tam_buffer);

            // Ordenar o buffer neste ponto
            // call ordenacao(buffer, tam_buffer)

            if (ei - esq < dir - es)
            { 
                extrairInf(buffer, &ultimo_lido, &tam_buffer);
                escreverInf(desc, &ei, ultimo_lido);
                lim_inf = ultimo_lido;
                
            }
            else
            {
                extrairSup(buffer, &ultimo_lido, &tam_buffer);
                escreverSup(desc, &es, ultimo_lido);
                lim_sup = ultimo_lido;

            }
        }
    }
    
    while (ei <= es) 
    {
        extrairInt(buffer, &ultimo_lido, &tam_buffer);
        escreverInf(desc, &ei, ultimo_lido);
    }

}

int lerSup(FILE **fileLEs, int *ls, int *ultimo_lido, int *ler_sup) 
{
    fseek(*fileLEs,sizeof(int) * (*ls-1), SEEK_SET);
    fread(ultimo_lido, sizeof(int), 1, *fileLEs);
    (*ls)--;
    *ler_sup = 0;
}

int lerInf(FILE **fileLi,int *li, int *ultimo_lido, int *ler_sup)
{
    fread(ultimo_lido, sizeof(int), 1, *fileLi);
    (*li)++;
    *ler_sup = 1;
}
void escreverSup(FILE **fileLEs, int *es, int ultimo_lido)
{
    fseek(*fileLEs, sizeof(int) * (*es-1), SEEK_SET);
    fwrite(&ultimo_lido, sizeof(int), 1, *fileLEs);
    (*es)--;
}
void escreverInf(FILE **fileEi, int *ei, int ultimo_lido)
{
    fwrite(&ultimo_lido, sizeof(int), 1, *fileEi);
    (*ei)++;
}
int extrairSup(int *buffer, int *ultimo_lido, int *tam_buffer)
{
}

int extrairInf(int *buffer, int *ultimo_lido, int *tam_buffer)
{
}

void inserirBuffer(int *buffer, int ultimo_lido, int *tam_buffer)
{
}

