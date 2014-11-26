#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define ARQUIVO "arquivo.bin"

void main(int argc, char *argv[]){
    char * file = ARQUIVO;
    FILE * fd;
    int tam,i;
    int inicio, fim, meio;   
    FILE * fd_inicio;    
    FILE * fd_fim;    
    FILE * fd_meio;    

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
    
    /* inicio do arquivo */ 
    fd_inicio   = posi_arquivo(ARQUIVO);
    fseek(fd_inicio, 0, SEEK_SET);
 
    /* posicao atual + metade do tamanho*/ 
    fd_meio     = posi_arquivo(ARQUIVO);    
    fseek(fd_meio, sizeof(int) *5, SEEK_CUR);
   
    /* fim do arquivo */ 
    fd_fim      = posi_arquivo(ARQUIVO);    
    fseek(fd_fim, -sizeof(int), SEEK_END);


    /* Impressao dos valores */
    fread(&inicio,sizeof(int),1,fd_inicio);
    fread(&meio,sizeof(int),1,fd_meio);
    fread(&fim,sizeof(int),1,fd_fim);

    printf("[+] Valores=> inicio:%d meio:%d fim:%d\n",inicio, meio, fim); 
    fread(&meio,sizeof(int),1,fd_meio);
    printf("[+] Valores=> inicio:%d meio:%d fim:%d\n",inicio, meio, fim); 
}
