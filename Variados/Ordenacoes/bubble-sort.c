#include <stdio.h>
#include <stdlib.h>
/*
	A ordenacao bolha eh uma ordenacao por trocas. Ela envolve repetidas compara-
	coes e, se necessario, a troca de dois elementos adjacentes. Os elementos sao
	como bolhas em um tanque de agua - cada uma procura o seu proprio nivel.
*/

int main(){
	//prototipo da funcao de ordenacao
	void bubbleSort(int *vetor, int tam);

	int i, n, *vetor;

	printf("Tamanho do vetor: ");
	scanf("%d", &n);

	vetor = malloc(sizeof(int)*n);

	//preenchendo vetor com dados do tipo int
	for(i=0; i<n; i++){
		printf("Informe o elemento %d: ", i);
		scanf("%d", &vetor[i]);
	}

	//Ordenando vetor
	printf("\nOrdenando vetor...\n\n");
	bubbleSort(vetor, n);

	//liberando vetor dinamicamente alocado da memoria
	free(vetor);

	getchar();
	return 0;
}

void bubbleSort(int *vetor, int tam){
	//prototipo da funcao para imprimir a situacao do vetor
	void imprimirVetor( int *vetor, int tam);

	register int i, j, temp;

	//percorrendo vetor (do primeiro ao ultimo)
	for (i=0; i<tam; i++){
		for (j=(tam-1); j>=i; j--){
			if ( vetor[i] > vetor[j] ){
				printf("Trocando %d por %d...\n", vetor[i], vetor[j]);
				//trocando valores
				temp = vetor[i];
				vetor[i] = vetor[j];
				vetor[j] = temp;
			}
			imprimirVetor(vetor, tam);
		}
	}
	printf("\nOrdenado!\n");

}

void imprimirVetor( int *vetor, int tam){
	int i, j;

	//imprimindo em forma de barra
	system("clear"); //limpando tela
	for (i=0; i<tam; i++){
		printf("| ");
		for (j=0; j<vetor[i]; j++){
			printf("*");
		}
		printf("\n");
	}

	/*imprimindo em forma numerica
	//system("clear"); //limpando tela
	printf("[ ");
	for(i=0; i<tam; i++){
		printf("%d ", vetor[i]);
	}
	printf("]\n");
	*/

}