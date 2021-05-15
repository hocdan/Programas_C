#include <stdio.h>
#include <stdlib.h>
/*
	A ordenacao por selecao seleciona o elemento de menor valor e troca-o pelo
	primeiro elemento. Entao, para os n-1 elementos restantes, eh encontrado o 
	elemento de menor chave, trocando pelo segundo elemento e assim por diante.
	As trocas continuam ate os dois ultimos elementos.
*/

int main(){
	//prototipo da funcao de ordenacao
	void selectionSort(int *vetor, int tam);

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
	selectionSort(vetor, n);

	//liberando vetor dinamicamente alocado da memoria
	free(vetor);

	getchar();
	return 0;
}

void selectionSort(int *vetor, int tam){
	//prototipo da funcao para imprimir a situacao do vetor
	void imprimirVetor( int *vetor, int tam);

	register int i, trocar, trocas = 0, menor, temp, pos;

	//enquanto numero de trocas <= (tam-1)
	while (trocas < (tam-1)){

		menor = vetor[trocas]; //resetando menor para primeiro valor do vetor nao ordenado
		trocar = 0; //setando flag para troca como FALSE
		//procurando menor elemento pelo resto do vetor nao-ordenado
		for (i=(trocas+1); i<tam; i++){
			if ( vetor[i] < menor){
				menor = vetor[i]; //atualizando menor elemento
				pos = i; //salvando posicao do menor elemento
				trocar = 1; //setando flag para troca como TRUE
			}
		}
		//jogando menor valor na posicao inicial do vetor nao-ordenado
		if (trocar){
			temp = vetor[trocas];
			vetor[trocas] = menor;
			vetor[pos] = temp;
		}
		//atualziando numero de trocas (ultima posicao trocada)
		trocas++;

		//imprimindo menor valor encontrado e vetor atualizado
		printf("Menor valor: %d\n", menor);
		imprimirVetor(vetor, tam);
	}

	printf("\nOrdenado!\n");

}

void imprimirVetor( int *vetor, int tam){
	int i, j;

	///*imprimindo em forma de barra
	system("clear"); //limpando tela
	for (i=0; i<tam; i++){
		printf("| ");
		for (j=0; j<vetor[i]; j++){
			printf("*");
		}
		printf("\n");
	}
	//*/

	/*imprimindo em forma numerica
	//system("clear"); //limpando tela
	printf("[ ");
	for(i=0; i<tam; i++){
		printf("%d ", vetor[i]);
	}
	printf("]\n");
	*/

}