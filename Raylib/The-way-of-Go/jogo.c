#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define TRUE 1
#define FALSE 0

int jogo() {
    //constantes da janela Jogo
    const int largura = 900;
    const int altura = 700;

    //variaveis da janela Jogo
    int encerrar = FALSE;
    int status = 1; //status de retorno da janela ao ser fechada (status = menu como padrao)

    //inicializando botao de retorno
    Rectangle botaoVoltar = {820, 20, 50, 50};

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

            DrawText( FormatText("JANELA DO JOGO DE GO"), 200, 350, 40, RAYWHITE); //frase teste

            //imprimindo botao de de retorno
            DrawRectangle(botaoVoltar.x, botaoVoltar.y, botaoVoltar.width, botaoVoltar.height, RAYWHITE);

        EndDrawing();

        if (encerrar) break; //encerrando loop da janela atual
    }

    CloseWindow(); //encerrando janela Jogo

    return status; //devolvendo status para o fluxo da main.c

}
