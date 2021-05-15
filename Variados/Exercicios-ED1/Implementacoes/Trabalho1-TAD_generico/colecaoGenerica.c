#include <stdio.h>


Colecao *colCriar( int maxItens) {
    Colecao *c;
    
    if (maxItens > 0) {
        c = (Colecao *) malloc(sizeof(Colecao));
        if (c != NULL) {
            c->item = (void **) malloc(sizeof(void*) * maxItens);
            if (c->item != NULL) {
                c->numItens = 0;
                c->maxItens = maxItens;
                return c;
            }
            free(c);
        }
    }
    return NULL;    
}

int colInserir( Colecao *c, void *item) {
    
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

int colRetirar( Colecao *c, void *key) {
    
}

int colBuscar( Colecao *c, void *key) {
    
}

int colDestruir( Colecao *c) {
    
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