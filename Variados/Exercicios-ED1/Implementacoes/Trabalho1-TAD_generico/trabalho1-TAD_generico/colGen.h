#ifndef __COLGEN_H
#define __COLGEN_H
/*--------------------------------------------------------------------
-----
 Definicoes locais
----------------------------------------------------------------------
-----*/
typedef struct _colecao_ Colecao;
//Definicao do tipo de dado
/*--------------------------------------------------------------------
-----
 Funcoes que implementam as operacoes do TAD ColecaoInt
----------------------------------------------------------------------
-----*/
/*
 Cria um novo TAD Colecao
 Pre-condicao: max_items > 0
 Pos-condicao: retorna um ponteiro para uma novo TAD Colecao vazio
*/
Colecao *colCriar( int max_itens );
/*
 Adiciona um item na Collecao
 Pre-condition: (c é um TAD Colecao criado por uma chamada a
 colCriar) e
 (o TAD Colecao nao esta cheio) e
 (item != NULL)
 Pos-condicao: item foi adicionado ao TAD c
*/
int colInserir( Colecao *c, void *item );
/*
 Retira um item da colecao
 Pre-condicao: (c é um TAD Colecao criado por uma chamada a
 colCriar) e &&
 (existe pelo menos um item no TAD Colecao) e
 (item != NULL)
 Pos-condicao: item foi eliminado do TAD c
*/
void *colRetirar( Colecao *c, void *item, int (*compar)( const void *, const void * ));
/*
 Encontra um item em um TAD Colecao
 Pre-condicao: (c é um TAD Colecao criado por uma chamada a
 colCriar) e
 (key != NULL)
 Pos-condicao: retorna um item identificado por key se ele existir
no TAD c,
 ou return NULL caso contrátrio
*/
void *colBuscar( Colecao *c, void *chave, int (*compar)( const void *, const void * ) );
/*
 Destroi um TAD Colecao
 Pre-condicao: (c é um TAD Colecao criado por uma chamada a
 colCriar)
 Pos-condicao: a memoria usada pelo TAD foi liberada
*/
int colDestruir( Colecao *c );

#endif /* __Colecao_INT_H */