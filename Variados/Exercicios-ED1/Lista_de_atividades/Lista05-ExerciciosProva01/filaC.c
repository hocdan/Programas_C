#include <stdio.h>
#include <stdlib.h>
#include "filaC.h"

/*
    Função que cria uma Fila circular de certo tamanho int N
    Argumentos: um inteiro que representa o tamanho da fila N
    Retorno: um ponteiro para a estrutura do tipo Fila de tamanho N ou NULL em caso de falha ao criar
*/
Fila * createQueueC(int maxItens) {
    int i;
    Fila *f;
    
    if (maxItens > 0) {
        f = (Fila *) malloc(sizeof(Fila)); //criando fila
        if (f != NULL) {
            f->Itens = (int *) malloc(sizeof(int) * maxItens); //alocando espaco para os elementos da fila
            if (f->Itens != NULL) {
                //setando valores iniciais da fila
                f->front = 0;
                f->rear = 0;
                f->maxItens = maxItens;
                //criando vetor nulo
                for (i=0; i<f->maxItens; i++) {
                    f->Itens[i] = NULL;
                }
                return f;
            }
            free(f); //liberando espaco alocado
        }
    }
    return NULL;
}
/*
    Função que irá inserir um elemento ao fim da fila (traseira)
    Argumentos: uma fila qualquer e um elemento
    Retorno: 1 (TRUE) em caso de enfileiramento bem sucedida e 0 (FALSE) caso contrário
*/
int enqueue(Fila *f, int item) {
     //verificando se a posicao da traseira (de inserção) está vazia
     if (f->Itens[f->rear] == NULL) {
         f->Itens[f->rear] = item; //enfileirando no final da fila
         //atualizando traseira da fila (modo circular)
         if (f->rear == (f->maxItens-1)) {
            f->rear = 0; //voltando ao inicio
         } else {
            f->rear++;
         }
         return 1; //item inserido com sucesso
     }
     return 0; //erro ao inserir elemento
}
/*
    Função que retira um elemento do inicio da fila (frente)
    Argumentos: uma fila qualquer
    Retorno: o item em caso de sucesso ou NULL caso contrário
*/
int dequeue(Fila *f) {
    int item;
    //verificando se a fila esta vazia
    if (f->Itens[f->front] != NULL) {
        item = f->Itens[f->front];
        f->Itens[f->front] = NULL; //esvaziando lugar
        //atualizando frente da fila (modo circular)
        if (f->front == (f->maxItens-1)) {
            f->front = 0;
        } else {
            f->front++;
        }
        return item; //devolvendo item desenfileirado
    }
    return NULL; //erro ao retirar elemento
}
/*
    Função que diz se uma fila está vazia ou não
    Argumentos: uma fila qualquer
    Retorno: devolve 1 (TRUE) caso a fila esteja vazia e 0 (FALSE) caso contrário
*/
int isEmpty(Fila *f) {
    
    if (f->front == f->rear && f->Itens[f->front] == NULL) {
        return 1; //TRUE
    }
    return 0; //FALSE
}
/*
    Função que retorna o tamanho atual de uma fila
    Argumentos: uma fila qualquer
    Retorno: um inteiro N que representa o numero de elementos contidos na fila
*/
int queueSize(Fila *f) {
    int tam;
    //calculando numero de elementos
    if (f->front == f->rear && f->Itens[f->front] != NULL) {
        return f->maxItens;
    } else if (f->front > f->rear) {
        return f->maxItens - f->front;
    }
    tam = f->rear - f->front;
    return tam;
}
/*
    Funcao que elimina uma fila
    Argumentos: uma fila qualquer
    Retorno: devolve 1 (TRUE) em caso de eliminacao e 0 (FALSE) caso contrário
*/
int qDestroy(Fila *f) {
    //eliminar fila apenas se estiver vazia
    if (f->front == f->rear && f->Itens[f->front] == NULL) {
        free(f->Itens); //desalocando vetor de elementos da fila
        free(f); //desalocando a fila
        return 1; // eliminacao bem sucedida
    }
    return 0; //erro ao eliminar fila
}