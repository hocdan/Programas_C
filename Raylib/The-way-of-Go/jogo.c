#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define TRUE 1
#define FALSE 0

int jogo() {
    //constantes da janela Jogo
    const int largura = 800;
    const int altura = 700;

    //variaveis da janela Jogo
    int bolaPreta = FALSE, bolaBranca = FALSE;
    int status = 0; //status de retorno da janela ao ser fechada (status = encerrar como padrao)

    //inicializando tela e FPS
    InitWindow(largura, altura, "Jogo - GO");

    SetTargetFPS(60);

    //lopp principal da janela Jogo
    while (!WindowShouldClose()) {
        //Update


        //Draw
        BeginDrawing();
            ClearBackground(BLACK);

            DrawText( FormatText("JANELA DO JOGO DE GO"), 400, 350, 40, RAYWHITE); //frase teste

        EndDrawing();
    }

    CloseWindow(); //encerrando janela Jogo

    return status; //devolvendo status para o fluxo da main.c

}