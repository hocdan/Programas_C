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

    if ( strcmp(tamTabuleiro, "09x09") == 0) tamanho = 8; //um a menos por conta das intercecoes
    else if ( strcmp(tamTabuleiro, "13x13") == 0) tamanho = 12;
    else if ( strcmp(tamTabuleiro, "19x19") == 0) tamanho = 18;

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

    //gerando tabuleiro visivel
    Rectangle tabuleiro[tamanho][tamanho];
    for (i=0; i<tamanho; i++) {
        for (j=0; j<tamanho; j++) {
            //gerando casas do tabuleiro visivel de acordo com as dimensoes configuradas
            if ( largura == 500 && altura == 300) {
                if (tamanho == 8) {
                    tabuleiro[i][j].x = j*30+30;
                    tabuleiro[i][j].y = i*30+30;
                    tabuleiro[i][j].width = 30;
                    tabuleiro[i][j].height = 30;
                } else if (tamanho == 12) {
                    tabuleiro[i][j].x = j*20+40;
                    tabuleiro[i][j].y = i*20+30;
                    tabuleiro[i][j].width = 20;
                    tabuleiro[i][j].height = 20;
                } else if (tamanho == 18) {
                    tabuleiro[i][j].x = j*15+16;
                    tabuleiro[i][j].y = i*15+16;
                    tabuleiro[i][j].width = 15;
                    tabuleiro[i][j].height = 15;
                }
            } else if ( largura == 700 && altura == 500) {
                if (tamanho == 8) {
                    tabuleiro[i][j].x = j*50+50;
                    tabuleiro[i][j].y = i*50+50;
                    tabuleiro[i][j].width = 50;
                    tabuleiro[i][j].height = 50;
                } else if (tamanho == 12) {
                    tabuleiro[i][j].x = j*35+50;
                    tabuleiro[i][j].y = i*35+40;
                    tabuleiro[i][j].width = 35;
                    tabuleiro[i][j].height = 35;
                } else if (tamanho == 18) {
                    tabuleiro[i][j].x = j*25+24;
                    tabuleiro[i][j].y = i*25+24;
                    tabuleiro[i][j].width = 25;
                    tabuleiro[i][j].height = 25;
                }
            } else if ( largura == 900 && altura == 700) {
                if (tamanho == 8) {
                    tabuleiro[i][j].x = j*70+80;
                    tabuleiro[i][j].y = i*70+70;
                    tabuleiro[i][j].width = 70;
                    tabuleiro[i][j].height = 70;
                } else if (tamanho == 12) {
                    tabuleiro[i][j].x = j*50+60;
                    tabuleiro[i][j].y = i*50+55;
                    tabuleiro[i][j].width = 50;
                    tabuleiro[i][j].height = 50;
                } else if (tamanho == 18) {
                    tabuleiro[i][j].x = j*35+42;
                    tabuleiro[i][j].y = i*35+38;
                    tabuleiro[i][j].width = 35;
                    tabuleiro[i][j].height = 35;
                }
            }
        }
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
                    //imprimindo casas do tabuleiro de acordo com as dimensoes configuradas
                    DrawRectangle(tabuleiro[i][j].x, tabuleiro[i][j].y, tabuleiro[i][j].width, tabuleiro[i][j].height, YELLOW);
                    DrawRectangleLines(tabuleiro[i][j].x, tabuleiro[i][j].y, tabuleiro[i][j].width, tabuleiro[i][j].height, BLACK);
                }
            }

            /*//imprimindo informacoes
            DrawText( FormatText("Dimensões: %s", tamTela), 200, 80, 20, RAYWHITE);
            DrawText( FormatText("Som: %s", ativarSom), 200, 120, 20, RAYWHITE);
            DrawText( FormatText("Tamanho: %s", tamTabuleiro), 200, 160, 20, RAYWHITE);
            DrawText( FormatText("Handicap: %s", ativarHandicap), 200, 200, 20, RAYWHITE);
            */

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
