//condicoes para nao repetir referenciamento
#ifndef ARVOREBIN_H_INCLUDED
#define ARVOREBIN_H_INCLUDED

//struct Node da Arvore Binaria simples
typedef struct _NodeT_ {
    int item; //dado do node
    struct _NodeT_ *esquerda, *direita; //links do node para a subarvore esquerda e direita
} NodeT;
//struct Arvore Binaria simples
typedef struct _ArvoreBin_ {
    NodeT *raiz; //aponta para o primeiro node da arvore (a raiz)
} ArvoreBin;

    //FUNCAO TESTE
    ArvoreBin * createArvoreBin();
    int insertArvoreBin(ArvoreBin *arvore, int item);
    NodeT * removeArvoreBin(NodeT *node, int item);
    NodeT* queryArvoreBin(NodeT *raiz, int item);
    void printArvoreBinInOrdem(NodeT *raiz);    
    
#endif //arquivo ARVOREBIN_H