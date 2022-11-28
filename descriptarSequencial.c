#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gmp.h>
#include "timer.h"
#include <time.h>

char **blocos;
int qnt;
double inicio, fim, elapsed;
mpz_t r;
// Tabela de correspodência entre os caracteres e seus códigos
char codSim[104] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', ' ', '9',
                    '=', '+', '-', '/', '*', 'a', 'b', 'c', ' ', 'd', 'e', 'f', 'g', 'h', 'i',
                    'j', 'k', 'l', ' ', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', ' ', 'v',
                    'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', ' ', 'E', 'F', 'G', 'H', 'I', 'J',
                    'K', 'L', 'M', ' ', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', ' ', 'W',
                    'X', 'Y', 'Z', ',', '.', '!', '?', ';', ' ', ':', '_', '(', ')', '\'', '#',
                    '$', '%', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                    '\n', '{', '}'};

void descriptarGMP(char *bloco, char *n, char *d)
{
    mpz_t b, N, D;
    mpz_init_set_str(b, bloco, 0);
    mpz_init_set_str(N, n, 0);
    mpz_init_set_str(D, d, 0);
    mpz_powm(r, b, D, N);
}
char *lerArquivo(char *arquivo)
{
    FILE *arq;
    char *texto;
    int tamanho;
    arq = fopen(arquivo, "r"); // Abertura do arquivo
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
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
        texto[i] = c; // Armazena todos caracteres em nossa string até o fim do arquivo
        i++;
    }
    texto[i] = '\0'; //"Fecha" a string
    fclose(arq);     // Fecha o arquivo
    return texto;
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

void descriptar(char *n, char *d)
{
    mpz_init(r);
    for (int i = 0; i < qnt; i++)
    {
        descriptarGMP(blocos[i], n, d);
        blocos[i] = mpz_get_str(NULL, 0, r);
    }
}
void escreverArquivo()
{
    FILE *arq;
    arq = fopen("textoSaidaSeq.txt", "w");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    /* Conversão de código para símbolo */
    // Recebe os três dígitos para convertê-los para a letra correspondente
    char str[3], simbolo;
    int digitos = 0;
    for (int i = 0; i < qnt; i++)
    {
        for (int j = 0; j < strlen(blocos[i]); j++)
        {
            str[digitos] = blocos[i][j];
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
    GET_TIME(inicio);
    if (argc < 2)
    {
        printf("Digite: %s <arquivo> \n", argv[0]);
        return 1;
    }
    char *texto = lerArquivo(argv[1]);
    int qntBlocos = 1;

    // Conta a quantidade de blocos
    for (int i = 0; i < strlen(texto); i++)
    {
        if (texto[i] == ' ')
            qntBlocos++;
    }
    qntBlocos -= 2; // Retira os dois primeiros blocos (n e d)
    qnt = qntBlocos;
    blocos = (char **)malloc(qntBlocos * sizeof(char *));
    int j = 0;
    n = strtok(texto, " ");
    d = strtok(NULL, " ");
    blocos[j] = strtok(NULL, " ");
    while (blocos[j] != NULL)
    {
        j++;
        blocos[j] = strtok(NULL, " ");
    }
    descriptar(n, d);
    escreverArquivo();
    GET_TIME(fim);
    printf("Tempo de execução: %lf\n", fim - inicio);
    return 0;
}