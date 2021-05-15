//condicoes para nao repetir referenciamento
#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

//struct Pilha
typedef struct _Pilha_ {
    int topo; //guarda a posicao do topo da pilha (-1 se nao houver elementos)
    int maxItens; //guarda o numero maximo de elementos que podem ser contidos na pilha
    char *Itens; //vetor que ira armazenar os elementos da pilha
} Pilha;

    //FUNCAO TESTE
    Pilha* createStack(int max);
    int isEmpty(Pilha *p);
    int push(Pilha *p, char item);
    int pop(Pilha *p);
    int stackSize(Pilha *p);
    int sDestroy(Pilha *p);
    
#endif //arquivo PILHA_H