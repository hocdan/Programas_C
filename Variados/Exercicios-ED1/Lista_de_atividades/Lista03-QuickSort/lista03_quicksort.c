#include <stdio.h>
#include <stdlib.h>

/*
    Faça um programa para:
    - ler a opção ( 1- Inteiro, 2 - Real)
    - ler um numero n;
    - alocar um vetor de n posições de números de acordo com a opçao do usuario;
    - ler os n numeros e guardar no vetor alocado;
    - usar a funcao qsort do C para ordenar esses dados;
    - imprimir os dados ordenados.
*/
int main() {
    //declaracoes de funcoes a serem utilizadas
    int comparaInt( const void * a, const void * b);
    int comparaFloat( const void * a, const void * b);
    
    int i, n, tipo, *vetorInt; 
    float *vetorFloat;
    
    //verificando o tipo de vetor a ser ordenado
    printf("Qual o vetor (1 - Inteiro, 2 - Real)? ");
    scanf("%d", &tipo);
    printf("Tamanho N do vetor: ");
    scanf("%d", &n);
    //alocando vetor de elementos de acordo com o tipo
    if (tipo == 1) {
        vetorInt = (int *) malloc(sizeof(int) * n);
        if (vetorInt == NULL) {
            printf("\nOcorreu um erro ao alocar o vetor! Encerrando programa...\n");
            exit(0);
        }
        //armazenando valores no vetor de inteiros
        for (i=0; i<n; i++) {
            printf("Informe o elemento %d do vetor de inteiros: ", i);
            scanf("%d", &vetorInt[i]);
        }
        //aplicando funcao de ordenacao qsort()
        qsort(vetorInt, n, sizeof(int), comparaInt);
        //mostrando vetor apos ordenacao
        printf("Vetor de inteiros ordenado: { ");
        for (i=0; i<n; i++) {
            printf("%d ", vetorInt[i]);
        }
        printf("}\n");
        
    } else if (tipo == 2) {
        vetorFloat = (float *) malloc(sizeof(float) * n);
        if (vetorFloat == NULL) {
            printf("\nocorreu um erro ao alocar o vetor! Encerrando programa...\n");
            exit(0);
        }
        //armazenando valores no vetor de reais
        for (i=0; i<n; i++) {
            printf("Informe o elemento %d do vetor de reais: ", i);
            scanf("%f", &vetorFloat[i]);
        }
        //aplicando funcao de ordenacao qsort()
        qsort(vetorFloat, n, sizeof(float), comparaFloat);
        //mostrando vetor apos ordenacao
        printf("Vetor de reais ordenado: { ");
        for (i=0; i<n; i++) {
            printf("%f ", vetorFloat[i]);
        }
        printf("}\n");  
    } else {
        printf("Sinto muito! Tipo de vetor invalido...\n");
    }
    //liberando vetores
    free(vetorInt);
    free(vetorFloat); 
    
    system("pause");
    return 0;
}
//compara numeros inteiros
int comparaInt( const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}
//compara numeros reais
int comparaFloat( const void * a, const void * b) {
    return ( *(float*)a - *(float*)b );
}