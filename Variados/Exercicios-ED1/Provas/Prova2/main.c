#include <stdio.h>
#include <stdlib.h>
#include "listaSLC.h"

int main() {
    //declaracao de funcao a ser utilizada
    int slcIntercala(ListaSLC *l1, ListaSLC *l2);
    int numVezesItem(ListaSLC *lista, int key);
    
    //variaveis do programa
    int tam, opcao, item, status;
    ListaSLC *lista, *lista2;
    
    //criando lista...
    lista = createListaSLC();
    
    //criando e preenchendo lista secundaria para realizar entrelacamento
    lista2 = createListaSLC();
    insertSLCQueue(lista2, 2);
    insertSLCQueue(lista2, 4);
    insertSLCQueue(lista2, 6);
    insertSLCQueue(lista2, 8);
    insertSLCQueue(lista2, 10);
    
    //loop principal
    while (1) {
        //menu de opcoes
        printf("\n1- Adicionar item (Pilha) \n2- Adicionar item (Fila) \n3- Remover item \n4- Tamanho da lista \n5- Intercalar listas \n6- Ocorrencias do item X \n7- Sair \n-->");
        scanf("%d", &opcao);
        //executando opcoes
        if (opcao == 1) {
            printf("\nInforme o item: ");
            scanf("%d", &item);
            //verificando inserção do item na lista
            status = insertSLCStack(lista, item);
            if (status == 1) {
                printf("\nO item %d foi inserido na lista com sucesso!\n", item);
            } else {
                printf("\nErro ao adicionar item %d na lista...\n", item);
            }
        } else if (opcao == 2) {
            printf("\nInforme o item: ");
            scanf("%d", &item);
            //verificando inserção do item na lista
            status = insertSLCQueue(lista, item);
            if (status == 1) {
                printf("\nO item %d foi inserido na lista com sucesso!\n", item);
            } else {
                printf("\nErro ao adicionar item %d na lista...\n", item);
            }
        } else if (opcao == 3) {
            item = removeSLC(lista);
            if (item != NULL) {
                printf("\nItem %d removido da lista com sucesso!\n", item);
            } else {
                printf("\nErro ao remover item da lista...\n");
            }
        } else if (opcao == 4) {
            tam = sizeListaSLC(lista);
            printf("\nTamanho atual da lista: %d\n", tam);
        } else if (opcao == 5) {
            status = slcIntercala(lista, lista2);
            //verificando se deu tudo certo...
            if (status == 1) {
                printf("\nSucesso ao intercalar as listas!\n");
            } else {
                printf("\nErro ao intercalar as listas...\n");
            }
        } else if (opcao == 6) {
            printf("\nInforme o item: ");
            scanf("%d", &item);
            status = numVezesItem(lista, item);
            printf("\nO item %d aparece %d vezes na lista!\n", item, status);
        } else if (opcao == 7) {
            if (slcDestroy(lista)) {
                printf("\nEncerrando programa...\n");
                break;
            } else {
               printf("\nVerifique se a lista esta vazia!\n"); 
            }
        } else {
            printf("\nSinto muito! Opcao invalida!!!\n");
        }
    }
    
    system("pause");
    return 0;
}
/*
    12.	Receber duas listas circulares simplesmente encadeadas (L1 e L2), incluir todos os nós de L2 em 
    L1, de maneira intercalada. Não pode alocar novos nós. A lista L1 ficara com um nó de L1, sempre 
    seguido de um nó de L2
    Exemplo: int sllIntercala  ( SLList *l1, SLList *l2)
*/
int slcIntercala(ListaSLC *l1, ListaSLC *l2) {
    int i, tam = (2*sizeListaSLC(l1))-1;
    //pontos iniciais das listas
    NodeSLC *nodeL1, *nodeL2, *nextL1, *nextL2;
    
    //l1 e l2 devem ter tamanhos iguais
    if (sizeListaSLC(l1) == sizeListaSLC(l2)) {
        nodeL1 = l1->primeiro;
        nodeL2 = l2->primeiro;
        for (i=0; i<tam; i++) {
            //realizando entrelacamento do node l1 com l2
            if ( i%2 == 0) {
                nextL1 = nodeL1->proximo; //salvando sucessor do antigo node l1
                nodeL1->proximo = nodeL2;
                printf("\nNodeL1 = %d | NodeL2 = %d | nextL1 = %d\n", nodeL1->item, nodeL2->item, nextL1->item);
                nodeL1 = nextL1; //proximo node de l1 que será entrelacado
                printf("\nNovo nodeL1 = %d\n", nodeL1->item);
            } 
            //realizando entrelacamento do node l2 com l1
            else {
                nextL2 = nodeL2->proximo; //salvando sucessor do antigo node l2
                nodeL2->proximo = nodeL1;
                printf("\nNodeL2 = %d | NodeL1 = %d | nextL2 = %d\n", nodeL2->item, nodeL1->item, nextL2->item);
                nodeL2 = nextL2; //proximo node de l2 que será entrelacado
                printf("\nNovo nodeL2 = %d\n", nodeL2->item);
            }
        }
        //setando fim da lista para o inicio (circular)
        nodeL2->proximo = l1->primeiro;
        return 1; //TRUE, sucesso ao entrelacar listas
    }
    
    return 0; //FALSE, listas nao satisfazem condicoes para entrelacamento
}
/*
    2. Escreva um algoritmo que recebe uma lista circular simplesmente encadeada e
    conta o número de vezes que um determinado dado identificado por key se encontra
    na lista.
*/
int numVezesItem(ListaSLC *lista, int key) {
    int i, vezes = 0;
    NodeSLC *nodeAtual;
    //verificando lista
    if (lista != NULL) {
        //percorrendo lista
        nodeAtual = lista->primeiro;
        for (i=0; i<sizeListaSLC(lista); i++) {
            if (nodeAtual != NULL) {
                if (nodeAtual->item == key) {
                    vezes++;
                }
                nodeAtual = nodeAtual->proximo;
            }
        }
    }
    return vezes;
}
