#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define TRUE 1
#define FALSE 0

int menu() {
    //constantes da janela Menu
    const int largura = 800;
    const int altura = 700;

    //variaveis da janela Menu
    int bolaPreta = FALSE, bolaBranca = FALSE, encerrar = FALSE;
    int status = 0; //status de retorno da janela ao ser fechada (status = encerrar como padrao)

    //inicializando paineis e botoes do menu
    Rectangle botaoTutorial = {300, 270, 200, 100};
    Rectangle botaoJogar = {300, 390, 200, 100};
    Rectangle botaoConfig = {300, 510, 200, 100};
    Rectangle botaoSair = {300, 630, 200, 100};

    //inicializando tela e FPS
    InitWindow(largura, altura, "Menu - GO");

    SetTargetFPS(60);

    //lopp principal da janela Menu
    while (!WindowShouldClose()) {
        //Update
        
        //realizando checagem de toque para efeito de bola branca/preta na ponta do mouse
        if ( CheckCollisionPointRec( GetMousePosition(), botaoTutorial) || 
        CheckCollisionPointRec( GetMousePosition(), botaoJogar) ||
        CheckCollisionPointRec( GetMousePosition(), botaoConfig) ) {
            bolaPreta = TRUE;
            bolaBranca = FALSE;
        } else {
            bolaPreta = FALSE;
            bolaBranca = TRUE;
        }
        
        //checando por toques nos botoes
        if ( CheckCollisionPointRec( GetMousePosition(), botaoTutorial) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            status = 2; //status = abrir janela tutorial
            encerrar = TRUE;
        }
        else if ( CheckCollisionPointRec( GetMousePosition(), botaoJogar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            status = 3; //status = abrir janela Jogo
            encerrar = TRUE;
        }
        else if ( CheckCollisionPointRec( GetMousePosition(), botaoConfig) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            status = 4; //status = abrir janela Configuracoes
            encerrar = TRUE;
        }

        //Draw
        BeginDrawing();
            ClearBackground(BLACK);
            
            //imprimindo menu
            DrawText(FormatText("THE WAY OF GO"), 238, 100, 40, RAYWHITE);

            DrawRectangle(botaoTutorial.x, botaoTutorial.y, botaoTutorial.width, botaoTutorial.height, RAYWHITE);
            DrawRectangleLines(botaoTutorial.x+15, botaoTutorial.y+15, botaoTutorial.width-30, botaoTutorial.height-30, BLACK);
            DrawText(FormatText("How to play"), botaoTutorial.x+40, botaoTutorial.y+40, 20, BLACK);

            DrawRectangle(botaoJogar.x, botaoJogar.y, botaoJogar.width, botaoJogar.height, RAYWHITE);
            DrawRectangleLines(botaoJogar.x+15, botaoJogar.y+15, botaoJogar.width-30, botaoJogar.height-30, BLACK);
            DrawText(FormatText("Play"), botaoJogar.x+80, botaoJogar.y+40, 20, BLACK);

            DrawRectangle(botaoConfig.x, botaoConfig.y, botaoConfig.width, botaoConfig.height, RAYWHITE);
            DrawRectangleLines(botaoConfig.x+15, botaoConfig.y+15, botaoConfig.width-30, botaoConfig.height-30, BLACK);
            DrawText(FormatText("Configurations"), botaoConfig.x+28, botaoConfig.y+40, 20, BLACK);

            //imprimindo efeito de bola branca/preta na ponta do mouse
            if (bolaPreta) DrawCircle( GetMousePosition().x, GetMousePosition().y, 10, BLACK);
            else if (bolaBranca) DrawCircle( GetMousePosition().x, GetMousePosition().y, 10, RAYWHITE);

        EndDrawing();

        if (encerrar) break; //encerrando loop da janela atual
    }

    CloseWindow(); //encerrando janela Menu

    return status; //devolvendo status para o fluxo da main.c
}