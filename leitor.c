#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *lerArquivo(char *arquivo){
    FILE *arq;
    char *texto;
    int tamanho;
    arq = fopen(arquivo, "r");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    fseek(arq, 0, SEEK_END);
    tamanho = ftell(arq);
    fseek(arq, 0, SEEK_SET);
    texto = (char *) malloc(tamanho+1 * sizeof(char));
    
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
int main(int argc, char *argv[]){
    char *texto;
    texto = lerArquivo(argv[1]);
    int qntStrings = 0;
    for(int i = 0; i < strlen(texto); i++){
        if(texto[i] == ' '){
            qntStrings++;
        }
    }
    qntStrings++;
    char *strings[qntStrings];
    int j = 0;
    strings[j] = strtok(texto, " ");
    while(strings[j] != NULL){
        j++;
        strings[j] = strtok(NULL, " ");
    }
    for(int i = 0; i < qntStrings; i++){
        printf("%s\n", strings[i]);
    }
}