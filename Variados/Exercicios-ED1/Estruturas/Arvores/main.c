#include <stdio.h>
#include <stdlib.h>
#include "arvoreBin.h"

int main() {
    //variaveis do programa
    int item, opcao, status;
    ArvoreBin *arvore;
    NodeT *node;
    
    //criando arvore para utilizacao do programa
    arvore = createArvoreBin();
    
    //Loop principal
    while (1) {
        printf("\n 1- Adicionar item\n 2- Remover item\n 3- Consultar item\n 4- Imprimir arvore (simetrica)\n 5-Sair\n --> ");
        scanf("%d", &opcao);
        //menu de opcoes
        if (opcao == 1) {
            printf("\nInforme o item: ");
            scanf("%d", &item);
            //inserindo item na arvore
            status = insertArvoreBin(arvore, item);
            if (status == 1) {
                printf("\nO item %d foi adicionado com sucesso na arvore!\n", item);
            } else {
                printf("\nErro ao adicionar o item %d na arvore...\n", item);
            }
        } else if (opcao == 2) {
            printf("\nInforme o item: ");
            scanf("%d", &item);
            //removendo item na arvore
            if (arvore->raiz == NULL) {
                printf("\nArvore vazia! Impossivel remover itens...\n");
            } else {
                node = removeArvoreBin(arvore->raiz, item);
                if (node != NULL) {
                    printf("\nO item %d foi removido com sucesso!\n", node->item);
                } else {
                    printf("\nErro ao remover o item da arvore...\n");
                }
            }
        } else if (opcao == 3) {
            printf("\nInforme o item: ");
            scanf("%d", &item);
            //procurando item na arvore
            if (arvore->raiz == NULL) {
                printf("\nArvore vazia! Sem itens...\n");
            } else {
                node = queryArvoreBin(arvore->raiz, item);
                if (node != NULL) {
                    printf("\nO item %d se encontra na arvore!\n", node->item);
                } else {
                    printf("\nO item %d nao se encontra na arvore...\n", item);
                }
            }
        } else if (opcao == 4) {
            printf("\nImprimindo arvore em ordem simetrica:\n\n");
            printArvoreBinInOrdem(arvore->raiz);
            printf("\n\n");
        } else if (opcao == 5) {
            printf("\nEncerrando programa...\n");
            break; //saindo do loop
        } else {
            printf("\nOpcao invalida!!! Tente novamente...\n");
        }
    }
    
    system("pause");
    return 0;
}