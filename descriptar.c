#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 
#include <math.h>
#include <gmp.h>

typedef struct{
    int id;
    char *bloco;
    char *n;
    char *d;
}t_Args;



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
    printf("Thread %d: %s %s %s\n", args->id, args->bloco, args->n, args->d);
    char *b, *n, *d;
    b = args->bloco;
    n = args->n;
    d = args->d;
    mpz_t *r;
    mpz_init(&r);
    descriptarGMP(b, n, d, &r);   
    gmp_printf("Resultado: %Zd\n", &r);
    free(arg);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){ // tentando passar o bloco, n e d por linha de comando b[1] = n b[2] = d b[3] = bloco b[4] outro bloco e assim vai
    pthread_t tid[3];
    t_Args *args;
    char *n, *d;
    n = argv[1];
    d = argv[2];
    long long b;
    b = descriptar(115901, 210649, 41933);
    printf("%lld", b);
    printf("\n");
    for(int i=0; i<3;i++){
        args = malloc(sizeof(t_Args));
        args->id = i;
        args->bloco = argv[i+3];
        args->n = n;
        args->d = d;
        pthread_create(&tid[i], NULL, descriptarThread, (void*) args);
    }
    for(int i=0; i<3;i++){
        pthread_join(tid[i], NULL);
    }
    /* Uso do descriptar GMP sequencial na propria main
    mpz_t *r;
    mpz_init(&r);
    descriptarGMP("1514730309574", "13527252160957", "1229749519127", &r);
    gmp_printf("Resultado: %Zd\n", &r);
    printf("\n");
    */

}
