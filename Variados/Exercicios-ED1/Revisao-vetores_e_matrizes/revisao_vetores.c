#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    //REVISAO DE VETORES E MATRIZES
    
    /*1. Escreva um programa que leia três vetores de tamanho 3 e calcule
    //a) Calcule a norma de cada vetor e retorne qual a norma do vetor com maior norma.
    //b) Calcule o vetor resultante da soma dos três vetores.
    int i, j, vetor1[3], vetor2[3], vetor3[3], vetorR[3];
    float norma, normaMaior = 0;
    
    for (i=0; i<3; i++) {
        printf("\nPreenchendo vetor %d\n", i+1);
        for (j=0; j<3; j++) {
            if (i == 0) {
                printf("\nValor de vetor1[%d]: ", j);
                scanf("%d", &vetor1[j]);
            } else if (i == 1){
                printf("\nValor de vetor1[%d]: ", j);
                scanf("%d", &vetor2[j]);
            } else {
               printf("\nValor de vetor1[%d]: ", j);
                scanf("%d", &vetor3[j]); 
            }
        }
    }
    //calculando norma de cada vetor
    for (i=0; i<3; i++){
        if (i == 0) {
            norma = sqrt( pow(vetor1[0], 2) + pow(vetor1[1], 2) + pow(vetor1[2], 2) );
        } else if (i == 1) {
            norma = sqrt( pow(vetor2[0], 2) + pow(vetor2[1], 2) + pow(vetor2[2], 2) );
        } else {
            norma = sqrt( pow(vetor3[0], 2) + pow(vetor3[1], 2) + pow(vetor3[2], 2) );
        }
        if ( norma > normaMaior){
            normaMaior = norma;
        }
    }
    //calculando vetor resultante
    for (i=0; i<3; i++){
        vetorR[i] = vetor1[i] + vetor2[i] + vetor3[i];
    }
    //mostrando resultados
    printf("Maior norma encontrada: %f\n", normaMaior);
    printf("Vetor resultante: {%d, %d, %d}\n", vetorR[0], vetorR[1], vetorR[2]);
    */
    /*
    //4.Construa um programa que leia dois números inteiros a e b, um vetor x de tamanho n e
    //exiba como resposta a contagem de quantos elementos do vetor estão no intervalo a<x[i]<v.
    int i, a, b, n, *x;
    
    printf("Tamanho do vetor: ");
    scanf("%d", &n);
    //alocando vetor de tamanho n
    x = (int*) (malloc(sizeof(int)*n));
    //lendo valores
    printf("\nInforme o valor de a: ");
    scanf("%d", &a);
    printf("\nInforme o valor de b: ");
    scanf("%d", &b);
    printf("\nLendo valores do vetor x...\n");
    for (i=0; i<n; i++){
        printf("Informe valor de x[%d]: ", i);
        scanf("%d", &x[i]);
    }
    //verificando numeros dentro do intervalo a, b
    printf("\nNumeros dentro do intervalo %d < x[i] < %d: { ", a, b);
    for (i=0; i<n; i++){
        if (x[i] > a && x[i] < b){
            printf("%d ", x[i]);
        }
    }
    printf("}\n");
    //liberando vetor
    free(x);
    */
    /*
    //5. Faça um programa para calcular a maior diferença entre dois elementos consecutivos de um
    //vetor a, com N elementos. O tamanho do vetor e seus elementos deverá ser lido via teclado.
    int i, n, *vetor, delta, deltaMaior = 0;
    
    printf("Tamanho do vetor: ");
    scanf("%d", &n);
    //alocando vetor de tamanho n
    vetor = (int*) (malloc(sizeof(int)*n));
    //lendo valores do vetor
    printf("\nPreenchendo vetor...\n");
    for (i=0; i<n; i++) {
        printf("\nInforme o valor de vetor[%d]: ", i);
        scanf("%d", &vetor[i]);
    }
    //procurando maior diferenca entre elementos consecutivos...
    for (i=0; i<(n-1); i++) {
        delta = abs(vetor[i]-vetor[i+1]);
        if (delta > deltaMaior) {
            deltaMaior = delta;
        }
    }
    //imprimindo resultados
    printf("Maior variacao entre elementos consecutivos do vetor: %d\n", deltaMaior);
    //liberando vetor alocado dinamicamente
    free(vetor);
    */
    
    system("pause");
    
    return 0;
}