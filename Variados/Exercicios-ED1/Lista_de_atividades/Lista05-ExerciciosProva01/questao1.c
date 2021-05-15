#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
/*
    1. Use as operações push, pop, top e empty para construir operações que façam o
    seguinte:
    a. Definir i como o segundo elemento a partir do topo da pilha, deixando a pilha sem
    seus dois elementos superiores.
    b. Definir i como o segundo elemento a partir do topo da pilha, deixando a pilha
    inalterada.
    c. Dado um inteiro n, definir i como o enésimo elemento a partir do topo da pilha,
    deixando a pilha sem seus n elementos superiores.
    d. Dado um inteiro n, definir i como o enésimo elemento a partir do topo da pilha,
    deixando a pilha inalterada.
    e. Definir i como o último elemento da pilha, deixando a pilha vazia.
    f. Definir i como o último elemento da pilha, deixando a pilha inalterada.(Dica: use
    outra pilha auxiliar.)
    g. Definir i como o terceiro elemento a partir do final da pilha.
*/
int main () {
    //declaracao das funcoes a serem utilizadas
    void mostrarPilha(Pilha *pilha);
    int alterarPilha(Pilha *pilha1, int item, int pos);
    
    //variaveis do programa
    int tam, opcao, status, item, pos;
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
        printf("\n 1-Adicionar item\n 2-Retirar item\n 3-Tamanho da pilha\n 4-Vazia?\n 5-Inserir como elemento N\n 6-Destruir\n 7-Sair\n --> ");
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
            printf("\nInforme o item: ");
            scanf("%d", &item);
            printf("\nInforme a posicao (segundo, terceiro...em relacao ao topo): ");
            scanf("%d", &pos);
            
            status = alterarPilha(p, item, pos);
            if (status == 1) {
                printf("\nInsercao do item %d no %d lugar a partir do topo da pilha feita com sucesso!\n", item, pos);
                mostrarPilha(p);
            } else {
                printf("\nErro ao inserir o item %d no %d lugar a partir do topo da pilha...\n", item, pos);
            }
        }else if (opcao == 6) {
            status = sDestroy(p);
            if (status) {
                printf("\nPilha destruida com sucesso!\n");
                printf("\nEncerrando programa...\n");
                break;
            } else {
                printf("\nErro ao destruir pilha...verifique se ha elementos na pilha!\n");
            }
        } else if (opcao == 7){
            printf("\nEncerrando programa...\n");
            break;
        } else {
            printf("\nOpcao invalida!!!\n");
        }
    }
    

    system("pause");
    return 0;
}

void mostrarPilha(Pilha *pilha) {
    int i;
    //retirando itens da pilha e imprimindo cada um
    printf("\nPilha = [ ");
    for (i=stackSize(pilha)-1; i>=0; i--) {
        printf("%d ", pilha->Itens[i]);
    }
    printf("]\n");
}

int alterarPilha(Pilha *pilha1, int item, int pos) {
    int i;
    Pilha *pilha2;
    
    //alocando memoria para a pilha auxiliar (mesmo tamanho da original)
    pilha2 = createStack(pilha1->maxItens);
    if (pilha2 != NULL) {
        //verificando se a posicao do item é valida
        if ( (pos-1) <= stackSize(pilha1) && stackSize(pilha1) < (pilha1->maxItens) && (pos-1) > 0) {
            //desempilhando ate chegar na posicao do item (segundo, terceiro...)
            for (i=0; i<pos-1; i++) {
                push(pilha2, pop(pilha1));
            }
            push(pilha1, item); //adicionando item na posicao desejada
            //restaurando ordem dos elementos da pilha antiga
            for (i=0; i<pos-1; i++) {
                push(pilha1, pop(pilha2));
            }
            return 1; //TRUE, deu certo
        }
    }
    return 0; //FALSE, deu erro
}