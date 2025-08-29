#ifndef CPU_H
#define CPU_H

#include "ram.h"
#include <math.h>
#include <stdbool.h>
#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define uma estrutura para qualquer CPU
typedef struct {
    int registrador1;
    int registrador2;
    int PC;
    int opcode;
    Instrucao *programa;
} CPU;

// Funções que serão compartilhadas
CPU *criarCPU();
CPU *liberaCPU(CPU *cpu);
void defPrograma(CPU *cpu, Instrucao *programa);
void iniciar(CPU *cpu, RAM *ram);

#endif
