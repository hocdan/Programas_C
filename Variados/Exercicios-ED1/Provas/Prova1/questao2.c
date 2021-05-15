#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
/*
    Escreva um algoritmo para a operação Pune que pune um elemento em uma pilha
    colocando ele n posições para baixo. Considere que a pilha está implementada como
    um vetor.
    int Pune (Stack *s, int n)
*/
int main () {
    //declaracao das funcoes a serem utilizadas
    void mostrarPilha(Pilha *pilha);
    int Pune(Pilha *p, int n);
    
    //variaveis do programa
    int tam, opcao, status, item, n;
    Pilha *p;

    printf("Tamanho da pilha: ");
    scanf("%d", &tam);
    //criando pilha
    p = createStack(tam);

    if (p == NULL) {
        printf("\nErro ao criar pilha...encerrando programa...\n");
        exit(1);
    }
    //loop principal para manipular a pilha
    while (1) {
        printf("\n 1-Adicionar item\n 2-Retirar item\n 3-Tamanho da pilha\n 4-Vazia?\n 5-Rebaixar topo\n 6-Destruir\n 7-Sair\n --> ");
        scanf("%d", &opcao);
        //realizando opcoes
        if (opcao == 1){
            printf("Informe um inteiro: ");
            scanf("%d", &item);
            status = push(p, item);
            if (status == 1) {
                printf("\nItem %d adicionado com sucesso!\n", item);
            } else {
                printf("\nErro ao adicionar item %d...\n", item);
            }
        } else if (opcao == 2){
            item = pop(p);
            if (item != NULL) {
                printf("\nItem %d retirado com sucesso!\n", item);
            } else {
                printf("\nErro ao retirar item...pilha provavelmente vazia!\n");
            }
        } else if (opcao == 3){
            tam = stackSize(p);
            printf("\nTamanho atual: %d\n", tam);
        } else if (opcao == 4){
            status = isEmpty(p);
            if (status == 1) {
                printf("\nPilha vazia!\n");
            } else {
                printf("\nPilha ocupada!\n");
            }
        } else if (opcao == 5) {
            printf("\nInforme o rebaixamento: ");
            scanf("%d", &n);
            status = Pune(p, n);
            if (status == 1) {
                printf("\nSucesso ao rebaixar topo da pilha em %d posicoes!\n", n);
                mostrarPilha(p);
            } else {
                printf("\nErro ao rebaixar topo da pilha...\n");
            }
        }else if (opcao == 6) {
            status = sDestroy(p);
            if (status) {
                printf("\nPilha destruida com sucesso!\n");
                printf("\nEncerrando programa...\n");
                break;
            } else {
                printf("\nErro ao destruir pilha...verifique se ha elementos na pilha!\n");
            }
        } else if (opcao == 7){
            printf("\nEncerrando programa...\n");
            break;
        } else {
            printf("\nOpcao invalida!!!\n");
        }
    }
    

    system("pause");
    return 0;
}

void mostrarPilha(Pilha *pilha) {
    int i;
    //retirando itens da pilha e imprimindo cada um
    printf("\nPilha = [ ");
    for (i=stackSize(pilha)-1; i>=0; i--) {
        printf("%d ", pilha->Itens[i]);
    }
    printf("]\n");
}

int Pune(Pilha *p1, int n) {
    int i, topo, tam = stackSize(p1);
    Pilha *p2;
    
    p2 = createStack(tam);
    //verificando se a pilha eh valida e se N nao passa dos limites da pilha
    if (p2 != NULL && n < stackSize(p1) && n > 0 && !isEmpty(p1)) {
        //percorrendo pilha principal e armazenando itens que serao mexidos na pilha secundaria
        topo = pop(p1);
        for (i=0; i<n; i++) {
            push(p2, pop(p1));
        }
        //restaurando pilha, agora com o topo rebaixado
        push(p1, topo);
        for (i=0; i<n; i++) {
            push(p1, pop(p2));
        }
        return 1; //TRUE
    }
    return 0; //FALSE
}