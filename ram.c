#include "ram.h"
#include <math.h>
#include <stdbool.h>
#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Cria uma memória RAM de tamanho customizável
RAM *criarRAM(const int tamanho)
{
    RAM *ram = malloc(sizeof(RAM));
    ram->tamanho = tamanho;
    ram->memoria = malloc(tamanho * sizeof(int));
    return ram;
}

// Assume valores aleatórios para uma RAM
void criarRAM_aleatoria(RAM *ram, const int tamRam)
{
    srand(time(NULL));
    ram->tamanho = tamRam;
    ram->memoria = malloc(tamRam * sizeof(int));
    for (int i = 0; i < tamRam; i++) 
    {
        ram->memoria[i] = rand();
    }
}

// Insere o dado(int) especificado para a RAM
void setDado(RAM *ram, int endereco, int conteudo) 
{
    if (endereco >= 0 && endereco < ram->tamanho)
    {
        ram->memoria[endereco] = conteudo;
    }
}

// Retorna um dado contido no endereço especificado da RAM
int meDEpapai(const RAM *ram, int endereco)
{
    if (endereco >= 0 && endereco < ram->tamanho)
    {
        return ram->memoria[endereco];
    }
    return -1;
}

// Imprime todo o conteúdo contido em uma RAM
void imprimirRAM(const RAM *ram) 
{
    printf("Conteudo da RAM:\n");
    for (int i = 0; i < ram->tamanho; i++)
    {
        printf("%d, ", ram->memoria[i]);
    }
    printf("\n");
}

//Libera a RAM
RAM *freeRAM(RAM *ram) 
{
    free(ram->memoria);
    free(ram);
    return ram;
}

// Cria uma RAM vazia
void emptyRAM(RAM *ram, int tamanho) 
{
    ram->tamanho = tamanho;
    ram->memoria = calloc(tamanho, sizeof(int));
}

// funcoes novas 
// usar para funcoes char e programas char
// tam char e o tamanho da string 
// n tamanho da matriz para armazenar multiplos strings possiveis
RAM *allocaCHar(int n, int tamchar)
{
    RAM* r = malloc(sizeof(RAM));
    r->memoriaParaChar = malloc(sizeof(char*)*n);
    for (int i = 0; i < n; i++)
    {
        r->memoriaParaChar[i] = malloc(sizeof(char)*tamchar);
    }
    return r;
}

// inicializa a ram com qualquer numero em todas as possicoes vai presisar para funcao fatorial do professor
void criarRAM_NUM_inicializado(RAM *ram, int tamRam, int NUM){
    
    for (int i = 0; i < tamRam; i++)
    {
        ram->memoria[i] = NUM;
    }
}

void freeCharAlloc(RAM *ram, int tamanho){
    for (int i = 0; i < tamanho; i++)
    {
        free(ram->memoriaParaChar[i]);
    }
    
    free(ram->memoriaParaChar);
    
}


/*
void aleatorio (RAM ram, int tam, int ammountIterations){

    for (int i = 0; i < ammountIterations; i++) // trocar coisas de lugar
    {
         srand(time(NULL));
         int index_one = rand()%tam;
         int index_two = rand()%tam;
         abs(index_one);
         abs(index_two);

        int aux;
        int bb = meDEpapai(ram,index_one);
        int cc = meDEpapai(ram,index_two);
        aux = bb;
        placeDado(ram,index_one,cc);
        placeDado(ram,index_two,aux);

    }


    for (int i = 0; i < ammountIterations; i++)
    {
         srand(time(NULL));
         int index_one = rand()%tam;
         int index_two = rand()%tam;
         abs(index_one);
         abs(index_two);

        ram.memoria[i] = ram.memoria[index_one] + ram.memoria[index_two];
    }
    
}
*/

