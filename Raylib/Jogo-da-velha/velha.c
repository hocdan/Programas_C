#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define LINHAS 3
#define COLUNAS 3
#define TRUE 1
#define FALSE 0

/*
                    Jogo da velha 1.0    

    Um simples jogo da velha utilizando a framework Raylib
    O jogo pode ser resetado e terá um ranking dinamico que
    será resetado toda vez que a aplicação for fechada.
*/

//Variaveis globais
const int largura = 400; // tem que ser divisivel por 10
const int altura = 300; // tem que ser divisivel por 10

int main() {
    //definicao de funcao extra a ser usada
    int deuVelha( int velha[LINHAS][COLUNAS]);

    //variaveis do jogo
    int i, j, valido, vezX = TRUE, vezO = FALSE, vitoriaX = FALSE, vitoriaO = FALSE;
    int alet, jogando = TRUE, empate = FALSE, totalVitoriasX = 0, totalVitoriasO = 0;
    int velha[LINHAS][COLUNAS] = { { 0, 0, 0 },
                                   { 0, 0, 0 },
                                   { 0, 0, 0 } };
    //botao do menu
    Rectangle botaoReset = {20, 180, 60, 40}; //botao na posicao (20, 180) com dimensoes 60x40
    //quadrantes da velha
    Rectangle area1 = {100, 0, 100, 100};
    Rectangle area2 = {200, 0, 100, 100};
    Rectangle area3 = {300, 0, 100, 100};
    Rectangle area4 = {100, 100, 100, 100};
    Rectangle area5 = {200, 100, 100, 100};
    Rectangle area6 = {300, 100, 100, 100};
    Rectangle area7 = {100, 200, 100, 100};
    Rectangle area8 = {200, 200, 100, 100};
    Rectangle area9 = {300, 200, 100, 100};

    //inicializando janela
    InitWindow(largura, altura, "JOGO DA VELHA 1.0");
    SetTargetFPS(60);

    //loop principal
    while (!WindowShouldClose()) {
        //area responsavel pelo update do jogo
        valido = FALSE; //flag para dizer se um movimento foi valido
        //checando toque dos jogadores (X = Player 1 e O = Player 2)
        if ( vezX ) {
            if ( CheckCollisionPointRec( GetMousePosition(), area1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[0][0] == 0) {
                velha[0][0] = 1;
                valido = TRUE;            
            } else if ( CheckCollisionPointRec( GetMousePosition(), area2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[0][1] == 0) {
                velha[0][1] = 1;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[0][2] == 0) {
                velha[0][2] = 1;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[1][0] == 0) {
                velha[1][0] = 1;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area5) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[1][1] == 0) {
                velha[1][1] = 1;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area6) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[1][2] == 0) {
                velha[1][2] = 1;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area7) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[2][0] == 0) {
                velha[2][0] = 1;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area8) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[2][1] == 0) {
                velha[2][1] = 1;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area9) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[2][2] == 0) {
                velha[2][2] = 1;
                valido = TRUE;
            }
            //se X fez uma jogada valida entao é a vez de O
            if (valido) {
                vezX = FALSE;
                vezO = TRUE;
            }
        } else {
            if ( CheckCollisionPointRec( GetMousePosition(), area1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[0][0] == 0) {
                velha[0][0] = 2;
                valido = TRUE;            
            } else if ( CheckCollisionPointRec( GetMousePosition(), area2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[0][1] == 0) {
                velha[0][1] = 2;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[0][2] == 0) {
                velha[0][2] = 2;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[1][0] == 0) {
                velha[1][0] = 2;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area5) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[1][1] == 0) {
                velha[1][1] = 2;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area6) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[1][2] == 0) {
                velha[1][2] = 2;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area7) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[2][0] == 0) {
                velha[2][0] = 2;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area8) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[2][1] == 0) {
                velha[2][1] = 2;
                valido = TRUE;
            } else if ( CheckCollisionPointRec( GetMousePosition(), area9) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && velha[2][2] == 0) {
                velha[2][2] = 2;
                valido = TRUE;
            }
            //se O fez uma jogada valida entao é a vez de X
            if (valido) {
                vezO = FALSE;
                vezX = TRUE;
            }
        }
        //checando se um dos jogadores ganhou...
        if (!vitoriaX && !vitoriaO) {
            if ( (velha[0][0] == 1 && velha[0][1] == 1 && velha[0][2] == 1) ||		// horizontal 1
			     (velha[1][0] == 1 && velha[1][1] == 1 && velha[1][2] == 1) ||		// horizontal 2
			     (velha[2][0] == 1 && velha[2][1] == 1 && velha[2][2] == 1) ||		// horizontal 3
			     (velha[0][0] == 1 && velha[1][0] == 1 && velha[2][0] == 1) ||		// vertical 1
			     (velha[0][1] == 1 && velha[1][1] == 1 && velha[2][1] == 1) ||		// vertical 2
			     (velha[0][2] == 1 && velha[1][2] == 1 && velha[2][2] == 1) ||		// vertical 3
			     (velha[0][0] == 1 && velha[1][1] == 1 && velha[2][2] == 1) ||		// diagonal principal
			     (velha[0][2] == 1 && velha[1][1] == 1 && velha[2][0] == 1) ) {		// diagonal inversa
		     	vitoriaX = TRUE;
                jogando = FALSE;
                totalVitoriasX++;
		    }
		    else if ((velha[0][0] == 2 && velha[0][1] == 2 && velha[0][2] == 2) ||		// horizontal 1
			     	 (velha[1][0] == 2 && velha[1][1] == 2 && velha[1][2] == 2) ||		// horizontal 2
				     (velha[2][0] == 2 && velha[2][1] == 2 && velha[2][2] == 2) ||		// horizontal 3
				     (velha[0][0] == 2 && velha[1][0] == 2 && velha[2][0] == 2) ||		// vertical 1
				     (velha[0][1] == 2 && velha[1][1] == 2 && velha[2][1] == 2) ||		// vertical 2
				     (velha[0][2] == 2 && velha[1][2] == 2 && velha[2][2] == 2) ||		// vertical 3
				     (velha[0][0] == 2 && velha[1][1] == 2 && velha[2][2] == 2) ||		// diagonal principal
				     (velha[0][2] == 2 && velha[1][1] == 2 && velha[2][0] == 2) ) {		// diagonal inversa
			     	vitoriaO = TRUE;
                    jogando = FALSE;
                    totalVitoriasO++;
		    }
            else if ( deuVelha(velha) ) {
                empate = TRUE;
                jogando = FALSE;            
            }
        }
        //checando se o botao RESET foi pressionado
        if ( CheckCollisionPointRec( GetMousePosition(), botaoReset) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !jogando) {
            for (i=0; i<LINHAS; i++) {
                for (j=0; j<COLUNAS; j++) {
                    velha[i][j] = 0; //limpando quadrante da velha        
                }
            }
            //resetando flags
            if (vitoriaX) {
                vezO = TRUE;
                vezX = FALSE;            
            } else if (vitoriaO){
                vezX = TRUE;
                vezO = FALSE;
            } else {
                //aleatoriamente escolhe um dos jogadores para comecar (50%-50%)
                alet = GetRandomValue(1, 10);
                if (alet%2 == 0) {
                    vezX = TRUE;
                    vezO = FALSE;
                } else {
                    vezO = TRUE;
                    vezX = FALSE;
                }            
            }
            vitoriaX = FALSE;
            vitoriaO = FALSE;
            jogando = TRUE;
        }

        //area responsavel pelo desenho do jogo
        BeginDrawing();

            ClearBackground(BLACK);
            
            DrawRectangle( 0, 0, 100, altura, DARKGRAY); //aba que contem as informacoes
            
            //imprimindo informacoes na aba
            DrawText(FormatText("STATUS"), 8, 8, 18, BLACK); //titulo do jogo
            if ( vezX ) {
                DrawText(FormatText("TURNO: P1"), 8, 40, 15, BLACK); //turno do jogador X
            } else {
                DrawText(FormatText("TURNO: P2"), 8, 40, 15, BLACK); //turno do jogador O
            }
            DrawText(FormatText("VITORIAS"), 5, 90, 18, BLACK); //total de vitorias
            DrawText(FormatText("Player 1:  %d", totalVitoriasX), 5, 120, 15, BLACK); //total de vitorias do X
            DrawText(FormatText("Player 2: %d", totalVitoriasO), 5, 140, 15, BLACK); //total de vitorias do O
            //desenhando botao de reset
            if (jogando) {
                DrawRectangleRec(botaoReset, DARKGRAY);
            } else {
                DrawRectangleRec(botaoReset, RED);           
            }
            DrawRectangleLines(botaoReset.x, botaoReset.y, botaoReset.width, botaoReset.height, BLACK);
            DrawText(FormatText("RESET"), botaoReset.x+5, botaoReset.y+15, 15, BLACK);
            //desenhando cruzada do jogo da velha (se estiverem jogando)
            if (jogando) {
                for (i=1; i<=LINHAS; i++) {
                    for (j=1; j<=COLUNAS; j++) {
                        //desenhando quadrados da cruzada
                        DrawRectangle(j*100, (i-1)*100, 100, 100, RAYWHITE);
                        //desenhando conteudo da matriz (1-X, 2-O)
                        if ( velha[i-1][j-1] == 1) {
                            DrawLine(j*100+20, (i-1)*100+20, j*100+80, (i-1)*100+80, BLACK);
                            DrawLine(j*100+80, (i-1)*100+20, j*100+20, (i-1)*100+80, BLACK);
                        } else if ( velha[i-1][j-1] == 2) {
                            DrawCircleLines(j*100+50, (i-1)*100+50, 30, BLACK);
                        }               
                    }            
                }
                //desenhando divisorias da cruzada
                DrawLine(200, 10, 200, altura-10, BLACK); //primeira linha vertical
                DrawLine(300, 10, 300, altura-10, BLACK); //segunda linha vertical
                DrawLine(110, 100, largura-10, 100, BLACK); //primeira linha horizontal
                DrawLine(110, 200, largura-10, 200, BLACK); //segunda linha horizontal
            } else {
                //imprimindo vitoria do jogador X
                if (vitoriaX) DrawText(FormatText("VITORIA DO JOGADOR 1 !"), 120, 130, 20, GREEN);
                //imprimindo vitoria do jogador O
                else if (vitoriaO) DrawText(FormatText("VITORIA DO JOGADOR 2 !"), 120, 130, 20, GREEN);
                //imprimindo quando der velha
                else if (empate) DrawText(FormatText("DEU VELHA !"), 175, 130, 20, GREEN);            
            }
        //finalizando renderizacao do jogo
        EndDrawing();    

    }

    CloseWindow(); //encerrando jogo

    return 0;
}

int deuVelha( int velha[LINHAS][COLUNAS]) {
    //verificando se o jogo deu velha (empacou)
    int i, j, empacou = TRUE;
    
    for (i=0; i<LINHAS; i++) {
        for (j=0; j<COLUNAS; j++) {
            if (velha[i][j] == 0) empacou = FALSE;    
        }
    }

    return empacou;
}

