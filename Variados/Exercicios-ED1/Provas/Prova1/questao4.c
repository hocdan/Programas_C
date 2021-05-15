#include <stdio.h>
#include <stdlib.h>
#include "filaC.h"
/*
    4. Faça um algoritmo que recebe uma fila implementada como um vetor circular e
    promove o n-esimo elemento da fila (caso ele exista) colocando-o na primeira
    posição. Caso a fila tenha menos que n elementos coloca o ultimo elemento na
    primeira posição da fila.
    int PromoveElementoFila (Queue *q, int n)
*/
int main() {
    //declaracao da funcao a ser utilizada
    int promoveElementoFila(Fila *f, int n);
    
    //variaveis do programa
    int opcao, item, tam, status;
    Fila *fila;
    
    //inicializando fila 
    printf("Tamanho da fila circular: ");
    scanf("%d", &tam);
    fila = createQueueC(tam);
    if (fila == NULL) {
        printf("\nErro ao criar fila circular...encerrando programa...\n");
        exit(1);
    }
    //loop principal
    while (1) {
        printf("\n 1-Enfileirar\n 2-Desenfileirar\n 3-Vazia?\n 4-Tamanho da fila\n 5-Promover elemento\n 6-Destruir\n 7-Sair\n--> ");
        scanf("%d", &opcao);
        //executando opcoes 
        if (opcao == 1) {
            printf("Informe o elemento: ");
            scanf("%d", &item);
            status = enqueue(fila, item); //inserindo item na fila
            if (status) {
                printf("\nItem %d enfileirado com sucesso!\n", item);
            } else {
                printf("\nErro ao enfileirar item %d...\n", item);
            }
        } else if (opcao == 2) {
            item = dequeue(fila);
            if (item != NULL) {
                printf("\nItem %d desenfileirado com sucesso!\n", item);
            } else {
                printf("\nErro ao desenfileirar item...\n");
            }
        } else if (opcao == 3) {
            status = isEmpty(fila);
            if (status) {
                printf("\nFila vazia!\n");
            } else {
                printf("\nFila ocupada!\n");
            }
        } else if (opcao == 4) {
            tam = queueSize(fila);
            printf("\nTamanho atual: %d\n", tam);
        } else if (opcao == 5) {
            
        } else if (opcao == 6) {
            status = qDestroy(fila);
            if (status) {
                printf("\nFila destruida com sucesso!\n");
                printf("\nEncerrando programa...\n");
                break;
            } else {
                printf("\nErro ao destruir fila...verifique se ha elementos na fila!\n");
            }
        } else if (opcao == 7) {
            printf("\nEncerrando programa...\n");
            break;
        } else {
            printf("\nOpcao invalida!!!\n");
        }
    }
    

    system("pause");
    return 0;
}

int promoveElementoFila(Fila *f, int n) {
    
    
}