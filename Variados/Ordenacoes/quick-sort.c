#include <stdio.h>
#include <stdlib.h>
/*
	O quicksort eh baseado na ideia de particoes. O procedimento geral eh sele-
	cionar um valor, chamado de pivo, e, entao, fazer a particao da matriz em 
	2 secoes, com todos os elementos maiores ou iguais ao valor da particao de
	um lado e os menores do outro. Esse processo eh repetido para cada secao
	restante ate que a matriz esteja ordenada.

	Exemplo:
		inicio: [ 6 5 4 1 3 2 ]      pivo: 1
		passo1: [ 1 4 5 6 3 2 ]      
		passo2: [ 1 4 5 ]  [ 6 3 2 ] pivos: 4 e 3
		passo3: [ 1 4 5]  [ 2 3 6 ]
		passo4: [ 1 4 ] [ 5 ] [ 2 3 ] [ 6 ] pivos: 1 e 5
		passo5: [ 1 4 ]   X   [ 2 3 ]   X 
		passo6: [ 1 ] [ 4 ]  [ 2 ] [ 3 ]
		passo7:   X     X      X     X
		passo8: [ 1 2 3 4 5 6 ]

*/

int main(){
	//prototipo da funcao de ordenacao
	void quickSort(int *vetor, int tam);

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
	quickSort(vetor, n);

	//liberando vetor dinamicamente alocado da memoria
	free(vetor);

	getchar();
	return 0;
}

void quickSort(int *vetor, int tam){
	//prototipo da funcao para imprimir a situacao do vetor
	void imprimirVetor( int *vetor, int tam);
	//prototipo da funcao recursiva do quicksort
	void qs(int *vetor, int inicio, int fim);

	//aplicando quicksort
	qs(vetor, 0, tam-1);

	//imprimindo situacao final do vetor
	imprimirVetor(vetor, tam);

	printf("\nOrdenado!\n");

}

void qs(int *vetor, int inicio, int fim){
	//prototipo da funcao para imprimir a situacao do vetor
	void imprimirVetor( int *vetor, int tam);
	
	register  int i, j, pivo, temp;

	i = inicio;
	j = fim;
	pivo = vetor[ (inicio+fim)/2];

	do {
		while ( vetor[i] < pivo && i < fim) i++;
		while ( vetor[j] > pivo && j > inicio) j--;

		if ( i <= j){
			temp = vetor[i];
			vetor[i] = vetor[j];
			vetor[j] = temp;
			i++;
			j--;
		}
		imprimirVetor(vetor, (fim-inicio));
	} while ( i <= j);

	if ( j > inicio) qs(vetor, inicio, j);
	if ( i < fim ) qs(vetor, i, fim);


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

	///*imprimindo em forma numerica
	//system("clear"); //limpando tela
	printf("[ ");
	for(i=0; i<tam; i++){
		printf("%d ", vetor[i]);
	}
	printf("]\n");
	//*/

}