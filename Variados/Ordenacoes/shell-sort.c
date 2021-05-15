#include <stdio.h>
#include <stdlib.h>
/*
	O metodo geral eh derivado da ordenacao por insercao e eh baseado na dimi-
	nuicao dos incrementos. Primeiro, todos os elementos que estao N posicoes
	afastados um do outro sao ordenados. Em seguida, todos os elementos que estao
	N-1 posicoes afastados sao ordenados e assim por diante, ate todos os elementos
	adjacentes estiverem ordenados. 

	Exemplo:
		inicial: [ 6 5 1 3 2 4]
		passo 1: [ 3 2 1 6 5 4]
		passo 2: [ 1 2 3 4 5 6]

		OBS: N equivale a 3 neste exemplo
*/

int main(){
	//prototipo da funcao de ordenacao
	void shellSort(int *vetor, int tam);

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
	shellSort(vetor, n);

	//liberando vetor dinamicamente alocado da memoria
	free(vetor);

	getchar();
	return 0;
}

void shellSort(int *vetor, int tam){
	//prototipo da funcao para imprimir a situacao do vetor
	void imprimirVetor( int *vetor, int tam);

	register int i, n, trocar, temp;

	if ( tam%2 == 0) n = tam/2; //se o numero de elementos for par
	else n = (tam/2)+1; //se for impar...

	//ordenando enquanto houver trocas
	while (n>=1){
		trocar = 0;
		//percorrendo todo o vetor
		for (i=0; i<tam; i++){
			//realizando trocas na range de N, se possivel
			if ( (i+n) < tam && vetor[i] > vetor[i+n]){
				temp = vetor[i];
				vetor[i] = vetor[i+n];
				vetor[i+n] = temp;
				trocar = 1;
			}
			imprimirVetor(vetor, tam);
		}
		printf("\n");
		if (!trocar) n--; //atualizando valor de N caso nao haja mais trocas possiveis
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

	///*imprimindo em forma numerica
	//system("clear"); //limpando tela
	printf("[ ");
	for(i=0; i<tam; i++){
		printf("%d ", vetor[i]);
	}
	printf("]\n");
	//*/

}