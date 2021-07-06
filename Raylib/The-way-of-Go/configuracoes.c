#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define TRUE 1
#define FALSE 0

int config() {
    //constantes da janela Configuracoes
    const int largura = 900;
    const int altura = 700;

    //variaveis da janela Configuracoes
    int bolaPreta = FALSE, bolaBranca = FALSE, encerrar = FALSE;
    int status = 1; //status de retorno da janela ao ser fechada (status = menu como padrao)

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

    //inicializando tela e FPS
    InitWindow(largura, altura, "Configuracoes - GO");

    SetTargetFPS(60);

    //lopp principal da janela Configuracoes
    while (!WindowShouldClose()) {
        //Update

        //verificando toque no botao de retornar
        if ( CheckCollisionPointRec( GetMousePosition(), botaoVoltar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            status = 1; //status = abrir janela Menu
            encerrar = TRUE;
        }
        //verificando toques nos botoes de configuracoes
        

        //Draw
        BeginDrawing();
            ClearBackground(BLACK);

            //imprimindo opcoes de configuracoes
            DrawText(FormatText("JANELA DE CONFIGURACOES"), 120, 25, 40, RAYWHITE);

            DrawText(FormatText("-> Change screen size:"), 50, 180, 30, RAYWHITE);
            DrawRectangle(tela1.x, tela1.y, tela1.width, tela1.height, RAYWHITE);
            DrawRectangle(tela2.x, tela2.y, tela2.width, tela2.height, RAYWHITE);
            DrawRectangle(tela3.x, tela3.y, tela3.width, tela3.height, RAYWHITE);

            DrawText(FormatText("-> Sound: "), 50, 300, 30, RAYWHITE);
            DrawRectangle(somOn.x, somOn.y, somOn.width, somOn.height, RAYWHITE);
            DrawRectangle(somOff.x, somOff.y, somOff.width, somOff.height, RAYWHITE);

            DrawText(FormatText("-> Board Size: "), 50, 420, 30, RAYWHITE);
            DrawRectangle(tabuleiro1.x, tabuleiro1.y, tabuleiro1.width, tabuleiro1.height, RAYWHITE);
            DrawRectangle(tabuleiro2.x, tabuleiro2.y, tabuleiro2.width, tabuleiro2.height, RAYWHITE);
            DrawRectangle(tabuleiro3.x, tabuleiro3.y, tabuleiro3.width, tabuleiro3.height, RAYWHITE);

            DrawText(FormatText("-> White Handicap: "), 50, 540, 30, RAYWHITE);
            DrawRectangle(vantagem0.x, vantagem0.y, vantagem0.width, vantagem0.height, RAYWHITE);
            DrawRectangle(vantagem1.x, vantagem1.y, vantagem1.width, vantagem1.height, RAYWHITE);
            DrawRectangle(vantagem2.x, vantagem2.y, vantagem2.width, vantagem2.height, RAYWHITE);
            DrawRectangle(vantagem3.x, vantagem3.y, vantagem3.width, vantagem3.height, RAYWHITE);
            DrawRectangle(vantagem4.x, vantagem4.y, vantagem4.width, vantagem4.height, RAYWHITE);
            DrawRectangle(vantagem5.x, vantagem5.y, vantagem5.width, vantagem5.height, RAYWHITE);
            DrawRectangle(vantagem6.x, vantagem6.y, vantagem6.width, vantagem6.height, RAYWHITE);
            DrawRectangle(vantagem7.x, vantagem7.y, vantagem7.width, vantagem7.height, RAYWHITE);
            DrawRectangle(vantagem8.x, vantagem8.y, vantagem8.width, vantagem8.height, RAYWHITE);
            DrawRectangle(vantagem9.x, vantagem9.y, vantagem9.width, vantagem9.height, RAYWHITE);

            //imprimindo botao de retorno
            DrawRectangle(botaoVoltar.x, botaoVoltar.y, botaoVoltar.width, botaoVoltar.height, RAYWHITE);
            DrawText(FormatText("<"), botaoVoltar.x+16, botaoVoltar.y+8, 40, BLACK);

            //imprimindo efeito de bola branca/preta na ponta do mouse
            if (bolaPreta) DrawCircle( GetMousePosition().x, GetMousePosition().y, 10, BLACK);
            else if (bolaBranca) DrawCircle( GetMousePosition().x, GetMousePosition().y, 10, RAYWHITE);

        EndDrawing();

        if (encerrar) break; //encerrando loop da janela atual
    }

    CloseWindow(); //encerrando janela Configuracoes

    return status; //devolvendo status para o fluxo da main.c

}
