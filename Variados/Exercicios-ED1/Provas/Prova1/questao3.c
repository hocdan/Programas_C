#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilhaChar.h"

int main() {
    //declaracao de funcao a ser utilizada
    char * inverterString(char *str);
    
    //variaveis do programa
    char *novaFrase, frase[51];
    
    //lendo expressao e verificando sua parentizacao
    printf("Informe uma frase: ");
    scanf(" %[^\n]s", frase);
    
    novaFrase = inverterString(frase);
    
    if (novaFrase != NULL) {
        printf("\nA frase foi invertida com sucesso!\n");
        //imprimindo frase
        printf("%s\n", novaFrase);
    } else {
        printf("\nErro ao inverter a frase...\n");
    }
    
    free(novaFrase);

    system("pause");
    return 0;
}

char * inverterString(char *str) {
    //declaracao de funcao a ser utilizada
    int ehDigito(char digito);
    
    //variaveis da funcao
    int i, pos, tam;
    char *novaStr;
    Pilha *p;
    
    //alocando memoria para a pilha
    p = createStack(strlen(str));
    if (p != NULL) {
        //alocando memoria para a nova frase
        novaStr = (char *) malloc(sizeof(char) * (strlen(str)+1));
        if (novaStr != NULL) {
            pos = 0; //posicao de insercao na nova string
            //percorrendo frase e armazenando digitos em uma pilha e apenas movendo letras
            for (i=0; i<strlen(str); i++) {
                //verificando se a letra eh um digito (0 .. 9)
                if (ehDigito(str[i])) {
                    push(p, str[i]);
                } else {
                    //se nao for um digito entao apenas adicionar na nova string
                    novaStr[pos] = str[i];
                    pos++; //atualizando posicao de insercao
                }
            }
            //apos percorrer toda a frase, basta esvaziar a pilha e jogar os elementos na nova string
            tam = stackSize(p);
            for (i=0; i<tam; i++) {
                novaStr[pos] = pop(p);
                pos++;
            }
            novaStr[pos] = '\0'; //encerrando string
            return novaStr; //retornando nova string
        }
    }
    return NULL; //erro ao alocar pilha
}

int ehDigito(char letra) {
    //verificando se a letra um digito
    if (letra == '0' || letra == '1' || letra == '2' || letra == '3' || letra == '4' || letra == '5' 
        || letra == '6' || letra == '7' || letra == '8' || letra == '9') {
            return 1; //TRUE
    }
    return 0; //FALSE
}