#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <gmp.h>
#include "timer.h"
#include <time.h>

int nThreads;

// Variáveis para tomada de tempo
double inicio, fim, elapsed;

// Estrutura para os argumentos da thread
typedef struct
{
    int id;
    char *n;
    char *d;
} t_Args;

char **gargv;
int gargc;

// Tabela de correspodência entre os caracteres e seus códigos
char codSim[104] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', ' ', '9',
                    '=', '+', '-', '/', '*', 'a', 'b', 'c', ' ', 'd', 'e', 'f', 'g', 'h', 'i',
                    'j', 'k', 'l', ' ', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', ' ', 'v',
                    'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', ' ', 'E', 'F', 'G', 'H', 'I', 'J',
                    'K', 'L', 'M', ' ', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', ' ', 'W',
                    'X', 'Y', 'Z', ',', '.', '!', '?', ';', ' ', ':', '_', '(', ')', '\'', '#',
                    '$', '%', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                    '\n', '{', '}'};

void decriptarGMP(char *bloco, char *n, char *d, mpz_t *r)
{
    // Para decriptar, recebe o bloco, o modulo e a chave privada. Também recebe r para ser o valor de retorno
    // O GMP é uma biblioteca em C que permite fazer aritmética modular com números grandes em C, tratando todos como se fossem stings
    mpz_t b, N, D;
    mpz_init_set_str(b, bloco, 0);
    mpz_init_set_str(N, n, 0);
    mpz_init_set_str(D, d, 0);
    mpz_powm(*r, b, D, N); // r = b^D (mod N), alterando por referência
}

void *decriptarThread(void *arg)
{
    t_Args *args = (t_Args *)arg;
    int id = args->id;
    char *n, *d, **argumentos;
    n = args->n;
    d = args->d;
    mpz_t r;
    mpz_init(r);
    for (int i = id; i < gargc; i += nThreads)
    {
        decriptarGMP(gargv[i], n, d, &r);    // Descripta o bloco, passando o resultado para o &r
        gargv[i] = mpz_get_str(NULL, 10, r); // Converte o mpz_t para string e salva no vetor de strings
    }
    free(arg);
    pthread_exit(NULL);
}

char codigoParaSimbolo(int codigo)
{
    int temp;
    for (int i = 0; i < 104; i++)
    {
        temp = 111 + i;
        if (codigo == temp)
            return codSim[i];
    }
}

char *lerArquivo(char *arquivo)
{
    FILE *arq;
    char *texto;
    int tamanho;
    arq = fopen(arquivo, "r"); // Abertura do arquivo
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    fseek(arq, 0, SEEK_END);                            // Movendo o ponteiro pro final do arquivo
    tamanho = ftell(arq);                               // Pegando a posição do ponteiro (nosso tamanho do arquivo)
    fseek(arq, 0, SEEK_SET);                            // Voltando o ponteiro pro inicio do arquivo
    texto = (char *)malloc(tamanho + 1 * sizeof(char)); // Alocando o espaço necessário

    char c;
    int i = 0;
    while ((c = fgetc(arq)) != EOF)
    {
        texto[i] = c;
        i++;
    }
    texto[i] = '\0';
    fclose(arq);
    return texto;
}

void escreverArquivo()
{
    FILE *arq;
    arq = fopen("textoSaida.txt", "w");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    /* Conversão de código para símbolo */
    // Recebe os três dígitos para convertê-los para a letra correspondente
    char str[3], simbolo;
    int digitos = 0;
    for (int i = 0; i < gargc; i++)
    {
        for (int j = 0; j < strlen(gargv[i]); j++)
        {
            str[digitos] = gargv[i][j];
            digitos++;
            if (digitos == 3)
            {
                // Se digitos == 3, já temos um código completo e podemos converter
                simbolo = codigoParaSimbolo(atoi(str));
                // Escreve o char no arquivo
                fputc(simbolo, arq);
                digitos = 0;
            }
        }
    }

    fclose(arq);
}

int main(int argc, char *argv[])
{
    char *n, *d;

    // Inicia a contagem do tempo
    GET_TIME(inicio);

    if (argc < 3)
    {
        printf("Digite: %s <arquivo de entrada> <número de threads>\n", argv[0]);
        return -1;
    }

    char *texto = lerArquivo(argv[1]);
    nThreads = atoi(argv[2]);

    pthread_t tid[nThreads];
    t_Args *args;

    int qntBlocos = 1;
    for (int i = 0; i < strlen(texto); i++)
    {
        // Calcula a quantidade de blocos
        if (texto[i] == ' ')
        {
            qntBlocos++;
        }
    }
    qntBlocos -= 2;

    // Separa a string com todos os blocos em um vetor de strings (blocos)
    char *strings[qntBlocos];
    int j = 0;
    n = strtok(texto, " ");
    d = strtok(NULL, " ");
    strings[j] = strtok(NULL, " ");
    while (strings[j] != NULL)
    {
        j++;
        strings[j] = strtok(NULL, " "); // Equivalente ao .split() em java, separa a string até o determinado ponto
    }
    gargv = strings;
    gargc = qntBlocos;

    // Cria as threads
    for (int i = 0; i < nThreads; i++)
    {
        args = malloc(sizeof(t_Args));
        args->id = i;
        args->n = n;
        args->d = d;
        pthread_create(&tid[i], NULL, decriptarThread, (void *)args);
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < nThreads; i++)
    {
        pthread_join(tid[i], NULL);
    }
    for (int i = 0; i < gargc; i++)
    {
        printf("DESCRIPTADO: %s\n", gargv[i]);
    }
    escreverArquivo();

    // Finaliza a contagem do tempo
    GET_TIME(fim);
    elapsed = fim - inicio;
    printf("\nO codigo demorou %f segundos\n", elapsed);
    return 0;
}
