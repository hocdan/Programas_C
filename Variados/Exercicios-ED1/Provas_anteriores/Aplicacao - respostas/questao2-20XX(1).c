#include <stdio.h>
#include <stdlib.h>
#include "filaC.h"
/*
   Receber uma fila armazenada em um vetor circular removendo os
   elementos de ordem impar da fila (primeiro, terceiro, etc...)   
*/
int main() {
    //declarando funcao a ser utilizada
    void removeImpar(Fila *f);
    
    //variaveis do programa
    int i, opcao, item, tam, status;
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
        printf("\n 1-Enfileirar\n 2-Desenfileirar\n 3-Vazia?\n 4-Tamanho da fila\n 5-Destruir\n 6-Remove Impar\n 7-Sair\n--> ");
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
        }else if (opcao == 6) {
            removeImpar(fila);
            //imprimindo fila resultante
            printf("\nSituacao da fila:\n");
            for (i=0; i<fila->maxItens; i++) {
                printf("Fila[%d] = %d\n", i, fila->Itens[i]);
            }
        }else if (opcao == 7 && qDestroy(fila)) {
            printf("\nEncerrando programa...\n");
            break;
        } else {
            printf("\nOpcao invalida!!!\n");
        }
    }
    
    
    system("pause");
    return 0;
}

void removeImpar(Fila *f) {
    int i;
    //percorrendo fila e elimando os elementos de ordem impar (primeiro, terceiro, etc...)
    for (i=0; i<f->maxItens; i++) {
        if ((i+1)%2 != 0) {
            f->Itens[i] = NULL;
        }
    }
    //percorrendo novamente a fila para reordenar os itens restantes
    f->front = 0;
    f->rear = 0;
    for (i=0; i<f->maxItens; i++) {
        if (f->Itens[i] != NULL) {
            f->Itens[f->rear] = f->Itens[i]; //infileirando para a posicao mais inicial
            f->Itens[i] = NULL; //eliminando duplicata do item
            f->rear++; //atualizando traseira da fila
        }
    }   
}