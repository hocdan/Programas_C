#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#include "manipularArquivos.h"

#define TRUE 1
#define FALSE 0

int jogo() {
    //constantes da janela Jogo
    int largura, altura, som, tamanho, handicap;

    //variaveis da janela Jogo
    int i, j;
    int encerrar = FALSE;
    int status = 1; //status de retorno da janela ao ser fechada (status = menu como padrao)
    char tamTela[11], tamTabuleiro[11], ativarSom[4], ativarHandicap[2];

    //setando valores iniciais das variaveis da janela Jogo
    enviarDado(tamTela, 0);
    enviarDado(ativarSom, 1);
    enviarDado(tamTabuleiro, 2);
    enviarDado(ativarHandicap, 3);

    if ( strcmp(tamTela, "500x300") == 0) {
        largura = 500;
        altura = 300;
    } else if ( strcmp(tamTela, "700x500") == 0) {
        largura = 700;
        altura = 500;
    } else if ( strcmp(tamTela, "900x700") == 0) {
        largura = 900;
        altura = 700;
    }

    if ( strcmp(ativarSom, "YES") == 0) som = TRUE;
    else som = FALSE;

    if ( strcmp(tamTabuleiro, "09x09") == 0) tamanho = 9;
    else if ( strcmp(tamTela, "13x13") == 0) tamanho = 13;
    else if ( strcmp(tamTela, "19x19") == 0) tamanho = 19;

    handicap = atoi(ativarHandicap);

    //inicializando botao de retorno (de acordo com as dimensoes atuais da janela)
    Rectangle botaoVoltar;
    if ( largura == 500 && altura == 300) {
        botaoVoltar.width = 30;
        botaoVoltar.height = 30;
        botaoVoltar.x = 460;
        botaoVoltar.y = 10;
    }
    else if ( largura == 700 && altura == 500) {
        botaoVoltar.width = 40;
        botaoVoltar.height = 40;
        botaoVoltar.x = 640;
        botaoVoltar.y = 20;
    }
    else {
        botaoVoltar.width = 50;
        botaoVoltar.height = 50;
        botaoVoltar.x = 820;
        botaoVoltar.y = 20;
    }

    //inicializando tela e FPS
    InitWindow(largura, altura, "Jogo - GO");

    SetTargetFPS(60);

    //lopp principal da janela Jogo
    while (!WindowShouldClose()) {
        //Update

        //verificando toque no botao de retornar
        if ( CheckCollisionPointRec( GetMousePosition(), botaoVoltar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            status = 1; //status = abrir janela Menu
            encerrar = TRUE;
        }

        //Draw
        BeginDrawing();
            ClearBackground(BLACK);

            //imprimindo tabuleiro
            for (i=0; i<tamanho; i++) {
                for (j=0; j<tamanho; j++) {
                    DrawRectangle(j*10+10, i*10, 10, 10, YELLOW);
                }
            }

            //imprimindo informacoes
            DrawText( FormatText("Dimensões: %s", tamTela), 20, 20, 20, RAYWHITE);
            DrawText( FormatText("Som: %s", ativarSom), 20, 60, 20, RAYWHITE);
            DrawText( FormatText("Tamanho: %s", tamTabuleiro), 20, 100, 20, RAYWHITE);
            DrawText( FormatText("Handicap: %s", ativarHandicap), 20, 140, 20, RAYWHITE);

            //imprimindo botao de de retorno
            DrawRectangle(botaoVoltar.x, botaoVoltar.y, botaoVoltar.width, botaoVoltar.height, RAYWHITE);
            if ( largura == 500 && altura == 300) {
                DrawText(FormatText("<"), botaoVoltar.x+10, botaoVoltar.y+5, 28, BLACK);
            } else if ( largura == 700 && altura == 500) {
                DrawText(FormatText("<"), botaoVoltar.x+14, botaoVoltar.y+7, 30, BLACK);
            } else {
                DrawText(FormatText("<"), botaoVoltar.x+16, botaoVoltar.y+8, 40, BLACK);
            }

        EndDrawing();

        if (encerrar) break; //encerrando loop da janela atual
    }

    CloseWindow(); //encerrando janela Jogo

    return status; //devolvendo status para o fluxo da main.c

}
