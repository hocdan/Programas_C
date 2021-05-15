#include <stdio.h>
#include <stdlib.h>

int main() {
	char comando[101];
    int opcao;

    //lopp principal
    while(1){
        //imprimindo menu do programa
        printf("# Chamadas ao sistema Linux #\n");
        printf("1- Inserir comando\n");
        printf("2- Sair\n");
        printf("--> ");

        scanf("%d", &opcao);
        getchar(); //limpando buffer do teclado
        //realizando acoes de acordo com a opcao
        if (opcao == 1) {
            printf("> ");
            scanf("%[^\n]", comando);
            if (system(comando) != 0) {
                printf("\nErro ao executar comando...\n");            
            } else {
                printf("\nComando executado com sucesso!\n");
            }
        } else if (opcao == 2) {
            printf("\nEncerrando programa!!!\n");
            break;
        } else {
            printf("\nOpcao invalida!!!\n");        
        }
    }
    
	return 0;

}
