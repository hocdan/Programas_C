//condicoes para nao repetir referenciamento
#ifndef LISTASLC_H_INCLUDED
#define LISTASLC_H_INCLUDED

//struct Node da Lista simplesmente encadeada
typedef struct _NodeSLC_ {
    struct _NodeSLC_ *proximo; //aponta para o proximo node
    int item; //dado do node
} NodeSLC;
//struct Lista simplesmente encadeada
typedef struct _ListaSLC_ {
    NodeSLC *primeiro; //aponta para o primeiro node da lista
} ListaSLC;

    //FUNCAO TESTE
    ListaSLC * createListaSLC();
    int insertSLCStack(ListaSLC *lista, int item); //comportamento de pilha
    int insertSLCQueue(ListaSLC *lista, int item); //comportamento de fila
    int removeSLC(ListaSLC *lista);
    int sizeListaSLC(ListaSLC *lista);
    int slcDestroy(ListaSLC *lista);
    
    
#endif //arquivo LISTASLC_H