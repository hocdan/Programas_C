#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#define LINHAS 31
#define COLUNAS 28
#define TRUE 1
#define FALSE 0

/*
        OBSERVACAO: POSSIVEL LOGICA PARA SOLUCIONAR BUG DO DESENCONTRO FANTASMA

        -> modificar a funcao movimentar() do jogador para que a checagem de colisoes com outros itens seja
        independente e chamada a cada frame (ou multiplos do frame dos fantasmas e do pacman).
*/

/*  MOUSE_LEFT_BUTTON   = 0 e MOUSE_RIGHT_BUTTON  = 1
    KEY_ZERO            = 48, KEY_W               = 87
    KEY_ONE             = 49, KEY_A               = 65,
    KEY_TWO             = 50, KEY_S               = 83,
    KEY_THREE           = 51, KEY_D               = 68,
    KEY_FOUR            = 52, KEY_R               = 82,
    KEY_FIVE            = 53, KEY_RIGHT           = 262,
    KEY_SIX             = 54, KEY_LEFT            = 263,
    KEY_SEVEN           = 55, KEY_DOWN            = 264,
    KEY_EIGHT           = 56, KEY_UP              = 265,
    KEY_NINE            = 57,
    
    DARKGRAY, MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, DARKBROWN,
    GRAY, RED, GOLD, LIME, BLUE, VIOLET, BROWN, LIGHTGRAY, PINK, YELLOW,
    GREEN, SKYBLUE, PURPLE, BEIGE!
    
    OBS: legenda da matriz
    0- vazio
    1- parede
    2- moeda pequena
    3- moeda grande
    4- jogador
    5- fantasma vermelho
    6- fantasma rosa
    7- fantasma azul
    8- fantasma laranja
    
*/

//struct responsavel pelos dados do jogador
typedef struct Jogador{
    int vidas; //vidas do jogador (3 vidas, perde uma quando eh pego por um fantasma)
    int pontuacao; //pontuacao do jogador (10-moeda pequena, 100-moeda grande e 500-fantasma)
    int linha; //posicao nas linhas da matriz
    int coluna; //posicao nas colunas da matriz
    int bocaAberta; //TRUE ou FALSE (spawna com a boca aberta)
    char direcao; // W-CIMA, A-ESQUERDA, S-BAIXO, D-DIREITA (spawna na direcao da esquerda)
}Jogador;

//struct responsavel pelos dados do fantasma
typedef struct Fantasma{
    char rota[151]; //string contendo a rota do fantasma
    int tipo; //5-vermelho, 6-rosa, 7-azul, 8-laranja
    int linha; //posicao nas linhas da matriz
    int coluna; //posicao nas colunas da matriz
    int liberado; //TRUE ou FALSE (fantasma so pode se mover quando for verdadeiro/quando for a hora)
    int vulneravel; //TRUE ou FALSE (apenas verdadeiro quando o pacman come uma moeda grande)
    int temp; //usada para armazenar o valor anterior ao fantasma no local da matriz
}Fantasma;

int main(){
    //prototipos das funcoes a serem utilizadas no jogo
    void movimentar( int grade[LINHAS][COLUNAS], Fantasma *fantasmas, Jogador *pacman, char direcao, int *intimidar);
    void moverFantasmas(int grade[LINHAS][COLUNAS], Fantasma *fantasmas, Jogador *pacman);
    void limparGrade(int grade[LINHAS][COLUNAS], Fantasma *fantasmas);
    int checarVitoria(int grade[LINHAS][COLUNAS]);
    
    //constantes do jogo
    const int largura = 630;
    const int altura = 730;
    
    //inicializando jogador
    Jogador pacman = {3, 0, 23, 13, TRUE, 'a'};
    
    //inicializando vetor de fantasmas
    Fantasma fantasmas[4] = { {"", 5, 14, 12, FALSE, FALSE, 0},
                              {"", 6, 14, 13, FALSE, FALSE, 0},
                              {"", 7, 14, 14, FALSE, FALSE, 0},
                              {"", 8, 14, 15, FALSE, FALSE, 0} };
    
    //variaveis do jogo
    int i, j, alet, frames = 0, intimidar = FALSE, jogando = TRUE;
    int grade[LINHAS][COLUNAS] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
                                   1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1,
                                   1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 3, 1,
                                   1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1,
                                   1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 3, 2, 2, 2, 2, 2, 1,
                                   1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1,
                                   1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1,
                                   1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1,
                                   1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,
                                   0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0,
                                   1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1,
                                   0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
                                   1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1,
                                   0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0,
                                   1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1,
                                   1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
                                   1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1,
                                   1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1,
                                   1, 3, 2, 2, 1, 1, 2, 2, 2, 2, 2, 3, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 3, 1,
                                   1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1,
                                   1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1,
                                   1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1,
                                   1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,
                                   1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,
                                   1, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 1,
                                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    
    //Iniciando tela e FPS
    InitWindow( largura, altura, "Pacman");
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()){
        //Update do jogo (enquanto o pacman estiver vivo...)
        if ( pacman.vidas > 0){
            frames++; //atualizando frames
            limparGrade(grade, fantasmas); //limpando "lixo" da grade
            //liberando fantasmas, se possivel (intervalo de 5 segundos)
            //ao se passar 5 segundos..., liberar o fantasma vermelho
            if ( frames%300 == 0 && fantasmas[0].liberado == FALSE){
                //liberando fantasma para se movimentar...
                fantasmas[0].liberado = TRUE;
                //escolhendo uma das 3 rotas disponiveis pro fantasma de maneira aleatoria
                alet = GetRandomValue(1, 3);
                if (alet == 1) strcpy(fantasmas[0].rota, "wdwwaaaasssaaasssssssssdddddddddddddddwwwwwwwwwwwwwwwwwwaaasssaaasssaassas"); //74 chars
                else if (alet == 2) strcpy(fantasmas[0].rota, "wdwwawwwaaawwwaaaaaaaawwwwdddddddddddssssdddwwwwdddddddddddsssssssaaaaawwwaaasssaaasssaassas"); //97 chars
                else if (alet == 3) strcpy(fantasmas[0].rota, "wdwwdddddsssdddsssssssssaaaaaaaaaaaaaaawwwwwwwwwdddwwwddddssas"); //62 chars
            }
            else if ( frames%600 == 0 && fantasmas[1].liberado == FALSE){
                //liberando fantasma para se movimentar...
                fantasmas[1].liberado = TRUE;
                //escolhendo uma das 3 rotas disponiveis pro fantasma de maneira aleatoria
                alet = GetRandomValue(1, 3);
                if (alet == 1) strcpy(fantasmas[1].rota, "wwwaaaasssssssssdddsssdddwwwdddwwwwwwwwwaaawwwdddwwwaaaaaaaaasssdddsssdsss"); //74 chars
                else if (alet == 2) strcpy(fantasmas[1].rota, "wwwaaaasssaaawwwwwwaaaaawwwwwwwdddddddddddssssdddwwwwdddddddddddsssssssaaaaawwwaaasssaaasssassas"); //100 chars
                else if (alet == 3) strcpy(fantasmas[1].rota, "wwwaaaasssaaassssssssssssaaawwwaawwwdddddddddddsssdddddddddsssdddwwwddwwwaaaaawwwwwwaaawwwaaaassas"); //102 chars
            }
            else if ( frames%900 == 0 && fantasmas[2].liberado == FALSE){
                //liberando fantasma para se movimentar...
                fantasmas[2].liberado = TRUE;
                //escolhendo uma das 3 rotas disponiveis pro fantasma de maneira aleatoria
                alet = GetRandomValue(1, 3);
                if (alet == 1) strcpy(fantasmas[2].rota, "wwwddddsssdddwwwwwwwwwaaaaaaaaaaaaaaasssssssssdddwwwddddssds"); //60 chars
                else if (alet == 2) strcpy(fantasmas[2].rota, "wawwaaaasssssssssaaassssssaaaaasssdddddddddddddddddddddddddwwwaaaaawwwwwwaaawwwwwwwwwaaaasss"); //97 chars
                else if (alet == 3) strcpy(fantasmas[2].rota, "wwwddddssssssaaaaaaaaawwwwwwddddsssd"); //36 chars
            }
            else if ( frames%1200 == 0 && fantasmas[3].liberado == FALSE){
                //liberando fantasma para se movimentar...
                fantasmas[3].liberado = TRUE;
                //escolhendo uma das 3 rotas disponiveis pro fantasma de maneira aleatoria
                alet = GetRandomValue(1, 3);
                if (alet == 1) strcpy(fantasmas[3].rota, "wawwddddsssssssssaaasssdddsssaaasssaaawwwaaawwwdddwwwaaawwwwwwwwwddddsssdd"); //74 chars
                else if (alet == 2) strcpy(fantasmas[3].rota, "wawwaaaaasssssssssaaassssssaaaaasssdddddddddddddddddddddddddwwwaaaaawwwwwwaaawwwwwwwwwaaaasssd"); //98 chars
                else if (alet == 3) strcpy(fantasmas[3].rota, "wawwdwwwdddwwwddddddddsssaaaaassssssssssssdddddsssaasssaaawwwaaaaaaaaaaaaaaasssaaawwwaawwwdddddwwwwwwwwwwwwaaaaawwwddddddddsssdddsssddssds"); //143 chars
            }
        
            //verificando jogador e fantasmas liberados a cada 5 vezes por segundo
            if (frames%12 == 0){
                //verificando se o jogador moveu o pacman atravez das setas ou teclas WASD
                if ( IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) ) movimentar(grade, fantasmas, &pacman, 'w', &intimidar);
                else if ( IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ) movimentar(grade, fantasmas, &pacman, 'a', &intimidar);
                else if ( IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ) movimentar(grade, fantasmas, &pacman, 's', &intimidar);
                else if ( IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ) movimentar(grade, fantasmas, &pacman, 'd', &intimidar);
            }
            if (frames%6 == 0){
                //movendo fantasmas (aqueles que ja foram liberados)
                moverFantasmas(grade, fantasmas, &pacman);
            }
            
            //verificando se o jogador comeu uma moeda grande, se sim entao fantasmas ficarao vulneraveis por 5 segundos
            if ( intimidar > 0){
                intimidar--; //decrementando efeito, pois ira acabar com o tempo
                //alterando status dos fantasmas para vulneraveis
                for (i=0; i<4; i++){
                    if ( fantasmas[i].liberado == TRUE) fantasmas[i].vulneravel = TRUE;
                }
            }
            else{
                //alterando status dos fantasmas para vulneraveis
                for (i=0; i<4; i++){
                    if ( fantasmas[i].liberado == TRUE) fantasmas[i].vulneravel = FALSE;
                }
            }
        }
        else jogando = FALSE; //encerrando jogo, pois pacman morreu
        //Desenho do jogo
        BeginDrawing();
            ClearBackground(BLACK); //limpando todo fundo da tela para preto
            //verificando se o jogador ganhou o jogo
            if (checarVitoria(grade)){
                DrawText(FormatText("YOU WIN!"), 220, 355, 40, WHITE);
                DrawText(FormatText("FINAL SCORE: %d pts", pacman.pontuacao), 80, 455, 40, WHITE);
                jogando = FALSE;
                
            }
            if ( jogando){
                //Desenhando grade do jogo
                for (i=0; i<LINHAS; i++){
                    for (j=0; j<COLUNAS; j++){
                        if ( grade[i][j] == 0 ) DrawRectangle(30 + j*20, 60 + i*20, 20, 20, BLACK);
                        else if ( grade[i][j] == 1 ) DrawRectangle(30 + j*20, 60 + i*20, 20, 20, DARKBLUE);
                        else if ( grade[i][j] == 2 ) DrawCircle( 30 + j*20 + 10, 60 + i*20 + 10, 3, YELLOW);
                        else if ( grade[i][j] == 3 ) DrawCircle( 30 + j*20 + 10, 60 + i*20 + 10, 7, ORANGE);
                        else if ( grade[i][j] == 4 ) {
                            //Desenhando pacman com boca aberta
                            if ( pacman.bocaAberta){
                                DrawCircle( 30 + j*20 + 10, 60 + i*20 + 10, 7, YELLOW);
                                //desenhando boca do pacman de acordo com a direcao que ela esta voltada
                                if ( pacman.direcao == 'w'){
                                    DrawTriangle((Vector2){30+j*20,    60+i*20},
                                                 (Vector2){30+j*20+10, 60+i*20+10},
                                                 (Vector2){30+j*20+20, 60+i*20}, BLACK);
                                }
                                else if ( pacman.direcao == 'a'){
                                    DrawTriangle((Vector2){30+j*20,    60+i*20}, 
                                                 (Vector2){30+j*20,    60+i*20+20},
                                                 (Vector2){30+j*20+10, 60+i*20+10}, BLACK);
                                }
                                else if ( pacman.direcao == 's'){
                                    DrawTriangle((Vector2){30+j*20,    60+i*20+20}, 
                                                 (Vector2){30+j*20+20, 60+i*20+20},
                                                 (Vector2){30+j*20+10, 60+i*20+10}, BLACK);
                                }
                                else if ( pacman.direcao == 'd'){
                                    DrawTriangle((Vector2){30+j*20+10, 60+i*20+10}, 
                                                 (Vector2){30+j*20+20, 60+i*20+20},
                                                 (Vector2){30+j*20+20, 60+i*20}, BLACK);
                                }
                            }
                            //Desenhando pacman de boca fechada
                            else DrawCircle( 30 + j*20 + 10, 60 + i*20 + 10, 7, YELLOW);
                        }
                        else if ( grade[i][j] == 5 && fantasmas[0].vulneravel == FALSE) DrawRectangle(30 + j*20 + 5, 60 + i*20, 10, 20, RED);
                        else if ( grade[i][j] == 5 && fantasmas[0].vulneravel == TRUE) {
                            //simulando efeito de piscar azul e branco
                            if ( frames%2 == 0) DrawRectangle(30 + j*20 + 5, 60 + i*20, 10, 20, BLUE);
                            else DrawRectangle(30 + j*20 + 5, 60 + i*20, 10, 20, WHITE);
                        }
                        else if ( grade[i][j] == 6 && fantasmas[0].vulneravel == FALSE) DrawRectangle(30 + j*20 + 5, 60 + i*20, 10, 20, PINK);
                        else if ( grade[i][j] == 6 && fantasmas[0].vulneravel == TRUE) {
                            //simulando efeito de piscar azul e branco
                            if ( frames%2 == 0) DrawRectangle(30 + j*20 + 5, 60 + i*20, 10, 20, BLUE);
                            else DrawRectangle(30 + j*20 + 5, 60 + i*20, 10, 20, WHITE);
                        }
                        else if ( grade[i][j] == 7 && fantasmas[0].vulneravel == FALSE) DrawRectangle(30 + j*20 + 5, 60 + i*20, 10, 20, SKYBLUE);
                        else if ( grade[i][j] == 7 && fantasmas[0].vulneravel == TRUE) {
                            //simulando efeito de piscar azul e branco
                            if ( frames%2 == 0) DrawRectangle(30 + j*20 + 5, 60 + i*20, 10, 20, BLUE);
                            else DrawRectangle(30 + j*20 + 5, 60 + i*20, 10, 20, WHITE);
                        }
                        else if ( grade[i][j] == 8 && fantasmas[0].vulneravel == FALSE) DrawRectangle(30 + j*20 + 5, 60 + i*20, 10, 20, ORANGE);
                        else if ( grade[i][j] == 8 && fantasmas[0].vulneravel == TRUE) {
                            //simulando efeito de piscar azul e branco
                            if ( frames%2 == 0) DrawRectangle(30 + j*20 + 5, 60 + i*20, 10, 20, BLUE);
                            else DrawRectangle(30 + j*20 + 5, 60 + i*20, 10, 20, WHITE);
                        }

                    }
                }
                //Desenhando informacoes do jogo
                DrawText(FormatText("1 UP"), 100, 10, 20, WHITE);
                DrawText(FormatText("%d", pacman.pontuacao), 120, 30, 20, WHITE);
                DrawText(FormatText("HIGH SCORE"), 300, 10, 20, WHITE);
                DrawText(FormatText("%d", pacman.pontuacao), 320, 30, 20, WHITE);
                //Desenhando icones de vidas
                for (i=0; i<pacman.vidas; i++){
                    DrawCircle( 30 + i*20 + 20, altura-30, 7, YELLOW);
                    DrawTriangle((Vector2){30+i*20+10,    altura-40}, 
                                 (Vector2){30+i*20+10,    altura-20},
                                 (Vector2){30+i*20+20, altura-30}, BLACK);
                }
            }
            //mostrando tela de GAME OVER
            else if (pacman.vidas <= 0){
                DrawText(FormatText("GAME OVER"), 195, 355, 40, WHITE);
            }
  
        EndDrawing();
        
    }
    
    CloseWindow(); //finalizando aplicacao
    
    return 0;
}
//funcao responsavel por checar se todas as moedas foram comidas
int checarVitoria(int grade[LINHAS][COLUNAS]){
    int i, j;
    //percorrendo matriz e verificando se ha alguma moeda sobrando...
    for (i=0; i<LINHAS; i++){
        for (j=0; j<COLUNAS; j++){
            if ( grade[i][j] == 2 || grade[i][j] == 3) return FALSE;
        }
    }
    return TRUE;
    
}

//funcao responsavel por movimentar o pacman
void movimentar( int grade[LINHAS][COLUNAS], Fantasma *fantasmas, Jogador *pacman, char direcao, int *intimidar){
    //Verificando coordenadas atuais do pacman, sua direcao futura e se o movimento eh valido...
    int linha = pacman->linha;
    int coluna = pacman->coluna;
    int index;
    
    if ( direcao == 'w'){
        if ( (linha-1) >= 0 && grade[linha-1][coluna] != 1){
            //checando se o pacman comeu alguma moeda...
            if ( grade[linha-1][coluna] == 2) pacman->pontuacao += 10;
            else if ( grade[linha-1][coluna] == 3) {
                pacman->pontuacao += 100;
                *intimidar = 420; //equivale a 7 segundos de efeito
            }
            //ou fantasma ao mover...
            else if ( grade[linha-1][coluna] > 0){
                pacman->pontuacao += 1000;
                //achando index do vetor, ou seja, qual fantasma foi comido
                index = (grade[linha-1][coluna] - 5);
                if (fantasmas[index].tipo == 5){
                    fantasmas[0].linha = 14;
                    fantasmas[0].coluna = 12;
                    fantasmas[0].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
                else if (fantasmas[index].tipo == 5){
                    fantasmas[1].linha = 14;
                    fantasmas[1].coluna = 13;
                    fantasmas[1].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
                else if (fantasmas[index].tipo == 5){
                    fantasmas[2].linha = 14;
                    fantasmas[2].coluna = 14;
                    fantasmas[2].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
                else if (fantasmas[index].tipo == 5){
                    fantasmas[3].linha = 14;
                    fantasmas[3].coluna = 15;
                    fantasmas[3].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
            }
            grade[linha][coluna] = 0; //limpando antigo local
            pacman->linha -= 1; //atualizando posicao do pacman
            grade[pacman->linha][pacman->coluna] = 4; //atualizando local na grade
            //atualizando estado da boca do pacman pois ele se moveu...
            if (pacman->bocaAberta) pacman->bocaAberta = FALSE;
            else pacman->bocaAberta = TRUE;
            //atualizando direcao do pacman
            pacman->direcao = 'w';
        }
    }
    else if ( direcao == 'a'){
        //verificando se o pacman chegou no tunel da esquerda, se sim sera "teleportado"
        if ( linha == 14 && (coluna-1) == 0){
            grade[linha][coluna] = 0; //limpando antigo local
            pacman->linha = 14; //atualizando posicao do pacman
            pacman->coluna = 26; //atualizando posicao do pacman
            grade[pacman->linha][pacman->coluna] = 4; //atualizando local na grade
            //atualizando estado da boca do pacman pois ele se moveu...
            if (pacman->bocaAberta) pacman->bocaAberta = FALSE;
            else pacman->bocaAberta = TRUE;
            //atualizando direcao do pacman
            pacman->direcao = 'a';
        }
        else if ( (coluna-1) >= 0 && grade[linha][coluna-1] != 1){
            //checando se o pacman comeu alguma moeda ou fantasma ao mover...
            if ( grade[linha][coluna-1] == 2) pacman->pontuacao += 10;
            else if ( grade[linha][coluna-1] == 3){
                pacman->pontuacao += 100;
                *intimidar = 420; //equivale a 7 segundos de efeito
            }
            //ou fantasma ao mover...
            else if ( grade[linha][coluna-1] > 0){
                pacman->pontuacao += 1000;
                //achando index do vetor, ou seja, qual fantasma foi comido
                index = (grade[linha][coluna-1] - 5);
                if (fantasmas[index].tipo == 5){
                    fantasmas[0].linha = 14;
                    fantasmas[0].coluna = 12;
                    fantasmas[0].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
                else if (fantasmas[index].tipo == 5){
                    fantasmas[1].linha = 14;
                    fantasmas[1].coluna = 13;
                    fantasmas[1].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
                else if (fantasmas[index].tipo == 5){
                    fantasmas[2].linha = 14;
                    fantasmas[2].coluna = 14;
                    fantasmas[2].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
                else if (fantasmas[index].tipo == 5){
                    fantasmas[3].linha = 14;
                    fantasmas[3].coluna = 15;
                    fantasmas[3].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
            }
            grade[linha][coluna] = 0; //limpando antigo local
            pacman->coluna -= 1; //atualizando posicao do pacman
            grade[pacman->linha][pacman->coluna] = 4; //atualizando local na grade
            //atualizando estado da boca do pacman pois ele se moveu...
            if (pacman->bocaAberta) pacman->bocaAberta = FALSE;
            else pacman->bocaAberta = TRUE;
            //atualizando direcao do pacman
            pacman->direcao = 'a';
        }
    }
    else if ( direcao == 's'){
        if ( (linha+1) < LINHAS && grade[linha+1][coluna] != 1){
            //checando se o pacman comeu alguma moeda
            if ( grade[linha+1][coluna] == 2) pacman->pontuacao += 10;
            else if ( grade[linha+1][coluna] == 3) {
                pacman->pontuacao += 100;
                *intimidar = 420; //equivale a 7 segundos de efeito
            }
            //ou fantasma ao mover...
            else if ( grade[linha+1][coluna] > 0){
                pacman->pontuacao += 1000;
                //achando index do vetor, ou seja, qual fantasma foi comido
                index = (grade[linha+1][coluna] - 5);
                if (fantasmas[index].tipo == 5){
                    fantasmas[0].linha = 14;
                    fantasmas[0].coluna = 12;
                    fantasmas[0].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
                else if (fantasmas[index].tipo == 5){
                    fantasmas[1].linha = 14;
                    fantasmas[1].coluna = 13;
                    fantasmas[1].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
                else if (fantasmas[index].tipo == 5){
                    fantasmas[2].linha = 14;
                    fantasmas[2].coluna = 14;
                    fantasmas[2].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
                else if (fantasmas[index].tipo == 5){
                    fantasmas[3].linha = 14;
                    fantasmas[3].coluna = 15;
                    fantasmas[3].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
            }
            grade[linha][coluna] = 0; //limpando antigo local
            pacman->linha += 1; //atualizando posicao do pacman
            grade[pacman->linha][pacman->coluna] = 4; //atualizando local na grade
            //atualizando estado da boca do pacman pois ele se moveu...
            if (pacman->bocaAberta) pacman->bocaAberta = FALSE;
            else pacman->bocaAberta = TRUE;
            //atualizando direcao do pacman
            pacman->direcao = 's';
        }
    }
    else if ( direcao == 'd'){
        //verificando se o pacman chegou no tunel da direita, se sim sera "teleportado"
        if ( linha == 14 && (coluna+1) == 27){
            grade[linha][coluna] = 0; //limpando antigo local
            pacman->linha = 14; //atualizando posicao do pacman
            pacman->coluna = 1; //atualizando posicao do pacman
            grade[pacman->linha][pacman->coluna] = 4; //atualizando local na grade
            //atualizando estado da boca do pacman pois ele se moveu...
            if (pacman->bocaAberta) pacman->bocaAberta = FALSE;
            else pacman->bocaAberta = TRUE;
            //atualizando direcao do pacman
            pacman->direcao = 'd';
        }
        else if ( (coluna+1) < COLUNAS && grade[linha][coluna+1] != 1){
            //checando se o pacman comeu alguma moeda
            if ( grade[linha][coluna+1] == 2) pacman->pontuacao += 10;
            else if ( grade[linha][coluna+1] == 3) {
                pacman->pontuacao += 100;
                *intimidar = 420; //equivale a 7 segundos de efeito
            }
            //ou fantasma ao mover...
            else if ( grade[linha][coluna+1] > 0){
                pacman->pontuacao += 1000;
                //achando index do vetor, ou seja, qual fantasma foi comido
                index = (grade[linha][coluna+1] - 5);
                if (fantasmas[index].tipo == 5){
                    fantasmas[0].linha = 14;
                    fantasmas[0].coluna = 12;
                    fantasmas[0].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
                else if (fantasmas[index].tipo == 5){
                    fantasmas[1].linha = 14;
                    fantasmas[1].coluna = 13;
                    fantasmas[1].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
                else if (fantasmas[index].tipo == 5){
                    fantasmas[2].linha = 14;
                    fantasmas[2].coluna = 14;
                    fantasmas[2].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
                else if (fantasmas[index].tipo == 5){
                    fantasmas[3].linha = 14;
                    fantasmas[3].coluna = 15;
                    fantasmas[3].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                }
            }
            grade[linha][coluna] = 0; //limpando antigo local
            pacman->coluna += 1; //atualizando posicao do pacman
            grade[pacman->linha][pacman->coluna] = 4; //atualizando local na grade
            //atualizando estado da boca do pacman pois ele se moveu...
            if (pacman->bocaAberta) pacman->bocaAberta = FALSE;
            else pacman->bocaAberta = TRUE;
            //atualizando direcao do pacman
            pacman->direcao = 'd';
        }
    }
    
}

void moverFantasmas(int grade[LINHAS][COLUNAS], Fantasma *fantasmas, Jogador *pacman){
    int i, j, linha, coluna;
    char direcao;
    //verificando se os fantasmas podem se mover, se sim...
    for (i=0; i<4; i++){
        direcao = fantasmas[i].rota[0];
        linha = fantasmas[i].linha;
        coluna = fantasmas[i].coluna;
        if ( fantasmas[i].liberado){
            if (direcao == 'w'){
                linha -= 1;
                //se o fantasma encontrar o pacman e nao estiver vulneravel...
                if (grade[linha][coluna] == 4 && fantasmas[i].vulneravel == FALSE){
                    pacman->vidas -= 1;
                    //se pacman ainda estiver vida ira renascer no inicio, senao...
                    if (pacman->vidas > 0){
                        pacman->linha = 23;
                        pacman->coluna = 13;
                    }
                    //restaurando valor do local anterior ao que o fantasma estava...
                    grade[linha+1][coluna] = fantasmas[i].temp;
                    //atualizando posicao do fantasma e grade
                    fantasmas[i].linha -= 1;
                    grade[fantasmas[i].linha][fantasmas[i].coluna] = fantasmas[i].tipo;
                }
                //se o fantasma encontrar o pacman e estiver vulneravel...entao ele ira morrer e respawnar
                else if (grade[linha][coluna] == 4 && fantasmas[i].vulneravel == TRUE){
                    //pacman recebe 1000 pontos por "devorar" um fantasma
                    pacman->pontuacao += 1000;
                    //restaurando valor do local anterior ao que o fantasma estava...
                    grade[linha+1][coluna] = fantasmas[i].temp;
                    //local de respawn do fantasma de acordo com sua cor/tipo
                    if (fantasmas[i].tipo == 5){
                        fantasmas[0].linha = 14;
                        fantasmas[0].coluna = 12;
                        fantasmas[0].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                    else if (fantasmas[i].tipo == 6){
                        fantasmas[1].linha = 14;
                        fantasmas[1].coluna = 13;
                        fantasmas[1].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                    else if (fantasmas[i].tipo == 7){
                        fantasmas[2].linha = 14;
                        fantasmas[2].coluna = 14;
                        fantasmas[2].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                    else if (fantasmas[i].tipo == 8){
                        fantasmas[2].linha = 14;
                        fantasmas[2].coluna = 15;
                        fantasmas[3].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                }
                //se o pacman nao estiver no local...apenas mover o fantasma e guardar valor anterior a ele no local
                else if ( grade[linha][coluna] != 4){
                    //restaurando valor do local anterior ao que o fantasma estava...
                    grade[linha+1][coluna] = fantasmas[i].temp;
                    //guardando novo valor temporario que o fantasma ira sobrescrever
                    fantasmas[i].temp = grade[linha][coluna];
                    //atualizando posicoes do fantasma e da grade
                    fantasmas[i].linha -= 1;
                    grade[fantasmas[i].linha][fantasmas[i].coluna] = fantasmas[i].tipo;
                }
            }
            else if (direcao == 'a'){
                coluna -= 1;
                //se o fantasma encontrar o pacman e nao estiver vulneravel...
                if (grade[linha][coluna] == 4 && fantasmas[i].vulneravel == FALSE){
                    pacman->vidas -= 1;
                    //se pacman ainda estiver vida ira renascer no inicio, senao...
                    if (pacman->vidas > 0){
                        pacman->linha = 23;
                        pacman->coluna = 13;
                    }
                    //restaurando valor do local anterior ao que o fantasma estava...
                    grade[linha][coluna+1] = fantasmas[i].temp;
                    //atualizando posicao do fantasma e grade
                    fantasmas[i].coluna -= 1;
                    grade[fantasmas[i].linha][fantasmas[i].coluna] = fantasmas[i].tipo;
                }
                //se o fantasma encontrar o pacman e estiver vulneravel...entao ele ira morrer e respawnar
                else if (grade[linha][coluna] == 4 && fantasmas[i].vulneravel == TRUE){
                    //pacman recebe 1000 pontos por "devorar" um fantasma
                    pacman->pontuacao += 1000;
                    //restaurando valor do local anterior ao que o fantasma estava...
                    grade[linha][coluna+1] = fantasmas[i].temp;
                    //local de respawn do fantasma de acordo com sua cor/tipo
                    if (fantasmas[i].tipo == 5){
                        fantasmas[0].linha = 14;
                        fantasmas[0].coluna = 12;
                        fantasmas[0].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                    else if (fantasmas[i].tipo == 6){
                        fantasmas[1].linha = 14;
                        fantasmas[1].coluna = 13;
                        fantasmas[1].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                    else if (fantasmas[i].tipo == 7){
                        fantasmas[2].linha = 14;
                        fantasmas[2].coluna = 14;
                        fantasmas[2].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                    else if (fantasmas[i].tipo == 8){
                        fantasmas[3].linha = 14;
                        fantasmas[3].coluna = 15;
                        fantasmas[3].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                }
                //se o pacman nao estiver no local...apenas mover o fantasma e guardar valor anterior a ele no local
                else if ( grade[linha][coluna] != 4){
                    //restaurando valor do local anterior ao que o fantasma estava...
                    grade[linha][coluna+1] = fantasmas[i].temp;
                    //guardando novo valor temporario que o fantasma ira sobrescrever
                    fantasmas[i].temp = grade[linha][coluna];
                    //atualizando posicoes do fantasma e da grade
                    fantasmas[i].coluna -= 1;
                    grade[fantasmas[i].linha][fantasmas[i].coluna] = fantasmas[i].tipo;
                }
            }
            else if (direcao == 's'){
                linha += 1;
                //se o fantasma encontrar o pacman e nao estiver vulneravel...
                if (grade[linha][coluna] == 4 && fantasmas[i].vulneravel == FALSE){
                    pacman->vidas -= 1;
                    //se pacman ainda estiver vida ira renascer no inicio, senao...
                    if (pacman->vidas > 0){
                        pacman->linha = 23;
                        pacman->coluna = 13;
                    }
                    //restaurando valor do local anterior ao que o fantasma estava...
                    grade[linha-1][coluna] = fantasmas[i].temp;
                    //atualizando posicao do fantasma e grade
                    fantasmas[i].linha += 1;
                    grade[fantasmas[i].linha][fantasmas[i].coluna] = fantasmas[i].tipo;
                }
                //se o fantasma encontrar o pacman e estiver vulneravel...entao ele ira morrer e respawnar
                else if (grade[linha][coluna] == 4 && fantasmas[i].vulneravel == TRUE){
                    //pacman recebe 1000 pontos por "devorar" um fantasma
                    pacman->pontuacao += 1000;
                    //restaurando valor do local anterior ao que o fantasma estava...
                    grade[linha-1][coluna] = fantasmas[i].temp;
                    //local de respawn do fantasma de acordo com sua cor/tipo
                    if (fantasmas[i].tipo == 5){
                        fantasmas[0].linha = 14;
                        fantasmas[0].coluna = 12;
                        fantasmas[0].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                    else if (fantasmas[i].tipo == 6){
                        fantasmas[1].linha = 14;
                        fantasmas[1].coluna = 13;
                        fantasmas[1].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                    else if (fantasmas[i].tipo == 7){
                        fantasmas[2].linha = 14;
                        fantasmas[2].coluna = 14;
                        fantasmas[2].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                    else if (fantasmas[i].tipo == 8){
                        fantasmas[3].linha = 14;
                        fantasmas[3].coluna = 15;
                        fantasmas[3].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                }
                //se o pacman nao estiver no local...apenas mover o fantasma e guardar valor anterior a ele no local
                else if ( grade[linha][coluna] != 4){
                    //restaurando valor do local anterior ao que o fantasma estava...
                    grade[linha-1][coluna] = fantasmas[i].temp;
                    //guardando novo valor temporario que o fantasma ira sobrescrever
                    fantasmas[i].temp = grade[linha][coluna];
                    //atualizando posicoes do fantasma e da grade
                    fantasmas[i].linha += 1;
                    grade[fantasmas[i].linha][fantasmas[i].coluna] = fantasmas[i].tipo;
                }
            }
            else if (direcao == 'd'){
                coluna += 1;
                //se o fantasma encontrar o pacman e nao estiver vulneravel...
                if (grade[linha][coluna] == 4 && fantasmas[i].vulneravel == FALSE){
                    pacman->vidas -= 1;
                    //se pacman ainda estiver vida ira renascer no inicio, senao...
                    if (pacman->vidas > 0){
                        pacman->linha = 23;
                        pacman->coluna = 13;
                    }
                    //restaurando valor do local anterior ao que o fantasma estava...
                    grade[linha][coluna-1] = fantasmas[i].temp;
                    //atualizando posicao do fantasma e grade
                    fantasmas[i].coluna += 1;
                    grade[fantasmas[i].linha][fantasmas[i].coluna] = fantasmas[i].tipo;
                }
                //se o fantasma encontrar o pacman e estiver vulneravel...entao ele ira morrer e respawnar
                else if (grade[linha][coluna] == 4 && fantasmas[i].vulneravel == TRUE){
                    //pacman recebe 1000 pontos por "devorar" um fantasma
                    pacman->pontuacao += 1000;
                    //restaurando valor do local anterior ao que o fantasma estava...
                    grade[linha][coluna-1] = fantasmas[i].temp;
                    //local de respawn do fantasma de acordo com sua cor/tipo
                    if (fantasmas[i].tipo == 5){
                        fantasmas[0].linha = 14;
                        fantasmas[0].coluna = 12;
                        fantasmas[0].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                    else if (fantasmas[i].tipo == 6){
                        fantasmas[1].linha = 14;
                        fantasmas[1].coluna = 13;
                        fantasmas[1].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                    else if (fantasmas[i].tipo == 7){
                        fantasmas[2].linha = 14;
                        fantasmas[2].coluna = 14;
                        fantasmas[2].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                    else if (fantasmas[i].tipo == 8){
                        fantasmas[3].linha = 14;
                        fantasmas[3].coluna = 15;
                        fantasmas[3].liberado = FALSE; //fantasma tera uma nova rota e devera ser liberado novamente...
                    }
                }
                //se o pacman nao estiver no local...apenas mover o fantasma e guardar valor anterior a ele no local
                else if ( grade[linha][coluna] != 4){
                    //restaurando valor do local anterior ao que o fantasma estava...
                    grade[linha][coluna-1] = fantasmas[i].temp;
                    //guardando novo valor temporario que o fantasma ira sobrescrever
                    fantasmas[i].temp = grade[linha][coluna];
                    //atualizando posicoes do fantasma e da grade
                    fantasmas[i].coluna += 1;
                    grade[fantasmas[i].linha][fantasmas[i].coluna] = fantasmas[i].tipo;
                }
            }
            //Apos a movimentacao, atualizar a string que contem a rota do fantasma
            for (j=0; j<strlen(fantasmas[i].rota); j++){
                //se chegar ao final da string...substituir pela movimentacao feita
                if ( j == (strlen(fantasmas[i].rota)-1) ) fantasmas[i].rota[j] = direcao;
                //se nao, substituir pelo posterior
                else fantasmas[i].rota[j] = fantasmas[i].rota[j+1];
            }
        }
    }
    
}

void limparGrade(int grade[LINHAS][COLUNAS], Fantasma *fantasmas){
    int i, j;
    //verificando se ha algum fantasma duplicado na grade, se sim sera eliminado
    for (i=0; i<LINHAS; i++){
        for (j=0; j<COLUNAS; j++){
            if (grade[i][j] == 5 && (fantasmas[0].linha != i || fantasmas[0].coluna != j)) grade[i][j] = 0;
            else if (grade[i][j] == 6 && (fantasmas[1].linha != i || fantasmas[1].coluna != j)) grade[i][j] = 0;
            else if (grade[i][j] == 7 && (fantasmas[2].linha != i || fantasmas[2].coluna != j)) grade[i][j] = 0;
            else if (grade[i][j] == 8 && (fantasmas[3].linha != i || fantasmas[3].coluna != j)) grade[i][j] = 0;
        }
    }
}
