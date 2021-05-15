#include <stdio.h>
#include <stdlib.h>
#include "listaSL.h"

int main() {
    //variaveis do programa
    int tam, opcao, item, status, pos;
    ListaSL *lista;
    
    //criando lista...
    lista = createListaSL();
    
    //loop principal
    while (1) {
        //menu de opcoes
        printf("\n1- Adicionar item (Pilha) \n2- Adicionar item (Fila) \n3- Remover item \n4- Tamanho da lista \n5- Inserir antes da posicao N \n6- Remover depois da posicao N \n7- Sair \n-->");
        scanf("%d", &opcao);
        //executando opcoes
        if (opcao == 1) {
            printf("\nInforme o item: ");
            scanf("%d", &item);
            //verificando inserção do item na lista
            status = insertSLStack(lista, item);
            if (status == 1) {
                printf("\nO item %d foi inserido na lista com sucesso!\n", item);
            } else {
                printf("\nErro ao adicionar item %d na lista...\n", item);
            }
        } else if (opcao == 2) {
            printf("\nInforme o item: ");
            scanf("%d", &item);
            //verificando inserção do item na lista
            status = insertSLQueue(lista, item);
            if (status == 1) {
                printf("\nO item %d foi inserido na lista com sucesso!\n", item);
            } else {
                printf("\nErro ao adicionar item %d na lista...\n", item);
            }
        } else if (opcao == 3) {
            item = removeSL(lista);
            if (item != NULL) {
                printf("\nItem %d removido da lista com sucesso!\n", item);
            } else {
                printf("\nErro ao remover item da lista...\n");
            }
        } else if (opcao == 4) {
            tam = sizeListaSL(lista);
            printf("\nTamanho atual da lista: %d\n", tam);
        } else if (opcao == 5) {
            printf("\nInforme o item: ");
            scanf("%d", &item);
            printf("\nInforme a posicao N: ");
            scanf("%d", &pos);
            //verificando inserção especial na lista
            status = insertBeforeN(lista, item, pos);
            if (status == 1) {
                printf("\nO item %d foi inserido na posicao %d da lista com sucesso!\n", item, pos);
            } else {
                printf("\nErro ao adicionar item na lista...\n");
            }
        } else if (opcao == 6) {
            printf("\nInforme a posicao N: ");
            scanf("%d", &pos);
            //verificando inserção especial na lista
            item = removeAfterN(lista, pos);
            if (item != NULL) {
                printf("\nO item %d foi removido da posicao %d da lista com sucesso!\n", item, pos+1);
            } else {
                printf("\nErro ao remover item da lista...\n");
            } 
        } else if (opcao == 7) {
            if (sizeListaSL(lista) != 0) {
                printf("\nVerifique se a lista esta vazia!\n");
            } else {
                printf("\nEncerrando programa...\n");
                break;
            }
        } else {
            printf("\nSinto muito! Opcao invalida!!!\n");
        }
    }
    
    system("pause");
    return 0;
}