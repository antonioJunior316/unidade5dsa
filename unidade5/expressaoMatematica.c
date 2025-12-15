#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMO 1000

typedef struct{
    char items[MAXIMO];
    int topo;
}Pilha;

void inicializando(Pilha *pilha){
    pilha->topo = -1;
}

int vazio(Pilha *pilha){
    return pilha->topo == -1;
}

int empilhando(Pilha *pilha,char expressao){
    if(pilha->topo < MAXIMO - 1){
        pilha->items[++pilha->topo] = expressao;
    }
}

char desempilhando(Pilha *pilha){
    if(!vazio(pilha)){
        return pilha->items[pilha->topo--];
    }
    return '\0';
}

int verificandoBalanceados(char abrindo,char fechando){
    if(abrindo == '(' && fechando == ')') return 1;
    if(abrindo == '[' && fechando == ']') return 1;
    if(abrindo == '{' && fechando == '}') return 1;
    return 0;
}

int main(){

    Pilha pilha;
    char expressao[MAXIMO];

    inicializando(&pilha);

    printf("Digite a expressao :  \n\n");
    fgets(expressao,MAXIMO,stdin);

    for(int i = 0; i < strlen(expressao);i++){
        char c = expressao[i];

        if(c == '(' || c == '[' || c == '{'){
            empilhando(&pilha,c);
        }else if(c == ')' || c == ']' || c == '}'){
            if(vazio(&pilha)){
                printf("expressa é invalida\n\n");
                return 0;
            }
            char topo = desempilhando(&pilha);
            if(!verificandoBalanceados(topo,c)){
                printf("erro é invalida\n");
                return 0;
            }
        }
    }

    if(vazio(&pilha)){
        printf("expressao é valida\n");
    }else{
        printf("erro é invalida\n");
    }

    return 0;

}