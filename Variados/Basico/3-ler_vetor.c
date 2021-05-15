#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int i, j, n, soma = 0;
    char *vetor, num[5];
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    scanf("%d", &n);
    //alocando vetor para armazenar N numeros separados por espacos
    vetor = (char *)malloc((n*8) * sizeof(char));
    //lendo string com os numeros e jogando no vetor alocado
    scanf("%s", vetor);
    for (i=0; i<(n*8); i++) {
        printf("%c", vetor[i]);
    }
    //iterando o vetor, convertendo char em int e armazenando soma dos numeros
    i = 0;
    j = 0;
    while (vetor[i] != '\n') {
        if (vetor[i] != ' ') {
            //capturando numero separado por espaco
            num[j] = vetor[i];
            j++;
        } else {
            //encerrando captura de numero, zerando temp e somando numero
            soma += atoi(num);
            for (j=0; j<4; j++) {
                num[j] = ' ';
            }
            num[4] = '\n';
            j = 0;
        }
        i++;
    }
    printf("%d\n", soma);
    
    free(vetor);
    
    return 0;
}
