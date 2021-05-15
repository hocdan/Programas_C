#include <stdio.h>
#include <stdlib.h>
#include "colGen.h"

/*
    Programa simples de TAD generico
*/

int main(){
    
    Colecao colecao; //criando colecao simples de numeros int
    int opcao, sair = 0; //controladores do programa
    int maxItens, elemento; //atributos da colecao
    
    //Loop principal do programa
    while(1){
        printf("\nMenu - TAD 1.0\n 1-Criar\n 2-Inserir\n 3-Retirar\n 4-Buscar\n 5-Destruir\n 6-Sair\nOpcao --> ");
        scanf("%d", &opcao);
        //acoes a serem realizadas
        if (opcao == 1) {
            printf("\nInsira o numero maximo de elementos da Colecao: ");
            scanf("%d", &maxItens);
            colecao = colCriar(maxItens);
            printf("\nColecao de numeros criada com sucesso!\n");
        }
        else if (opcao == 2){
            printf("\nInforme o elemento: ");
            scanf("%d", &colecao);
            if (colInserir(colecao, (void*)elemento)){
                printf("\nElemento adicionado com sucesso na colecao!\n");
            }
            else {
                printf("\nSinto muito! Erro ao adicionar elemento na colecao...\n");
            }
        }
        else if (opcao == 3){
            printf("\nAINDA NAO IMPLEMENTADO!!!\n");
        }
        else if (opcao == 4){
            printf("\nAINDA NAO IMPLEMENTADO!!!\n");
        }
        else if (opcao == 5){
            if (colecao != NULL) {
                if (colDestruir(colecao) == 0){
                    printf("Sinto muito...verifique a sua colecao de numeros antes!\n");
                    sair = 0;
                } else {
                    sair = 1;
                }
            } else {
                sair = 1;
            }
        }
        else if (opcao == 6){
            if (colecao != NULL) {
                if (colDestruir(colecao) == 0){
                    printf("Sinto muito...verifique a sua colecao de numeros antes!\n");
                    sair = 0;
                } else {
                    sair = 1;
                }
            } else {
                sair = 1;
            }
        }
        //encerrando programa
        if (sair) {
            printf("Encerrando programa...");
            break;
        }  
    }
    
    system("pause");
    return 0;
}