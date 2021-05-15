#include <stdio.h>
#include <stdlib.h>
#include "listaDL.h"
/*
    Função que cria uma lista duplamente encadeada
    Argumentos: nenhum
    Retorno: devolve um ponteiro para a lista se bem sucedido ou NULL caso contrário
*/
ListaDL * createListaDL() {
    ListaDL *lista;
    //alocando espaco para a struct lista
    lista = (ListaDL *) malloc(sizeof(ListaDL));
    //testando se houve sucesso na alocacao
    if (lista != NULL) {
        //setando primeiro node para NULL (lista vazia)
        lista->primeiro = NULL;
        return lista; //retornando lista
    }
    return NULL; //erro ao criar lista
}
/*
    Função que irá inserir o item no inicio da lista (como uma pilha)
    Argumento: uma lista qualquer e um item
    Retorno: devolve 1 (TRUE) se for bem sucedido e 0 (FALSE) caso contrário
*/
int insertDLStack(ListaDL *lista, int item) {
    NodeDL *node;
    //verificando se a lista é válida
    if (lista != NULL) {
        //criando Node para guardar item a ser inserido
        node = (NodeDL *) malloc(sizeof(NodeDL));
        //verificando se a alocacao foi bem sucedida
        if (node != NULL) {
            node->item = item; //armazenando item no novo node
            node->anterior = NULL; //link anterior inexistente pois esse é o primeiro node
            node->proximo = lista->primeiro; //link posterior será o que o primeiro da lista for
            //se ja houver item na lista, fazer o novo apontar para o anterior do primeiro item
            if (lista->primeiro != NULL) {
                lista->primeiro->anterior = node;
            }
            lista->primeiro = node;
            lista->atual = node;
            return 1; //TRUE, sucesso ao adicionar item
        }
    }
    return 0; //FALSE, erro ao adicionar item
}
/*
    Função que irá inserir elemento no final da lista (como uma fila)
    Argumentos: uma lista qualquer e um item
    Retorno: devolve 1 (TRUE) se for bem sucedido e 0 (FALSE) caso contrário
*/
int insertDLQueue(ListaDL *lista, int item) {
    NodeDL *nodeNovo, *nodeAtual;
    //verificando se a lista é válida
    if (lista != NULL) {
        //criando Node para guardar item a ser inserido
        nodeNovo = (NodeDL *) malloc(sizeof(NodeDL));
        //verificando se a alocacao foi bem sucedida
        if (nodeNovo != NULL) {
            nodeNovo->item = item; //armazenando item no node a ser inserido na lista
            //caso a lista esteja vazia...apenas inserir no inicio
            nodeAtual = lista->primeiro;
            if (nodeAtual == NULL) {
                nodeNovo->anterior = NULL; //link anterior inexistente, pois é o primeiro item
                lista->primeiro = nodeNovo; //setando inicio da lista para o novo node
            } else {
                //procurando final da lista...
                while (nodeAtual->proximo != NULL) {
                    nodeAtual = nodeAtual->proximo; //andando para a frente na lista
                }
                //linkando o final do antigo ultimo node com o comeco do novo ultimo node da lista
                nodeAtual->proximo = nodeNovo;
                nodeNovo->anterior = nodeAtual;
            }
            nodeNovo->proximo = NULL; //link posterior do novo node inexistente, pois é o último
            return 1; //TRUE, sucesso ao inserir item na lista
        }
    }
    return 0; //FALSE, erro ao inserir item na lista
}
/*
    Função que irá inserir um item na lista antes do índice N fornecido
    Argumentos: uma lista qualquer, um item e um inteiro N
    Retorno: 1 (TRUE) se for bem sucedido e 0 (FALSE) caso contrário
*/
int insertBeforeN(ListaDL *lista, int item, int n) {
    int posicao;
    NodeDL *nodeNovo, *nodeAtual;
    //verificando se a lista é válida, tem itens e se N é válido
    if (lista != NULL && sizeListaDL(lista) > 0 && n < sizeListaDL(lista)) {
        //criando Node para guardar item a ser inserido
        nodeNovo = (NodeDL *) malloc(sizeof(NodeDL));
        //verificando se a alocacao foi bem sucedida e se o índice é válido
        if (nodeNovo != NULL && n >= 0) {
            //guardando item no Node e proximo elemento da lista
            nodeNovo->item = item;
            //se N = 0, tornar o item o primeiro da lista e referenciar o antigo primeiro
            if (n == 0) {
                nodeNovo->proximo = lista->primeiro;
                nodeNovo->anterior = NULL; //link anterior inexistente, pois é o primeiro item
                lista->primeiro = nodeNovo; //setando inicio da lista para o novo node
            } else {
                posicao = 1; //setando contador de posições
                nodeAtual = lista->primeiro; //iniciando busca a partir do primeiro node
                //procurando node anterior ao que será feita a inserção
                while (posicao < n) {
                    nodeAtual = nodeAtual->proximo;
                    posicao++;
                }
                //encontrado o node, inserir novo node e fazer as linkagens
                nodeNovo->proximo = nodeAtual->proximo;
                nodeAtual->proximo = nodeNovo;
                nodeNovo->anterior = nodeAtual;
            }
            return 1; //TRUE, sucesso ao inserir item na lista
        }
    }
    return 0; //FALSE, erro ao inserir item na lista
}
/*
    Função que irá inserir um item após o índice N fornecido
    Argumentos: uma lista qualquer, um item e um inteiro N
    Retorno: 1 (TRUE) se for bem sucedido e 0 (FALSE) caso contrário
*/
int insertAfterN (ListaDL *lista, int item, int n) {
    int posicao;
    NodeDL *nodeNovo, *nodeAtual;
    //verificando se a lista é válida, tem itens e se N é válido
    if (lista != NULL && sizeListaDL(lista) > 0 && n < sizeListaDL(lista)) {
        //criando Node para guardar item a ser inserido
        nodeNovo = (NodeDL *) malloc(sizeof(NodeDL));
        //verificando se a alocacao foi bem sucedida e se o índice é válido
        if (nodeNovo != NULL && n >= 0) {
            //guardando item no Node e proximo elemento da lista
            nodeNovo->item = item;
            //iniciando busca a partir do primeiro node
            nodeAtual = lista->primeiro;
            posicao = 0; //setando contador de posições
            //procurando node em que será feita a inserção
            while (posicao < n) {
                nodeAtual = nodeAtual->proximo;
                posicao++;
            }
            //encontrado o node, inserir novo node e fazer as linkagens
            nodeNovo->proximo = nodeAtual->proximo;
            nodeAtual->proximo = nodeNovo;
            nodeNovo->anterior = nodeAtual;
            return 1; //TRUE, sucesso ao inserir item na lista
        }
    }
    return 0; //FALSE, erro ao inserir item na lista
}
/*
    Função que irá remover um item na posição N da lista
    Argumentos: uma lista qualquer e um inteiro N
    Retorno: devolve o item se for bem sucedido e NULL caso contrário
*/
int removeDL(ListaDL *lista, int n) {
    int item;
    int posicao;
    NodeDL *nodeAtual, *nodeAnterior, *nodeProximo;
    //verificando se a lista é válida, se tem itens e se N é válido
    if (lista != NULL && sizeListaDL(lista) > 0 && n >= 0 && n < sizeListaDL(lista)) {
        nodeAtual = lista->primeiro;
        posicao = 0; //setando contador de posição
        //procurando a partir do inicio da lista...
        while (posicao < n) {
            nodeAtual = nodeAtual->proximo;
            posicao++;
        }
        //encontrado o node, fazer a linkagem dos nodes sem perder informação
        item = nodeAtual->item;
        nodeAnterior = nodeAtual->anterior;
        nodeProximo = nodeAtual->proximo;
        if (nodeAnterior != NULL) {
            nodeAnterior->proximo = nodeProximo;
        } else {
            lista->primeiro = nodeProximo; //já que so havia um item
        }
        if (nodeProximo != NULL) {
            nodeProximo->anterior = nodeAnterior;
        }
        free(nodeAtual); //desalocando memoria do node a ser removido
        return item;
    }
    return NULL; //erro ao remover item
}
/*
    Função que irá informar o tamanho de uma lista
    Argumentos: uma lista qualquer
    Retorno: um inteiro N representando o número de itens armazenados
*/
int sizeListaDL(ListaDL *lista) {
    int tam = 0;
    NodeDL *nodeAtual = lista->primeiro;
    
    //percorrendo elementos da lista e incrementando contador (se lista não está vazia)
    while (nodeAtual != NULL) {
        tam++;
        //movendo para o proximo node
        nodeAtual = nodeAtual->proximo;
    }
    return tam;
}
/*
    Função que deleta uma lista vazia da memória
    Argumentos: uma lista qualquer
    Retorno: devolve (1) se for bem sucedido e 0 (FALSE) caso contrário
*/
int dlDestroy(ListaDL *lista) {
    //verificando se a lista é válida e se está vazia
    if (lista != NULL && lista->primeiro == NULL) {
        free(lista);
        return 1; //TRUE, sucesso ao eliminar lista
    }
    return 0; //FALSE, erro ao eliminar lista (pode estar ocupada)
}
