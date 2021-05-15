#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#define LINHA 7
#define COLUNA 5
#define N 105

/*  MOUSE_LEFT_BUTTON   = 0 e MOUSE_RIGHT_BUTTON  = 1
    KEY_ZERO            = 48, KEY_W               = 87
    KEY_ONE             = 49, KEY_A               = 65,
    KEY_TWO             = 50, KEY_S               = 83,
    KEY_THREE           = 51, KEY_D               = 68,
    KEY_FOUR            = 52,
    KEY_FIVE            = 53,
    KEY_SIX             = 54,
    KEY_SEVEN           = 55,
    KEY_EIGHT           = 56,
    KEY_NINE            = 57,
    
    DARKGRAY, MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, DARKBROWN,
    GRAY, RED, GOLD, LIME, BLUE, VIOLET, BROWN, LIGHTGRAY, PINK, YELLOW,
    GREEN, SKYBLUE, PURPLE, BEIGE!
    
    Legenda da matriz:
    0- sem nota
    1- nota, e dependendo de qual coluna estiver a cor podera ser: VERMELHA, VERDE, AZUL, AMARELO OU ROXO
    Pontuacao:
    50 pontos -> acertou a nota em uma distancia de 1 quadrado antes da area
    100 pontos -> acertou a nota em cima da area
    -50 pontos -> errou/deixou passar uma nota
*/

int main(){
    //constantes do jogo
    const int largura = 900;
    const int altura = 700;
    
    //variaveis do jogo
    int pista[LINHA][COLUNA];
    int i, j, frames = 0, velocidade = 60, inicio = 0, pontuacao = 0;
    char notas[N] = "100000100000100000100000100010001000100010000111111010101010111000010100101101010000101010101010101111111";
    bool okVermelho = false, okVerde = false, okAzul = false, okAmarelo = false, okRoxo = false;
    
    //janelas e botoes do jogo
    Rectangle abaInfo = {0, 0, 200, altura};
    Rectangle abaJogo = {200, 0, 700, altura};
    Rectangle vermelho = {230, 600, 100, 80};
    Rectangle verde = {360, 600, 100, 80};
    Rectangle azul = {500, 600, 100, 80};
    Rectangle amarelo = {640, 600, 100, 80};
    Rectangle roxo = {780, 600, 100, 80};
    
    //setando janela e fps do jogo
    InitWindow(largura, altura, "Guitar Hero");
    SetTargetFPS(60);
    
    //Inicializando a matriz
    for (i=0; i<LINHA; i++){
        for (j=0; j<COLUNA; j++){
            pista[i][j] = 0;
        }
    }
    
    //Loop principal
    while (!WindowShouldClose()){
        //Update do jogo
        
        //atualizando botoes
        okVermelho = false;
        okVerde = false;
        okAzul = false;
        okAmarelo = false;
        okRoxo = false;
        //atualizando a velocidade conforme a pontuacao
        if ( pontuacao >= 500 && pontuacao < 1000) velocidade = 50;
        else if ( pontuacao >= 1000 && pontuacao < 1500) velocidade = 40;
        else if ( pontuacao >= 1500 && pontuacao < 2000) velocidade = 30;
        else if ( pontuacao >= 2500 && pontuacao < 3000) velocidade = 20;
        else if ( pontuacao >= 3000) velocidade = 10;
        //checando toque dos botoes e verificando se acertou alguma nota
        if ( IsKeyPressed(KEY_ONE)) { 
            okVermelho = true;
            if ( pista[6][0] == 1){
                pontuacao += 100; //acertou em cheio
                pista[6][0] = 0; //eliminando nota
            }
            else if ( pista[5][0] == 1){
                pontuacao += 50; //acertou a nota no limite
                pista[5][0] = 0; //eliminando nota
            }
            else pontuacao -= 50;
        }
        if ( IsKeyPressed(KEY_TWO)){
            okVerde = true;
            if ( pista[6][1] == 1){
                pontuacao += 100; //acertou em cheio
                pista[6][1] = 0; //eliminando nota
            }
            else if ( pista[5][1] == 1){
                pontuacao += 50; //acertou a nota no limite
                pista[5][1] = 0; //eliminando nota
            }
            else pontuacao -= 50;
        }
        if ( IsKeyPressed(KEY_THREE)) {
            okAzul = true;
            if ( pista[6][2] == 1){
                pontuacao += 100; //acertou em cheio
                pista[6][2] = 0; //eliminando nota
            }
            else if ( pista[5][2] == 1){
                pontuacao += 50; //acertou a nota no limite
                pista[5][2] = 0; //eliminando nota
            }
            else pontuacao -= 50;
        }
        if ( IsKeyPressed(KEY_FOUR)){
            okAmarelo = true;
            if ( pista[6][3] == 1){
                pontuacao += 100; //acertou em cheio
                pista[6][3] = 0; //eliminando nota
            }
            else if ( pista[5][3] == 1){
                pontuacao += 50; //acertou a nota no limite
                pista[5][3] = 0; //eliminando nota
            }
            else pontuacao -= 50;
        }
        if ( IsKeyPressed(KEY_FIVE)) {
            okRoxo = true;
            if ( pista[6][4] == 1){
                pontuacao += 100; //acertou em cheio
                pista[6][4] = 0; //eliminando nota
            }
            else if ( pista[5][4] == 1){
                pontuacao += 50; //acertou a nota no limite
                pista[5][4] = 0; //eliminando nota
            }
            else pontuacao -= 50;
        }
        //verificando apertos nos botoes e se acertou alguma nota, se sim entao eliminar a nota (distancia de ate 1 quadrado)
        if ( frames%velocidade == 0){
            //movendo as notas da matriz
            for (i=(LINHA-1); i>=0; i--){
                for (j=(COLUNA-1); j>=0; j--){
                    if (pista[i][j] == 1){
                        if ( i == (LINHA-1)){
                            pista[i][j] = 0;
                            pontuacao -= 50; //deixou passar uma nota...
                        }
                        else{
                            pista[i][j] = 0;
                            pista[i+1][j] = 1;
                        }
                    }
                }
            }
            //atualizando a matriz de acordo com a velocidade
            for (i=0; i<LINHA; i++){
                for (j=0; j<COLUNA; j++){
                    //lendo vetor de notas (de 5 em 5) e jogando no inicio da matriz, movendo as ja existentes se necesssario
                    if ( i == 0) pista[i][j] = (notas[inicio+j] - '0'); //convertendo de char para int  
                }
            }
            inicio += 5; //incrementando o inicio da leitura das notas
        }
        if ( inicio == N) inicio = 0; //resetando inicio, voltando ao comeco do vetor de notas
        frames++; //atualizando frames
        //Renderizando o jogo
        BeginDrawing();
            ClearBackground(WHITE);//limpando toda a tela para a cor branca
            //Desenhando janelas
            DrawRectangleRec(abaInfo, DARKGRAY);
            DrawRectangleRec(abaJogo, BLACK);
            //Desenhando placar de pontuacao
            DrawText(FormatText("Pontuacao: %d", pontuacao), 0, 0, 20, BLACK);
            //Desenhando notas circulares de acordo com a matriz pista
            for(i=0; i<LINHA; i++){
                for(j=0; j<COLUNA; j++){
                    if ( pista[i][j] == 1 && j == 0) DrawCircle(280, i*100+50, 40, RED);
                    else if ( pista[i][j] == 1 && j == 1) DrawCircle(410, i*100+50, 40, GREEN);
                    else if ( pista[i][j] == 1 && j == 2) DrawCircle(550, i*100+50, 40, BLUE);
                    else if ( pista[i][j] == 1 && j == 3) DrawCircle(690, i*100+50, 40, YELLOW);
                    else if ( pista[i][j] == 1 && j == 4) DrawCircle(830, i*100+50, 40, PURPLE);
                }
            }
            //Desenhando botoes
            if (okVermelho) DrawRectangleLines(vermelho.x, vermelho.y, vermelho.width, vermelho.height, DARKGRAY);
            else DrawRectangleRec(vermelho, RED);
            if (okVerde) DrawRectangleLines(verde.x, verde.y, verde.width, verde.height, DARKGRAY);
            else DrawRectangleRec(verde, GREEN);
            if (okAzul) DrawRectangleLines(azul.x, azul.y, azul.width, azul.height, DARKGRAY);
            else DrawRectangleRec(azul, BLUE);
            if (okAmarelo) DrawRectangleLines(amarelo.x, amarelo.y, amarelo.width, amarelo.height, DARKGRAY);
            else DrawRectangleRec(amarelo, YELLOW);
            if (okRoxo) DrawRectangleLines(roxo.x, roxo.y, roxo.width, roxo.height, DARKGRAY);
            else DrawRectangleRec(roxo, PURPLE);
            //Faixas divisorias (linhas)
            DrawLine(200, 0, 900, 0, GOLD);
            DrawLine(200, 100, 900, 100, GOLD);
            DrawLine(200, 200, 900, 200, GOLD);
            DrawLine(200, 300, 900, 300, GOLD);
            DrawLine(200, 400, 900, 400, GOLD);
            DrawLine(200, 500, 900, 500, GOLD);
            DrawLine(200, 600, 900, 600, GOLD);
            //Faixas divisorias (colunas)
            DrawLine(230, 0, 230, 600, GOLD);
            DrawLine(330, 0, 330, 600, GOLD);
            DrawLine(360, 0, 360, 600, GOLD);
            DrawLine(460, 0, 460, 600, GOLD);
            DrawLine(500, 0, 500, 600, GOLD);
            DrawLine(600, 0, 600, 600, GOLD);
            DrawLine(640, 0, 640, 600, GOLD);
            DrawLine(740, 0, 740, 600, GOLD);
            DrawLine(780, 0, 780, 600, GOLD);
            DrawLine(880, 0, 880, 600, GOLD);
            
        EndDrawing();
        
    }
    
    CloseWindow(); //encerrando jogo
    
    return 0;
}