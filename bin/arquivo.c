#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>

void gerar_arquivo(int tam, char * arquivo){
    FILE *fd;
    int i, temp;
    fd = fopen(arquivo,"wb+");
    if(fd == NULL){
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(1);
    }

    /* geracao de numeros aleatorios */
    srand(time(NULL));

    for(i=0;i<tam;i++){
        temp = rand()%20;
        fwrite(&temp,sizeof(int), 1, fd);
    }


    printf("[+] Arquivo gerado com sucesso.\n");

    fclose(fd);
}

FILE * posi_arquivo(char * arquivo){
    FILE *fd;
    fd = fopen(arquivo,"rb+");
    if(fd == NULL){
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(1);
    }
    return fd;
}
