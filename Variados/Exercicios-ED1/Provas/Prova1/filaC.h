//condicoes para nao repetir referenciamento
#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

//struct Fila
typedef struct _Fila_ {
    int front; //posicao do inicio da fila (a ser retirado)
    int rear; //posicao do final da fila (a ser adicionado)
    int maxItens; //limite de elementos que podem ser armazenados
    int *Itens; //vetor de armazenamento dos elementos
} Fila;

    //FUNCAO TESTE
    Fila * createQueueC(int maxItens);
    int enqueue(Fila *f, int item);
    int dequeue(Fila *f);
    int isEmpty(Fila *f);
    int queueSize(Fila *f);
    int qDestroy(Fila *f);
    
    
#endif //arquivo PILHA_H