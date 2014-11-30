#include <stdlib.h>
#include <stdio.h>
#define ARQUIVO "arquivo.bin"
#define ORDENADO "ordenado.bin"

void main(int argc, char *argv[])
{
    char * file = ARQUIVO;
    int tam,i;
    int inicio, fim, meio;
    FILE *fd_LEs;
    FILE *fd_Ei;
    FILE *fd_Li;

    if(argc < 3){
        printf("Usage: %s quantidade GerarArquivo(y/n)\n",argv[0]);
  
        exit(1);
    }
        
    tam = atoi(argv[1]);

    /* gera um arquivo com inteiros aleatorios */
    if(strcmp(argv[2],"y") == 0){
        gerar_arquivo(tam,ARQUIVO);
        //exit(1);
    }

    printf("[+] arquivo:%s\n",file);

    fd_LEs = posi_arquivo(ORDENADO);
    fd_Li = posi_arquivo(ORDENADO);
    fd_Ei = posi_arquivo(ORDENADO);
    puts("chamando quicksort externo");
    quicksortExterno(1, tam, &fd_LEs, &fd_Li);

    fclose(fd_LEs);
    fclose(fd_Li);
    fclose(fd_Ei);
}
