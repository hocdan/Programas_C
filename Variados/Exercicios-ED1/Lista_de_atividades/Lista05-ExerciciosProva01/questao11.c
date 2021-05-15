#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
/*
    11. Implemente um programa que recebe como entrada uma string e indica se a mesma é
    bem formada ou não. Uma string é bem formada quando seus delimitadores
    (parênteses, colchetes e chaves) à esquerda possuem os correspondentes à direita na
    ordem de ocorrência inversa. Exemplos:
    • “abas[ssas{aslk(as )saa}asssssssss]” => bem formado
    • “mnmk{}asa[ssd]aa{} (as{ss})” => bem formado
    • “sas{asd[sdds(sds]sd]sds}das” => mal formado
    • “as{assd{fdfff}sdddd}dffsfd}” => mal formado
    • “sadsadsds” => bem formado
*/
int main() {
    //declaracao da funcao a ser utilizada
    int checaParentizacao2(char expressao[51]);
    
    //variaveis do programa
    int status;
    char expressao[51];
    
    //lendo expressao e verificando sua parentizacao
    printf("Informe uma expressao de parenteses: ");
    scanf(" %[^\n]s", expressao);
    
    status = checaParentizacao2(expressao);
    
    if (status == 1) {
        printf("\nA expressao eh bem formada!\n");
    } else {
        printf("\nA expressao esta com a parentizacao incorreta...\n");
    }
    
    system("pause");
    return 0;
}

int checaParentizacao2(char expressao[51]) {
    //variaveis da funcao
    int i, valida = 1;
    Pilha *pilha;
    
    //alocando memoria para a pilha
    pilha = createStack(strlen(expressao));
    if (pilha != NULL) {
        //percorrendo expressao e:
        //1- empilhando quando ha parenteses de abertura ( = 1, { = 2, [ = 3
        //2- desempilhando quando ha parenteses de fechamento
        for (i=0; i<strlen(expressao); i++) {
            if (expressao[i] == '(') {
                push(pilha, 1); //empilhando parentese de abertura
            } else if (expressao[i] == '{') {
                push(pilha, 2);
            } else if (expressao[i] == '[') {
                push(pilha, 3);
            } else if (expressao[i] == ')' && !isEmpty(pilha)) {
                if (pop(pilha) != 1) {
                    valida = 0; //fechamento errado
                }
            } else if (expressao[i] == '}' && !isEmpty(pilha)) {
                if (pop(pilha) != 2) {
                    valida = 0; //fechamento errado
                }
            } else if (expressao[i] == ']' && !isEmpty(pilha)) {
                if (pop(pilha) != 3) {
                    valida = 0; //fechamento errado
                }
            } else if ( (expressao[i] == ')' || expressao[i] == '}' || expressao[i] == ']') && isEmpty(pilha)) {
                valida = 0; //fechamento errado
            }
        }
        //se ainda houver itens na pilha entao alguns parenteses nao foram fechados
        if (!isEmpty(pilha)) {
            valida = 0; //expressao mal formada...
        }
        return valida; //retornando flag (1=TRUE, 0=FALSE)
    }
    return 0; //erro ao alocar pilha
}