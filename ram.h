#ifndef RAM_H
#define RAM_H

#include <math.h>
#include <stdbool.h>
#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define uma estrutura que classifica as instruções dadas para uma operação
typedef struct {
    int add1;
    int add2;
    int add3;
    bool stop;
    int opcode;
} Instrucao;

typedef struct 
{
    int *memoria;
    int tamanho; 
    char **memoriaParaChar;

} RAM;

// Funções compartilhadas
RAM *criarRAM(int tamanho);
RAM *allocaCHar(int n, int tam);// nova
void criarRAM_aleatoria(RAM *ram, int tamRam);
void criarRAM_NUM_inicializado(RAM *ram, int tamRam, int NUM);// nova tem que ser implementada
void setDado(RAM *ram, int endereco, int conteudo);
int meDEpapai(const RAM *ram, int endereco); // troquei o nome de getdado para o nome melhorado 
void imprimirRAM(const RAM *ram);
RAM* freeRAM(RAM *ram);
void emptyRAM(RAM *ram, int tamanho);
void freeCharAlloc(RAM *ram, int tamanho);


#endif
