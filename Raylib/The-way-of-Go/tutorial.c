#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define TRUE 1
#define FALSE 0

int tutorial() {
    //constantes da janela Tutorial
    const int largura = 900;
    const int altura = 700;

    //variaveis da janela Tutorial
    int bolaPreta = FALSE, bolaBranca = FALSE, encerrar = FALSE;
    int status = 1; //status de retorno da janela ao ser fechada (status = menu como padrao)

    //inicializando botao de retorno
    Rectangle botaoVoltar = {820, 20, 50, 50};

    //inicializando tela e FPS
    InitWindow(largura, altura, "Tutorial - GO");

    SetTargetFPS(60);

    //carregando imagens para uso
    Image image1 = LoadImage("Images/go1.png");
    Texture2D texture1 = LoadTextureFromImage(image1);

    Image image2 = LoadImage("Images/go2.png");
    Texture2D texture2 = LoadTextureFromImage(image2);

    Image image3 = LoadImage("Images/go3.png");
    Texture2D texture3 = LoadTextureFromImage(image3);

    UnloadImage(image1);
    UnloadImage(image2);
    UnloadImage(image3);

    //lopp principal da janela Menu
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
            //imprimindo informações sobre o jogo e como jogar
            DrawText(FormatText("About the game: Go, Weiqi or Baduk"), 50, 20, 40, RAYWHITE);

            DrawText(FormatText("It is an abstract strategy board game for two players"), 50, 100, 20, RAYWHITE);
            DrawText(FormatText("in which the aim is to surround more territory than the opponent."), 50, 125, 20, RAYWHITE);
            DrawText(FormatText("The game was invented in China more than 2,500 years ago and is"), 50, 150, 20, RAYWHITE);
            DrawText(FormatText("believed to be the oldest board game continuously played to the present day."), 50, 175, 20, RAYWHITE);

            DrawText(FormatText("The playing pieces are called stones. One player uses the white stones and "), 50, 225, 20, RAYWHITE);
            DrawText(FormatText("and the other, black. The players take turns placing the stones on the "), 50, 250, 20, RAYWHITE);
            DrawText(FormatText("vacant intersections (points) of a board. Once placed on the board, stones "), 50, 275, 20, RAYWHITE);
            DrawText(FormatText("may not be moved, but stones are removed from the board if the stone "), 50, 300, 20, RAYWHITE);
            DrawText(FormatText("(or group of stones) is surrounded by opposing stones on all "), 50, 325, 20, RAYWHITE);
            DrawText(FormatText("orthogonally-adjacent points, in which case the stone is captured."), 50, 350, 20, RAYWHITE);

            DrawText(FormatText("The game proceeds until neither player wishes to make another move."), 50, 400, 20, RAYWHITE);
            DrawText(FormatText("When a game concludes, the winner is determined by counting each player's"), 50, 425, 20, RAYWHITE);
            DrawText(FormatText("surrounded territory along with captured stones and komi (points added to the"), 50, 450, 20, RAYWHITE);
            DrawText(FormatText("score of the player with the white stones as compensation for playing second)."), 50, 475, 20, RAYWHITE);
            DrawText(FormatText("Games may also be terminated by resignation."), 50, 500, 20, RAYWHITE);
            
            //imprimindo imagem carregada como textura
            DrawTexture(texture1, 150, 560, WHITE);
            DrawTexture(texture2, 400, 560, WHITE);
            DrawTexture(texture3, 650, 560, WHITE);

            //imprimindo botao de de retorno
            DrawRectangle(botaoVoltar.x, botaoVoltar.y, botaoVoltar.width, botaoVoltar.height, RAYWHITE);
            DrawText(FormatText("<"), botaoVoltar.x+16, botaoVoltar.y+8, 40, BLACK);

            //imprimindo efeito de bola branca/preta na ponta do mouse
            if (bolaPreta) DrawCircle( GetMousePosition().x, GetMousePosition().y, 10, BLACK);
            else if (bolaBranca) DrawCircle( GetMousePosition().x, GetMousePosition().y, 10, RAYWHITE);

        EndDrawing();

        if (encerrar) break; //encerrando loop da janela atual
    }

    UnloadTexture(texture1);
    UnloadTexture(texture2);
    UnloadTexture(texture3);

    CloseWindow(); //encerrando janela Tutorial

    return status; //devolvendo status para o fluxo da main.c
}
