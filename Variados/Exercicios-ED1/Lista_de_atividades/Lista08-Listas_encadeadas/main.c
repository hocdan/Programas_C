#include <stdio.h>
#include <stdlib.h>
#include "listaDL.h"
/*
    A lista de exercício deve ser manuscrita. Para entregar somente as questoes 1, 5 e 12.
    
    1.	Escreva um algoritmo que calcule o comprimento de uma lista L1:
    
    5.	Escreva um algoritmo NumComuns (L1,L2) , que deve retornar um valor inteiro igual ao número de
    valores comuns às duas listas ordenadas L1 e L2.
    Exemplo: int sllNumComuns ( SLList *l1, SLList *l2, int (*cmp) ( void *, void *));
    
    12.	Receber duas listas circulares simplesmente encadeadas (L1 e L2), incluir todos os nós de L2 em
    L1, de maneira intercalada. Não pode alocar novos nós. A lista L1 ficara com um nó de L1, sempre 
    seguido de um nó de L2.
    Exemplo: int sllIntercala ( SLList *l1, SLList *l2);
*/
int main () {
    //declaracoes de funcoes a serem utilizadas
    int numComuns(ListaDL *l1, ListaDL *l2);
    
    //variaveis do programa
    int tam, opcao, item, status, pos;
    ListaDL *lista, *lista2;
    
    //criando lista...
    lista = createListaDL();
    
    //criando e preenchendo lista extra para comparacoes
    lista2 = createListaDL();
    insertDLQueue(lista2, 1);
    insertDLQueue(lista2, 1);
    insertDLQueue(lista2, 1);
    insertDLQueue(lista2, 2);
    insertDLQueue(lista2, 3);
    insertDLQueue(lista2, 3);
    insertDLQueue(lista2, 4);
    
    //loop principal
    while (1) {
        printf("\n 1-Adicionar item na lista (pilha)\n 2-Adicionar item na lista (fila)\n 3-Adicionar item antes da posicao N\n 4-Adicionar item depois da posicao N\n 5-Remover item N da lista\n 6-Tamanho da lista\n 7-Comparar listas\n 8-Sair\n --> ");
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
            //utilizando lista extra declarada e preenchida anteriormente
            status = numComuns(lista, lista2);
            printf("\n Numero de elementos em comum: %d\n", status);
        } else if (opcao == 8) {
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

int numComuns(ListaDL *l1, ListaDL *l2) {
    int i, j, vezes = 0;
    NodeDL *nodeL1, *nodeL2;
    
    //percorrendo a primeira lista e comparando com a segunda
    for (i=0; i<sizeListaDL(l1); i++) {
        //armazenando item i da lista 1
        if (i == 0) {
            nodeL1 = l1->primeiro;
        } else {
            nodeL1 = nodeL1->proximo;
        }
        for (j=0; j<sizeListaDL(l2); j++) {
            //armazenando item j da lista 2
            if (j == 0) {
                nodeL2 = l2->primeiro;
            } else {
                nodeL2 = nodeL2->proximo;
            }
            //comparando item da lista 1 com o item da lista 2
            if ( nodeL1->item == nodeL2->item ) {
                vezes++; //atualizando contador de itens em comum
            }
        }
    }
    
    return vezes; //devolvendo numero de itens em comum entre l1 e l2
}
