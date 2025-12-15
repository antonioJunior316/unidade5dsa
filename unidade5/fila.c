#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void  enfileirar(Fila *fila,char nome[],int idade){
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

void desenfileirando(Fila *fila){
    if(fila->inicio == NULL){
        printf("fila vazia!\n");
        return;
    }
    Pessoa *remove = fila->inicio;
    printf("Atendimento realizado nome = %s idade = %d\n",remove->nome,remove->idade);

    fila->inicio = remove->prox;
    if(fila->inicio == NULL){
        fila->fim = NULL;
    }
    free(remove);
}

void mostrandoAFila(Fila *fila){
    if(fila->inicio == NULL){
        printf("fila vazia\n");
        return ;
    }
 Pessoa *aux = fila->inicio;
    printf("\n--- Pessoas na fila ---\n");

    while(aux != NULL){
        printf("nome: %s  idade: %d\n", aux->nome, aux->idade);
        aux = aux->prox;
    }
    
}

int main(){
    Fila fila;
    
    inicio(&fila);

    int decisao;
    int idade;
    char nome[50];

        printf("\nFila do banco\n");
        printf("1 - enfileira pessoa\n");
        printf("2 - Atender (retira pessoa)\n");
        printf("3 - Mostrando fila completa\n");
        printf("0 - saindo\n");
        printf("Escolha : ");

    do{

        scanf("%d",&decisao);
        getchar();

        switch (decisao) {
            case 1:
                printf("Nome: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Idade: ");
                scanf("%d", &idade);

                enfileirar(&fila, nome, idade);
                break;

            case 2:
                desenfileirando(&fila);
                break;

            case 3:
                mostrandoAFila(&fila);
                break;

            case 0:
                printf("Encerrando sistema...\n");
                break;

            default:
                printf("Decisao invalida!\n");
        }

    }while(decisao != 0);

    return 0;
}