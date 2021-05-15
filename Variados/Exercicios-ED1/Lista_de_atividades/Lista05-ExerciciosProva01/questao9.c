#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilhaChar.h"
/*
    9. Escreva um algoritmo, usando uma Pilha, que inverte as letras de cada palavra de um
    texto terminado por ponto (.) preservando a ordem das palavras. 
    Por exemplo, dado o texto:
    ESTE EXERCICIO E MUITO FACIL.
    A saída deve ser:
    ETSE OICICREXE E OTIUM LICAF
*/
int main() {
    //declaracao da funcao a ser utilizada
    char * inverteFrase(char frase[51]);
    
    //variaveis do programa
    char *novaFrase, frase[51];
    
    //lendo expressao e verificando sua parentizacao
    printf("Informe uma frase: ");
    scanf(" %[^\n]s", frase);
    
    novaFrase = inverteFrase(frase);
    
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

char * inverteFrase(char frase[51]) {
    //variaveis da funcao
    int i, j, tam;
    char *novaFrase, letra;
    Pilha *pilha;
    
    //alocando memoria para a pilha
    pilha = createStack(strlen(frase));
    if (pilha != NULL) {
        //alocando memoria para a nova frase
        novaFrase = (char *) malloc(sizeof(char) * strlen(frase));
        if (novaFrase != NULL) {
            //percorrendo frase e invertendo suas palavras ate encontrar o sinal de ponto (.)
            for (i=0; i<strlen(frase); i++) {
                letra = frase[i];
                //empilhando letras da frase
                if (letra != ' ' && letra != '.') {
                    push(pilha, letra);
                    printf("\nEmpilhando %c...\n", letra);
                } else {
                    //desempilhando letras para inverter palavra da frase
                    tam = stackSize(pilha);
                    for (j=i-tam; j<i; j++) {
                        novaFrase[j] = pop(pilha);
                        printf("\nDesempilhando %c...\n", novaFrase[j]);
                    }
                    //se letra atual for espaco (' ') entao apeans inserir sem inverter na nova frase
                    if (letra == ' ') {
                        novaFrase[i] = ' ';
                    }
                    if (letra == '.') {
                        novaFrase[i] = '\0'; //encerrando frase
                    }
                }
            }
            return novaFrase; //devolvendo frase antiga invertida nas palavras
        }
    }
    return NULL; //erro ao alocar pilha
}