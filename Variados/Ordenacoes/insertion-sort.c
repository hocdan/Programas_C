#include <stdio.h>
#include <stdlib.h>
/*
	A ordenacao por insercao eh o terceiro e ultimo dos algoritmos simples de or-
	denacao. Inicialmente, ela ordena os dois primeiros elementos. Em seguida, o 
	algoritmo insere o terceiro elemento na sua posicao ordenada com relacao aos
	dois primeiros elementos. Entao, insere o quarto elemento na lista dos 3 ele-
	mentos. O processo continua ate que todos os elementos tenham sido ordenados.

	Exemplo:
		inicial: [ 4 3 1 2]
		passo 1: [ 3 4 1 2]
		passo 2: [ 1 3 4 2]
		passo 3: [ 1 2 3 4]
*/

int main(){
	//prototipo da funcao de ordenacao
	void insertionSort(int *vetor, int tam);

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
	insertionSort(vetor, n);

	//liberando vetor dinamicamente alocado da memoria
	free(vetor);

	system("pause");
	return 0;
}

void insertionSort(int *vetor, int tam){
	//prototipo da funcao para imprimir a situacao do vetor
	void imprimirVetor( int *vetor, int tam);

	register int i, j, ponta, temp;

	//passando por todo o vetor e comparando a ponta com seus antecessores
	for (i=1; i<tam; i++){
		ponta = i;
		for (j=(i-1); j>=0; j--){
			//trocando ponta com o resto do vetor caso ela seja menor
			if ( vetor[ponta] < vetor[j]){
				temp = vetor[ponta];
				vetor[ponta] = vetor[j];
				vetor[j] = temp;
				ponta--; //mantendo registro da posicao do elemento ponta
			}
            imprimirVetor(vetor, tam);
		}
	}

	printf("\nOrdenado!\n");

}

void imprimirVetor( int *vetor, int tam){
	int i, j;

	/*//imprimindo em forma de barra
	system("clear"); //limpando tela
	for (i=0; i<tam; i++){
		printf("| ");
		for (j=0; j<vetor[i]; j++){
			printf("*");
		}
		printf("\n");
	}
    */

	//imprimindo em forma numerica
	//system("clear"); //limpando tela
	printf("[ ");
	for(i=0; i<tam; i++){
		printf("%d ", vetor[i]);
	}
	printf("]\n");
	//*/

}