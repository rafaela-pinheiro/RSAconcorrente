#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 
#include <math.h>
#include <gmp.h>
#define NTHREADS 4

typedef struct{
    int id;
    //char *bloco;
    char *n;
    char *d;
    //char **argumentos;
    //int qntArgumentos;
}t_Args;

char **gargv;
int gargc;

long long int descriptar(double bloco, int n, int d){
    double r;
    r = (int)pow(bloco, d) % n;
    return bloco;
}

//Para descriptar, recebe o bloco, o modulo e a chave privada. Também recebe o R para ser o valor de retorno.
void descriptarGMP(char *bloco, char *n, char * d, mpz_t *r){
    char * resString;
    mpz_t b, N, D;
    mpz_init_set_str(b, bloco, 0);
    mpz_init_set_str(N, n, 0);
    mpz_init_set_str(D, d, 0);
    mpz_powm(*r, b, D, N);
}
void *descriptarThread(void *arg){
    t_Args *args = (t_Args*) arg;
    int id = args->id;
    //int qntArgumentos = args->qntArgumentos;
    char *n, *d, **argumentos;
    n = args->n;
    d = args->d;
    //argumentos = args->argumentos;
    mpz_t *r;
    mpz_init(&r);
    for(int i = id; i < gargc; i+=NTHREADS){
        descriptarGMP(gargv[i], n, d, &r); //Descripta o bloco, passando o resultado para o &r
        gmp_printf("DESCRIPTADO PELA Thread %d: %Zd\n", id, &r); 
        gargv[i] = mpz_get_str(NULL, 10, &r); //Converte o mpz_t para string e salva no vetor de strings
    }
    free(arg);
    pthread_exit(NULL);
}
void codigoParaSimbolo(char *str){
    int a;
    a = atoi(str);
    if(a == 111)
        printf("0");
    if(a == 112)
        printf("1");
    if(a == 113)
        printf("2");
    if(a == 114)
        printf("3");
    if(a == 115)
        printf("4");
    if(a == 116)
        printf("5");
    if(a == 117)
        printf("6");
    if(a == 118)
        printf("7");
    if(a == 119)
        printf("8");
    if(a == 121)
        printf("9");
    if(a == 122)
        printf("=");
    if(a == 123)
        printf("+");
    if(a == 124)
        printf("-");
    if(a == 125)    
        printf("/");
    if(a == 126)
        printf("*");
    if(a == 127)
        printf("a");
    if(a == 128)
        printf("b");
    if(a == 129)
        printf("c");
    if(a == 131)
        printf("d");
    if(a == 132)
        printf("e");
    if(a == 133)
        printf("f");
    if(a == 134)                
        printf("g");
    if(a == 135)    
        printf("h");
    if(a == 136)                        
        printf("i");
    if(a == 137)    
        printf("j");
    if(a == 138)
        printf("k");
    if(a == 139)
        printf("l");
    if(a == 141)
        printf("m");
    if(a == 142)
        printf("n");
    if(a == 143)
        printf("o");
    if(a == 144)
        printf("p");
    if(a == 145)
        printf("q");
    if(a == 146)
        printf("r");
    if(a == 147)
        printf("s");
    if(a == 148)
        printf("t");
    if(a == 149)    
        printf("u");
    if(a == 151)    
        printf("v");
    if(a == 152)    
        printf("w");
    if(a == 153)    
        printf("x");
    if(a == 154)    
        printf("y");
    if(a == 155)
        printf("z");
    if(a == 156 || a == 157 || a == 158 || a == 159)
        printf("a");
    if(a == 161 || a == 162) 
        printf("e");
    if(a == 163)
        printf("i");
    if(a == 164 || a == 165 || a == 166)
        printf("o");
    if(a == 167)
        printf("u");
    if(a == 168)
        printf("c");
    if(a == 169)
        printf("A");
    if(a == 171)
        printf("B");
    if(a == 172)
        printf("C");
    if(a == 173)    
        printf("D");
    if(a == 174)    
        printf("E");
    if(a == 175)    
        printf("F");
    if(a == 176)
        printf("G");
    if(a == 177)    
        printf("H");
    if(a == 178)    
        printf("I");
    if(a == 179)
        printf("J");
    if(a == 181)
        printf("K");
    if(a == 182)    
        printf("L");    
    if(a == 183)
        printf("M");
    if(a == 184)
        printf("N");
    if(a == 185)
        printf("O");
    if(a == 186)    
        printf("P");
    if(a == 187)    
        printf("Q");
    if(a == 188)    
        printf("R");
    if(a == 189)
        printf("S");
    if(a == 191)
        printf("T");
    if(a == 192)
        printf("U");
    if(a == 193)
        printf("V");
    if(a == 194)
        printf("W");
    if(a == 195)
        printf("X");
    if(a == 196)    
        printf("Y");
    if(a == 197)    
        printf("Z");
    if(a == 198 || a == 199 || a == 211 || a == 212)
        printf("A");
    if(a == 213 || a == 214)
        printf("E");
    if(a == 215)
        printf("I");
    if(a == 216 || a == 217 || a == 218)    
        printf("O");
    if(a == 219)    
        printf("U");
    if(a == 221)    
        printf("C");
    if(a == 222)    
        printf(",");
    if(a == 223)    
        printf(".");
    if(a == 224)    
        printf("!");
    if(a == 225)    
        printf("?");
    if(a == 226)    
        printf(";");
    if(a == 227)
        printf(":");
    if(a == 228)
        printf("_");
    if(a == 229)
        printf("(");
    if(a == 231)
        printf(")");
    if(a == 232)
        printf('"');
    if(a == 233)
        printf("#");
    if(a == 234)
        printf("$");
    if(a == 235)
        printf("%%");    
    if(a == 236)
        printf("@");
    if(a == 237)
        printf(" ");
    if(a == 238)    
        printf("\n");
    if(a == 239)
        printf("{");
    if(a == 241)
        printf("}");
    if(a == 242)
        printf("'");
}

int simboloParaCodigo(char simbolo){
    if(simbolo == '0')
        return 111;
    if(simbolo == '1')
        return 112;
    if(simbolo == '2')
        return 113;
    if(simbolo == '3')
        return 114;
    if(simbolo == '4')
        return 115;
    if(simbolo == '5')
        return 116;
    if(simbolo == '6')
        return 117;
    if(simbolo == '7')
        return 118;
    if(simbolo == '8')
        return 119;
    if(simbolo == '9')
        return 121;
    if(simbolo == '=')
        return 122;
    if(simbolo == '+')
        return 123;
    if(simbolo == '-')
        return 124;
    if(simbolo == '/')
        return 125;
    if(simbolo == '*')
        return 126;
    if(simbolo == 'a')
        return 127;
    if(simbolo == 'b')
        return 128;
    if(simbolo == 'c')
        return 129;
    if(simbolo == 'd')
        return 131;
    if(simbolo == 'e')
        return 132;
    if(simbolo == 'f')
        return 133;
    if(simbolo == 'g')
        return 134;
    if(simbolo == 'h')
        return 135;
    if(simbolo == 'i')
        return 136;
    if(simbolo == 'j')
        return 137;
    if(simbolo == 'k')
        return 138;
    if(simbolo == 'l')
        return 139;
    if(simbolo == 'm')
        return 141;
    if(simbolo == 'n')
        return 142;
    if(simbolo == 'o')
        return 143;
    if(simbolo == 'p')
        return 144;
    if(simbolo == 'q')
        return 145;
    if(simbolo == 'r')
        return 146;
    if(simbolo == 's')
        return 147;
    if(simbolo == 't')
        return 148;
    if(simbolo == 'u')
        return 149;
    if(simbolo == 'v')
        return 151;
    if(simbolo == 'w')
        return 152;
    if(simbolo == 'x')
        return 153;
}

char *lerArquivo(char *arquivo){
    FILE *arq;
    char *texto;
    int tamanho;
    arq = fopen(arquivo, "r"); //Abertura do arquivo
    if(arq == NULL){
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    fseek(arq, 0, SEEK_END); //Movendo o ponteiro pro final do arquivo
    tamanho = ftell(arq); //Pegando a posição do ponteiro (nosso tamanho do arquivo)
    fseek(arq, 0, SEEK_SET); // Voltando o ponteiro pro inicio do arquivo
    texto = (char *) malloc(tamanho+1 * sizeof(char)); //Alocando o espaço necessário
    
    char c;
    int i = 0;
    while((c = fgetc(arq)) != EOF){
        texto[i] = c;
        i++;
    }
    texto[i] = '\0';
    fclose(arq);
    return texto;
}

int main(int argc, char *argv[]){ // tentando passar o bloco, n e d e o nome do arquivo com os outros blocos
    pthread_t tid[NTHREADS];
    t_Args *args;
    char *n, *d;
    n = argv[1];
    d = argv[2];
    char *texto = lerArquivo(argv[3]);
    int qntBlocos = 1;
    for(int i = 0; i < strlen(texto); i++){ //Começa o processo de seperação da strings
        if(texto[i] == ' '){
            qntBlocos++;
        }
    }
    char *strings[qntBlocos];
    int j = 0;
    strings[j] = strtok(texto, " ");
    while(strings[j] != NULL){
        j++;
        strings[j] = strtok(NULL, " ");
    }
    gargv = strings;
    gargc = qntBlocos;
    for(int i=0; i<NTHREADS;i++){
        args = malloc(sizeof(t_Args));
        args->id = i;
        args->n = n;
        args->d = d;
        //args->argumentos = argv;
        //args->qntArgumentos = argc;
        pthread_create(&tid[i], NULL, descriptarThread, (void*) args);
    }
    for(int i=0; i<NTHREADS;i++){
        pthread_join(tid[i], NULL);
    }
    for(int i = 0; i < gargc; i++){
        printf("DESCRIPTADO: %s\n", gargv[i]);
    }
    char str[3];
    int k = 0;
    for(int i=0; i < gargc; i++){
        for(int j = 0; j < strlen(gargv[i]); j++){
            str[k] = gargv[i][j];
            k++;
            if(k == 3){
                k=0;
                codigoParaSimbolo(str);
            }
        }
    }
}
