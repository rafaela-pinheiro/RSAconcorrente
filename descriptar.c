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
    for(int i = id + 3; i < gargc; i+=NTHREADS){
        descriptarGMP(gargv[i], n, d, &r);
        gmp_printf("DESCRIPTADO PELA Thread %d: %Zd\n", id, &r);
        gargv[i] = mpz_get_str(NULL, 10, &r);
    }
    free(arg);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){ // tentando passar o bloco, n e d por linha de comando b[1] = n b[2] = d b[3] = bloco b[4] outro bloco e assim vai
    pthread_t tid[NTHREADS];
    t_Args *args;
    char *n, *d;
    n = argv[1];
    d = argv[2];
    gargv = argv;
    gargc = argc;
    printf("QNT ARGUMENTOS: %d\n", argc);
    long long b;
    b = descriptar(115901, 210649, 41933);
    printf("%lld", b);
    printf("\n");
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
    for(int i = 3; i < argc; i++){
        printf("DESCRIPTADO: %s\n", gargv[i]);
    }
    /* Uso do descriptar GMP sequencial na propria main
    mpz_t *r;
    mpz_init(&r);
    descriptarGMP("1514730309574", "13527252160957", "1229749519127", &r);
    gmp_printf("Resultado: %Zd\n", &r);
    printf("\n");
    */

}
