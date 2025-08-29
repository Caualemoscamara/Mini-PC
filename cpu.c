#include "cpu.h"
#include <math.h>
#include <stdbool.h>
#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Reseta/Inicializa
CPU *criarCPU()
{
    CPU *cpu = malloc(sizeof(CPU));
    cpu->registrador1 = 0;
    cpu->registrador2 = 0;
    cpu->PC = 0;
    cpu->opcode = 0;
    cpu->programa = NULL;
    return cpu;
}

// Libera
CPU* liberaCPU(CPU *cpu)
{
    //free(cpu->programa);
    free(cpu);
    return cpu;
}

// Adere o programa à CPU
void defPrograma(CPU *cpu, Instrucao *programa) {
    cpu->programa = programa;
}

// Inicia uma sequência de operações
void iniciar(CPU *cpu, RAM *ram)
{
    cpu->opcode = 0;
    cpu->PC = 0;

    do
    {
        Instrucao inst = cpu->programa[cpu->PC];
        cpu->opcode = inst.opcode;

        switch (cpu->opcode)
        {
        case -1://-1 -> halt
            printf("Encerrando Sessão...");
            imprimirRAM(ram);
            break;
        
        case 0:// 0 -> soma
            cpu->registrador1 = meDEpapai(ram, inst.add1);
            cpu->registrador2 = meDEpapai(ram, inst.add2);
            cpu->registrador1 += cpu->registrador2;
            setDado(ram, inst.add3, cpu->registrador1);
            break;
        
        case 1:// 1 -> subtrai
            cpu->registrador1 = meDEpapai(ram, inst.add1);
            cpu->registrador2 = meDEpapai(ram, inst.add2);
            cpu->registrador1 -= cpu->registrador2;
            setDado(ram, inst.add3, cpu->registrador1);
            break;
            
        case 2:// 2 -> copia do registrador para RAM
            if (inst.add1 == 1) 
            {
                setDado(ram, inst.add2, cpu->registrador1);
            } 
            else if (inst.add1 == 2) 
            {
                setDado(ram, inst.add2, cpu->registrador2);
            }
            break;
        
        case 3:// 3 -> copia da RAM para o registrador
            if(inst.add1 == 1)
            {
                cpu->registrador1 = meDEpapai(ram, inst.add2);
            }
            else if(inst.add1 == 2)
            {
                cpu->registrador2 = meDEpapai(ram, inst.add2);
            }
            break;
        
        case 4:// 4 -> salva conteudo externo no registrador
            if(inst.add1 == 1)
            {
                cpu->registrador1 = inst.add2;
            }
            else if(inst.add1 == 2)
            {
                cpu->registrador2 = inst.add2;
            }
            break;
        
        case 5:// 5 -> obtem conteudo externo do registrador
            if(inst.add1 == 1)
            {
                inst.add2 = cpu->registrador1;
            }
            else if(inst.add1 == 2)
            {
                inst.add2 = cpu->registrador2;
            }
            break;
        }
        cpu->PC++;
    }while(cpu->opcode != -1);
    
}