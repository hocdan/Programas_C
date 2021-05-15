#include <stdio.h>
#include <stdlib.h>
#include "listaSLC.h"
/*
    Função que irá criar uma lista circular simplesmente encadeada
    Argumentos: nenhum
    Retorno: devolve um ponteiro para a lista se bem sucedido ou NULL caso contrário
*/
ListaSLC * createListaSLC() {
    ListaSLC *lista;
    //alocando espaco para a struct lista
    lista = (ListaSLC *) malloc(sizeof(ListaSLC));
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
int insertSLCStack(ListaSLC *lista, int item) {
    NodeSLC *node, *nodeAtual;
    //verificando se a lista é válida
    if (lista != NULL) {
        //criando Node para guardar item a ser inserido
        node = (NodeSLC *) malloc(sizeof(NodeSLC));
        //verificando se a alocacao foi bem sucedida
        if (node != NULL) {
            //guardando item no Node
            node->item = item;
            //verificando se a lista está vazia ou não
            if (lista->primeiro == NULL) {
                node->proximo = node; //novo node está sozinho, logo aponta para ele mesmo
            } else {
                node->proximo = lista->primeiro; //fazendo o novo node apontar para o antigo primeiro
                nodeAtual = node->proximo; //setando inicio da busca do ultimo elemento
                while (nodeAtual->proximo != lista->primeiro) {
                    nodeAtual = nodeAtual->proximo;
                }
                //achado o ultimo elemento, fazer apontar para o novo primeiro(novo node inserido)
                nodeAtual->proximo = node;
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
int insertSLCQueue(ListaSLC *lista, int item) {
    NodeSLC *nodeNovo, *nodeAtual;
    //verificando se a lista é válida
    if (lista != NULL) {
        //criando Node para guardar item a ser inserido
        nodeNovo = (NodeSLC *) malloc(sizeof(NodeSLC));
        nodeAtual = (NodeSLC *) malloc(sizeof(NodeSLC));
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
                while (nodeAtual->proximo != lista->primeiro) {
                    nodeAtual = nodeAtual->proximo;
                }
                //achado o fim da lista, apontar para o novo node
                nodeAtual->proximo = nodeNovo;
            }
            nodeNovo->proximo = lista->primeiro;
            return 1; //sucesso ao inserir item na lista
        }
    }
    return 0; //erro ao inserir item na lista
}
/*
    Função que remove um elemento da lista (primeiro)
    Argumentos: uma lista qualquer
    Retorno: devolve o item em caso de sucesso ou NULL caso contrário
*/
int removeSLC(ListaSLC *lista) {
    int item;
    //verificando se a lista é válida
    if (lista != NULL) {
        //verificando se a lista não está vazia
        if (lista->primeiro != NULL) {
            item = lista->primeiro->item;
            //eliminando referencia ao antigo node
            NodeSLC *node = lista->primeiro;
            if (node->proximo == node) {
                lista->primeiro = NULL;
            } else {
                NodeSLC *nodeAtual = node->proximo;
                //procurando fim da lista para atualizar a ponta
                while (nodeAtual->proximo != node) {
                    nodeAtual = nodeAtual->proximo;
                }
                //achado a ponta, atualizar ela com o novo primeiro (antigo segundo)
                lista->primeiro = node->proximo;
                nodeAtual->proximo = lista->primeiro;
            }
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
int sizeListaSLC(ListaSLC *lista) {
    int tam = 0;
    NodeSLC *nodeAtual = lista->primeiro;
    
    //percorrendo elementos da lista e incrementando contador (se lista não está vazia)
    if (nodeAtual != NULL) {
        tam++;
        while (nodeAtual->proximo != lista->primeiro) {
            tam++;
            //movendo para o proximo node
            nodeAtual = nodeAtual->proximo;
        }
    }
    
    return tam;
}
/*
    Função que deleta uma lista vazia da memória
    Argumentos: uma lista qualquer
    Retorno: 1 (TRUE) se for bem sucedido e 0 (FALSE) caso contrário
*/
int slcDestroy(ListaSLC *lista) {
    //verificando se a lista é válida e se está vazia
    if (lista != NULL && lista->primeiro == NULL) {
        free(lista);
        return 1; //TRUE, sucesso ao eliminar lista vazia
    }
    return 0; //FALSE, erro ao eliminar lista (pode estar ocupada)
}
