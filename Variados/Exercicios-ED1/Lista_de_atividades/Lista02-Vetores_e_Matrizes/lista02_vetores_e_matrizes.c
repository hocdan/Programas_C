#include <stdio.h>
#include <stdlib.h>
/*
    3.	Faça um algoritmo para:
    a.	Receber uma Matriz armazenada em um vetor e:
        I)	Retornar:
            0 – Se for um Matriz Quadrada;
            1 – Se for uma Matriz simétrica;
            2 – Se for Matriz Diagonal;
            3 – Se é Matriz Assimétrica;
            int TipodeMatriz(int *va, int n, int m);
        II)	Retornar um vetor com a transposta da Matriz
            int *transposta(int *va, int n, int m);
        III)	Retornar um vetor com os elementos da linha l da matriz a
            int * linhadaMatriz(int *va, int n, int m, int l);
        IV)	Retornar Um vetor com os elementos da coluna “p” da matriz
            int * colunadaMatriz(int *va, int n, int m, int p);
        V)	Retornar Um vetor com os elementos da diagonal principal da matriz
            int * diagonaldaMatriz(int *va, int n, int m)
*/

int main() {
    /*
    //QUESTAO 3 - Letra A1
    int TipodeMatriz(int *va, int n, int m); //declaracao da funcao
    
    int i, j, n, m, tipo, *va;
    //lendo dimensoes da matriz
    printf("QUESTAO 3 - Letra A1\n");
    printf("\nNumero de linhas da matriz: ");
    scanf("%d", &n);
    printf("\nNumero de colunas da matriz: ");
    scanf("%d", &m);
    //alocando vetor que ira simular uma matriz 2D
    va = (int *) malloc(sizeof(int) * (n*m));
    if (va == NULL) {
        printf("\nOcorreu um erro ao alocar o vetor! Encerrando programa...\n");
        exit(0);
    }
    //lendo elementos da matriz
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("\nInforme o elemento va[%d][%d]: ", i, j);
            scanf("%d", &va[i*m+j]);
        }
    }
    //aplicando funcao de identificacao de matriz
    tipo = TipodeMatriz(va, n, m);
    if (tipo == -1) {
        printf("\nA matriz va nao eh quadrada!\n");
    } else if (tipo == 0) {
        printf("\nA matriz va eh do tipo quadrada!\n");
    } else if (tipo == 1) {
        printf("\nA matriz va eh do tipo simetrica!\n");
    } else if (tipo == 2) {
        printf("\nA matriz va eh do tipo diagonal!\n");
    } else if (tipo == 3) {
        printf("\nA matriz va eh do tipo antissimetrica!\n");
    }
    //imprimindo vetor
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("%d ", va[i*m+j]);
        }
        printf("\n");
    }
    //liberando vetor
    free(va);
    */
    /*
    //QUESTAO 3 - Letra A2
    int * transposta(int *va, int n, int m); //declarando a variavel
    
    int i, j, n, m, *va, *vr;
    //lendo dimensoes da matriz
    printf("QUESTAO 3 - Letra A2\n");
    printf("\nNumero de linhas da matriz: ");
    scanf("%d", &n);
    printf("\nNumero de colunas da matriz: ");
    scanf("%d", &m);
    //alocando vetor que ira simular uma matriz 2D
    va = (int *) malloc(sizeof(int) * (n*m));
    if (va == NULL) {
        printf("\nOcorreu um erro ao alocar o vetor! Encerrando programa...\n");
        exit(0);
    }
    //lendo elementos da matriz
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("\nInforme o elemento va[%d][%d]: ", i, j);
            scanf("%d", &va[i*m+j]);
        }
    }
    //aplicando funcao que devolvera a transposta de va
    vr = transposta(va, n, m);
    //imprimindo matriz va e vr (resultante da transposta de va)
    printf("\nMatriz va:\n");
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("%d ", va[i*m+j]);
        }
        printf("\n");
    }
    printf("\nMatriz vr (transposta de va):\n");
    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            printf("%d ", vr[i*n+j]);
        }
        printf("\n");
    }
    //liberando vetor
    free(va);
    free(vr);
    */
    /*
    //QUESTAO 3 - Letra A3
    int * linhadaMatriz(int *va, int n, int m, int l); //declarando funcao
    
    int i, j, n, m, l, *va, *vL;
    //lendo dimensoes da matriz
    printf("QUESTAO 3 - Letra A3\n");
    printf("\nNumero de linhas da matriz: ");
    scanf("%d", &n);
    printf("\nNumero de colunas da matriz: ");
    scanf("%d", &m);
    //alocando vetor que ira simular uma matriz 2D
    va = (int *) malloc(sizeof(int) * (n*m));
    if (va == NULL) {
        printf("\nOcorreu um erro ao alocar o vetor! Encerrando programa...\n");
        exit(0);
    }
    //lendo elementos da matriz
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("\nInforme o elemento va[%d][%d]: ", i, j);
            scanf("%d", &va[i*m+j]);
        }
    }
    //lendo em qual linha devera ser feita a copia de elementos
    printf("\nInforme a linha L a ser copiada da matriz va: ");
    scanf("%d", &l);
    //aplicando funcao que devolvera a linha L da matriz va
    vL = linhadaMatriz(va, n, m, l);
    //imprimindo matriz va e o vetor contendo a linha L de va
    printf("\nMatriz va:\n");
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("%d ", va[i*m+j]);
        }
        printf("\n");
    }
    printf("\nvetor da linha %d de va:\n", l);
    for (i=0; i<m; i++) {
        printf("%d ", vL[i]);
    }
    printf("\n");
    //liberando vetores
    free(va);
    free(vL);
    */
    /*
    //QUESTAO 3 - Letra A4
    int * colunadaMatriz(int *va, int n, int m, int p); //declarando funcao
    
    int i, j, n, m, p, *va, *vC;
    //lendo dimensoes da matriz
    printf("QUESTAO 3 - Letra A4\n");
    printf("\nNumero de linhas da matriz: ");
    scanf("%d", &n);
    printf("\nNumero de colunas da matriz: ");
    scanf("%d", &m);
    //alocando vetor que ira simular uma matriz 2D
    va = (int *) malloc(sizeof(int) * (n*m));
    if (va == NULL) {
        printf("\nOcorreu um erro ao alocar o vetor! Encerrando programa...\n");
        exit(0);
    }
    //lendo elementos da matriz
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("\nInforme o elemento va[%d][%d]: ", i, j);
            scanf("%d", &va[i*m+j]);
        }
    }
    //lendo em qual linha devera ser feita a copia de elementos
    printf("\nInforme a coluna P a ser copiada da matriz va: ");
    scanf("%d", &p);
    //aplicando funcao que devolvera a linha L da matriz va
    vC = colunadaMatriz(va, n, m, p);
    //imprimindo matriz va e o vetor contendo a coluna P de va
    printf("\nMatriz va:\n");
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("%d ", va[i*m+j]);
        }
        printf("\n");
    }
    printf("\nvetor da coluna %d de va:\n", p);
    for (i=0; i<n; i++) {
        printf("%d ", vC[i]);
    }
    printf("\n");
    //liberando vetores
    free(va);
    free(vC);
    */
    /*
    //QUESTAO 3 - Letra A5
    int * diagonaldaMatriz(int *va, int n, int m); //declarando funcao
    
    int i, j, n, m, tam, *va, *vD;
    //lendo dimensoes da matriz
    printf("QUESTAO 3 - Letra A5\n");
    printf("\nNumero de linhas da matriz: ");
    scanf("%d", &n);
    printf("\nNumero de colunas da matriz: ");
    scanf("%d", &m);
    //alocando vetor que ira simular uma matriz 2D
    va = (int *) malloc(sizeof(int) * (n*m));
    if (va == NULL) {
        printf("\nOcorreu um erro ao alocar o vetor! Encerrando programa...\n");
        exit(0);
    }
    //lendo elementos da matriz
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("\nInforme o elemento va[%d][%d]: ", i, j);
            scanf("%d", &va[i*m+j]);
        }
    }
    //aplicando funcao que devolvera a diagonal principal da matriz va
    vD = diagonaldaMatriz(va, n, m);
    //imprimindo matriz va e o vetor contendo a diagonal principal de va
    printf("\nMatriz va:\n");
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("%d ", va[i*m+j]);
        }
        printf("\n");
    }
    printf("\nvetor da diagonal principal de va:\n");
    if (n < m) {
        tam = n;
    } else {
        tam = m;
    }
    for (i=0; i<tam; i++) {
        printf("%d ", vD[i]);
    }
    printf("\n");
    //liberando vetores
    free(va);
    free(vD);
    */
    
    system("pause");
    return 0;
}
/*
int TipodeMatriz(int *va, int n, int m) {
    int i, j, diagonal, simetrica, antissimetrica;
    
    if (n == m) {
        //verificando se é uma matriz diagonal
        diagonal = 1; //verdadeiro
        for (i=0; i<n; i++) {
            for (j=0; j<m; j++) {
                //realizando comparacoes fora da diagona principal
                if ( j != i && va[i*m+j] != 0){
                    diagonal = 0;
                    break; //encerrando pois matriz ja nao eh mais diagonal
                }
            }
        }
        if (diagonal) {
            return 2; //a matriz eh diagonal
        }
        //verificando se é uma matriz simetrica
        simetrica = 1; //verdadeiro
        for (i=0; i<n; i++) {
            for (j=0; j<m; j++) {
                if (va[i*m+j] != va[j*m+i]) {
                    simetrica = 0; 
                    break; //encerrando pois matriz ja nao eh simetrica
                }
            }
        }
        if (simetrica) {
            return (1);
        }
        //verificando se é uma matriz antissimetrica
        antissimetrica = 1; //verdadeiro
        for (i=0; i<n; i++) {
            for (j=0; j<m; j++) {
                if (i == j && va[i*m+j] != 0) {
                    antissimetrica = 0;
                    break; //encerrando pois matriz ja nao eh antissimetrica
                } else {
                    if (va[i*m+j] != (va[j*m+i] * -1)) {
                        antissimetrica = 0;
                        break; //encerrando pois matriz ja nao eh antissimetrica
                    }
                }
            }
        }
        if (antissimetrica) {
            return (3);
        }
        return 0; //a matriz eh apenas quadrada
    } else {
        return -1;//a matriz nao eh quadrada
    }
}
*/
/*
int* transposta(int *va, int n, int m) {
    int i, j, *vr;
    
    //alocando matriz transposta
    vr = (int *) malloc(sizeof(int) * (m*n));
    if (vr == NULL) {
        printf("\nOcorreu um erro ao alocar o vetor! Encerrando programa...\n");
        exit(0);
    }
    //criando a matriz transposta de va e armazenando em vr
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            vr[j*n+i] = va[i*m+j];
        }
    }
    //retornando matriz transposta
    return vr;
}
*/
/*
int* linhadaMatriz(int *va, int n, int m, int l) {
    int i, j, *vL;
    
    //alocando vetor para armazenar elementos da linha L de va
    vL = (int *) malloc(sizeof(int) * m);
    if (vL == NULL) {
        printf("\nOcorreu um erro ao alocar o vetor! Encerrando programa...\n");
        exit(0);
    }
    //copiando elementos da linha L de va para o vetor vL
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            if (i == l) {
                vL[j] = va[i*m+j];
            }
        }
    }
    //retornando vetor dos elementos da linha L de va
    return vL;
}
*/
/*
int * colunadaMatriz(int *va, int n, int m, int p) {
    int i, j, *vC;
    
    //alocando vetor para armazenar elementos da coluna P de va
    vC = (int *) malloc(sizeof(int) * n);
    if (vC == NULL) {
        printf("\nOcorreu um erro ao alocar o vetor! Encerrando programa...\n");
        exit(0);
    }
    //copiando elementos da coluna P de va para o vetor vC
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            if (j == p) {
                vC[i] = va[i*m+j];
            }
        }
    }
    //retornando vetor dos elementos da coluna P de va
    return vC;
}
*/
/*
int* diagonaldaMatriz(int *va, int n, int m) {
    int i, j, tam, *vD;
    
    //verificando limitante do vetor diagonal principal
    if (n < m) {
        tam = n;
    } else {
        tam = m;
    }
    //alocando vetor para armazenar elementos da diagonal principal de va
    vD = (int *) malloc(sizeof(int) * tam);
    if (vD == NULL) {
        printf("\nOcorreu um erro ao alocar o vetor! Encerrando programa...\n");
        exit(0);
    }
    //copiando elementos da diagonal principal de va para o vetor vD
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            if (i == j) {
                vD[i] = va[i*m+j];
            }
        }
    }
    //retornando vetor dos elementos da diagonal principal de va
    return vD;
}
*/