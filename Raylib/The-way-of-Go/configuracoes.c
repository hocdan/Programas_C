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

        //Draw
        BeginDrawing();
            ClearBackground(BLACK);

            DrawText( FormatText("JANELA DE CONFIGURACOES"), 200, 350, 40, RAYWHITE); //frase teste

            //imprimindo botao de de retorno
            DrawRectangle(botaoVoltar.x, botaoVoltar.y, botaoVoltar.width, botaoVoltar.height, RAYWHITE);

            //imprimindo efeito de bola branca/preta na ponta do mouse
            if (bolaPreta) DrawCircle( GetMousePosition().x, GetMousePosition().y, 10, BLACK);
            else if (bolaBranca) DrawCircle( GetMousePosition().x, GetMousePosition().y, 10, RAYWHITE);

        EndDrawing();

        if (encerrar) break; //encerrando loop da janela atual
    }

    CloseWindow(); //encerrando janela Configuracoes

    return status; //devolvendo status para o fluxo da main.c

}
