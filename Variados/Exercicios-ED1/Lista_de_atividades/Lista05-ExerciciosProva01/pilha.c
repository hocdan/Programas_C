#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
/*
    Função que irá criar uma struct do tipo Pilha
    Argumentos: um número inteiro que determina o tamanho inicial da pilha
    Retorno: devolve um ponteiro do tipo Pilha (a propria struct pilha)
*/
Pilha* createStack( int max ) {
    Pilha *p;
    
    if (max > 0) {
        p = (Pilha *) malloc(sizeof(Pilha)); //alocando memoria para a pilha
        if (p != NULL) {
            p->Itens = (int *) malloc(sizeof(int) * max);
            if (p->Itens != NULL) {
                p->topo = -1; //setando topo de pilha vazia
                p->maxItens = max; //setando limite de itens da pilha
                return p; //retornando a pilha criada
            }
            free(p); //limpando memoria de pilha mal-sucedida
        }
    }
    return NULL; //erro ao criar pilha
}
/*
    Função que irá mostrar o status de ocupacao de uma pilha
    Argumentos: uma struct pilha qualquer
    Retorno: TRUE (1) caso esteja vazia ou FALSE(0) caso tenha algum elemento armazenado
*/
int isEmpty(Pilha *p) {
    //tendo como base o topo da pilha
    if (p->topo == -1) {
        return 1; //verdadeiro, pilha vazia
    } else {
        return 0; //falso, pilha contem elementos
    }
}
/*
    Funcao que ira adicionar um item à pilha
    Argumentos: uma pilha qualquer e um item
    Retorno: TRUE(1) caso a adição seja bem sucedida e FALSE(0) caso contrario
*/
int push(Pilha *p, int item) {
    //se ainda houver espaco para guardar...
    if (p->topo < (p->maxItens-1)){
        p->topo++; //atualizando topo da pilha
        p->Itens[p->topo] = item; //adicionando item à pilha
        return 1; //realizado com sucesso
    }
    return 0; //erro ao adicionar item
}
/*
    Funcao que retira um elemento da pilha
    Argumentos: uma pilha qualquer
    Retorno: devolve o elemento do topo ou NULL em caso de erro (pilha vazia)
*/
int pop(Pilha *p) {
    int item;
    
    //verificando se ha algum item para retirar
    if (p->topo == -1) {
        return NULL; //erro ao retirar elemento
    }
    item = p->Itens[p->topo];
    p->topo--;
    return item; //devolvendo item retirado da pilha 
}
/*
    Funcao que informa o numero de elementos em uma pilha
    Argumentos: uma pilha qualquer
    Retorno: devolve um inteiro com base no numero de elementos presente na pilha
*/
int stackSize(Pilha *p) {
    
    return p->topo+1; //0 caso vazia
}
/*
    Funcao que elimina uma pilha
    Argumentos: uma pilha qualquer
    Retorno: devolve 1 (TRUE) em caso de eliminacao e 0 (FALSE) caso contrário
*/
int sDestroy(Pilha *p) {
    //verificando se a pilha esta vazia
    if (p->topo == -1) {
        free(p->Itens); //desalocando vetor de elementos da pilha
        free(p); //desalocando pilha
        return 1; //eliminacao bem sucedida
    }
    return 0; //erro ao eliminar pilha
}
/*
    Função que imprime os elementos de uma pilha indo do topo até o fundo 
    Argumentos: uma pilha qualquer
    Retorno: nenhum, apenas imprime os itens da pilha
*/
void showStack(Pilha *pilha) {
    int i;
    //retirando itens da pilha e imprimindo cada um
    printf("\nPilha = [ ");
    for (i=stackSize(pilha)-1; i>=0; i--) {
        printf("%d ", pilha->Itens[i]);
    }
    printf("]\n");
}