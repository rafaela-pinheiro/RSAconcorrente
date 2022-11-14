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

void descriptarGMP(char *bloco, char *n, char *d, mpz_t *r)
{
    mpz_t b, N, D;
    mpz_init_set_str(b, bloco, 0);
    mpz_init_set_str(N, n, 0);
    mpz_init_set_str(D, d, 0);
    mpz_powm(*r, b, D, N);
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
void codigoParaSimbolo(char *str)
{
    int a;
    a = atoi(str);
    if (a == 111)
        printf("0");
    if (a == 112)
        printf("1");
    if (a == 113)
        printf("2");
    if (a == 114)
        printf("3");
    if (a == 115)
        printf("4");
    if (a == 116)
        printf("5");
    if (a == 117)
        printf("6");
    if (a == 118)
        printf("7");
    if (a == 119)
        printf("8");
    if (a == 121)
        printf("9");
    if (a == 122)
        printf("=");
    if (a == 123)
        printf("+");
    if (a == 124)
        printf("-");
    if (a == 125)
        printf("/");
    if (a == 126)
        printf("*");
    if (a == 127)
        printf("a");
    if (a == 128)
        printf("b");
    if (a == 129)
        printf("c");
    if (a == 131)
        printf("d");
    if (a == 132)
        printf("e");
    if (a == 133)
        printf("f");
    if (a == 134)
        printf("g");
    if (a == 135)
        printf("h");
    if (a == 136)
        printf("i");
    if (a == 137)
        printf("j");
    if (a == 138)
        printf("k");
    if (a == 139)
        printf("l");
    if (a == 141)
        printf("m");
    if (a == 142)
        printf("n");
    if (a == 143)
        printf("o");
    if (a == 144)
        printf("p");
    if (a == 145)
        printf("q");
    if (a == 146)
        printf("r");
    if (a == 147)
        printf("s");
    if (a == 148)
        printf("t");
    if (a == 149)
        printf("u");
    if (a == 151)
        printf("v");
    if (a == 152)
        printf("w");
    if (a == 153)
        printf("x");
    if (a == 154)
        printf("y");
    if (a == 155)
        printf("z");
    if (a == 156 || a == 157 || a == 158 || a == 159)
        printf("a");
    if (a == 161 || a == 162)
        printf("e");
    if (a == 163)
        printf("i");
    if (a == 164 || a == 165 || a == 166)
        printf("o");
    if (a == 167)
        printf("u");
    if (a == 168)
        printf("c");
    if (a == 169)
        printf("A");
    if (a == 171)
        printf("B");
    if (a == 172)
        printf("C");
    if (a == 173)
        printf("D");
    if (a == 174)
        printf("E");
    if (a == 175)
        printf("F");
    if (a == 176)
        printf("G");
    if (a == 177)
        printf("H");
    if (a == 178)
        printf("I");
    if (a == 179)
        printf("J");
    if (a == 181)
        printf("K");
    if (a == 182)
        printf("L");
    if (a == 183)
        printf("M");
    if (a == 184)
        printf("N");
    if (a == 185)
        printf("O");
    if (a == 186)
        printf("P");
    if (a == 187)
        printf("Q");
    if (a == 188)
        printf("R");
    if (a == 189)
        printf("S");
    if (a == 191)
        printf("T");
    if (a == 192)
        printf("U");
    if (a == 193)
        printf("V");
    if (a == 194)
        printf("W");
    if (a == 195)
        printf("X");
    if (a == 196)
        printf("Y");
    if (a == 197)
        printf("Z");
    if (a == 198 || a == 199 || a == 211 || a == 212)
        printf("A");
    if (a == 213 || a == 214)
        printf("E");
    if (a == 215)
        printf("I");
    if (a == 216 || a == 217 || a == 218)
        printf("O");
    if (a == 219)
        printf("U");
    if (a == 221)
        printf("C");
    if (a == 222)
        printf(",");
    if (a == 223)
        printf(".");
    if (a == 224)
        printf("!");
    if (a == 225)
        printf("?");
    if (a == 226)
        printf(";");
    if (a == 227)
        printf(":");
    if (a == 228)
        printf("_");
    if (a == 229)
        printf("(");
    if (a == 231)
        printf(")");
    if (a == 232)
        printf(".");
    if (a == 233)
        printf("#");
    if (a == 234)
        printf("$");
    if (a == 235)
        printf("%%");
    if (a == 236)
        printf("@");
    if (a == 237)
        printf(" ");
    if (a == 238)
        printf("\n");
    if (a == 239)
        printf("{");
    if (a == 241)
        printf("}");
    if (a == 242)
        printf("'");
}

void descriptar(char *n, char *d)
{
    mpz_t r;
    mpz_init(r);
    for (int i = 0; i < qnt; i++)
    {
        descriptarGMP(blocos[i], n, d, &r);
        blocos[i] = mpz_get_str(NULL, 0, r);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Erro na quantidade de argumentos\n");
        exit(1);
    }

    GET_TIME(inicio);
    char *texto = lerArquivo(argv[3]);
    int qntBlocos = 1;
    for (int i = 0; i < strlen(texto); i++)
    { // Começa o processo de seperação da strings
        if (texto[i] == ' ')
        {
            qntBlocos++;
        }
    }
    char *blocos_separados[qntBlocos];
    int j = 0;
    blocos_separados[j] = strtok(texto, " ");
    while (blocos_separados[j] != NULL)
    {
        j++;
        blocos_separados[j] = strtok(NULL, " ");
    }
    blocos = blocos_separados;
    qnt = qntBlocos;
    char *n, *d;
    n = argv[1];
    d = argv[2];
    descriptar(n, d);
    for (int i = 0; i < qnt; i++)
    {
        printf("%s ", blocos[i]);
    }
    char str[3];
    int k = 0;
    for (int i = 0; i < qntBlocos; i++)
    {
        for (int j = 0; j < strlen(blocos[i]); j++)
        {
            // gargv[i] = String correspondente na posição i. Quando a gente pega gargv[i][j], estamos iterando pelos char.
            str[k] = blocos[i][j];

            k++;
            if (k == 3)
            {
                codigoParaSimbolo(str);
                k = 0;
            }
        }
    }
    GET_TIME(fim);
    elapsed = fim - inicio;
    printf("\nO codigo demorou %f segundos\n", elapsed);
    // faroeste caboclo teste 1 : 5.220687e-01 segundos
    // 1.654219e+00 segundos
    return 0;
}