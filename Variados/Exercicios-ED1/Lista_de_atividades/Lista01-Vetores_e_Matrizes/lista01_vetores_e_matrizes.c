#include <stdio.h>
#include <stdlib.h>
/*
1.	Faça um algoritmo que recebe um vetor de n números reais e uma matriz mxp de números reais, 
e imprime em quais posições da matriz (linha e coluna) o valor é igual a um dos valores do vetor 
(informe também a posição do vetor).
a.	Considere a matriz alocada como vetor de vetores (matriz 2D)
int CmpVectorMatrix ( int n, int m, int p, float *vet, float **mat)
b.	Considere a matriz alocada em um vetor unidimensional
int CmpVectorMatrix ( int n, int m, int p, float *vet, float *mat)

2.	Faça um algoritmo que recebe os inteiros n, m, p e q, e duas matrizes ma e mb e retorna o produto
 entre as duas matrizes.
a.	Considere as matrizes alocadas como vetor de vetores (matriz 2D)
int MultMatrix ( int n, int m, int p, int q, float **ma, float **mb)
b.	Considere as matrizes alocadas em um vetor unidimensional
int MultMatrix ( int n, int m, int p, int q, float *ma, float *mb)
*/

int main() {
    /*
    //QUESTAO 1 - letra A
    void CmpVectorMatrix ( int n, int m, int p, float *vet, float **mat); //declaracao da funcao
    
    int i, j, n, m, p;
    float *vet, **mat;
    
    //lendo dimensoes dos vetores
    printf("QUESTAO 1 - Letra A\n\n");
    printf("Tamanho N do vetor: ");
    scanf("%d", &n);
    printf("Tamanho M de linhas da matriz: ");
    scanf("%d", &m);
    printf("Tamanho P de colunas da matriz: ");
    scanf("%d", &p);
    //alocando vetores
    vet = (float *) malloc(sizeof(float) * n);
    if (vet == NULL) {
        printf("\nOcorreu um problema ao alocar vetor!Encerrando programa...\n");
        exit(0);
    }
    mat = (float **) malloc(sizeof(float*) * m);
    for (i=0; i<m; i++) {
        mat[i] = (float *) malloc(sizeof(float) * p);
        if (mat[i] == NULL){
            //liberando os vetores 
            for (j=0; j<i; j++){
                free(mat[j]);
            }
            //liberando o vetor de vetores
            free(mat);
            //finalizando programa...
            printf("\nOcorreu um problema ao alocar vetor!Encerrando programa...\n");
            exit(0);
        }
    }
    //preenchendo vetor e matriz
    for (i=0; i<n; i++) {
        printf("\nInforme o valor de vetor[%d]: ", i);
        scanf("%f", &vet[i]);
    }
    for (i=0; i<m; i++) {
        for (j=0; j<p; j++) {
            printf("\nInforme o valor de matriz[%d][%d]: ", i, j);
            scanf("%f", &mat[i][j]);
        }
    }
    //realizando bsuca de elementos entre vetor e matriz
    CmpVectorMatrix(n, m, p, vet, mat);
    //liberando vetores alocados dinamicamente
    free(vet);
    for (i=0; i<m; i++) {
        free(mat[i]);
    }
    free(mat);
    */
    /*
    //QUESTAO 1 - letra B
    void CmpVectorMatrix ( int n, int m, int p, float *vet, float *mat);  //declaracao de funcao
    
    int i, j, n, m, p;
    float *vet, *mat;
    
    //lendo dimensoes dos vetores
    printf("QUESTAO 1 - Letra B\n\n");
    printf("Tamanho N do vetor: ");
    scanf("%d", &n);
    printf("Tamanho M de linhas da matriz: ");
    scanf("%d", &m);
    printf("Tamanho P de colunas da matriz: ");
    scanf("%d", &p);
    //alocando vetores
    vet = (float *) malloc(sizeof(float) * n);
    if (vet == NULL) {
        printf("\nOcorreu um problema ao alocar vetor!Encerrando programa...\n");
        exit(0);
    }
    mat = (float *) malloc(sizeof(float) * (m*p));
    if (mat == NULL) {
        printf("\nOcorreu um problema ao alocar vetor!Encerrando programa...\n");
        exit(0);
    }
    //lendo valores
    for (i=0; i<n; i++) {
        printf("\nInforme o valor de vet[%d]: ", i);
        scanf("%f", &vet[i]);
    }
    for (i=0; i<m; i++){
        for (j=0; j<p; j++) {
            printf("\nInforme o valor de mat[%d][%d]: ", i, j);
            scanf("%f", &mat[i*p+j]);
        }
    }
    //realizando busca de elementos entre vetor e matriz
    CmpVectorMatrix(n, m, p, vet, mat);
    //liberando vetores
    free(vet);
    free(mat);
    */
    /*
    //QUESTAO 2 - Letra A
    float ** MultMatrix ( int n, int m, int p, int q, float **ma, float **mb); //declaracao de funcao
    
    int i, j, n, m, p, q;
    float **ma, **mb, **mc;
    //lendo dimensoes dos vetores
    printf("QUESTAO 2 - Letra A\n\n");
    printf("Tamanho N das linhas da matriz A: ");
    scanf("%d", &n);
    printf("Tamanho M das colunas da matriz A: ");
    scanf("%d", &m);
    printf("Tamanho P das linhas da matriz B: ");
    scanf("%d", &p);
    printf("Tamanho Q das colunas da matriz B: ");
    scanf("%d", &q);
    //alocando vetores
    ma = (float **) malloc(sizeof(float*) * n);
    if (ma == NULL) {
        printf("\nOcorreu um problema ao alocar vetor!Encerrando programa...\n");
        exit(0);
    } else {
        for(i=0; i<n; i++) {
            ma[i] = (float*) malloc(sizeof(float) * m);
            if (ma[i] == NULL) {
                //liberando vetores
                for (j=0; j<i; j++) {
                    free(ma[j]);
                }
                //liberando vetor de vetores
                free(ma);
                printf("\nOcorreu um problema ao alocar vetor!Encerrando programa...\n");
                exit(0);
            }
        }
    }
    mb = (float **) malloc(sizeof(float*) * p);
    if (mb == NULL) {
        printf("\nOcorreu um problema ao alocar vetor!Encerrando programa...\n");
        exit(0);
    } else {
        for(i=0; i<p; i++) {
            mb[i] = (float*) malloc(sizeof(float) * q);
            if (mb[i] == NULL) {
                //liberando vetores
                for (j=0; j<i; j++) {
                    free(mb[j]);
                }
                //liberando vetor de vetores
                free(mb);
                printf("\nOcorreu um problema ao alocar vetor!Encerrando programa...\n");
                exit(0);
            }
        }
    }
    //lendo valores da matrizes
    printf("\nPreenchendo matriz A:\n");
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("\nInforme o valor de ma[%d][%d]: ", i, j);
            scanf("%f", &ma[i][j]);
        }
    }
    printf("\nPreenchendo matriz B:\n");
    for (i=0; i<p; i++) {
        for (j=0; j<q; j++) {
            printf("\nInforme o valor de mb[%d][%d]: ", i, j);
            scanf("%f", &mb[i][j]);
        }
    }
    //realizando multiplicacao entre as duas matrizes
    if (m != p) {
        printf("\nSinto muito! Multiplicacao de A e B invalida...\n");
    } else {
        mc = MultMatrix(n, m, p, q, ma, mb);
        //imprimindo matriz resultante
        printf("\nMatriz C resultante de A e B:\n");
        for (i=0; i<n ; i++) {
            for (j=0; j<q ; j++) {
                printf("%f ", mc[i][j]);
            }
            printf("\n");
        }
    }
    //liberando vetores
    for (i=0; i<n; i++) {
        free(ma[i]);
    }
    free(ma);
    for (i=0; i<p; i++) {
        free(mb[i]);
    }
    free(mb);
    for (i=0; i<n; i++){
        free(mc[i]);
    }
    free(mc);
    */
    
    //QUESTAO 2 - Letra B
    float* MultMatrix ( int n, int m, int p, int q, float *ma, float *mb); //declaracao da funcao
    
    int i, j, n, m, p, q;
    float *ma, *mb, *mc;
    //lendo dimensoes dos vetores
    printf("QUESTAO 2 - Letra B\n\n");
    printf("Tamanho N das linhas da matriz A: ");
    scanf("%d", &n);
    printf("Tamanho M das colunas da matriz A: ");
    scanf("%d", &m);
    printf("Tamanho P das linhas da matriz B: ");
    scanf("%d", &p);
    printf("Tamanho Q das colunas da matriz B: ");
    scanf("%d", &q);
    //alocando vetores
    ma = (float *) malloc(sizeof(float) * (n*m));
    if ( ma == NULL) {
        printf("\nOcorreu um erro ao alocar a matriz! Encerrando programa...\n");
        exit(0);
    }
    mb = (float *) malloc(sizeof(float) * (p*q));
    if ( mb == NULL) {
        printf("\nOcorreu um erro ao alocar a matriz! Encerrando programa...\n");
        exit(0);
    }
    //lendo valores das matrizes
    printf("\nPreenchendo matriz A:\n");
    for (i=0; i<n; i++){
        for (j=0; j<m; j++) {
            printf("\nInforme o valor de ma[%d][%d]: ", i, j);
            scanf("%f", &ma[i*m+j]);
        }
    }
    printf("\nPreenchendo matriz B:\n");
    for (i=0; i<p; i++){
        for (j=0; j<q; j++) {
            printf("\nInforme o valor de mb[%d][%d]: ", i, j);
            scanf("%f", &mb[i*q+j]);
        }
    }
    //realizando multiplicacao entre matrizes A e B, armazenando o resultado em C
    if ( m != p) {
        printf("\nSinto muito! Multiplicacao de A e B invalida...\n");
    } else {
        mc = MultMatrix(n, m, p, q, ma, mb);
        //imprimindo matriz resultante C
        printf("\nMatriz resultante C: \n");
        for (i=0; i<n; i++) {
            for (j=0; j<q; j++) {
                printf("%f ", mc[i*q+j]);
            }
            printf("\n");
        }
    }
    //liberando vetores
    free(ma);
    free(mb);
    free(mc);
    
    system("pause");
    
    return 0;
}
/*
void CmpVectorMatrix ( int n, int m, int p, float *vet, float **mat) {
    int i, j, k;
    //percorrendo cada elemento do vetor e comparando com todos os elementos da matriz
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            for (k=0; k<p; k++) {
                if (vet[i] == mat[j][k]) {
                    printf("Encontrado! Vet[%d] = %f e Mat[%d][%d] = %f\n", i, vet[i], j, k, mat[j][k]);
                }
            }
        }
    }
}
*/
/*
void CmpVectorMatrix ( int n, int m, int p, float *vet, float *mat) {
    int i, j, k;
    //percorrendo cada elemento do vetor e comparando com todos os elementos da matriz
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            for (k=0; k<p; k++) {
                if (vet[i] == mat[j*p+k]) {
                    printf("Encontrado! Vet[%d] = %f e mat[%d][%d] = %f\n", i, vet[i], j, k, mat[j*p+k]);
                }
            }
        }
    }
}
*/
/*
float** MultMatrix ( int n, int m, int p, int q, float **ma, float **mb) {
    int i, j, k;
    float valor, **mc;
    //alocando matriz C que ira armazenar a multiplicacao de AxB...
    mc = (float **) malloc(sizeof(float *) * n);
    if (mc == NULL) {
        printf("\nOcorreu um problema ao alocar a matriz! Encerrando programa...\n");
        exit(0);
    }
    for (i=0; i<n; i++) {
        mc[i] = (float *) malloc(sizeof(float) * q);
        if (mc[i] == NULL) {
            //liberando vetores
            for (j=0; j<i; j++) {
                free(mc[j]);
            }
            //liberando vetor de vetores
            free(mc);
            printf("\nOcorreu um problema ao alocar a matriz! Encerrando programa...\n");
            exit(0);
        }
    }
    //relizando multiplicacao entre A e B, armazenando na matriz C
    for (i=0; i<n; i++) {
        for (j=0; j<q; j++) {
            valor = 0;
            for (k=0; k<m; k++) {
                valor += ma[i][k]*mb[k][j];
            }
            mc[i][j] = valor;
        }
    }
    //retornando matriz resultante C
    return mc;
}
*/
/*
float* MultMatrix ( int n, int m, int p, int q, float *ma, float *mb) {
    int i, j, k;
    float valor, *mc;
    //alocando matriz C que ira armazenar a multiplicacao de AxB
    mc = (float *) malloc(sizeof(float) * (n*q));
    if ( mc == NULL) {
        printf("\nOcorreu um erro ao alocar a matriz! Encerrando programa...\n");
        exit(0);
    }
    //realizando multiplicacao de A e B, armazenando em C
    for (i=0; i<n; i++) {
        for (j=0; j<q; j++) {
            valor = 0;
            for (k=0; k<p; k++) {
                //printf("\nma[%d]->(%f) X mb[%d]->(%f) = %f\n", i*q+k, ma[i*q+k], k*q+j, mb[k*q+j], ma[i*q+k]*mb[k*q+j]);
                valor += ma[i*m+k]*mb[k*q+j];
            }
            mc[i*q+j] = valor;
        }
    }
    //retornando matriz resultante C
    return mc;
}
*/