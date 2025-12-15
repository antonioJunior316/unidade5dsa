#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

double tempoTotalEspera = 0;
double tempoTotalAtendimento = 0;
int pessoasAtendidas = 0;

typedef struct Pessoa {
    char nome[50];
    int idade;
    struct Pessoa *prox;
    time_t tempo;
} Pessoa;

typedef struct {
    Pessoa *topo;
} Pilha;

void inicio(Pilha *pilha){
    pilha->topo = NULL;
}

void empilhar(Pilha *pilha, char nome[], int idade){
    Pessoa *novaPessoa = (Pessoa *) malloc(sizeof(Pessoa));
    if(novaPessoa == NULL){
        printf("memória insuficiente!\n");
        return;
    }

    strcpy(novaPessoa->nome, nome);
    novaPessoa->idade = idade;
    novaPessoa->tempo = time(NULL);

    novaPessoa->prox = pilha->topo;
    pilha->topo = novaPessoa;
}


void desempilhar(Pilha *pilha){
    if(pilha->topo == NULL){
        printf("pilha vazia!\n");
        return;
    }

    Pessoa *remove = pilha->topo;
    time_t inicioAtendimento = time(NULL);
    double tempoEsperando = difftime(inicioAtendimento, remove->tempo);

    sleep(5);

    time_t fimAtendimento = time(NULL);
    double tempoAtendimento = difftime(fimAtendimento, inicioAtendimento);

    tempoTotalEspera += tempoEsperando;
    tempoTotalAtendimento += tempoAtendimento;
    pessoasAtendidas++;

    printf("Atendimento realizado nome = %s idade = %d\n", remove->nome, remove->idade);
    printf("Tempo de espera: %.0f segundos\n", tempoEsperando);
    printf("Tempo de atendimento: %.0f segundos\n", tempoAtendimento);

    pilha->topo = remove->prox;
    free(remove);
}

void mostrandoAPilha(Pilha *pilha){
    if(pilha->topo == NULL){
        printf("Pilha vazia\n");
        return;
    }

    Pessoa *aux = pilha->topo;
    printf("\n--- Pessoas na pilha ---\n");
    while(aux != NULL){
        printf("Nome: %s  Idade: %d\n", aux->nome, aux->idade);
        aux = aux->prox;
    }
}


void mediaDeTempo(){
    if(pessoasAtendidas == 0){
        printf("Não existem pessoas atendidas!\n");
        return;
    }

    printf("\nInformações\n");
    printf("Tempo médio de espera: %.0f segundos\n", tempoTotalEspera / pessoasAtendidas);
    printf("Tempo médio do atendimento: %.0f segundos\n", tempoTotalAtendimento / pessoasAtendidas);
}

int main(){
    Pilha pilha;
    inicio(&pilha);

    int decisao;
    int idade;
    char nome[50];

    printf("\nPilha do banco\n");
    printf("1 - Empilhar pessoa\n");
    printf("2 - Atender (desempilha)\n");
    printf("3 - Mostrando pilha completa\n");
    printf("4 - Média de tempo do atendimento\n");
    printf("0 - Saindo\n");
    printf("Escolha: ");

    do {
        scanf("%d", &decisao);
        getchar();

        switch(decisao){
            case 1:
                printf("Nome: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Idade: ");
                scanf("%d", &idade);
                getchar();

                empilhar(&pilha, nome, idade);
                break;

            case 2:
                desempilhar(&pilha);
                break;

            case 3:
                mostrandoAPilha(&pilha);
                break;

            case 4:
                mediaDeTempo();
                break;

            case 0:
                printf("Encerrando sistema...\n");
                break;

            default:
                printf("Decisão inválida!\n");
        }

    } while(decisao != 0);

    return 0;
}
