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
int insertSLStack(ListaSL *lista, Aluno *item) {
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
int insertSLQueue(ListaSL *lista, Aluno *item) {
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
    Função que remove um elemento da lista (primeiro)
    Argumentos: uma lista qualquer
    Retorno: devolve o item em caso de sucesso ou NULL caso contrário
*/
Aluno * removeSL(ListaSL *lista) {
    Aluno *item;
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
    Função que remove um elemento da lista em específico, dado pelo campo ID
    Argumentos: uma lista qualquer e um inteiro referente ao numero de ID
    Retorno: devolve um ponteiro do tipo Aluno com o ID dado se houver ou NULL caso haja erro.
*/
Aluno * removeStudent(ListaSL *lista, int ID) {
    int i, tam;
    Aluno *item;
    NodeSL *nodeAtual, *nodeExcluido;
    //verificando se a lista é válida
    if (lista != NULL) {
        //verificando se a lista está vazia
        if (lista->primeiro != NULL) {
            nodeAtual = lista->primeiro; //setando inicio da busca na lista
            //ajustando tamanho da busca para nao haver erros
            if (sizeListaSL(lista)-1 <= 0) {
                tam = 1;
            } else {
                tam = sizeListaSL(lista)-1;
            }
            //procurando na lista até encontrar o aluno antes do aluno de ID informado
            for (i=0; i<tam; i++) {
                //se aluno encontrado for o primeiro...
                if (i == 0 && nodeAtual->item->ID == ID) {
                    nodeExcluido = nodeAtual;
                    item = nodeExcluido->item;
                    lista->primeiro = nodeAtual->proximo;
                    free(nodeExcluido);
                    return item;
                } else if (nodeAtual->proximo->item->ID == ID) {
                    nodeExcluido = nodeAtual->proximo; //guardando endereco do aluno antigo
                    item = nodeExcluido->item; //guardando informações do aluno antigo
                    nodeAtual->proximo = nodeExcluido->proximo; //referenciando o proximo aluno
                    free(nodeExcluido); //removendo da memoria o aluno antigo
                    return item;
                }
                nodeAtual = nodeAtual->proximo; //atualizando node de pesquisa
            }
        }
    }
    return NULL; //erro ao remover item
}
/*
    Função que devolve um elemento da lista em específico, dado pelo campo ID, sem removê-lo
    Argumentos: uma lista qualquer e um inteiro referente ao numero de ID
    Retorno: devolve um ponteiro do tipo Aluno com o ID dado se houver ou NULL caso haja erro.
*/
Aluno * searchStudent(ListaSL *lista, int ID) {
    NodeSL *nodeAtual;
    //verificando se a lista é válida
    if (lista != NULL) {
        //verificando se lista não está vazia
        if (lista->primeiro != NULL) {
            //iniciando busca por aluno com o ID informado
            nodeAtual = lista->primeiro;
            while (nodeAtual != NULL) {
                if (nodeAtual->item->ID == ID) {
                    return nodeAtual->item;
                }
                nodeAtual = nodeAtual->proximo;
            }
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