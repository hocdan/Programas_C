//condicao para nao repetir referenciamento
#ifndef MANIPULARARQUIVOS_H_INCLUDED
#define MANIPULARARQUIVOS_H_INCLUDED

/*
    TABELA DE ALTERAÇÕES DO VALORES

    > SCREEN_SIZE pode assumir os valores: "500x300", "700X500" ou "900x700".
    > SOUND pode assumir os valores: "YES" ou "NOP".
    > BOARD_SIZE pode assumir os valores: "09x09", "13x13" ou "19x19".
    > HANDICAP pode assumir os valores: "0", "1", "2", "3", ... , "8" ou "9".
*/

    //funcoes disponiveis para manipular arquivos
    void enviarDado(char* valor, int posicao);
    void lerDados(char *tamTela, char *ativarSom, char *tamTabuleiro, char *ativarHandicap);
    void editarArquivo(char *novoValor, int local);

#endif //arquivo MANIPULARARQUIVOS_H
