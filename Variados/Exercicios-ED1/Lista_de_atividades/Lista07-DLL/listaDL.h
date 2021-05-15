//condicoes para nao repetir referenciamento
#ifndef LISTADL_H_INCLUDED
#define LISTADL_H_INCLUDED

//struct Node da Lista simplesmente encadeada
typedef struct _NodeDL_ {
    struct _NodeDL_ *anterior, *proximo; //links do node com o anterior e o proximo
    int item; //dado do node
} NodeDL;
//struct Lista simplesmente encadeada
typedef struct _ListaDL_ {
    NodeDL *primeiro; //aponta para o primeiro node da lista
    NodeDL *atual; //aponta para o ultimo item procurado/utilizado da lista
} ListaDL;

    //FUNCAO TESTE
    ListaDL * createListaDL();
    int insertDLStack(ListaDL *lista, int item); //comportamento de pilha
    int insertDLQueue(ListaDL *lista, int item); //comportamento de fila
    int insertBeforeN(ListaDL *lista, int item, int n);
    int insertAfterN (ListaDL *lista, int item, int n);
    int removeDL(ListaDL *lista, int n);
    int sizeListaDL(ListaDL *lista);
    int dlDestroy(ListaDL *lista);    
    
#endif //arquivo LISTASIMPLES_H