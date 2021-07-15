#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#include "manipularArquivos.h"

#define TRUE 1
#define FALSE 0
#define NUM_BOTOES 18

int config() {
    //constantes da janela Configuracoes
    const int largura = 900;
    const int altura = 700;

    //variaveis da janela Configuracoes
    int i, entrou, bolaPreta = FALSE, bolaBranca = FALSE, encerrar = FALSE;
    int status = 1; //status de retorno da janela ao ser fechada (status = menu como padrao)
    int configuracoesAtivas[NUM_BOTOES] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
    FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE};

    //variavies para manipular o arquivo de configuração
    char letra, novoValor[11], tamTela[11], tamTabuleiro[11], ativarSom[4], ativarHandicap[2];
    int local;

    //inicializando botao de retorno
    Rectangle botaoVoltar = {820, 20, 50, 50};
    Rectangle tela1 = {450, 170, 100, 60};
    Rectangle tela2 = {580, 170, 100, 60};
    Rectangle tela3 = {710, 170, 100, 60};
    Rectangle somOn = {250, 290, 100, 60};
    Rectangle somOff = {380, 290, 100, 60};
    Rectangle tabuleiro1 = {350, 410, 100, 60};
    Rectangle tabuleiro2 = {480, 410, 100, 60};
    Rectangle tabuleiro3 = {610, 410, 100, 60};
    Rectangle vantagem0 = {400, 530, 80, 50};
    Rectangle vantagem1 = {490, 530, 80, 50};
    Rectangle vantagem2 = {580, 530, 80, 50};
    Rectangle vantagem3 = {670, 530, 80, 50};
    Rectangle vantagem4 = {760, 530, 80, 50};
    Rectangle vantagem5 = {400, 600, 80, 50};
    Rectangle vantagem6 = {490, 600, 80, 50};
    Rectangle vantagem7 = {580, 600, 80, 50};
    Rectangle vantagem8 = {670, 600, 80, 50};
    Rectangle vantagem9 = {760, 600, 80, 50};
    Rectangle botoes[NUM_BOTOES+1] = {tela1, tela2, tela3, somOn, somOff, tabuleiro1, tabuleiro2, tabuleiro3,
    vantagem0, vantagem1, vantagem2, vantagem3, vantagem4, vantagem5, vantagem6, vantagem7, vantagem8, vantagem9, botaoVoltar};

    //inicializando tela e FPS
    InitWindow(largura, altura, "Configuracoes - GO");

    SetTargetFPS(60);

    //lopp principal da janela Configuracoes
    while (!WindowShouldClose()) {
        //Update

        //realizando checagem de toque para efeito de bola branca/preta na ponta do mouse
        entrou = FALSE;
        for (i=0; i<(NUM_BOTOES+1); i++) {
            if ( CheckCollisionPointRec( GetMousePosition(), botoes[i]) ) {
                entrou = TRUE;
                break;
            }
        }
        if (entrou) {
            bolaPreta = TRUE;
            bolaBranca = FALSE;
        } else {
            bolaPreta = FALSE;
            bolaBranca = TRUE;
        }
        //verificando toque no botao de retornar
        if ( CheckCollisionPointRec( GetMousePosition(), botaoVoltar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            status = 1; //status = abrir janela Menu
            encerrar = TRUE;
        }
        //verificando toques nos botoes de configuracoes
        for (i=0; i<NUM_BOTOES; i++) {
            if ( CheckCollisionPointRec( GetMousePosition(), botoes[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                //verificando qual botao foi apertado e realizando as devidas alterações
                if ( i == 0) {
                    //alterando valores de dimensoes de tela no arquivo para 500x300
                    editarArquivo("500x300", 1);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[0] = TRUE;
                    configuracoesAtivas[1] = FALSE;
                    configuracoesAtivas[2] = FALSE;
                } else if ( i == 1) {
                    //alterando valores de dimensoes de tela no arquivo para 700x500
                    editarArquivo("700x500", 1);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[0] = FALSE;
                    configuracoesAtivas[1] = TRUE;
                    configuracoesAtivas[2] = FALSE;
                } else if ( i == 2) {
                    //alterando valores de dimensoes de tela no arquivo para 900x700
                    editarArquivo("900x700", 1);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[0] = FALSE;
                    configuracoesAtivas[1] = FALSE;
                    configuracoesAtivas[2] = TRUE;
                } else if ( i == 3) {
                    //alterando valor do status do som no arquivo para "YES"
                    editarArquivo("YES", 2);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[3] = TRUE;
                    configuracoesAtivas[4] = FALSE;
                } else if ( i == 4) {
                    //alterando valor do status do som no arquivo para "NOP"
                    editarArquivo("NOP", 2);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[3] = FALSE;
                    configuracoesAtivas[4] = TRUE;
                } else if ( i == 5) {
                    //alterando valores de dimensoes do tabuleiro no arquivo para "09x09"
                    editarArquivo("09X09", 3);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[5] = TRUE;
                    configuracoesAtivas[6] = FALSE;
                    configuracoesAtivas[7] = FALSE;
                } else if ( i == 6) {
                    //alterando valores de dimensoes do tabuleiro no arquivo para "13x13"
                    editarArquivo("13X13", 3);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[5] = FALSE;
                    configuracoesAtivas[6] = TRUE;
                    configuracoesAtivas[7] = FALSE;
                } else if ( i == 7) {
                    //alterando valores de dimensoes do tabuleiro no arquivo para "19x19"
                    editarArquivo("19X19", 3);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[5] = FALSE;
                    configuracoesAtivas[6] = FALSE;
                    configuracoesAtivas[7] = TRUE;
                } else if ( i == 8) {
                    //alterando valor do handicap no arquivo para "0"
                    editarArquivo("0", 4);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[8] = TRUE;
                    configuracoesAtivas[9] = FALSE;
                    configuracoesAtivas[10] = FALSE;
                    configuracoesAtivas[11] = FALSE;
                    configuracoesAtivas[12] = FALSE;
                    configuracoesAtivas[13] = FALSE;
                    configuracoesAtivas[14] = FALSE;
                    configuracoesAtivas[15] = FALSE;
                    configuracoesAtivas[16] = FALSE;
                    configuracoesAtivas[17] = FALSE;
                } else if ( i == 9) {
                    //alterando valor do handicap no arquivo para "1"
                    editarArquivo("1", 4);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[8] = FALSE;
                    configuracoesAtivas[9] = TRUE;
                    configuracoesAtivas[10] = FALSE;
                    configuracoesAtivas[11] = FALSE;
                    configuracoesAtivas[12] = FALSE;
                    configuracoesAtivas[13] = FALSE;
                    configuracoesAtivas[14] = FALSE;
                    configuracoesAtivas[15] = FALSE;
                    configuracoesAtivas[16] = FALSE;
                    configuracoesAtivas[17] = FALSE;
                } else if ( i == 10) {
                    //alterando valor do handicap no arquivo para "2"
                    editarArquivo("2", 4);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[8] = FALSE;
                    configuracoesAtivas[9] = FALSE;
                    configuracoesAtivas[10] = TRUE;
                    configuracoesAtivas[11] = FALSE;
                    configuracoesAtivas[12] = FALSE;
                    configuracoesAtivas[13] = FALSE;
                    configuracoesAtivas[14] = FALSE;
                    configuracoesAtivas[15] = FALSE;
                    configuracoesAtivas[16] = FALSE;
                    configuracoesAtivas[17] = FALSE;
                } else if ( i == 11) {
                    //alterando valor do handicap no arquivo para "3"
                    editarArquivo("3", 4);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[8] = FALSE;
                    configuracoesAtivas[9] = FALSE;
                    configuracoesAtivas[10] = FALSE;
                    configuracoesAtivas[11] = TRUE;
                    configuracoesAtivas[12] = FALSE;
                    configuracoesAtivas[13] = FALSE;
                    configuracoesAtivas[14] = FALSE;
                    configuracoesAtivas[15] = FALSE;
                    configuracoesAtivas[16] = FALSE;
                    configuracoesAtivas[17] = FALSE;
                } else if ( i == 12) {
                    //alterando valor do handicap no arquivo para "4"
                    editarArquivo("4", 4);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[8] = FALSE;
                    configuracoesAtivas[9] = FALSE;
                    configuracoesAtivas[10] = FALSE;
                    configuracoesAtivas[11] = FALSE;
                    configuracoesAtivas[12] = TRUE;
                    configuracoesAtivas[13] = FALSE;
                    configuracoesAtivas[14] = FALSE;
                    configuracoesAtivas[15] = FALSE;
                    configuracoesAtivas[16] = FALSE;
                    configuracoesAtivas[17] = FALSE;;
                } else if ( i == 13) {
                    //alterando valor do handicap no arquivo para "5"
                    editarArquivo("5", 4);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[8] = FALSE;
                    configuracoesAtivas[9] = FALSE;
                    configuracoesAtivas[10] = FALSE;
                    configuracoesAtivas[11] = FALSE;
                    configuracoesAtivas[12] = FALSE;
                    configuracoesAtivas[13] = TRUE;
                    configuracoesAtivas[14] = FALSE;
                    configuracoesAtivas[15] = FALSE;
                    configuracoesAtivas[16] = FALSE;
                    configuracoesAtivas[17] = FALSE;
                } else if ( i == 14) {
                    //alterando valor do handicap no arquivo para "6"
                    editarArquivo("6", 4);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[8] = FALSE;
                    configuracoesAtivas[9] = FALSE;
                    configuracoesAtivas[10] = FALSE;
                    configuracoesAtivas[11] = FALSE;
                    configuracoesAtivas[12] = FALSE;
                    configuracoesAtivas[13] = FALSE;
                    configuracoesAtivas[14] = TRUE;
                    configuracoesAtivas[15] = FALSE;
                    configuracoesAtivas[16] = FALSE;
                    configuracoesAtivas[17] = FALSE;
                } else if ( i == 15) {
                    //alterando valor do handicap no arquivo para "7"
                    editarArquivo("7", 4);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[8] = FALSE;
                    configuracoesAtivas[9] = FALSE;
                    configuracoesAtivas[10] = FALSE;
                    configuracoesAtivas[11] = FALSE;
                    configuracoesAtivas[12] = FALSE;
                    configuracoesAtivas[13] = FALSE;
                    configuracoesAtivas[14] = FALSE;
                    configuracoesAtivas[15] = TRUE;
                    configuracoesAtivas[16] = FALSE;
                    configuracoesAtivas[17] = FALSE;
                } else if ( i == 16) {
                    //alterando valor do handicap no arquivo para "8"
                    editarArquivo("8", 4);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[8] = FALSE;
                    configuracoesAtivas[9] = FALSE;
                    configuracoesAtivas[10] = FALSE;
                    configuracoesAtivas[11] = FALSE;
                    configuracoesAtivas[12] = FALSE;
                    configuracoesAtivas[13] = FALSE;
                    configuracoesAtivas[14] = FALSE;
                    configuracoesAtivas[15] = FALSE;
                    configuracoesAtivas[16] = TRUE;
                    configuracoesAtivas[17] = FALSE;
                } else if ( i == 17) {
                    //alterando valor do handicap no arquivo para "9"
                    editarArquivo("9", 4);
                    //sinalizando que o botao dessa configuração foi ativado e suas variantes nao
                    configuracoesAtivas[8] = FALSE;
                    configuracoesAtivas[9] = FALSE;
                    configuracoesAtivas[10] = FALSE;
                    configuracoesAtivas[11] = FALSE;
                    configuracoesAtivas[12] = FALSE;
                    configuracoesAtivas[13] = FALSE;
                    configuracoesAtivas[14] = FALSE;
                    configuracoesAtivas[15] = FALSE;
                    configuracoesAtivas[16] = FALSE;
                    configuracoesAtivas[17] = TRUE;
                }
            }
        }

        //Draw
        BeginDrawing();
            ClearBackground(BLACK);

            //imprimindo opcoes de configuracoes
            DrawText(FormatText("JANELA DE CONFIGURACOES"), 120, 25, 40, RAYWHITE);

            DrawText(FormatText("-> Change screen size:"), 50, 180, 30, RAYWHITE);
            DrawRectangle(tela1.x, tela1.y, tela1.width, tela1.height, RAYWHITE);
            DrawText(FormatText("500x300"), tela1.x+10, tela1.y+20, 20, BLACK);
            DrawRectangle(tela2.x, tela2.y, tela2.width, tela2.height, RAYWHITE);
            DrawText(FormatText("700x500"), tela2.x+8, tela2.y+20, 20, BLACK);
            DrawRectangle(tela3.x, tela3.y, tela3.width, tela3.height, RAYWHITE);
            DrawText(FormatText("900x700"), tela3.x+8, tela3.y+20, 20, BLACK);

            DrawText(FormatText("-> Sound: "), 50, 300, 30, RAYWHITE);
            DrawRectangle(somOn.x, somOn.y, somOn.width, somOn.height, RAYWHITE);
            DrawText(FormatText("YES"), somOn.x+30, somOn.y+20, 20, BLACK);
            DrawRectangle(somOff.x, somOff.y, somOff.width, somOff.height, RAYWHITE);
            DrawText(FormatText("NOP"), somOff.x+30, somOff.y+20, 20, BLACK);

            DrawText(FormatText("-> Board Size: "), 50, 420, 30, RAYWHITE);
            DrawRectangle(tabuleiro1.x, tabuleiro1.y, tabuleiro1.width, tabuleiro1.height, RAYWHITE);
            DrawText(FormatText("09x09"), tabuleiro1.x+20, tabuleiro1.y+20, 20, BLACK);
            DrawRectangle(tabuleiro2.x, tabuleiro2.y, tabuleiro2.width, tabuleiro2.height, RAYWHITE);
            DrawText(FormatText("13x13"), tabuleiro2.x+25, tabuleiro2.y+20, 20, BLACK);
            DrawRectangle(tabuleiro3.x, tabuleiro3.y, tabuleiro3.width, tabuleiro3.height, RAYWHITE);
            DrawText(FormatText("19x19"), tabuleiro3.x+25, tabuleiro3.y+20, 20, BLACK);

            DrawText(FormatText("-> White Handicap: "), 50, 540, 30, RAYWHITE);
            DrawRectangle(vantagem0.x, vantagem0.y, vantagem0.width, vantagem0.height, RAYWHITE);
            DrawText(FormatText("0"), vantagem0.x+35, vantagem0.y+15, 25, BLACK);
            DrawRectangle(vantagem1.x, vantagem1.y, vantagem1.width, vantagem1.height, RAYWHITE);
            DrawText(FormatText("1"), vantagem1.x+35, vantagem1.y+15, 25, BLACK);
            DrawRectangle(vantagem2.x, vantagem2.y, vantagem2.width, vantagem2.height, RAYWHITE);
            DrawText(FormatText("2"), vantagem2.x+35, vantagem2.y+15, 25, BLACK);
            DrawRectangle(vantagem3.x, vantagem3.y, vantagem3.width, vantagem3.height, RAYWHITE);
            DrawText(FormatText("3"), vantagem3.x+35, vantagem3.y+15, 25, BLACK);
            DrawRectangle(vantagem4.x, vantagem4.y, vantagem4.width, vantagem4.height, RAYWHITE);
            DrawText(FormatText("4"), vantagem4.x+35, vantagem4.y+15, 25, BLACK);
            DrawRectangle(vantagem5.x, vantagem5.y, vantagem5.width, vantagem5.height, RAYWHITE);
            DrawText(FormatText("5"), vantagem5.x+35, vantagem5.y+15, 25, BLACK);
            DrawRectangle(vantagem6.x, vantagem6.y, vantagem6.width, vantagem6.height, RAYWHITE);
            DrawText(FormatText("6"), vantagem6.x+35, vantagem6.y+15, 25, BLACK);
            DrawRectangle(vantagem7.x, vantagem7.y, vantagem7.width, vantagem7.height, RAYWHITE);
            DrawText(FormatText("7"), vantagem7.x+35, vantagem7.y+15, 25, BLACK);
            DrawRectangle(vantagem8.x, vantagem8.y, vantagem8.width, vantagem8.height, RAYWHITE);
            DrawText(FormatText("8"), vantagem8.x+35, vantagem8.y+15, 25, BLACK);
            DrawRectangle(vantagem9.x, vantagem9.y, vantagem9.width, vantagem9.height, RAYWHITE);
            DrawText(FormatText("9"), vantagem9.x+35, vantagem9.y+15, 25, BLACK);

            //imprimindo botao de retorno
            DrawRectangle(botaoVoltar.x, botaoVoltar.y, botaoVoltar.width, botaoVoltar.height, RAYWHITE);
            DrawText(FormatText("<"), botaoVoltar.x+16, botaoVoltar.y+8, 40, BLACK);

            //imprimindo efeito de selecao dos botoes de configuração
            for (i=0; i<NUM_BOTOES; i++) {
                if ( configuracoesAtivas[i] ) {
                    DrawRectangleLines(botoes[i].x+5, botoes[i].y+5, botoes[i].width-10, botoes[i].height-10, BLACK);
                }
            }

            //imprimindo efeito de bola branca/preta na ponta do mouse
            if (bolaPreta) DrawCircle( GetMousePosition().x, GetMousePosition().y, 10, BLACK);
            else if (bolaBranca) DrawCircle( GetMousePosition().x, GetMousePosition().y, 10, RAYWHITE);

        EndDrawing();

        if (encerrar) break; //encerrando loop da janela atual
    }

    CloseWindow(); //encerrando janela Configuracoes

    return status; //devolvendo status para o fluxo da main.c

}