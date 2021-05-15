//condicoes para nao repetir referenciamento
#ifndef LISTASL_H_INCLUDED
#define LISTASL_H_INCLUDED

//struct Node da Lista simplesmente encadeada
typedef struct _NodeSL_ {
    struct _NodeSL_ *proximo; //aponta para o proximo node
    int item; //dado do node
} NodeSL;
//struct Lista simplesmente encadeada
typedef struct _ListaSL_ {
    NodeSL *primeiro; //aponta para o primeiro node da lista
} ListaSL;

    //FUNCAO TESTE
    ListaSL * createListaSL();
    int insertSLStack(ListaSL *lista, int item); //comportamento de pilha
    int insertSLQueue(ListaSL *lista, int item); //comportamento de fila
    int removeSL(ListaSL *lista);
    int sizeListaSL(ListaSL *lista);
    int insertBeforeN(ListaSL *lista, int item, int n); //operação extra (exercício)
    int removeAfterN(ListaSL *lista, int n); //operacao extra (exercicio)
    
#endif //arquivo LISTASIMPLES_H