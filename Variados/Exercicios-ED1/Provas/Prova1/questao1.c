#include <stdio.h>
#include <stdlib.h>

/*
    1. Faça um algoritmo que recebe duas matrizes nxn armazenadas nos vetores v1 e v2 e,
    calcula uma nova matriz a ser armazenada no vetor v3 que corresponde a soma da
    matriz v1 com a matriz v2.
    int SomaMatrizes (int *v1, int *v2, int *v3, int n)
*/
int main() {
    //declaracao da funcao a ser utilizada
    int SomaMatrizes(int *v1, int *v2, int *v3, int n);
    
    //variaveis do programa
    int status, i, j, n;
    int *ma, *mb, *mc;
    
    //lendo dimensoes dos vetores
    printf("PROVA 1 - questao 1\n\n");
    printf("Tamanho N das linhas das matrizes: ");
    scanf("%d", &n);
    //alocando vetores
    ma = (int *) malloc(sizeof(int) * (n*n));
    if ( ma == NULL) {
        printf("\nOcorreu um erro ao alocar a matriz! Encerrando programa...\n");
        exit(0);
    }
    mb = (int *) malloc(sizeof(int) * (n*n));
    if ( mb == NULL) {
        printf("\nOcorreu um erro ao alocar a matriz! Encerrando programa...\n");
        exit(0);
    }
    mc = (int *) malloc(sizeof(int) * (n*n));
    if ( mc == NULL) {
        printf("\nOcorreu um erro ao alocar a matriz! Encerrando programa...\n");
        exit(0);
    }
    //lendo valores das matrizes
    printf("\nPreenchendo matriz A:\n");
    for (i=0; i<n; i++){
        for (j=0; j<n; j++) {
            printf("\nInforme o valor de ma[%d][%d]: ", i, j);
            scanf("%d", &ma[i*n+j]);
        }
    }
    printf("\nPreenchendo matriz B:\n");
    for (i=0; i<n; i++){
        for (j=0; j<n; j++) {
            printf("\nInforme o valor de mb[%d][%d]: ", i, j);
            scanf("%d", &mb[i*n+j]);
        }
    }
    //realizando soma das matrizes ma e mb, armazenando na matriz mc
    status = SomaMatrizes(ma, mb, mc, n);
    //imprimindo resultado
    if (status == 1) {
        printf("\nMatriz resultante C:\n");
        for (i=0; i<n; i++){
            for (j=0; j<n; j++) {
                printf("%d ", mc[i*n+j]);
            }
            printf("\n");
        }
        printf("\n");
    } else {
        printf("\nErro ao realizar soma das matrizes...\n");
    }
    //liberando vetores
    free(ma);
    free(mb);
    free(mc);
    
    system("pause");
    return 0;
}

int SomaMatrizes(int *v1, int *v2, int *v3, int n) {
    int i, j;
    if (v1 != NULL && v2 != NULL && v3 != NULL) {
        //percorrendo matrizes e realizando soma dos elementos
        for (i=0; i<n; i++) {
            for (j=0; j<n; j++) {
                v3[i*n+j] = v1[i*n+j] + v2[i*n+j];
            }
        }
        return 1; //TRUE
    }
    return 0; //FALSE
}