#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
/*
    10. Escreva um programa que utilize uma pilha para verificar se uma sequência de
    caracteres formada somente pelos caracteres ‘(‘ e ‘) ‘ (expressoes aritméticas) está
    com a parentização correta. O programa deve verificar para ver se cada “abre
    parenteses” tem um “fecha parenteses” correspondente.
    Ex.:
    Correto: ( ( ) ) ( ( )( ) ) ( ) ( )
    Incorreto: )( ( ( ) ( ) ) ( (
*/
int main() {
    //declaracao da funcao a ser utilizada
    int checaParentizacao(char expressao[51]);
    
    //variaveis do programa
    int status;
    char expressao[51];
    
    //lendo expressao e verificando sua parentizacao
    printf("Informe uma expressao de parenteses: ");
    scanf(" %[^\n]s", expressao);
    
    status = checaParentizacao(expressao);
    
    if (status == 1) {
        printf("\nA expressao eh bem formada!\n");
    } else {
        printf("\nA expressao esta com a parentizacao incorreta...\n");
    }
    
    system("pause");
    return 0;
}

int checaParentizacao(char expressao[51]) {
    int i;
    Pilha *pilha;
    
    //alocando memoria para a pilha
    pilha = createStack(strlen(expressao));
    if (pilha != NULL) {
        //percorrendo expressao e:
        //1- empilhando quando ha parenteses de abertura (1)
        //2- desempilhando quando ha parenteses de fechamento (0)
        for (i=0; i<strlen(expressao); i++) {
            if (expressao[i] == '(') {
                push(pilha, 1); //empilhando parentese de abertura
            } else if (expressao[i] == ')' && !isEmpty(pilha)) {
                pop(pilha);
            } else {
                return 0; //expressao mal formada...
            }
        }
        //se ainda houver itens na pilha entao algum(s) parenteses nao foram fechados
        if (!isEmpty(pilha)) {
            return 0; //expressao mal formada...
        }
        return 1; //expressao foi bem formada
    }
    return 0; //erro ao alocar pilha
}