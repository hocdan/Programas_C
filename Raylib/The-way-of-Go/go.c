#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#include "menu.c"
#include "tutorial.c"
#include "jogo.c"
#include "configuracoes.c"

#define TRUE 1
#define FALSE 0

/*
    Ponto de inicio do jogo

    Fará chamada para as outras janelas por
    meio de estados de jogo.

    Janelas chamadas serao executadas e entao
    devolveram um numero referente ao novo
    estado que deve ser executado, como:

    0- encerrando jogo
    1- menu
    2- tutorial
    3- jogo em si
    4- configuracoes

    OBS: futuros estados podem ser adcionados
    posteriormente...
*/
int main() {
    //variaveis
    int gamestate = 1;

    //direcionador de fluxo do jogo
    while(TRUE) {
        if (gamestate == 1) gamestate = menu();
        else if (gamestate == 2) gamestate = tutorial();
        else if (gamestate == 3) gamestate = jogo();
        else if (gamestate == 4) gamestate = config();
        else break; //saindo caso status nao seja de uma janela
    }

    return 0; //sinaliza término do programa
}