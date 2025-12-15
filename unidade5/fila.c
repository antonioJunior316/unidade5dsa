#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

double tempoTotalEspera = 0;
double tempoTotalAtendimento = 0;
int pessoasAtendidas = 0;


typedef struct Pessoa{
    char nome[50];
    int idade;
    struct Pessoa *prox;
    time_t tempo;

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
    novaPessoa->tempo = time(NULL);

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

    time_t inicioAtendimento = time(NULL);

    double tempoEsperando = difftime(inicioAtendimento,remove->tempo);

    sleep(5);

    time_t fimAtendimento = time(NULL);
    double tempoAtendimento = difftime(fimAtendimento,inicioAtendimento);

    tempoTotalEspera += tempoEsperando;
    tempoTotalAtendimento += tempoAtendimento;
    pessoasAtendidas++;

    printf("Atendimento realizado nome = %s idade = %d\n",remove->nome,remove->idade);
    printf("tempo de esperando : %0.f\n",tempoEsperando);
    printf("Tempo de atendimento : %.0f\n",tempoAtendimento);

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

void mediaDeTempo(){
    if(pessoasAtendidas == 0){
        printf("nao existem pessoas pra atender!!!!\n");
        return ;
    }
    printf("\ninformações\n");
    printf("Tempo de espera : %.0f segundos\n",tempoTotalEspera / pessoasAtendidas);
    printf("Tempo media do atendimento : %.0f segundos\n",tempoTotalAtendimento/pessoasAtendidas);
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
        printf("4 - Media de tempo do atendimento\n");
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
            
            case 4:
                mediaDeTempo();
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