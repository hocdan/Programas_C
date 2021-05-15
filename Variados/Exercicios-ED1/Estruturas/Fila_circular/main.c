#include <stdio.h>
#include <stdlib.h>
#include "filaC.h"

int main() {
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
        printf("\n 1-Enfileirar\n 2-Desenfileirar\n 3-Vazia?\n 4-Tamanho da fila\n 5-Destruir\n 6-Sair\n--> ");
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
            status = qDestroy(fila);
            if (status) {
                printf("\nFila destruida com sucesso!\n");
                printf("\nEncerrando programa...\n");
                break;
            } else {
                printf("\nErro ao destruir fila...verifique se ha elementos na fila!\n");
            }
        } else if (opcao == 6) {
            printf("\nEncerrando programa...\n");
            break;
        } else {
            printf("\nOpcao invalida!!!\n");
        }
    }
    

    system("pause");
    return 0;
}