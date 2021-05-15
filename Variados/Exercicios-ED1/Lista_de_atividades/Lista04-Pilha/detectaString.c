#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

/*
    1 - Escreva um algoritmo para determinar se uma string de caracteres de entrada é
    da forma: xCy,  onde x é uma string consistindo nas letras 'A' e 'B', e y é o 
    inverso de x (isto é, se x = "ABABBA", y deve equivaler a "ABBABA").
*/
int main() {
    //variaveis do programa
    char str[101], letra; //tamanho arbitrario grande para poder armazenar strings de ate 100 caracteres
    int meio, i, flag = 1;
    Pilha *p1;
    
    //lendo string do usuario 
    printf("Informe uma string: ");
    scanf("%[^\n]s", str);
    //aplicando algoritmo de deteccao da string xCy com pilhas
    meio = strlen(str)/2; //ponto do meio da string
    p1 = createStack(meio); //criando pilha que armazena metade dos caracteres 
    //se meio da string nao for o caractere C entao string ja é invalida
    if (str[meio] != 'C') {
        flag = 0; //setando flag para FALSE, pois string nao eh do tipo xCy
    } else {
        //passando caracteres do lado x da string para uma pilha
        for (i=0; i<meio; i++) {
            push(p1, str[i]);
        }
        //desempilhando os caracteres e comparando com o lado y da string
        for (i=meio+1; i<strlen(str); i++) {
            letra = pop(p1);
            if (letra != str[i]) {
                flag = 0; //setando flag para FALSE
                break; //encerrando pois ja se sabe que a string nao eh do tipo xCy
            }
        }
    }
    //imprimindo resposta: string eh do tipo xCy?
    if (flag) {
        printf("\nA string %s eh do tipo xCy!\n", str);
    } else {
        printf("\nA string %s nao eh do tipo xCy!\n", str);
    }
    
    
    system("pause");
    return 0;
}