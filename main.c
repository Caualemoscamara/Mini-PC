#include "cpu.h"
#include "programas.h"
#include "ram.h"
#include <math.h>
#include <stdbool.h>
#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main () {
    RAM *r;
    CPU *c;
    int **matA;
    int **matB;
    int tamMat;

    r = criarRAM(50);
    c = criarCPU();

    //bernouliiInput utiliza o programa: bernoulli_probability, que é formado por: binomial_coeff
    //bernouliiInput(r,c);

    //Realiza multiplicação básica, retorno em int para reutilização em outros programas;
    //int a = multiplicate(r,c,5,5);

    //Retorna o valor especificado em fatorial
    //fatorialPc(r,c,12);

    //Soma matrizes quadradas de proporção customizável
    //printf("Digite o tamanho da matriz: ");
    //scanf("%d",&tamMat);
    //sumMat(r,c,tamMat,matA,matB);
    
    //Raiz quadrada aproximada
    //raiz_scuffed(r,c,82);

    //Imprime ram aleatória
    //aleatorio(r,c,6);

    //Realiza divisão simples aproximada
    //int a = divide(r, c, 10345, 8);
    
    //Media de valores aleatórios
    //calcularMedia(r,c);

    //Mediana de valores aleatórios
    //calcularMediana(r,c);

    //Calcula a moda entre 10 valores aleatórios
    //calcularModa(r,c);

    //Calcula o termo n da sequência de Fibonacci 
    //calcularFibonacci(r,c);
    
    //Progressão aritmética
    //pa(r,c);

    //Progressão Geométrica
    //pg(r,c);
    
    r = freeRAM(r);
    c = liberaCPU(c);
    return 0;
}



