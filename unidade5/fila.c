#include <stdio.h>
#include <string.h>

typedef struct Pessoa{
    char nome[50];
    int idade;
    struct Pessoa *prox;

}Pessoa;

typedef struct {
    Pessoa *inicio;
    Pessoa *fim;
}Fila;


void inicio(Fila *fila){
    fila->fim = NULL;
    fila->inicio = NULL;
}

void enfilerar(Fila *fila,char nome[],int idade){
    Pessoa *novaPessoa  = (Pessoa *) malloc(sizeof(Pessoa));

    if(novaPessoa == NULL){
        printf("memoria insuficiente!\n");
        return;
    }
    strcpy(novaPessoa->nome,nome);
    novaPessoa->idade = idade;
    novaPessoa->prox = NULL;

    if(fila->inicio == NULL){
        fila->inicio = novaPessoa;
        fila->fim = novaPessoa;
    }else{
        fila->fim->prox = novaPessoa;
        fila->fim = novaPessoa;
    }
}


int main(){
    Fila fila;
    
    inicio(&fila);

    return 0;
}