#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main () {
    //declarando um ponteiro do tipo FILE para manipular um arquivo
    FILE *arquivo;
    //declarando variaveis responsaveis pela manipulacao do arquivo
    int i, opcao, opcao2, rodando = TRUE;
    char letra, modo[2], texto[101] = {"\0"}, nomeArquivo[51] = {"\0"}; 

    //menu de interacao para configurar manipulacao do arquivo
    while (rodando) {
        printf("\n# MANIPULADOR DE ARQUIVOS 1.0 #\n");
        printf("\n1- Nomear arquivo");
        printf("\n2- Setar modo de manipulacao (r, w, a)");
        printf("\n3- Aplicar configuracoes");
        printf("\n4- Sair");
        printf("\n\n--> ");
        scanf("%d", &opcao);
        getchar(); //limpando buffer do teclado
        //executando opcoes do menu
        switch (opcao) {
            case (1):
                //setando nome do arquivo a ser aberto
                printf("\nInforme o nome do arquivo: ");
                scanf("%[^\n]", nomeArquivo);
                break;
            case (2):
                //setando modo de manipulacao
                printf("\nInforme o modo: ");
                scanf("%[^\n]", modo);
                printf("\nModo selecionado: %s\n", modo);
                break;
            case (3):
                /*
                    Abrindo um arquivo chamado "nomeArquivo" no modo de stream "modo".

                    OBS: sempre testar o retorno da função par ver se nao houve erros e
                    se o arquivo está pronto para manuseio!!!
                */
                if ( (arquivo = fopen(nomeArquivo, modo)) == NULL) {
                    printf("\nErro ao abrir arquivo...\n");
                    exit(1); //encerrando programa com sinalizacao de erro
                } else {
                    //se arquivo pronto sem problemas, seguir manipulacao...
                    if ( strcmp(modo, "r") == 0) {
                        printf("\n MODO DE [APENAS LEITURA] INICIADO! \n");
                        //lendo caracteres do arquivo aberto e mostrando na tela
                        while ( (letra = getc(arquivo)) != EOF) {
                            printf("%c", letra);
                        }
                        printf("\n\nFIM DO ARQUIVO ATINGIDO!\n\n");
                    } else if ( strcmp(modo, "w") == 0) {
                        printf("\n MODO DE [APENAS  ESCRITA] INICIADO!\n");
                        //esperando pelo input do usuario para armazenar no arquivo
                        while (strcmp(texto, "$") != 0) {
                            printf("\n(Digite apenas $ para encerrar escrita) > ");
                            scanf("%[^\n]", texto);
                            //ignorando o caractere de finalizacao na hora de armazenar
                            if ( strcmp(texto, "$") != 0 ) {
                                //armazenando input do usuario no arquivo (ira sobrescrever)
                                for (i=0; i<strlen(texto); i++) {
                                    putc(texto[i], arquivo);
                                }
                            }
                            getchar(); //limpando buffer do teclado
                        }
                        strcpy(texto, "\n"); //"resetando" valor inicial
                        printf("\n\nFIM DA ESCRITA NO ARQUIVO!\n\n");
                    } else if ( strcmp(modo, "a") == 0) {
                        printf("\n MODO DE [APENAS ANEXAR] INICIADO! \n");
                        //esperando pelo input do usuario para armazenar no arquivo
                        while ( strcmp(texto, "$") != 0) {
                            printf("\n(Digite apenas $ para encerrar escrita) > ");
                            scanf("%[^\n]", texto);
                            //ignorando o caractere de finalizacao na hora de armazenar
                            if ( strcmp(texto, "$") != 0 ) {
                                //armazenando input do usuario no arquivo (ira sobrescrever)
                                for (i=0; i<strlen(texto); i++) {
                                    putc(texto[i], arquivo);
                                }
                            }
                            getchar(); //limpando buffer do teclado
                        }
                        strcpy(texto, "\n"); //"resetando" valor inicial
                        printf("\n\nFIM DA ESCRITA ANEXADA AO ARQUIVO!\n\n");
                    } else {
                        printf("\nModo de manipulacao nao suportado!!!\n");
                    }
                }
                //fechando stream do arquivo (maneira segura e que guarda buffer no arquivo)
                fclose(arquivo);
                break;
            case (4):
                rodando = FALSE;
                break;
            default:
                printf("\nopcao invalida!!!\n");
        }
    }
    printf("\nEncerrando programa...\n");

    return 0;
}