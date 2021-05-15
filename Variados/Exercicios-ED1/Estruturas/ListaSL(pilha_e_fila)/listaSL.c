#include <stdio.h>
#include <stdlib.h>
#include "listaSL.h"
/*
    Função que cria uma lista simplesmente encadeada
    Argumentos: nenhum
    Retorno: devolve um ponteiro para a struct ListaSL ou NULL caso haja erro na criacao
*/
ListaSL * createListaSL() {
    ListaSL *lista;
    //alocando espaco para a struct lista
    lista = (ListaSL *) malloc(sizeof(ListaSL));
    //testando se houve sucesso na alocacao
    if (lista != NULL) {
        //setando primeiro node para NULL (lista vazia)
        lista->primeiro = NULL;
        return lista; //retornando lista
    }
    return NULL; //erro ao criar lista
}
/*
    Função que insere um item em uma lista simplesmente encadeada (como uma pilha)
    Argumentos: uma lista qualquer e o item a ser adicionado
    Retorno: retorna (1) TRUE em caso de sucesso na inserção e 0 (FALSE) caso contrario
*/
int insertSLStack(ListaSL *lista, int item) {
    NodeSL *node;
    //verificando se a lista é válida
    if (lista != NULL) {
        //criando Node para guardar item a ser inserido
        node = (NodeSL *) malloc(sizeof(NodeSL));
        //verificando se a alocacao foi bem sucedida
        if (node != NULL) {
            //guardando item no Node
            node->item = item;
            //verificando se a lista está vazia ou não
            if (lista->primeiro == NULL) {
                node->proximo = NULL; //novo node está sozinho, logo aponta para o nada
            } else {
                node->proximo = lista->primeiro; //fazendo o novo node apontar para o antigo primeiro
            }
            lista->primeiro = node; //fazendo o inicio da lista apontar para o novo node
            return 1; //sucesso ao inserir item na lista
        }
    }
    return 0; //erro ao inserir item na lista
}
/*
    Função que insere um item em uma lista simplesmente encadeada (como uma fila)
    Argumentos: uma lista qualquer e o item a ser adicionado
    Retorno: retorna (1) TRUE em caso de sucesso na inserção e 0 (FALSE) caso contrario
*/
int insertSLQueue(ListaSL *lista, int item) {
    NodeSL *nodeNovo, *nodeAtual;
    //verificando se a lista é válida
    if (lista != NULL) {
        //criando Node para guardar item a ser inserido
        nodeNovo = (NodeSL *) malloc(sizeof(NodeSL));
        nodeAtual = (NodeSL *) malloc(sizeof(NodeSL));
        //verificando se a alocacao foi bem sucedida
        if (nodeNovo != NULL && nodeAtual != NULL) {
            //guardando item no Node e proximo elemento da lista
            nodeNovo->item = item;
            //caso a lista esteja vazia...apenas inserir no inicio
            if (lista->primeiro == NULL) {
                lista->primeiro = nodeNovo;
            } else {
                nodeAtual = lista->primeiro; //setando inicio da busca na lista
                //procurando fim da lista para inserir o elemento
                while (nodeAtual->proximo != NULL) {
                    nodeAtual = nodeAtual->proximo;
                }
                //achado o fim da lista, apontar para o novo node
                nodeAtual->proximo = nodeNovo;
            }
            nodeNovo->proximo = NULL;
            return 1; //sucesso ao inserir item na lista
        }
    }
    return 0; //erro ao inserir item na lista
}
/*
    Função que irá inserir um item antes da posição N fornecida
    Argumentos: uma lista qualquer e um inteiro(posição)
    Retorno: devolve 1 (TRUE) se inserção bem sucedida e 0 (FALSE) caso contrário
*/
int insertBeforeN(ListaSL *lista, int item, int n) {
    int posicao;
    NodeSL *nodeNovo, *nodeAtual;
    //verificando se a lista é válida, tem itens e se N é válido
    if (lista != NULL && sizeListaSL(lista) > 0 && n < sizeListaSL(lista) ) {
        //criando Node para guardar item a ser inserido
        nodeNovo = (NodeSL *) malloc(sizeof(NodeSL));
        nodeAtual = (NodeSL *) malloc(sizeof(NodeSL));
        //verificando se a alocacao foi bem sucedida e se N é válido
        if (nodeNovo != NULL && nodeAtual != NULL && n >= 0) {
            //guardando item no Node e proximo elemento da lista
            nodeNovo->item = item;
            //se N = 0, tornar o item o primeiro da lista e referenciar o antigo primeiro
            if (n == 0) {
                nodeNovo->proximo = lista->primeiro;
                lista->primeiro = nodeNovo;
            } else {
                posicao = 1; //setando contador de posicao
                nodeAtual = lista->primeiro; //setando inicio da busca na lista
                //procurando na lista até encontrar a posicao N
                while (posicao < n) {
                    nodeAtual = nodeAtual->proximo;
                    posicao++;
                }
                //achado o node da posicao N, inserir novo node antes dele na lista
                nodeNovo->proximo = nodeAtual->proximo;
                nodeAtual->proximo = nodeNovo;
            }
            return 1; //sucesso ao inserir item na lista
        }
    }
    return 0; //erro ao inserir item na lista
}
/*
    Função que irá remover um item depois da posição N fornecida
    Argumentos: uma lista qualquer e um inteiro(posição)
    Retorno: devolve 1 (TRUE) se remoção bem sucedida ou NULL caso contrário
*/ 
int removeAfterN(ListaSL *lista, int n) {
    int item, posicao;
    NodeSL *nodeAtual, *nodeExcluido;
    //verificando se a lista é válida
    if (lista != NULL) {
        //verificando se a lista não está vazia e se N+1 é valido
        if (lista->primeiro != NULL && sizeListaSL(lista) > 0 && n+1 < sizeListaSL(lista) && n >= 0) {
            posicao = 0; //setando contador de posicao
            nodeAtual = lista->primeiro; //setando inicio da busca na lista
            //procurando na lista até encontrar a posicao N
            while (posicao < n) {
                nodeAtual = nodeAtual->proximo;
                posicao++;
            }
            //achado o node da posicao N, apontar pro proximo do node N+1 e remover node N+1
            nodeExcluido = nodeAtual->proximo; //guardando endereco do node N+1
            item = nodeExcluido->item;
            nodeAtual->proximo = nodeExcluido->proximo; //referenciando o node N+2
            free(nodeExcluido); //removendo da memoria o node N+1
            return item;
        }
    }
    return NULL; //erro ao remover item
}
/*
    Função que remove um elemento da lista (primeiro)
    Argumentos: uma lista qualquer
    Retorno: devolve o item em caso de sucesso ou NULL caso contrário
*/
int removeSL(ListaSL *lista) {
    int item;
    //verificando se a lista é válida
    if (lista != NULL) {
        //verificando se a lista não está vazia
        if (lista->primeiro != NULL) {
            item = lista->primeiro->item;
            //eliminando referencia ao antigo node
            NodeSL *node = lista->primeiro;
            lista->primeiro = node->proximo;
            free(node);
            return item;
        }
    }
    return NULL; //erro ao remover item
}
/*
    Função que informa o numero de elementos na lista
    Argumentos: uma lista qualquer
    Retorno: devolve um inteiro N representando o numero de elementos
*/
int sizeListaSL(ListaSL *lista) {
    int tam = 0;
    NodeSL *nodeAtual = lista->primeiro;
    
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
    Retorno: 1 (TRUE) se for bem sucedido e 0 (FALSE) caso contrário
*/
int slDestroy(ListaSL *lista) {
    //verificando se a lista é válida e se está vazia
    if (lista != NULL && lista->primeiro == NULL) {
        free(lista);
        return 1; //TRUE, sucesso ao eliminar lista vazia
    }
    return 0; //FALSE, erro ao eliminar lista (pode estar ocupada)
}