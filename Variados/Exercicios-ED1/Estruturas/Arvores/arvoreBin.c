#include <stdio.h>
#include <stdlib.h>
#include "arvoreBin.h"
/*
    Função que irá criar uma árvore binária de raíz nula
    Argumentos: nenhum
    Retorno: devolve um ponteiro para a estrutura da arvore
*/
ArvoreBin * createArvoreBin() {
    ArvoreBin *arvore;
    //alocando espaco para a struct arvore
    arvore = (ArvoreBin *) malloc(sizeof(ArvoreBin));
    //testando se houve sucesso na alocacao
    if (arvore != NULL) {
        //setando primeiro node (raiz) para NULL (arvore vazia)
        arvore->raiz = NULL;
        return arvore; //retornando arvore
    }
    return NULL; //erro ao criar arvore
}
/*
    Função que irá inserir o item na arvore, se x < N (esquerda) ou x > N (direita)
    Argumento: uma lista qualquer e um item
    Retorno: devolve 1 (TRUE) se for bem sucedido e 0 (FALSE) caso contrário
*/
int insertArvoreBin(ArvoreBin *arvore, int item) {
    NodeT *nodeNovo, *nodeAtual;
    //verificando se a arvore é válida
    if (arvore != NULL) {
        //criando Node para guardar item a ser inserido
        nodeNovo = (NodeT *) malloc(sizeof(NodeT));
        //verificando se a alocacao foi bem sucedida
        if (nodeNovo != NULL) {
            nodeNovo->item = item; //armazenando item no novo node
            nodeNovo->esquerda = NULL; //setando subarvore esquerda do novo node
            nodeNovo->direita = NULL; //setando subarvore direita do novo node
            //percorrendo arvore ao realizar comparacoes do valor do node com os outros
            nodeAtual = arvore->raiz; //setando inicio da busca de insercao
            if (nodeAtual == NULL) {
                arvore->raiz = nodeNovo;
                printf("\nInserindo item na raiz da arvore...\n");
            } else {
                while (nodeAtual != NULL) {
                    if (item < nodeAtual->item && nodeAtual->esquerda != NULL) {
                        printf("\nIndo para a esquerda de %d\n", nodeAtual->item);
                        nodeAtual = nodeAtual->esquerda;
                    } else if (item < nodeAtual->item && nodeAtual->esquerda == NULL) {
                        printf("\nInserindo item na subarvore esquerda de %d\n", nodeAtual->item);
                        nodeAtual->esquerda = nodeNovo;
                        break;
                    } else if (item > nodeAtual->item && nodeAtual->direita != NULL) {
                        printf("\nIndo para a direita de %d\n", nodeAtual->item);
                        nodeAtual = nodeAtual->direita;
                    } else if (item > nodeAtual->item && nodeAtual->direita == NULL) {
                        printf("\nInserindo item na subarvore direita de %d\n", nodeAtual->item);
                        nodeAtual->direita = nodeNovo;
                        break;
                    } else {
                        printf("\nITEM JA SE ENCONTRA NA ARVORE!\n");
                        return 0; //FALSE, item já se encontra na árvore!
                    }
                }
            }
            return 1; //TRUE, sucesso ao adicionar item
        }
    }
    return 0; //FALSE, erro ao adicionar item
}
/*
    Função que irá remover um item da árvore, necessita de outra funcao auxiliar
    Argumentos: uma árvore qualquer (sua raiz) e uma chave sinalizando o item a ser removido
    Retorno: 1 (TRUE) em caso de sucesso e 0 (FALSE) caso contrário
*/
NodeT * removeArvoreBin(NodeT *node, int item) {
    //declaracao de funcao extra a ser utilizada
    NodeT * find_minimum(NodeT *node);
    
    NodeT *aux; //node auxiliar
    //procurando pelo item a ser removido (inicia pela raiz da arvore)
    if (node == NULL) {
        return NULL;
    } else if (item > node->item) {
        node->direita = removeArvoreBin(node->direita, item);
    } else if (item < node->item) {
        node->esquerda = removeArvoreBin(node->esquerda, item);
    } else {
        //Caso 1: sem filhos
        if (node->esquerda == NULL && node->direita == NULL) {
            aux = node;
            free(node);
            return aux;
        }
        //Caso 2: apenas 1 filho
        else if (node->esquerda == NULL || node->direita == NULL) {
            if (node->esquerda == NULL) {
                aux = node->direita;
            } else {
                aux = node->esquerda;
            }
            free(node);
            return aux;
        }
        //Caso 3: com 2 filhos
        else {
            aux = find_minimum(node->direita);
            node->item = aux->item;
            node->direita = removeArvoreBin(node->direita, aux->item);
        }
    }
    return node;
}
/*
    Função que irá realizar uma consulta na árvore em busca do item dado
    Argumentos: uma árvore qualquer e a chave que identifica o item
    Retorno: devolve o item, se existir, ou NULL caso contrário
*/
NodeT* queryArvoreBin(NodeT *raiz, int item){
    
    //elemento encontrado ou erro ao procurar (vazio ou inexistente)
    if(raiz == NULL || raiz->item == item) {
        return raiz;
    }
    //se o item eh maior entao procurar na subarvore direita
    else if (item > raiz->item) {
        return queryArvoreBin(raiz->direita, item);
    }
    //se o item eh menor entao procurar na subarvore esquerda
    else {
        return queryArvoreBin(raiz->esquerda, item);
    }
}
/*
    Função que irá imprimir a arvore em ordem simetrica
    Argumentos: uma árvore qualquer
    Retorno: nenhum
*/
void printArvoreBinInOrdem(NodeT *raiz) {
    //verificando se existe arvore para imprimir
    if (raiz != NULL) {
        printArvoreBinInOrdem(raiz->esquerda);
        printf(" %d ", raiz->item);
        printArvoreBinInOrdem(raiz->direita);
    }
}
/*
    Funcao que diz qual o menor node da arvore
    Argumentos: uma arvore qualquer
    Retorno: devolve o menor valor da arvore
*/
NodeT * find_minimum(NodeT *node) {
    //se nao houver itens entao devolver NULL
    if(node == NULL)
        return NULL;
    else if(node->esquerda != NULL) //node com o menor valor nao tera filho na esquerda
        return find_minimum(node->esquerda); //o elemento mais a esquerda sera o menor node
    return node;
}

