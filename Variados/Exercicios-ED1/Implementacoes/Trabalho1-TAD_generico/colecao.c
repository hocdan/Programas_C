#define __COLECAO_C_

#include <stdio.h>   //definicao da constante NULL
#include <assert.h>  //necessario para verificacoes de pre-condicao
#include "Colecao.h" //inclue a especificacao do TAD

#define TRUE 1
#define FALSE 0

//definicao do tipo de dado
struct _colecao_ {
    int numItens;
    int maxItens;
    int *itens;
} Colecao;

/*
    Construir uma nova colecao
    Pre-condicao: maxItens > 0
    Pos-condicao: retorna um ponteiro para uma colecao vazia ou NULL quando der errado
*/
Colecao *colCriar(int maxItens){
    Colecao *c;
    
    if (maxItens > 0) {
        c = (Colecao *) malloc(sizeof(Colecao)); //criando colecao
        if (c != NULL) {
            c->itens = (int *) malloc(sizeof(int) * maxItens); //criando vetor de elementos da colecao
            if (c->itens != NULL) {
                return c;
            }
        } else {
            free(c); //liberando memoria
        }
    }
    
    return NULL; //erro ao criar Colecao
}

/*
    Destruir uma colecao 
    Pre-condicao: a colecao deve existir e nao ter elementos dentro dela (numItens == 0)
    Pos-condicao: retorna TRUE(1) caso a colecao seja eliminada ou FALSE(0) caso contrario
*/
int colDestruir(Colecao *c) {
    
    if (c != NULL) {
        if (c->items != NULL) {
            if (c->numItens == 0) {
                free(c->items);
                free(c);
                return TRUE;
            }
        }
    }
    
    return FALSE;
}

/*
    Inserir um elemento na colecao
    Pre-condicao: o vetor de elementos nao estar cheio (numItens < maxItens)
    Pos-condicao: retorna TRUE(1) se a inserção for bem sucedida e FALSE(0) caso contrário
*/
int colInserir(Colecao *c, int item) {
    
    if ( c!= NULL) {
        if ( c->itens != NULL) {
            if ( c->numItens < c->maxItens) {
                c->itens[c->numItens] = item;
                c-numItens++;
                return TRUE;
            }
        }
    }
    
    return FALSE;
}

/*

*/
int colRetirar(Colecao *c, int key) {
    int i, j, elm;
    
    i = 0;
    while ( i < c->numItens && key != c->item[i]) {
        i++;
    }
    if (key == c->item[i]){
        elm = c->item[i];
        for (j=i; j<(c->numItens-1); j++) {
            c->item[j] = c->item[j+1];
        }
        c->numItens--;
        return elm;
    }
    return -1;
}

/*

*/
int colBuscar(Colecao *c, int key) {
    int i;
    
    i = 0;
    while (i < c->numItens && key != c->item[i]) {
        i++;
    }
    if ( key == c->item[i]) {
        return c->item[i];
    }
    return -1;
}
