#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.


void calculate_the_maximum(int n, int k) {
    int i, j, maxAND = 0, maxOR = 0, maxXOR = 0;
  //Write your code here.
    for (i=1; i<=n; i++) {
        for (j=1; j<=k; j++) {
            //apenas realizando operacao bit a bit com numeros diferentes
            if (i != j) {
                //comparacao AND
                if ( (i & j) < k && (i & j) > maxAND) {
                    maxAND = i & j;
                }
                //comparacao OR
                if ( (i | j) < k && (i | j) > maxOR) {
                    maxOR = i | j;
                }
                //comparacao XOR
                if ( (i ^ j) < k && (i ^ j) > maxXOR) {
                    maxXOR = i ^ j;
                }
            }
        }
    }
    //imprimindo resultados
    printf("%d\n%d\n%d\n", maxAND, maxOR, maxXOR);
}

int main() {
    int n, k;
  
    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);
 
    return 0;
}

