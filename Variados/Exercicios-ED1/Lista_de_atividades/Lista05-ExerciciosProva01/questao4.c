#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
/*
    4. Implemente uma fila usando duas pilhas.
*/
int main() {
    //declaracao de funcoes a serem utilizadas
    int enfileirar(Pilha *p1, int item);
    int desenfileirar(Pilha *p1);
    int estaVazia(Pilha *p1);
    int filaTamanho(Pilha *p1);
    int fDestruir(Pilha *p1);
    void mostrarFila(Pilha *p1);
    
    //variaveis do programa
    int opcao, item, tam, status;
    Pilha *p1;
    
    //inicializando fila 
    printf("Tamanho da fila: ");
    scanf("%d", &tam);
    p1 = createStack(tam);
    if (p1 == NULL) {
        printf("\nErro ao criar fila...encerrando programa...\n");
        exit(1);
    }
    //loop principal
    while (1) {
        printf("\n 1-Enfileirar\n 2-Desenfileirar\n 3-Vazia?\n 4-Tamanho da fila\n 5-Destruir\n 6-Mostrar fila\n 7-Sair\n--> ");
        scanf("%d", &opcao);
        //executando opcoes 
        if (opcao == 1) {
            printf("Informe o elemento: ");
            scanf("%d", &item);
            status = enfileirar(p1, item); //inserindo item na fila
            if (status) {
                printf("\nItem %d enfileirado com sucesso!\n", item);
            } else {
                printf("\nErro ao enfileirar item %d...\n", item);
            }
        } else if (opcao == 2) {
            item = desenfileirar(p1);
            if (item != NULL) {
                printf("\nItem %d desenfileirado com sucesso!\n", item);
            } else {
                printf("\nErro ao desenfileirar item...\n");
            }
        } else if (opcao == 3) {
            status = estaVazia(p1);
            if (status) {
                printf("\nFila vazia!\n");
            } else {
                printf("\nFila ocupada!\n");
            }
        } else if (opcao == 4) {
            tam = filaTamanho(p1);
            printf("\nTamanho atual: %d\n", tam);
        } else if (opcao == 5) {
            status = fDestruir(p1);
            if (status) {
                printf("\nFila destruida com sucesso!\n");
                printf("\nEncerrando programa...\n");
                break;
            } else {
                printf("\nErro ao destruir fila...verifique se ha elementos na fila!\n");
            }
        } else if (opcao == 6){
            mostrarFila(p1);
        } else if (opcao == 7) {
            status = fDestruir(p1);
            if (status == 1) {
                printf("\nEncerrando programa...\n");
                break;
            } else {
                printf("\nVerifique se a fila esta vazia!\n");
            }
        } else {
            printf("\nOpcao invalida!!!\n");
        }
    }
    
    system("pause");
    return 0;
}
int enfileirar(Pilha *p1, int item) {
    //basta apenas adicionar na pilha
    return push(p1, item);
}
int desenfileirar(Pilha *p1) {
    int i, item, tam;
    Pilha *p2;
    
    //alocando memoria para pilha auxiliar
    p2 = createStack(stackSize(p1));
    if (p2 != NULL) {
        //eliminar o item mais antigo da pilha, ou seja, desenpilhar ate o fundo da pilha principal
        if (isEmpty(p1)) {
            item = NULL;
        } else if (stackSize(p1) == 1) {
            item = pop(p1);
        } else {
            tam = stackSize(p1);
            //repassando itens que nao serao desenfileirados para a pilha auxiliar
            for (i=0; i<tam-1; i++) {
                push(p2, pop(p1));
            }
            item = pop(p1);
            //devolvendo itens para a pilha principal, item a ser desenfileirado encontrado
            for (i=0; i<tam-1; i++) {
                push(p1, pop(p2));
            }
        }
        return item;
    }
    return NULL;
}
int estaVazia(Pilha *p1) {
    if (p1->topo == -1) {
        return 1; //verdadeiro, pilha vazia
    } else {
        return 0; //falso, pilha contem elementos
    }
}
int filaTamanho(Pilha *p1) {
    return p1->topo+1; //0 caso vazia
}
int fDestruir(Pilha *p1) {
    //verificando se a pilha esta vazia
    if (p1->topo == -1) {
        free(p1->Itens); //desalocando vetor de elementos da pilha
        free(p1); //desalocando pilha
        return 1; //eliminacao bem sucedida
    }
    return 0; //erro ao eliminar pilha
}
void mostrarFila(Pilha *p1) {
    int i;
    //retirando itens da pilha e imprimindo cada um
    printf("\nFila = [ ");
    for (i=0; i<stackSize(p1); i++) {
        printf("%d ", p1->Itens[i]);
    }
    printf("]\n");
}

