#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, n;

    printf("Numero de bipes: ");
    scanf("%d", &n);

    for (i=0; i<n; i++) {
        printf("BIPE!\a\n");
        system("sleep 1"); //chamada do sistema linux
    }

}
