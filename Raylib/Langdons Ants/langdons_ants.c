#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

//MOUSE_LEFT_BUTTON   = 0,
//MOUSE_RIGHT_BUTTON  = 1,

int main(void){
    //Constantes do programa
    const int largura = 900; // tem que ser divisivel por 10
    const int altura = 700; // tem que ser divisivel por 10
    int frame = 0; //contador dos frames
    
    Rectangle vermelho = {200, 10, 20, 20}; // aba ativadora da cor VERMELHO
    Rectangle verde = {240, 10, 20, 20}; // aba ativadora da cor VERDE
    char pos = 'w'; // setando a direcao da cabeca da formiga (frente)
    int aleatorio; // variavel aleatoria para decisao de mudanca de cor
    int i, j, linha = (altura/10), coluna = (largura/10), posX = (coluna/2), posY = (linha/2); // onde posX = coluna e posY = linha
    int grade[linha][coluna]; //inicializando matriz contendo a simulacao, onde 0 = PRETO, 1 = BRANCO, 2 = VERMELHO e 3 = VERDE
    for (i=0; i<linha; i++){
        for (j=0; j<coluna; j++){
            grade[i][j] = 0;
        }
    }
    bool okVermelho = false, okVerde = false;
    bool mouseNoVermelho = false, mouseNoVerde = false;
    
    InitWindow(largura, altura, "Langdons Ants!");
    
    SetTargetFPS(60);
    //Loop principal do jogo
    while (!WindowShouldClose()){
        //Update do jogo
        // checando ativacao das cores extras
        if ( CheckCollisionPointRec(GetMousePosition(), vermelho)) mouseNoVermelho = true;
        else if (CheckCollisionPointRec(GetMousePosition(), verde)) mouseNoVerde = true;
        else{
            mouseNoVermelho = false;
            mouseNoVerde = false;
        }
        // caso toque na area de ativacao...
        if (mouseNoVermelho){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !okVermelho) okVermelho = true;
            else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && okVermelho) okVermelho = false;
        }
        else if (mouseNoVerde){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !okVerde) okVerde = true;
            else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && okVerde) okVerde = false;
        }
        //movimentacao da formiga
        frame++;
        aleatorio = GetRandomValue(1, 10);
        if ( frame%1 == 0){
            if ( grade[posY][posX] == 0){
                grade[posY][posX] = 1; // preto --> branco
                if (pos == 'w' && posX - 1 >= 0){
                    posX -= 1; // esquerda com formiga voltada para cima
                    pos = 'a'; // atualizando orientacao da formiga
                }
                else if ( pos == 'a' && posY + 1 < linha){
                    posY += 1; // esquerda com formiga voltada para o lado esquerda
                    pos = 's'; // atualizando orientacao da formiga
                }
                else if ( pos == 's' && posX + 1 < coluna){
                    posX += 1; // esquerda com formiga voltada para baixo
                    pos = 'd'; // atualizando orientacao da formiga
                }
                else if ( pos == 'd' && posY - 1 >= 0){
                    posY -= 1; // esquerda com formiga voltada para o lado direito
                    pos = 'w'; // atualizando orientacao da formiga
                }
            }
            else if ( (grade[posY][posX] == 1 && !okVermelho) || (grade[posY][posX] == 1 && aleatorio%2 == 0)){
                grade[posY][posX] = 0; // branco --> preto
                if (pos == 'w' && posX + 1 < coluna){
                    posX += 1; // direita com formiga voltada para cima
                    pos = 'd'; // atualizando orientacao da formiga
                }
                else if ( pos == 'd' && posY + 1 < linha){
                    posY += 1; // direita com formiga voltada para o lado direito
                    pos = 's'; // atualizando orientacao da formiga
                }
                else if ( pos == 's' && posX - 1 >= 0){
                    posX -= 1; // direita com formiga voltada para baixo
                    pos = 'a'; // atualizando orientacao da formiga
                }
                else if ( pos == 'a' && posY - 1 >= 0){
                    posY -= 1; // direita com formiga voltada para o lado esquerdo
                    pos = 'w'; // atualizando orientacao da formiga
                }
            }
            else if ( grade[posY][posX] == 1 && aleatorio%2 == 1 && okVermelho){
                grade[posY][posX] = 2; // branco --> vermelho
                if (pos == 'w' && posX + 1 < coluna){
                    posX += 1; // direita com formiga voltada para cima
                    pos = 'a'; // atualizando orientacao da formiga
                }
                else if ( pos == 'd' && posY + 1 < linha){
                    posY += 1; // direita com formiga voltada para o lado direito
                    pos = 'w'; // atualizando orientacao da formiga
                }
                else if ( pos == 's' && posX - 1 >= 0){
                    posX -= 1; // direita com formiga voltada para baixo
                    pos = 'd'; // atualizando orientacao da formiga
                }
                else if ( pos == 'a' && posY - 1 >= 0){
                    posY -= 1; // direita com formiga voltada para o lado esquerdo
                    pos = 's'; // atualizando orientacao da formiga
                }
            }
            else if ( (grade[posY][posX] == 2 && !okVerde) || (grade[posY][posX] == 2 && aleatorio%2 == 0)){
                grade[posY][posX] = 1; // vermelho --> branco
                if (pos == 'w' && posX + 1 < coluna){
                    posX += 1; // direita com formiga voltada para cima
                    pos = 'd'; // atualizando orientacao da formiga
                }
                else if ( pos == 'd' && posY + 1 < linha){
                    posY += 1; // direita com formiga voltada para o lado direito
                    pos = 's'; // atualizando orientacao da formiga
                }
                else if ( pos == 's' && posX - 1 >= 0){
                    posX -= 1; // direita com formiga voltada para baixo
                    pos = 'a'; // atualizando orientacao da formiga
                }
                else if ( pos == 'a' && posY - 1 >= 0){
                    posY -= 1; // direita com formiga voltada para o lado esquerdo
                    pos = 'w'; // atualizando orientacao da formiga
                }
            }
            else if ( grade[posY][posX] == 2 && okVerde && aleatorio%2 == 1){
                grade[posY][posX] = 3; // vermelho --> verde
                if (pos == 'w' && posX + 1 < coluna){
                    posX += 1; // direita com formiga voltada para cima
                    pos = 'a'; // atualizando orientacao da formiga
                }
                else if ( pos == 'd' && posY + 1 < linha){
                    posY += 1; // direita com formiga voltada para o lado direito
                    pos = 'w'; // atualizando orientacao da formiga
                }
                else if ( pos == 's' && posX - 1 >= 0){
                    posX -= 1; // direita com formiga voltada para baixo
                    pos = 'd'; // atualizando orientacao da formiga
                }
                else if ( pos == 'a' && posY - 1 >= 0){
                    posY -= 1; // direita com formiga voltada para o lado esquerdo
                    pos = 's'; // atualizando orientacao da formiga
                }
            }
            else if (grade[posY][posX] == 3 && aleatorio%2 == 0){
                grade[posY][posX] = 2; // verde --> vermelho
                if (pos == 'w' && posX + 1 < coluna){
                    posX += 1; // direita com formiga voltada para cima
                    pos = 'd'; // atualizando orientacao da formiga
                }
                else if ( pos == 'd' && posY + 1 < linha){
                    posY += 1; // direita com formiga voltada para o lado direito
                    pos = 's'; // atualizando orientacao da formiga
                }
                else if ( pos == 's' && posX - 1 >= 0){
                    posX -= 1; // direita com formiga voltada para baixo
                    pos = 'a'; // atualizando orientacao da formiga
                }
                else if ( pos == 'a' && posY - 1 >= 0){
                    posY -= 1; // direita com formiga voltada para o lado esquerdo
                    pos = 'w'; // atualizando orientacao da formiga
                }
            }
        }
        //Desenhos do programa
        BeginDrawing();
        
            ClearBackground(WHITE); //limpando toda a tela pela cor branca
               
            //percorrendo matriz e desenhando retangulos (coordenadas multiplas de 10) conforme o valor na matriz
            for (i=0; i< linha; i++){
                for (j=0; j< coluna; j++){
                    if ( grade[i][j] == 0) DrawRectangle(j*10, i*10, 10, 10, BLACK); //retangulos pretos
                    else if ( grade[i][j] == 1) DrawRectangle(j*10, i*10, 10, 10, RAYWHITE); //retangulos brancos
                    else if ( grade[i][j] == 2) DrawRectangle(j*10, i*10, 10, 10, RED); //retangulos vermelhos
                    else if ( grade[i][j] == 3) DrawRectangle(j*10, i*10, 10, 10, GREEN); //retangulos verdes
                }
            }
            DrawText(FormatText("Frames: %d", frame), 10, 10, 20, GREEN);
            //desenho da aba de ativacao da cor vermelha
            if (!okVermelho) DrawRectangleRec(vermelho, RAYWHITE);
            else DrawRectangleRec(vermelho, RED);
            if (mouseNoVermelho) DrawRectangleLines(vermelho.x, vermelho.y, vermelho.width, vermelho.height, BLUE);
            else DrawRectangleLines(vermelho.x, vermelho.y, vermelho.width, vermelho.height, DARKGRAY);
            //desenho da aba de ativacao da cor verde
            if (!okVerde) DrawRectangleRec(verde, RAYWHITE);
            else DrawRectangleRec(verde, GREEN);
            if (mouseNoVerde) DrawRectangleLines(verde.x, verde.y, verde.width, verde.height, BLUE);
            else DrawRectangleLines(verde.x, verde.y, verde.width, verde.height, DARKGRAY);

        EndDrawing();
        
    }
    
    CloseWindow(); //fechando a janela e o OpenGL
    
    return 0;
}