#include <stdio.h>
#include <stdlib.h>
#include "listaDL.h"

int main () {
    //variaveis do programa
    int tam, opcao, item, status, pos;
    ListaDL *lista;
    
    //criando lista...
    lista = createListaDL();
    
    //loop principal
    while (1) {
        printf("\n 1-Adicionar item na lista (pilha)\n 2-Adicionar item na lista (fila)\n 3-Adicionar item antes da posicao N\n 4-Adicionar item depois da posicao N\n 5-Remover item N da lista\n 6-Tamanho da lista\n 7-Sair\n --> ");
        scanf("%d", &opcao);
        //menu das opções
        if (opcao == 1) {
            printf("\n Informe o item: ");
            scanf("%d", &item);
            //inserindo item na lista
            status = insertDLStack(lista, item);
            if (status) {
                printf("\n O item %d foi inserido na lista com sucesso!\n", item);
            } else {
                printf("\n Erro ao adicionar o item %d na lista...\n", item);
            }
        } else if (opcao == 2) {
            printf("\n Informe o item: ");
            scanf("%d", &item);
            //inserindo item na lista
            status = insertDLQueue(lista, item);
            if (status) {
                printf("\n O item %d foi inserido na lista com sucesso!\n", item);
            } else {
                printf("\n Erro ao adicionar o item %d na lista...\n", item);
            }
        } else if (opcao == 3) {
            printf("\n Informe o item: ");
            scanf("%d", &item);
            printf("\n Informe a posição N: ");
            scanf("%d", &pos);
            //inserindo item na lista
            status = insertBeforeN(lista, item, pos);
            if (status) {
                printf("\n O item %d foi inserido na posicao %d da lista com sucesso!\n", item, pos);
            } else {
                printf("\n Erro ao adicionar o item %d na lista...\n", item);
            }
        } else if (opcao == 4) {
            printf("\n Informe o item: ");
            scanf("%d", &item);
            printf("\n Informe a posição N: ");
            scanf("%d", &pos);
            //inserindo item na lista
            status = insertAfterN(lista, item, pos);
            if (status) {
                printf("\n O item %d foi inserido na posicao %d da lista com sucesso!\n", item, pos+1);
            } else {
                printf("\n Erro ao adicionar o item %d na lista...\n", item);
            }
        } else if (opcao == 5) {
            printf("\n Informe a posicao N: ");
            scanf("%d", &pos);
            item = removeDL(lista, pos);
            //verificando se a remoção foi bem sucedida
            if (item != NULL) {
               printf("\n O item %d foi removido da posicao %d da lista com sucesso!\n", item, pos); 
            } else {
               printf("\n Erro ao remover item da lista...\n");
            }
        } else if (opcao == 6) {
            tam = sizeListaDL(lista);
            printf("\n Tamanho atual da lista: %d\n", tam);
        } else if (opcao == 7) {
            if (dlDestroy(lista)) {
                printf("\n Encerrando programa...\n");
                break; //encerrando loop principal
            } else {
                printf("\n Verifique se a lista esta vazia!\n");
            }
        } else {
            printf("\n Sinto muito! Opcao invalida!!!\n");
        }
    }

    system("pause");
    return 0;
}