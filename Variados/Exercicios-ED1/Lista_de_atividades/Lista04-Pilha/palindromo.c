#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

/*
    2 - Faca um algoritmo que recebe uma string e retorna verdadeiro se ela for um 
    palindromo ou falso caso contrario.
*/
int main() {
    //variaveis do programa
    char str[101], letra; //tamanho arbitrario grande para poder armazenar strings de ate 100 caracteres
    int i, flag = 1; //setando para TRUE
    Pilha *p1;
    
    //lendo string do usuario 
    printf("Informe uma string: ");
    scanf("%[^\n]s", str);
    //aplicando algoritmo de deteccao de palindromo com pilhas
    p1 = createStack(strlen(str)); //criando uma pilha para armazenar os caracteres da string
    for (i=0; i<strlen(str); i++) {
        //armazenando versao invertida da string na pilha
        letra = str[i];
        push(p1, letra);
    }
    for (i=0; i<strlen(str); i++) {
        letra = pop(p1);
        if (letra != str[i]) {
            flag = 0; //setando para FALSE
            break; //encerrando comparacoes pois ja sabemos que a string nao eh um palindromo
        }
    }
    //imprimindo se a string eh um palindromo ou nao
    if (flag) {
        printf("\nA string %s eh um palindromo!\n", str);
    } else {
        printf("\nA string %s nao eh um palindromo!\n", str);
    }
    
    system("pause");
    return 0;
}