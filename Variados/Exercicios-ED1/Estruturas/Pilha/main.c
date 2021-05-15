#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main() {
    //variaveis do programa
    int tam, opcao, status, item;
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
        printf("\n 1- Adicionar item\n 2- Retirar item\n 3-Tamanho da pilha\n 4-Vazia?\n 5-Destruir\n 6-Sair\n --> ");
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
            status = sDestroy(p);
            if (status) {
                printf("\nPilha destruida com sucesso!\n");
                printf("\nEncerrando programa...\n");
                break;
            } else {
                printf("\nErro ao destruir pilha...verifique se ha elementos na pilha!\n");
            }
        } else if (opcao == 6){
            printf("\nEncerrando programa...\n");
            break;
        } else {
            printf("\nOpcao invalida!!!\n");
        }
    }

    system("pause");
    return 0;
}