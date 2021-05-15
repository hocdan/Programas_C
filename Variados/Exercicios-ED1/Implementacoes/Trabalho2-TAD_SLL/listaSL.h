//condicoes para nao repetir referenciamento
#ifndef LISTASL_H_INCLUDED
#define LISTASL_H_INCLUDED

//struct Aluno, tipo de dado que será armazenado na lista
typedef struct _Aluno_ {
    char nome[30];
    int ID;
    float media;
} Aluno;
//struct Node da Lista simplesmente encadeada
typedef struct _NodeSL_ {
    struct _NodeSL_ *proximo; //aponta para o proximo node
    Aluno *item; //dado do node
} NodeSL;
//struct Lista simplesmente encadeada
typedef struct _ListaSL_ {
    NodeSL *primeiro; //aponta para o primeiro node da lista
} ListaSL;

    //FUNCOES DA LISTA
    ListaSL * createListaSL();
    int insertSLStack(ListaSL *lista, Aluno *item); //comportamento de pilha
    int insertSLQueue(ListaSL *lista, Aluno *item); //comportamento de fila
    Aluno * removeSL(ListaSL *lista);
    Aluno * removeStudent(ListaSL *lista, int ID);
    Aluno * searchStudent(ListaSL *lista, int ID);
    int sizeListaSL(ListaSL *lista);
    int slDestroy(ListaSL *lista);
    
#endif //arquivo LISTASL_H