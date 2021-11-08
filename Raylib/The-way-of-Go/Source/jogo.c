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
    int i, j, turno = 0;
    int encerrar = FALSE;
    int status = 1; //status de retorno da janela ao ser fechada (status = menu como padrao)
    char tamTela[11], tamTabuleiro[11], ativarSom[4], ativarHandicap[2];

    //variaveis dos jogadores
    int pretasCapturadas = 0, brancasCapturadas = 0;

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

    //inicializando botao de passar a vez de acordo com as dimensoes atuais da tela
    Rectangle botaoPassar;
    if ( largura == 500 && altura == 300) {
        botaoPassar.width = 100;
        botaoPassar.height = 40;
        botaoPassar.x = 350;
        botaoPassar.y = 250;
    }
    else if ( largura == 700 && altura == 500) {
        botaoPassar.width = 100;
        botaoPassar.height = 50;
        botaoPassar.x = 530;
        botaoPassar.y = 400;
    }
    else {
        botaoPassar.width = 140;
        botaoPassar.height = 60;
        botaoPassar.x = 710;
        botaoPassar.y = 600;
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

    /*
        gerando tabuleiro invisivel (maior que o tabuleiro visivel por 1 unidade em ambas as direcoes)
        e setando valores padroes da situacao de cada intersecao do tabuleiro.
    */
    Rectangle tabuleiro2[tamanho+1][tamanho+1];
    int tabuleiro3[tamanho+1][tamanho+1];
    for (i=0; i<=tamanho; i++) {
        for (j=0; j<=tamanho; j++) {
            tabuleiro3[i][j] = 0; //setando como vazio/sem pecas nessa posicao do tabuleiro
            //gerando casas do tabuleiro visivel de acordo com as dimensoes configuradas
            if ( largura == 500 && altura == 300) {
                if (tamanho == 8) {
                    tabuleiro2[i][j].x = j*30+15;
                    tabuleiro2[i][j].y = i*30+15;
                    tabuleiro2[i][j].width = 30;
                    tabuleiro2[i][j].height = 30;
                } else if (tamanho == 12) {
                    tabuleiro2[i][j].x = j*20+30;
                    tabuleiro2[i][j].y = i*20+20;
                    tabuleiro2[i][j].width = 20;
                    tabuleiro2[i][j].height = 20;
                } else if (tamanho == 18) {
                    tabuleiro2[i][j].x = j*15+8.5;
                    tabuleiro2[i][j].y = i*15+8.5;
                    tabuleiro2[i][j].width = 15;
                    tabuleiro2[i][j].height = 15;
                }
            } else if ( largura == 700 && altura == 500) {
                if (tamanho == 8) {
                    tabuleiro2[i][j].x = j*50+25;
                    tabuleiro2[i][j].y = i*50+25;
                    tabuleiro2[i][j].width = 50;
                    tabuleiro2[i][j].height = 50;
                } else if (tamanho == 12) {
                    tabuleiro2[i][j].x = j*35+32.5;
                    tabuleiro2[i][j].y = i*35+22.5;
                    tabuleiro2[i][j].width = 35;
                    tabuleiro2[i][j].height = 35;
                } else if (tamanho == 18) {
                    tabuleiro2[i][j].x = j*25+11.5;
                    tabuleiro2[i][j].y = i*25+11.5;
                    tabuleiro2[i][j].width = 25;
                    tabuleiro2[i][j].height = 25;
                }
            } else if ( largura == 900 && altura == 700) {
                if (tamanho == 8) {
                    tabuleiro2[i][j].x = j*70+45;
                    tabuleiro2[i][j].y = i*70+35;
                    tabuleiro2[i][j].width = 70;
                    tabuleiro2[i][j].height = 70;
                } else if (tamanho == 12) {
                    tabuleiro2[i][j].x = j*50+35;
                    tabuleiro2[i][j].y = i*50+30;
                    tabuleiro2[i][j].width = 50;
                    tabuleiro2[i][j].height = 50;
                } else if (tamanho == 18) {
                    tabuleiro2[i][j].x = j*35+24.5;
                    tabuleiro2[i][j].y = i*35+20.5;
                    tabuleiro2[i][j].width = 35;
                    tabuleiro2[i][j].height = 35;
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

        //TEEEEEEEEEEEEEEEESTEEEEEEEEEEEE!!!
        if (turno%2 == 0 && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) brancasCapturadas++;
        else if (turno%2 == 1 && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) pretasCapturadas++;

        //checando colisoes do cursor do mouse nas intercecoes do tabuleiro (usando tabuleiro invisivel de referencia)
        for (i=0; i<=tamanho; i++) {
            for (j=0; j<=tamanho; j++) {
                //verificando se houve toque nessa area e se está vazia
                if ( CheckCollisionPointRec( GetMousePosition(), tabuleiro2[i][j]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && tabuleiro3[i][j] == 0) {
                    //setando valor de acordo com a peca usada para jogar
                    if (turno%2 == 0) tabuleiro3[i][j] = 1; //PRETA
                    else tabuleiro3[i][j] = 2; //BRANCA
                    turno++; //atualizando turno e portanto de quem é a vez de jogar
                }
            }
        }

        //verificando toque no botao de retornar
        if ( CheckCollisionPointRec( GetMousePosition(), botaoVoltar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            status = 1; //status = abrir janela Menu
            encerrar = TRUE;
        }
        //verificando toque no botao de passar a vez
        if ( CheckCollisionPointRec( GetMousePosition(), botaoPassar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
           turno++; //atualizando turno (passando a vez do jogador atual)
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
            //imprimindo pecas do tabuleiro
            for (i=0; i<=tamanho; i++) {
                for (j=0; j<=tamanho; j++) {
                    //imprimindo pecas de acordo com as dimensoes configuradas
                    if ( tabuleiro3[i][j] == 1) {
                        DrawCircle(tabuleiro2[i][j].x+(int)(tabuleiro2[i][j].width/2), tabuleiro2[i][j].y+(int)(tabuleiro2[i][j].height/2), tabuleiro2[i][j].width/2, BLACK);
                        DrawCircleLines(tabuleiro2[i][j].x+(int)(tabuleiro2[i][j].width/2), tabuleiro2[i][j].y+(int)(tabuleiro2[i][j].height/2), tabuleiro2[i][j].width/2, RAYWHITE);
                    } else if ( tabuleiro3[i][j] == 2) {
                        DrawCircle(tabuleiro2[i][j].x+(int)(tabuleiro2[i][j].width/2), tabuleiro2[i][j].y+(int)(tabuleiro2[i][j].height/2), tabuleiro2[i][j].width/2, RAYWHITE);
                        DrawCircleLines(tabuleiro2[i][j].x+(int)(tabuleiro2[i][j].width/2), tabuleiro2[i][j].y+(int)(tabuleiro2[i][j].height/2), tabuleiro2[i][j].width/2, BLACK);
                    }
                }
            }

            //imprimindo informações
            if ( largura == 500 && altura == 300) {
                DrawText(FormatText("%d", pretasCapturadas), 430, 155, 25, RAYWHITE);
                DrawText(FormatText("%d", brancasCapturadas), 430, 205, 25, RAYWHITE);
                DrawCircle( 380, 160, tabuleiro2[i][j].width/2, BLACK);
                DrawCircleLines( 380, 160, tabuleiro2[i][j].width/2, RAYWHITE);
                DrawCircle( 380, 210, tabuleiro2[i][j].width/2, RAYWHITE);
                DrawText(FormatText("TURN: "), 350, 40, 25, RAYWHITE);
                if (turno%2 == 0) {
                    DrawCircle( 380, 100, tabuleiro2[i][j].width/2, BLACK);
                    DrawCircleLines( 380, 100, tabuleiro2[i][j].width/2, RAYWHITE);
                }
                else DrawCircle( 380, 100, tabuleiro2[i][j].width/2, RAYWHITE);
            } else if ( largura == 700 && altura == 500) {
                DrawText(FormatText("%d", pretasCapturadas), 610, 255, 30, RAYWHITE);
                DrawText(FormatText("%d", brancasCapturadas), 610, 315, 30, RAYWHITE);
                DrawCircle( 560, 260, tabuleiro2[i][j].width/2, BLACK);
                DrawCircleLines( 560, 260, tabuleiro2[i][j].width/2, RAYWHITE);
                DrawCircle( 560, 320, tabuleiro2[i][j].width/2, RAYWHITE);
                DrawText(FormatText("TURN: "), 530, 80, 28, RAYWHITE);
                if (turno%2 == 0) {
                    DrawCircle( 560, 150, tabuleiro2[i][j].width/2, BLACK);
                    DrawCircleLines( 560, 150, tabuleiro2[i][j].width/2, RAYWHITE);
                }
                else DrawCircle( 560, 150, tabuleiro2[i][j].width/2, RAYWHITE);
            } else {
                DrawText(FormatText("%d", pretasCapturadas), 820, 340, 40, RAYWHITE);
                DrawText(FormatText("%d", brancasCapturadas), 820, 440, 40, RAYWHITE);
                DrawCircle( 750, 350, tabuleiro2[i][j].width/2, BLACK);
                DrawCircleLines( 750, 350, tabuleiro2[i][j].width/2, RAYWHITE);
                DrawCircle( 750, 450, tabuleiro2[i][j].width/2, RAYWHITE);
                DrawText(FormatText("TURN: "), 710, 110, 30, RAYWHITE);
                if (turno%2 == 0) {
                    DrawCircle( 750, 200, tabuleiro2[i][j].width/2, BLACK);
                    DrawCircleLines( 750, 200, tabuleiro2[i][j].width/2, RAYWHITE);
                }
                else DrawCircle( 750, 200, tabuleiro2[i][j].width/2, RAYWHITE);
            }

            //imprimindo botao de de retorno
            DrawRectangle(botaoVoltar.x, botaoVoltar.y, botaoVoltar.width, botaoVoltar.height, RAYWHITE);
            if ( largura == 500 && altura == 300) {
                DrawText(FormatText("<"), botaoVoltar.x+10, botaoVoltar.y+4, 28, BLACK);
            } else if ( largura == 700 && altura == 500) {
                DrawText(FormatText("<"), botaoVoltar.x+14, botaoVoltar.y+7, 30, BLACK);
            } else {
                DrawText(FormatText("<"), botaoVoltar.x+16, botaoVoltar.y+8, 40, BLACK);
            }
            //imprimindo botao de passar a vez
            DrawRectangle(botaoPassar.x, botaoPassar.y, botaoPassar.width, botaoPassar.height, RAYWHITE);
            if ( largura == 500 && altura == 300) {
                DrawText(FormatText("PASS"), botaoPassar.x+13, botaoPassar.y+8, 28, BLACK);
            } else if ( largura == 700 && altura == 500) {
                DrawText(FormatText("PASS"), botaoPassar.x+12, botaoPassar.y+12, 30, BLACK);
            } else {
                DrawText(FormatText("PASS"), botaoPassar.x+18, botaoPassar.y+12, 40, BLACK);
            }

        EndDrawing();

        if (encerrar) break; //encerrando loop da janela atual
    }

    CloseWindow(); //encerrando janela Jogo

    return status; //devolvendo status para o fluxo da main.c

}
