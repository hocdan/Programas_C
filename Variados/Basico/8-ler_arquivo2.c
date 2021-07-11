#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define NOME_ARQUIVO "teste-config.txt" //nome padrao do arquivo
#define MODO "a+" //modo de anexar em leitura/escrita

/*
    Programa para teste de leitura de arquivos...parte 2

    Objetivo: ler um arquivo .txt de configuração pre-
    viamente preenchido e poder realizar buscas e al-
    terações em seu conteúdo.

    OBS: alterar conteudo de acordo com essa tabela ->

    conteudo 1 -> SCREEN_SIZE pode ser 400x300, 600x400 ou 800x500
    conteudo 2 -> SOUND pode ser YES ou NOP
    conteudo 3 -> BOARD_SIZE pode ser 09x09, 13x13 ou 19x19
    conteudo 4 -> HANDICAP pode ser 0, 1, 2, 3, 4, 5, 6, 7, 8 ou 9

    Esses valores devem ser seguidos para nao ocorrer 
    erros na edicao do arquivo, visto que a edicao fun-
    ciona num numero preciso de caracteres...logo o conteudo
    1 suporta 7 caracteres, o 2 suporta 3 caracteres, o 3 
    suporta 5 caracteres e o 4 suporta 1 caractere.
*/

int main () {
    //prototipo de funcao a ser utilizada
    void editarArquivo(FILE *arquivo, char *novoValor, int local);

    //variaveis do programa
    FILE *arquivo; //ponteiro para acessar o arquivo
    char letra, novoValor[11], tamTela[11], tamTabuleiro[11], ativarSom[4], ativarHandicap[2];
    int opcao1, opcao2, gravar, valoresLidos;

    //abrindo arquivo para manipulação
    if ( (arquivo = fopen(NOME_ARQUIVO, MODO)) == NULL) {
        printf("\nErro ao abrir arquivo!!!\n");
        exit(1); //encerrando programa com sinalizacao de erro
    } else {
        //loop principal
        while (1) {
            //menu de manipulação do arquivo
            printf("\n# MANIPULADOR DE ARQUIVOS 1.0 #\n");
            printf("\n1- Visualizar conteudo do arquivo");
            printf("\n2- Alterar conteudo do arquivo");
            printf("\n3- Sair");
            printf("\n\n--> ");
            scanf("%d", &opcao1);
            getchar(); //limpando buffer do teclado

            //executando opcoes do menu
            if ( opcao1 == 1) {
                //resetando flags e variaveis
                gravar = FALSE;
                valoresLidos = 0;
                strcpy(tamTela, "");
                strcpy(tamTabuleiro, "");
                strcpy(ativarSom, "");
                strcpy(ativarHandicap, "");
                while ( (letra = getc(arquivo)) != EOF) {
                    //verificando se chegou a hora de gravar
                    if ( letra == ':') {
                        gravar = TRUE;
                    } 
                    //varificando se chegou a hora de parar gravacao
                    else if ( letra == ';') {
                        gravar = FALSE;
                        valoresLidos++; //atualizando contador de gravacoes
                    }
                    //verificando se ha caracteres validos para armazenar
                    else if (gravar) {
                        if (valoresLidos == 0) {
                            //armazenando caracteres do primeiro valor
                            strncat(tamTela, &letra, 1);
                        } else if (valoresLidos == 1) {
                            //armazenando caracteres do segundo valor
                            strncat(tamTabuleiro, &letra, 1);
                        } else if (valoresLidos == 2) {
                            //armazenando caracteres do terceiro valor
                            strncat(ativarSom, &letra, 1);
                        } else if (valoresLidos == 3) {
                            //armazenando caracteres do quarto valor
                            strncat(ativarHandicap, &letra, 1);
                        }
                    }
                }
                rewind(arquivo); //retornando ponteiro para o inicio do arquivo
                printf("Tamanho da tela: %s", tamTela);
                printf("\nAtivar som: %s", ativarSom);
                printf("\nTamanho do tabuleiro: %s", tamTabuleiro);
                printf("\nHandicap ativo: %s", ativarHandicap);

                printf("\n\nFIM DO ARQUIVO ATINGIDO!\n\n");
            } else if (opcao1 == 2) {
                //submenu para alterar dados do arquivo
                printf("\n1- Alterar tamanho da tela");
                printf("\n2- Alterar status do som");
                printf("\n3- Alterar tamanho do tabuleiro");
                printf("\n4- Alterar handicap");
                printf("\n\n--> ");
                scanf("%d", &opcao2);
                getchar(); //limpando buffer do teclado

                //armazenando novo valor a ser registrado
                strcpy(novoValor, "");
                printf("\nNovo valor: ");
                scanf("%[^\n]", novoValor);
                getchar(); //limpando buffer do teclado

                //executando opcoes do submenu
                 if (opcao2 >= 1 && opcao2 <= 4) {
                    //editando arquivo com novo valor
                    editarArquivo(arquivo, novoValor, opcao2);
                    fclose(arquivo); //fechando ponteiro para antigo arquivo
                    remove(NOME_ARQUIVO); //removendo antigo arquivo
                    rename("temp.txt", NOME_ARQUIVO); //renomeando novo arquivo
                    //fazendo ponteiro do antigo arquivo apontar para novo arquivo
                    if ( (arquivo = fopen(NOME_ARQUIVO, MODO)) == NULL) {
                        printf("\nErro ao abrir arquivo!!!\n");
                        exit(1); //encerrando programa com sinalizacao de erro
                    }
                } else {
                    printf("\nOpcao invalida!!!\n");
                }
            } else if (opcao1 == 3) {
                //fechando arquivo para salvar de maneira segura os dados
                fclose(arquivo);
                printf("\nEncerrando programa...\n");
                break;
            } else {
                printf("\nopcao invalida!!!\n");
            }
        }
    }

    return 0;
}

void editarArquivo(FILE *arquivo, char *novoValor, int local) {
    FILE *novoArquivo;
    int i = 0, escrever = FALSE, valoresLidos = 0;
    char letra;

    //iniciando ponteiro para arquivo temporario
    if ( (novoArquivo = fopen("temp.txt", "a+")) == NULL) {
        printf("\nErro ao abrir arquivo temporario!!!\n");
        exit(1);
    } else {
        printf("\nAlterando arquivo...\n");
        //realizando busca do local a ser reescrito
        while ( (letra = getc(arquivo)) != EOF) {
            //verificando se chegou ao local de escrita desejado
            if ( letra == ':' && valoresLidos == local-1) {
                escrever = TRUE;
                //escrevendo antigos caracteres inalterados no novo arquivo
                putc(letra, novoArquivo);
            } 
            //verificando se um local de escrita ja foi percorrido
            else if ( letra == ';') {
                escrever = FALSE;
                valoresLidos++;
                //escrevendo antigos caracteres inalterados no novo arquivo
                putc(letra, novoArquivo);
            } 
            //verificando se eh possivel escrever no arquivo
            else if (escrever) {
                putc(novoValor[i], novoArquivo);
                i++; //atualizando contador
            } else {
                //escrevendo antigos caracteres inalterados no novo arquivo
                putc(letra, novoArquivo);
            }
        }
    }

    fclose(novoArquivo); //fechando ponteiro do novo arquivo (antigo arquivo editado)
}
