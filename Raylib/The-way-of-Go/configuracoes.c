#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define TRUE 1
#define FALSE 0

int config() {
    //constantes da janela Configuracoes
    const int largura = 800;
    const int altura = 700;

    //variaveis da janela Configuracoes
    int bolaPreta = FALSE, bolaBranca = FALSE;
    int status = 1; //status de retorno da janela ao ser fechada (status = menu como padrao)

    //inicializando paineis e botoes do menu

    //inicializando tela e FPS
    InitWindow(largura, altura, "Configuracoes - GO");

    SetTargetFPS(60);

    //lopp principal da janela Configuracoes
    while (!WindowShouldClose()) {
        //Update

        //Draw
        BeginDrawing();
            ClearBackground(BLACK);

            DrawText( FormatText("JANELA DE CONFIGURACOES"), 400, 350, 40, RAYWHITE); //frase teste

            //imprimindo efeito de bola branca/preta na ponta do mouse
            if (bolaPreta) DrawCircle( GetMousePosition().x, GetMousePosition().y, 10, BLACK);
            else if (bolaBranca) DrawCircle( GetMousePosition().x, GetMousePosition().y, 10, RAYWHITE);

        EndDrawing();
    }

    CloseWindow(); //encerrando janela Configuracoes

    return status; //devolvendo status para o fluxo da main.c

}