#include "programas.h"
#include <math.h>
#include <stdbool.h>
#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(char *a, char *b) 
{
    char temp[30];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

//  Fisher-Yates algorithm
// recebe o vetor champs e embaralha a ordem
// antes de chamar probability selector attempts chamar o shuffle
void shuffle(char array[][30], int n) 
{
    srand(time(NULL));

    for (int i = n - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1);  

        swap(array[i], array[j]);
    }
}

int probability_selector_attempts(RAM ram, char *champ,char **champs, int attempts, Instrucao inst, int qtd_vez){ // retorna as tentativas + sucesso ou nao

    char hold;

    if (qtd_vez == 0)
    {
        printf ("acabaram as tentativas\n");
        return attempts;
    }

 
    if (strcmp(champ, champs[attempts]) == 0)
    {
        printf ("achou\n");
        inst.stop = true;
        printf( "o campeao %s, estava na posicao %d do vetor champs\n",champ,attempts+1);
        attempts++;
        return attempts;
    }
    else 
    {
        inst.stop = false;
        printf("deseja continuar?\n responda com s/n");
        strcpy(ram.memoriaParaChar[attempts],champs[attempts]);
        scanf ("%c",&hold);
        if (hold == 's')
        {
            printf("Foi %s o campeao encontrado que nao 'e o seu\n",champs[attempts]);
            printf("deseja imprimir todos os campeos ja encontrados?\ns/n");
            fflush(stdin);
            scanf("%c",&hold);
            attempts++;
            if ('s'== hold)
            {
                for (int i = 0; i < sizeof(ram.memoriaParaChar); i++)
                {
                    printf("%s\n",ram.memoriaParaChar[i]);
                }
                
            } 
            else
            {
                printf ("ok\n");
            }    
        }
        else
        {
            if (hold == 'n')
                return attempts;
        }
    }
    
    if (inst.stop==true)
    {
        printf ("Voce parou. Eassa foi a quantidade de tentativas %d\n", attempts);
        return attempts;
    }

    probability_selector_attempts(ram, champ,champs,attempts, inst,--qtd_vez);
}

void bernouliiInput (RAM *ram, CPU *cpu){
    
    int n, k;
    double p;

    printf("Entre com o numero de tentativas (n): ");
    scanf("%d", &n);
    
    printf("Enter numero de suscessos (k): ");
    scanf("%d", &k);
    
    printf("Entre com a probabilidade de sucesso (p) [0.0 to 1.0]: ");
    scanf("%lf", &p);

    double probability = bernoulli_probability(ram,cpu,n, k, p);
    printf("\nA probabilidade de exatos %d sucessos de %d tentativas é: %lf\n", k, n, probability);
}

int multiplicate (RAM *ram, CPU *cpu, int num, int numAmmountMultiply)
{

    Instrucao instruct[5];
    Instrucao instru0;

    instru0.opcode = 4;
    instru0.add1 = 1;
    instru0.add2 = num;

    instruct[0]=instru0;


    Instrucao instru1;

    instru1.opcode = 2;
    instru1.add1 = 1;
    instru1.add2 = 0;

    instruct[1] = instru1;

    Instrucao instru2;
    instru2.opcode= 4;
    instru2.add1 = 2;
    instru2.add2 = num;

    instruct[2] = instru2;

    Instrucao instruN;
    instruN.opcode = 2;
    instruN.add1 = 2;
    instruN.add2 = 1;

    instruct [3] = instruN;

    Instrucao stop;
    stop.opcode = -1;
    instruct[4] = stop;

    defPrograma(cpu,instruct);
    iniciar (cpu,ram);

    for(int i = 0; i < numAmmountMultiply-1; i++)
    {
       Instrucao insttruct2[2];

       Instrucao instru3;
       instru3.opcode = 0;
       instru3.add1 = 0;
       instru3.add2 = 1;
       instru3.add3 = 0;

       Instrucao instru4;
       instru4.opcode = -1;
       insttruct2[0] = instru3;
       insttruct2[1] = instru4;

       defPrograma(cpu, insttruct2);
       iniciar(cpu,ram);
    }

    Instrucao instruct3[3];

    Instrucao instru5;
    instru5.opcode = 3;
    instru5.add1 = 1;
    instru5.add2 = 0;

    Instrucao instru6;
    instru6.opcode = 5;
    instru6.add1 = 1;
    instru6.add2 = -1;
    instru6.add3 = -1;

    Instrucao instru7;
    instru7.opcode = -1;

    instruct3[0] = instru5;
    instruct3[1] = instru6;
    instruct3[2] = instru7;

    defPrograma(cpu, instruct3);
    iniciar(cpu,ram);

    printf("O valor da multiplicacao : %d\n",ram->memoria[0]);

    int l = ram->memoria[0];

    return l;
}

int fatorialPc (RAM *ram ,CPU *cpu, int fat)
{

    int j = 1;

    for (int i = 1; i<=fat; i++)
    {
        // resultado da multiplicacao vai para indice 0
        int m = multiplicate(ram,cpu,j,i);
        j = ram->memoria[0];
    }

    Instrucao instruct2[3];
    Instrucao instru3;
    instru3.opcode = 3;
    instru3.add1 = 1;
    instru3.add2 = 0;

    instruct2[0] = instru3;

    Instrucao instru4;
    instru4.opcode = 5;
    instru4.add1 = 1;

    instruct2[1] = instru4;

    Instrucao instru5;
    instru5.opcode = -1;
    instruct2[2] = instru5;

    int result = ram->memoria[0];

    defPrograma(cpu, instruct2);
    iniciar(cpu,ram);
    printf("O resultado final = %d\n",result);

    int y = result;

    return y;
}

int binomial_coeff(RAM *ram, CPU *cpu,int n, int k){

  if (k>n)
    return 0;

  int fatore = fatorialPc(ram,cpu,n);
  int fatore2 = fatorialPc(ram,cpu,n-k);
  int fatore3 = fatorialPc(ram,cpu,k);
  int multin = multiplicate(ram,cpu,fatore3,fatore2);

  return (fatore / multin);
}

double bernoulli_probability(RAM *ram, CPU *cpu,int n, int k, double p){
  double binom_coef = binomial_coeff(ram,cpu,n,k);
  double probabilidade = binom_coef * pow(p,k) * pow(1-p,n-k);
  return probabilidade;
}

void raiz_scuffed(RAM *ram, CPU *cpu, int numRaiz){
    int squares[] = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100,121, 144, 169, 196, 225, 256, 289, 324, 361, 400,441, 484, 529, 576, 625, 676, 729, 784, 841, 900,961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600,1681, 1764};

    Instrucao instruct[3];
    Instrucao instru0;

    instru0.opcode = 4;
    instru0.add1 = 1;
    instru0.add2 = numRaiz;

    instruct[0]=instru0;
    Instrucao instru1;

    instru1.opcode = 2;
    instru1.add1 = 1;
    instru1.add2 = 0;

    instruct[1] = instru1;

    Instrucao instru2;
    instru2.opcode= -1;

    instruct[2] = instru2;
    defPrograma(cpu, instruct);
    iniciar(cpu,ram);

     for(int i = 0; i<42;i++)
     {
       if(squares[i] == ram->memoria[0])
       {
         	printf("\nRaiz igual a: %d\n",i+1);
            break;
       }
       else
       {
           	Instrucao instruct2[8];
         	Instrucao instruo4;
            instruo4.opcode = 4;
            instruo4.add1 = 2;
            instruo4.add2 = squares[i];
            instruct2[0] = instruo4;

            Instrucao instruu;
            instruu.opcode = 3;
            instruu.add1 = 1;
            instruu.add2 = 0;
            instruct2[1] = instruu;

            Instrucao instruo5;
            instruo5.opcode = 2;
            instruo5.add1 = 2;
            instruo5.add2 = 1;
            instruct2[2] = instruo5;

            Instrucao instruo6;
            instruo6.opcode = 1;
            instruo6.add1 = 0;
            instruo6.add2 = 1;
            instruo6.add3 = 5;
            instruct2[3] = instruo6;

            Instrucao instruo7;
            instruo7.opcode = 2;
            instruo7.add1 = 1;
            instruo7.add2 = 3;
            instruct2[4] = instruo7;

            Instrucao instruu2;
            instruu2.opcode = 4;
            instruu2.add1 = 2;
            instruu2.add2 = i;//quant de subs
            instruct2[5] = instruu2;

            Instrucao instruu3;
            instruu3.opcode =2;
            instruu3.add1 = 2;
            instruu3.add2 = 2;
            instruct2[6] = instruu3;

            Instrucao instruo8;
            instruo8.opcode = -1;
            instruct2[7] = instruo8;

            defPrograma(cpu, instruct2);
            iniciar(cpu,ram);

            if(ram->memoria[5] < 0)
            {
                break;
            } 	
        }

    }

    printf("\nA raiz, aproximadamente, é: %d\n", ram->memoria[2]);

}

void aleatorio(RAM *ram, CPU *cpu, int ammountIterations){

    for (int i = 0; i < ram->tamanho/2; i++) // trocar coisas de lugar
    {
        srand(time(NULL));

		Instrucao instruct[5];
        Instrucao isntruo0;
        isntruo0.opcode = 4;
        isntruo0.add1 = 1;
        isntruo0.add2 = rand();
        instruct[0] = isntruo0;

        Instrucao isntruo1;
        isntruo1.opcode = 2;
        isntruo1.add1 = 1;
        isntruo1.add2 = i;
        instruct[1] = isntruo1;

        Instrucao isntruo2;
        isntruo2.opcode = 4;
        isntruo2.add1 = 1;
        isntruo2.add2 = rand();
        instruct[2] = isntruo2;

        Instrucao isntruo3;
        isntruo3.opcode = 2;
        isntruo3.add1 = 1;
        isntruo3.add2 = ram->tamanho -i -1;
        instruct[3] = isntruo3;

        Instrucao isntruo4;
        isntruo4.opcode = -1;
        instruct[4] = isntruo4;

        defPrograma(cpu, instruct);
        iniciar(cpu,ram);
    }

    for (int i = 0; i < ammountIterations; i++)
    {
        srand(time(NULL));
        int index_one = rand()%ram->tamanho;
        int index_two = rand()%ram->tamanho;
        int index_three = rand()%ram->tamanho;


        Instrucao instruct2[8];
        Instrucao isntruo5;
        isntruo5.opcode = 3;
        isntruo5.add1 = 1;
        isntruo5.add2 = index_one;
        instruct2[0] = isntruo5;

        Instrucao isntruo6;
        isntruo6.opcode = 3;
        isntruo6.add1 = 2;
        isntruo6.add2 = index_two;
        instruct2[1] = isntruo6;
         // troca de valores
        Instrucao isntruo7;
        isntruo7.opcode = 1;
        isntruo7.add1 = 1;
        isntruo7.add2 = index_two;
        instruct2[2] = isntruo7;

        Instrucao isntruo8;
        isntruo8.opcode = 1;
        isntruo8.add1 = 2;
        isntruo8.add2 = index_one;
        instruct2[3] = isntruo8;

        Instrucao isntruo9;
        isntruo9.opcode = 0;
        isntruo9.add1 = index_three;
        isntruo9.add2 = index_one;
        isntruo9.add3 = index_one;
        instruct2[4] = isntruo9;

        Instrucao isntruo10;
        isntruo10.opcode = 1;
        isntruo10.add1 = index_two;
        isntruo10.add2 = index_one;
        isntruo10.add3 = index_three;
        instruct2[5] = isntruo10;

        Instrucao isntruo11;
        isntruo11.opcode = 0;
        isntruo11.add1 = index_three;
        isntruo11.add2 = index_two;
        isntruo11.add3 = index_two;
        instruct2[6] = isntruo11;

        Instrucao isntruo12;
        isntruo12.opcode = -1;
        instruct2[7]= isntruo12;

        defPrograma(cpu, instruct2);
        iniciar(cpu,ram);
    }

	imprimirRAM(ram);
}

void sumMat(RAM* ram, CPU* cpu, int prop, int **matrizA, int **matrizB)
{
    matrizA=malloc(prop*(sizeof(int*)));

    if (matrizA == NULL) 
    {
        printf("Memory allocation failed for rows.\n");
    }
   
    for (int i = 0; i < prop; i++)
    {
        matrizA[i]= malloc(prop * sizeof(int));
            if (matrizA[i] == NULL) 
            {
                printf("Memory allocation failed for row %d.\n", i);
            }
    }

    matrizB = malloc(prop*(sizeof(int*)));

    if (matrizB == NULL) 
    {
        printf("Memory allocation failed for rows.\n");
        //return 1;
    }
   
    for (int i = 0; i < prop; i++)
    {
        matrizB[i]= malloc(prop * sizeof(int));
            if (matrizB[i] == NULL) 
            {
                printf("Memory allocation failed for row %d.\n", i);
                //return 1;
            }

        
    }

    srand(time(NULL));

    for(int i = 0; i < prop; i++)
    {
        for(int j = 0; j < prop; j++)
        {
            matrizA[i][j] = rand() % 100;
            matrizB[i][j] = rand() % 100;
        }
    }

    int endRam = 0;

    for(int i = 0; i < prop; i++)
    {
        for(int j = 0; j < prop; j++)
        { 
            Instrucao inst0[3];
            inst0[0].opcode = 4;
            inst0[0].add1 = 1;
            inst0[0].add2 = matrizA[i][j];

            inst0[1].opcode = 2;
            inst0[1].add1 = 1;
            inst0[1].add2 = endRam;

            inst0[2].opcode = -1;

            defPrograma(cpu, inst0);
            iniciar(cpu, ram);
            endRam++;
        }
    }

    for(int i = 0; i < prop; i++)
    {
        for(int j = 0; j < prop; j++)
        { 
            Instrucao inst1[3];
            inst1[0].opcode = 4;
            inst1[0].add1 = 2;
            inst1[0].add2 = matrizB[i][j];

            inst1[1].opcode = 2;
            inst1[1].add1 = 2;
            inst1[1].add2 = endRam;

            inst1[2].opcode = -1;

            defPrograma(cpu, inst1);
            iniciar(cpu, ram);
            endRam++;

        }
    }

    int delta = prop*prop;
    endRam = 0;

    for(int i = 0; i < prop; i++)
    {
        for(int j = 0; j < prop; j++)
        {
            Instrucao inst3[2];

            inst3[0].opcode = 0;
            inst3[0].add1 = endRam;
            inst3[0].add2 = endRam+delta;
            inst3[0].add3 = endRam+(2*delta);

            inst3[1].opcode = -1;
            defPrograma(cpu, inst3);
            iniciar(cpu, ram);

            endRam++;
        }
    }
    
    for (int i = 0; i < prop; i++)
    {
        free(matrizA[i]);

    }
    free(matrizA);

       
    for (int i = 0; i < prop; i++)
    {
        free(matrizB[i]);

    }
    
    free(matrizB);
    return;
}

int divide(RAM* ram, CPU* cpu, int dividendo, int divisor)
{
    Instrucao inst0[5];
    inst0[0].opcode = 4;
    inst0[0].add1 = 1;//Reg1
    inst0[0].add2 = dividendo;

    inst0[1].opcode = 2;
    inst0[1].add1 = 1;//Reg1
    inst0[1].add2 = 0;//ram[0]

    inst0[2].opcode = 4;
    inst0[2].add1 = 2;//Reg1
    inst0[2].add2 = divisor;

    inst0[3].opcode = 2;
    inst0[3].add1 = 2;//Reg1
    inst0[3].add2 = 1;//ram[1]

    inst0[4].opcode = -1;

    defPrograma(cpu, inst0);
    iniciar(cpu, ram);

    //-------------------------------------------------------

    Instrucao inst1[3];

    inst1[0].opcode = 4;// externo->registrador
    inst1[0].add1 = 1;//reg1
    inst1[0].add2 = 1;//número salvo

    inst1[1].opcode = 2;// reg->ram
    inst1[1].add1 = 1;// reg1
    inst1[1].add2 = 2;// ram[2];

    inst1[2].opcode = -1;

    defPrograma(cpu, inst1);
    
        Instrucao inst2[3];
        iniciar(cpu, ram);

    //--------------------------------------------------------

    
    while(ram->memoria[0] > ram->memoria[1])
    {
        Instrucao inst2[3];
        inst2[0].opcode = 1;//subtrai
        inst2[0].add1 = 0;//ram[0]
        inst2[0].add2 = 1;//ram[1]
        inst2[0].add3 = 0;//ram[0]

        inst2[1].opcode = 0;//soma
        inst2[1].add1 = 2;//ram[2]
        inst2[1].add2 = 3;//ram[3]
        inst2[1].add3 = 3;//ram[3]
        
        inst2[2].opcode = -1;

        defPrograma(cpu, inst2);
        iniciar(cpu,ram);
    }


    Instrucao inst3[3];
    inst3[0].opcode = 3;//ram-> reg
    inst2[0].add1 = 1;//reg1
    inst3[0].add2 = 3;//ram[3]

    inst3[1].opcode = 5;// reg->externo
    inst2[1].add1 = 1;//reg1
    inst3[1].add2 = -1;

    inst2[2].opcode = -1;

    defPrograma(cpu, inst3);
    iniciar(cpu, ram);

    int outraVariavel = ram->memoria[3];// valor do dividendo alterado para o conteúdo retirado de reg1

    printf("\nTaí o resultado: %d\n", outraVariavel);

    return abs(outraVariavel);
}

// Função para calcular a média
void calcularMedia(RAM *ram, CPU *cpu) 
{
    int numeros[11];
    srand(time(NULL));
    for(int i = 0; i < 10; i++)
    {
        numeros[i] = (rand() % 100) + 1;
    }
    numeros[10] = 0;

    // Somar os números usando a CPU
    for (int i = 0; i < 10; i += 2) 
    {
        Instrucao inst[5];
        inst[0].opcode = 4; // Carregar número do vetor para registrador 1
        inst[0].add1 = 1;
        inst[0].add2 = numeros[i];

        inst[1].opcode = 4; // Carrega número do vetor para o registrador 2
        inst[1].add1 = 2;
        inst[1].add2 = numeros[i + 1];

        inst[2].opcode = 2; // Coleta os números dos registradores até a RAM 
        inst[2].add1 = 1;
        inst[2].add2 = i;

        inst[3].opcode = 2;
        inst[3].add1 = 2;
        inst[3].add2 = i + 1;

        inst[4].opcode = -1; // Fim da execução
        defPrograma(cpu, inst);
        iniciar(cpu, ram);
    }

    

    for(int i = 0; i < 10; i++)
    {
        Instrucao inst0[2];
        inst0[0].opcode = 0;
        inst0[0].add1 = i;
        inst0[0].add2 = 10;
        inst0[0].add3 = 10;

        inst0[1].opcode = -1;
        defPrograma(cpu, inst0);
        iniciar(cpu, ram);
    }

    

    Instrucao inst1[2];
    inst1[0].opcode = 3;
    inst1[0].add1 = 1;
    inst1[0].add2 = 10;

    inst1[1].opcode = -1;

    Instrucao inst2[2];

    inst2[0].opcode = 2;
    inst2[0].add1 = 1;
    inst2[0].add2 = 0;

    inst2[1].opcode = -1;

    defPrograma(cpu, inst2);
    iniciar(cpu, ram);

    Instrucao inst3[2];
    
    inst3[0].opcode = 4;
    inst3[0].add1 = 1;
    inst3[0].add2 = 0;

    inst3[1].opcode = -1;
    defPrograma(cpu, inst3);
    iniciar(cpu, ram);
    
    for(int i = 1; i < 10; i++)
    {
        Instrucao inst4[3];
        inst4[0].opcode = 2;
        inst4[0].add1 = 1;
        inst4[0].add2 = i;
        defPrograma(cpu, inst4);
        iniciar(cpu, ram);
    }
    
    int result = divide(ram, cpu, ram->memoria[0], 10);

    printf("\nMédia: %d\n", result);

    return;
}

// Função para calcular a moda
void calcularModa(RAM *ram, CPU *cpu) 
{
    int numeros[11];

    srand(time(NULL));
    for(int i = 0; i < 10; i++)
    {
        numeros[i] = (rand() % 10) + 1;
    }
    numeros[10] = 0; 

    // Somar os números usando a CPU
    for (int i = 0; i < 10; i += 2) 
    {
        Instrucao inst[5];
        inst[0].opcode = 4; // Carregar número do vetor para registrador 1
        inst[0].add1 = 1;
        inst[0].add2 = numeros[i];

        inst[1].opcode = 4; // Carrega número do vetor para o registrador 2
        inst[1].add1 = 2;
        inst[1].add2 = numeros[i + 1];

        inst[2].opcode = 2; // Coleta os números dos registradores até a RAM 
        inst[2].add1 = 1;
        inst[2].add2 = i;

        inst[3].opcode = 2;
        inst[3].add1 = 2;
        inst[3].add2 = i + 1;

        inst[4].opcode = -1; // Fim da execução
        defPrograma(cpu, inst);
        iniciar(cpu, ram);
    }
    int maj[10], moda = 0, index = 0;

    Instrucao inst0[2];
    for(int i = 0; i < 10; i++)
    {
        
        inst0[0].opcode = 3;// Coloca o primeiro valor no registrador 1;
        inst0[0].add1 = 1;
        inst0[0].add2 = i;
        inst0[0].add3 = 0;

        inst0[1].opcode = -1;

        defPrograma(cpu, inst0);
        iniciar(cpu, ram);

        for(int j = 0; j < 10; j++)
        {
            Instrucao inst1[2];
            inst1[0].opcode = 3;
            inst1[0].add1 = 2;
            inst1[0].add2 = j;

            inst1[1].opcode = -1;

            defPrograma(cpu, inst1);
            iniciar(cpu, ram);

            if(cpu->registrador1 == cpu->registrador2)
            {
                inst0[0].add3++;
            }
            
        }
        maj[i] = inst0[0].add3;

    }

    for(int i = 0; i < 10; i++)
    {
        if(maj[i] > moda)
        {
            moda = maj[i];
            index = i;
        }        
    }
    Instrucao inst2[2];

    inst2[0].opcode = 3;
    inst2[0].add1 = 1;
    inst2[0].add2 = index;

    inst2[1].opcode = -1;

    defPrograma(cpu, inst2);
    iniciar(cpu, ram);

    printf("\nA moda entre os dez valores é: %d\n", cpu->registrador1);

}

// Função para calcular a mediana
void calcularMediana(RAM *ram, CPU *cpu) 
{
    // Cria e organiza os números da área externa
    // Antes de colocá-los no sistema
    int numeros[10];

    srand(time(NULL));
    for(int i = 0; i < 10; i++)
    {
        numeros[i] = (rand() % 100) + 1;
    }
    numeros[10] = 0; 

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if (numeros[j] > numeros[j + 1]) 
            {
                int temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < 10; i += 2) 
    {
        Instrucao inst[5];
        inst[0].opcode = 4; // Carregar número do vetor para registrador 1
        inst[0].add1 = 1;
        inst[0].add2 = numeros[i];

        inst[1].opcode = 4; // Carrega número do vetor para o registrador 2
        inst[1].add1 = 2;
        inst[1].add2 = numeros[i + 1];

        inst[2].opcode = 2; // Coleta os números dos registradores até a RAM 
        inst[2].add1 = 1;
        inst[2].add2 = i;

        inst[3].opcode = 2;
        inst[3].add1 = 2;
        inst[3].add2 = i + 1;

        inst[4].opcode = -1; // Fim da execução
        defPrograma(cpu, inst);
        iniciar(cpu, ram);
    }

    Instrucao inst1[3];

    inst1[0].opcode = 0;
    inst1[0].add1 = 5;
    inst1[0].add2 = 4;
    inst1[0].add3 = 10;

    inst1[1].opcode = -1;
    
    defPrograma(cpu, inst1);
    iniciar(cpu, ram);

    Instrucao inst2[2];

    inst2[0].opcode = 3;//copia ram[10] para reg1
    inst2[0].add1 = 1;
    inst2[0].add2 = 10;

    inst2[1].opcode = -1;

    defPrograma(cpu, inst2);
    iniciar(cpu, ram);

    Instrucao inst3[2];
    
    inst3[0].opcode = 4;
    inst3[0].add1 = 1;
    inst3[0].add2 = 0;

    inst3[1].opcode = -1;
    defPrograma(cpu, inst3);
    iniciar(cpu, ram);
    
    for(int i = 1; i < 10; i++)
    {
        Instrucao inst4[3];
        inst4[0].opcode = 2;
        inst4[0].add1 = 1;
        inst4[0].add2 = i;
        defPrograma(cpu, inst4);
        iniciar(cpu, ram);
    }

    int val = divide(ram, cpu, ram->memoria[10], 2);

    printf("\nA mediana é aproximadamente: %d\n", val);

    return;
}

void calcularFibonacci(RAM *ram, CPU *cpu) 
{
    int x;
    int a = 1, b = 1, temp = 0;
    printf("Insira a posição do termo na sequência de fibonacci (min:1 max:46): ");
    scanf("%d", &x);
    if(x > 76 || x < 1)
    {
        while(x > 46 || x < 1)
        {
            printf("Por favor, insira um valor entre 1 e 46: ");
            scanf("%d", &x);
        }
    }

    Instrucao inst0[5];// Armazenando as variáveis externas na ram

    inst0[0].opcode = 4;
    inst0[0].add1 = 1;
    inst0[0].add2 = x;//ram[0]

    inst0[1].opcode = 4;
    inst0[1].add1 = 2;
    inst0[1].add2 = a;//ram[1]

    inst0[2].opcode = 2;
    inst0[2].add1 = 1;
    inst0[2].add2 = 0;

    inst0[3].opcode = 2;
    inst0[3].add1 = 2;
    inst0[3].add2 = 1;

    inst0[4].opcode = -1;

    defPrograma(cpu, inst0);
    iniciar(cpu, ram);

    Instrucao inst1[5];

    inst1[0].opcode = 4;
    inst1[0].add1 = 1;
    inst1[0].add2 = b;//ram[2]

    inst1[1].opcode = 4;
    inst1[1].add1 = 2;
    inst1[1].add2 = temp;//ram[3]

    inst1[2].opcode = 2;
    inst1[2].add1 = 1;
    inst1[2].add2 = 2;

    inst1[3].opcode = 2;
    inst1[3].add1 = 2;
    inst1[3].add2 = 3;

    inst1[4].opcode = -1;

    defPrograma(cpu, inst0);
    iniciar(cpu, ram);

    for(int i = 0; i < ram->memoria[0]; i++)
    {
        // temp = a + b 
        Instrucao inst2[6];

        inst2[0].opcode = 0;//somando a + b e guardando o valor em temp
        inst2[0].add1 = 1;
        inst2[0].add2 = 2;
        inst2[0].add3 = 3; // coloca na ram 3

        //a = b;

        inst2[1].opcode = 3;//copiando b(na ram) para o reg1
        inst2[1].add1 = 1;
        inst2[1].add2 = 2;

        inst2[2].opcode = 2;//sobrepondo o valor de a com o valor de b(reg->ram)
        inst2[2].add1 = 1;
        inst2[2].add2 = 1;

        //b = temp

        inst2[3].opcode = 3;//colocando temp(ram), em reg1
        inst2[3].add1 = 1;
        inst2[3].add2 = 3;

        inst2[4].opcode = 2;// sobrepondo b(ram[2]) por temp(reg1)
        inst2[4].add1 = 1;
        inst2[4].add2 = 2;

        inst2[5].opcode = -1;

        defPrograma(cpu, inst2);
        iniciar(cpu, ram);
    }
    
    Instrucao inst3[5];// extraindo b(ram->reg1)

    inst3[0].opcode = 3;
    inst3[0].add1 = 1;
    inst3[0].add2 = 2;

    inst3[1].opcode = 5; //extraindo b(reg1->externo)
    inst3[1].add1 = 1;
    inst3[1].add2 = -1;//local de b

    inst3[2].opcode = -1;

    defPrograma(cpu, inst3);
    iniciar(cpu, ram);

    a = inst3[1].add2;

    printf("\nO %dº número da sequência de Fibonacci é: %d\n", ram->memoria[0], ram->memoria[2]);

    return;
}

void pg(RAM* ram, CPU* cpu)
{
    int razao = 0, a1 = 0, n = 0;
    double termo;
    while(a1 < 1 || a1 > 100)
    {
        printf("Insira o primeiro termo da sua PG (1 até 100): ");
        scanf("%d", &a1);
    }
    while(razao < 2 || razao > 10)
    {
        printf("Insira a razão/quociente da sua PG (2 até 10): ");
        scanf("%d", &razao);
    }
    while(n < 1 || n > 20)
    {
        printf("Insira o número de termos da sua PG (1 até 20): ");
        scanf("%d", &n);
    }

    Instrucao inst0[5];

    inst0[0].opcode = 4;//(externo->reg1)
    inst0[0].add1 = 1;
    inst0[0].add2 = a1;//primeiro termo

    inst0[1].opcode = 4;//(externo->reg2)
    inst0[1].add1 = 2;
    inst0[1].add2 = razao;//razão

    inst0[2].opcode = 2;//(reg1->ram[0])
    inst0[2].add1 = 1;
    inst0[2].add2 = 0;

    inst0[3].opcode = 2;//(reg2->ram[1])
    inst0[3].add1 = 2;
    inst0[3].add2 = 1;

    inst0[4].opcode = -1;
    
    defPrograma(cpu, inst0);
    iniciar(cpu, ram);

    Instrucao inst1[5];

    inst1[0].opcode = 4;//(externo->reg1)
    inst1[0].add1 = 1;
    inst1[0].add2 = n;//número de termos

    inst1[1].opcode = 2;//(reg1->ram[2])
    inst1[1].add1 = 1;
    inst1[1].add2 = 2;

    inst1[2].opcode = 4;//(externo->reg2)
    inst1[2].add1 = 2;
    inst1[2].add2 = termo;//termo resultante

    inst1[3].opcode = 2;//(reg2->ram[3])
    inst1[3].add1 = 2;
    inst1[3].add2 = 3;

    inst1[4].opcode = -1;

    defPrograma(cpu, inst1);
    iniciar(cpu, ram);
    
    //termo = a1 * pow(razao, i)
    //--------------------------
    for(int i = 0; i < ram->memoria[2]; i++)
    {
           int termo = ram->memoria[0] * pow(ram->memoria[1], i);
           Instrucao inst4[3];

           inst4[0].opcode = 4;//Externo->reg1
           inst4[0].add1 = 1;
           inst4[0].add2 = termo;//termo a ser impresso

           inst4[1].opcode = 2;//reg1->ram[4]
           inst4[1].add1 = 1;
           inst4[1].add2 = 3;//ram[3]

           inst4[2].opcode = -1;
            
           defPrograma(cpu,inst4);
           iniciar(cpu,ram);
           printf("O termo %d é: %d\n", i + 1, ram->memoria[3]);
    }
    return;
}

void pa (RAM *ram, CPU *cpu){

    int qtd_termos;
    int termo_primeiro;
    int razao;
    // an = a1+(n+1)*r, r sendo a razao 
    printf("digite a quantidade de termos, o primeiro termo, e a razao: ");
    scanf("%d%d%d",&qtd_termos,&termo_primeiro,&razao);

    Instrucao instruct[7];

    Instrucao instrucao0;
    instrucao0.opcode = 4; // externo para reg
    instrucao0.add1 = 1;
    instrucao0.add2 = termo_primeiro;
    instruct[0] = instrucao0;
    
    Instrucao instrucao1;
    instrucao1.opcode= 4;
    instrucao1.add1 =2;
    instrucao1.add2 = razao;
    instruct[1] = instrucao1;

    Instrucao instrucao2;     
    instrucao2.opcode = 2; // reg para ram
    instrucao2.add1 = 1;
    instrucao2.add2 = 0;
    instruct[2] = instrucao2;
    
    Instrucao instrucao3;
    instrucao3.opcode = 2;
    instrucao3.add1 = 2;
    instrucao3.add2 = 1;
    instruct[3] = instrucao3;
    
    Instrucao instrucao4;
    instrucao4.opcode=4;
    instrucao4.add1 =1;
    instrucao4.add2 = qtd_termos;
    instruct[4] = instrucao4;

    Instrucao instrucao5;
    instrucao5.opcode =2;
    instrucao5.add1 = 1;
    instrucao5.add2 = 2;
    instruct[5] = instrucao5;

    Instrucao instrucao6;
    instrucao6.opcode = -1;
    instruct[6]= instrucao6;
    
    defPrograma(cpu, instruct);
    iniciar (cpu, ram);

    printf("%d, ",termo_primeiro);
    
    // somar razao
    for (int i = 1; i<ram->memoria[2]; i++){
        Instrucao instruct2[2];
        Instrucao instrucao7;
        instrucao7.opcode = 0;
        instrucao7.add1 = 0;
        instrucao7.add2 = 1;
        instrucao7.add3 = 0;
        instruct2[0] =instrucao7;
        
        Instrucao instrucao8;
        instrucao8.opcode = -1; 
        instruct2[1] = instrucao8;

        defPrograma(cpu, instruct2);
        iniciar (cpu, ram);
        printf("%d ",ram->memoria[0]);      
    }
    printf("\n");
}
