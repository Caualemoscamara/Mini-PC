#ifndef PROGRAMAS_H
#define PROGRAMAS_H
#include "cpu.h"
#include "ram.h"
#include <math.h>
#include <stdbool.h>
#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    RAM *ram;
    CPU *cpu;
} Programas;

void swap(char *a, char *b);
void shuffle(char array[][30], int n);
//int fatorial (RAM ram, int fat);
int probability_selector_attempts(RAM ram, char *champ,char **champs, int attempts, Instrucao inst, int qtd_vez);
void bernouliiInput (RAM *ram, CPU *cpu);
int multiplicate (RAM *ram, CPU *cpu, int num, int numAmmountMultiply);
int fatorialPc (RAM *ram ,CPU *cpu, int fat);
int binomial_coeff(RAM *ram,CPU *cpu,int n, int k);
double bernoulli_probability(RAM *ram, CPU *cpu,int n, int k, double p);
void raiz_scuffed(RAM *ram, CPU *cpu, int numRaiz); // feito
void aleatorio (RAM *ram, CPU *cpu, int ammountIterations);// feito
void sumMat(RAM* ram, CPU* cpu, int prop, int **matrizA, int **matrizB);
int divide(RAM* ram, CPU* cpu, int dividendo, int divisor);
void calcularMedia(RAM *ram, CPU *cpu);
void calcularModa(RAM *ram, CPU *cpu);
void calcularMediana(RAM *ram, CPU *cpu);
void calcularFibonacci(RAM *ram, CPU *cpu);
void pg(RAM* ram, CPU* cpu);
void pa (RAM *ram, CPU *cpu);


#endif

/*

   char champions[][30] = {
        "Aatrox", "Ahri", "Akali", "Alistar", "Amumu", "Anivia", "Ashe", "Aurelion Sol", "Azir", "Bard",
        "Blitzcrank", "Brand", "Braum", "Caitlyn", "Camille", "Cassiopeia", "Chogath", "Corki", "Darius",
        "Diana", "Dr. Mundo", "Ekko", "Elise", "Evelynn", "Ezreal", "Fiddlesticks", "Fiora", "Fizz",
        "Galio", "Gangplank", "Garen", "Gnar", "Gragas", "Graves", "Hecarim", "Heimerdinger", "Illaoi",
        "Irelia", "Ivern", "Janna", "Jarvan IV", "Jhin", "Jinx", "Kaisa", "Kallista", "Karma", "Karthus",
        "Kennen", "Kha'Zix", "Kindred", "Kled", "Kog'Maw", "LeBlanc", "Lee Sin", "Leona", "Lillia", "Lissandra",
        "Lucian", "Lulu", "Malphite", "Malzahar", "Maokai", "Miss Fortune", "Mordekaiser", "Nami", "Nasus",
        "Nautilus", "Neeko", "Olaf", "Orianna", "Pantheon", "Poppy", "Pyke", "Qiyana", "Rakan", "Rammus",
        "Rek'Sai", "Rell", "Renekton", "Riven", "Rumble", "Ryze", "Samira", "Sejuani", "Senna", "Seraphine",
        "Sett", "Shaco", "Shen", "Sivir", "Skarner", "Sona", "Soraka", "Swain", "Sylas", "Syndra", "Tahm Kench",
        "Taliyah", "Taric", "Teemo", "Thresh", "Tristana", "Trundle", "Tryndamere", "Twisted Fate", "Twitch",
        "Udyr", "Urgot", "Vayne", "Veigar", "Vel'Koz", "Vi", "Viego", "Viktor", "Vladimir", "Volibear",
        "Warwick", "Wukong", "Xayah", "Yasuo", "Yone", "Zac", "Zed", "Zeri", "Ziggs", "Zilean", "Zoe", "Zyra"
    };

*/