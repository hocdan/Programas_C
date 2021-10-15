#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manipularArquivos.h"

#define TRUE 1
#define FALSE 0
#define NOME_ARQUIVO "teste-config.txt" //nome padrao do arquivo
#define MODO "a+" //modo de anexar em leitura/escrita

/*
    Função feita para escanear um arquivo de configurações do jogo: The Way of Go
    e recolher o dado da posição X encontrado entre os símbolos ":" e ";".

    Input: um inteiro X que indica qual valor entre ":" e ";" deve ser lido e re-
    passado pela função para uso posterior.

    Output: uma cadeia de caracteres que contem o valor de uma das 4 variáveis: ta-
    manho de tela, ativar som do jogo, tamanho do tabuleiro e numero do Handicap.
*/

void enviarDado(char* valor, int posicao) {
    FILE *arquivo;
    int valoresLidos = 0, gravar = FALSE;
    char letra;

    //abrindo arquivo para manipulação
    if ( (arquivo = fopen(NOME_ARQUIVO, MODO)) == NULL) {
        exit(1); //encerrando programa com sinalizacao de erro
    } else {
        //resetando string
        strcpy(valor, "");
        //loop principal
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
            //e se sao valores da posicao desejada
            else if (gravar && valoresLidos == posicao) {
                //armazenando caracteres da posição desejada
                strncat(valor, &letra, 1);
            }
        }
        rewind(arquivo); //retornando ponteiro para o inicio do arquivo
        fclose(arquivo); //descartando ponteiro para o arquivo (uso finalizado)

    }
}

/*
    Função feita para escanear um arquivo de configurações do jogo: The Way of Go
    e recolher os dados encontrados entre os simbolos ":" e ";".

    Input: ponteiros para os enderecos dos dados a serem lidos do arquivo. Nesse ca- 
    so, 4  variaveis: tamanho da tela, ativarsom do jogo, tamanho do tabuleiro e numero
    do Handicap.

    Output: devolve nada, apenas altera os valores das variaveis que foram passa-
    das para a função de forma referencial.
*/

void lerDados(char *tamTela, char *ativarSom, char *tamTabuleiro, char *ativarHandicap) {
    FILE *arquivo;
    int valoresLidos = 0, gravar = FALSE;
    char letra;

    //abrindo arquivo para manipulação
    if ( (arquivo = fopen(NOME_ARQUIVO, MODO)) == NULL) {
        exit(1); //encerrando programa com sinalizacao de erro
    } else {
        //loop principal
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
        fclose(arquivo); //descartando ponteiro para o arquivo (uso finalizado)
    }
}

/*
    Função que irá modificar um dado X do arquivo repassado.
    
    Input: um ponteiro de char contendo o novo valor que será introduzido no
    arquivo e um inteiro representando a localizacao do dado a ser modifica-
    do no arquivo. Ou seja, um inteiro X que representa quantos valores entre
    os símbolos ":" e ";" ja foram lidos (a posicao em si).

    Output: nenhum, irá criar uma copia do antigo com as alterações desejadas e
    então excluir o antigo e renomear o novo com o nome do antigo (para futuras
    leituras ou modificações).
*/

void editarArquivo(char *novoValor, int local) {
    FILE *arquivo, *novoArquivo;
    int i = 0, escrever = FALSE, valoresLidos = 0;
    char letra;

    //iniciando ponteiro para arquivo temporario
    if ( (arquivo = fopen(NOME_ARQUIVO, MODO)) == NULL || (novoArquivo = fopen("temp.txt", MODO)) == NULL ) {
        exit(1); //encerrando programa com sinalizacao de erro
    } else {
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
    //editando arquivo com novo valor
    fclose(novoArquivo); //fechando ponteiro do novo arquivo (antigo arquivo editado)
    fclose(arquivo); //fechando ponteiro para antigo arquivo
    remove(NOME_ARQUIVO); //removendo antigo arquivo
    rename("temp.txt", NOME_ARQUIVO); //renomeando novo arquivo (irá tomar o lugar do antigo)
}
