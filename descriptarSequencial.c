#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include <gmp.h>

char **blocos;
int qnt;

void descriptarGMP(char *bloco, char *n, char * d, mpz_t *r){ 
    mpz_t b, N, D;
    mpz_init_set_str(b, bloco, 0);
    mpz_init_set_str(N, n, 0);
    mpz_init_set_str(D, d, 0);
    mpz_powm(*r, b, D, N);
}
char* lerArquivo(char *arquivo){
    FILE *arq;
    char *texto;
    int tamanho;
    arq = fopen(arquivo, "r"); //Abertura do arquivo
    if(arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    fseek(arq, 0, SEEK_END); //Movendo o ponteiro pro final do arquivo
    tamanho = ftell(arq); //Pegando a posição do ponteiro (nosso tamanho do arquivo)
    fseek(arq, 0, SEEK_SET); // Voltando o ponteiro pro inicio do arquivo
    texto = (char *) malloc(tamanho+1 * sizeof(char)); //Alocando o espaço necessário
    
    char c;
    int i = 0;
    while((c = fgetc(arq)) != EOF){
        texto[i] = c; //Armazena todos caracteres em nossa string até o fim do arquivo
        i++;
    }
    texto[i] = '\0'; //"Fecha" a string
    fclose(arq); //Fecha o arquivo  
    return texto;
}

void descriptar(char *n, char *d){
    mpz_t r;
    mpz_init(r);
    for(int i = 0; i < qnt; i++){
        descriptarGMP(blocos[i], n, d, &r);
        blocos[i] = mpz_get_str(NULL, 0, r);
    }
}

int main(int argc, char *argv[]){
    if(argc != 4){
        printf("Erro na quantidade de argumentos\n");
        exit(1);
    }
    char *texto = lerArquivo(argv[3]);
    int qntBlocos = 1;
    for(int i = 0; i < strlen(texto); i++){ //Começa o processo de seperação da strings
        if(texto[i] == ' '){
            qntBlocos++;
        }
    }
    char *blocos_separados[qntBlocos];
    int j = 0;
    blocos_separados[j] = strtok(texto, " ");
    while(blocos_separados[j] != NULL){
        j++;
        blocos_separados[j] = strtok(NULL, " ");
    }
    blocos = blocos_separados;
    qnt = qntBlocos;
    char *n, *d;
    n = argv[1];
    d = argv[2];
    descriptar(n, d);
    for(int i = 0; i < qnt; i++){
        printf("%s ", blocos[i]);
    }
    return 0;
}