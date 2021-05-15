#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#define LINHA 70
#define COLUNA 70
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
   -1- vazio
    0- terra (80% como padrao)
    1- agua  (20% como padrao)
    2- arvore (usuario)
    3- mobs   (usuario)
    4- areia  (usuario)
    5- construcoes (usuario)
    
*/
int main(){
    //variaveis constantes da simulacao
    const int largura = 900;
    const int altura = 700;
    //variaveis gerais da simulacao
    int mundo[LINHA][COLUNA];
    int chanceTerra[2] = {0, 80};
    int chanceAgua[2] = {80, 99};
    int i, j, alet, vizinhoA, vizinhoT;
    bool simular = false, limpar = false, editar = false, salvar = false;
    bool okTerra = false, okAgua = false, okArvore = false, okMobs = false, okAreia = false, okConstrucoes = false;
    //Variaveis para leitura de arquivo
    FILE *fp;
    char quadrado;
    //"Janelas" da simulacao
    Rectangle abaConfig = {0, 0, 200, altura};
    Rectangle simulacao = {200, 0, 700, altura};
    Rectangle botaoSimular = {20, 500, 160, 80};
    Rectangle botaoLimpar = {20, 600, 160, 80};
    Rectangle botaoEditar = {20, 200, 160, 80};
    Rectangle botaoSalvar = {20, 100, 160, 80};
    Rectangle botaoTerra = {40, 420, 40, 40};
    Rectangle botaoAgua = {120, 420, 40, 40};
    Rectangle botaoArvore = {40, 360, 40, 40};
    Rectangle botaoMobs = {120, 360, 40, 40};
    Rectangle botaoAreia = {40, 300, 40, 40};
    Rectangle botaoConstrucoes = {120, 300, 40, 40};
    
    //Inicializando matriz
    for (i=0; i<LINHA; i++){
        for (j=0; j<COLUNA; j++){
            mundo[i][j] = -1;
        }
    }
    //Iniciando tela e FPS
    InitWindow( largura, altura, "Gerador de Mundos");
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()){
        //Update da simulacao
        
        //Checando toque nos botoes
        if ( CheckCollisionPointRec( GetMousePosition(), botaoSimular) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) simular = true;
        if ( CheckCollisionPointRec( GetMousePosition(), botaoLimpar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) limpar = true;
        if ( CheckCollisionPointRec( GetMousePosition(), botaoEditar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && editar == true) editar = false;
        else if ( CheckCollisionPointRec( GetMousePosition(), botaoEditar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && editar == false) editar = true;
        if ( CheckCollisionPointRec( GetMousePosition(), botaoSalvar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && salvar == false) salvar = true;
        //preenchendo a matriz de acordo com a probabilidade dos elementos (se requerido)
        if (simular){
            for (i=0; i<LINHA; i++){
                for (j=0; j<COLUNA; j++){
                    alet = GetRandomValue(0, 99);
                    if ( alet >= chanceTerra[0] && alet <= chanceTerra[1]) mundo[i][j] = 0;
                    else if ( alet >= chanceAgua[0] && alet <= chanceAgua[1]) mundo[i][j] = 1;
                }
            }
            //juntando pedacos de terra ou eliminando pedacos desconectados
            for (i=0; i<LINHA; i++){
                for (j=0; j<COLUNA; j++){
                    if ( i > 0 && j > 0){
                        //verificando arredores do pixel
                        vizinhoA = 0;
                        vizinhoT = 0;
                        if ( mundo[i-1][j] == 0) vizinhoT++;
                        else vizinhoA++;
                        if ( mundo[i+1][j] == 0) vizinhoT++;
                        else vizinhoA++;
                        if ( mundo[i][j-1] == 0) vizinhoT++;
                        else vizinhoA++;
                        if ( mundo[i][j+1] == 0) vizinhoT++;
                        else vizinhoA++;
                        //modificando com base nos vizinhos
                        if ( vizinhoT > vizinhoA) mundo[i][j] = 0;
                        else if ( vizinhoA > vizinhoT) mundo[i][j] = 1;
                        else mundo[i][j] = 1; //preferencia para a Terra em caso de empate
                    }
                }
            }
            mundo[0][34] = 4; //ajuste para saber o meio do NORTE
            mundo[34][0] = 4; //ajuste para saber o meio do OESTE
            mundo[69][34] = 4; //ajuste para saber o meio do SUL
            mundo[34][69] = 4; //ajuste para saber o meio do LESTE
            simular = false;
        }
        if (limpar){
            for (i=0; i<LINHA; i++){
                for (j=0; j<COLUNA; j++){
                    mundo[i][j] = -1;
                }
            }
            limpar = false;
        }
        if (editar){
            //checando toque nos botoes de Terra e Agua
            if ( CheckCollisionPointRec( GetMousePosition(), botaoTerra) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                okTerra = true;
                okAgua = false;
                okArvore = false;
                okMobs = false;
                okAreia = false;
                okConstrucoes = false;
            }
            if ( CheckCollisionPointRec( GetMousePosition(), botaoAgua) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                okAgua = true;
                okTerra = false;
                okArvore = false;
                okMobs = false;
                okAreia = false;
                okConstrucoes = false;
            }
            if ( CheckCollisionPointRec( GetMousePosition(), botaoArvore) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                okAgua = false;
                okTerra = false;
                okArvore = true;
                okMobs = false;
                okAreia = false;
                okConstrucoes = false;
            }
            if ( CheckCollisionPointRec( GetMousePosition(), botaoMobs) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                okAgua = false;
                okTerra = false;
                okArvore = false;
                okMobs = true;
                okAreia = false;
                okConstrucoes = false;
            }
            if ( CheckCollisionPointRec( GetMousePosition(), botaoAreia) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                okAgua = false;
                okTerra = false;
                okArvore = false;
                okMobs = false;
                okAreia = true;
                okConstrucoes = false;
            }
            if ( CheckCollisionPointRec( GetMousePosition(), botaoConstrucoes) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                okAgua = false;
                okTerra = false;
                okArvore = false;
                okMobs = false;
                okAreia = false;
                okConstrucoes = true;
            }
            //checando na area da simulacao caso o modo Editar esteja ativo e se uma das opcoes (Terra ou Agua) foi selecionada
            for (i=0; i<LINHA; i++){
                for (j=0; j<COLUNA; j++){
                    if ( okTerra && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec( GetMousePosition(), (Rectangle) {j*10 + 200, i*10, 10, 10})) mundo[i][j] = 0;
                    else if ( okAgua && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec( GetMousePosition(), (Rectangle) {j*10 + 200, i*10, 10, 10})) mundo[i][j] = 1;
                    else if ( okArvore && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec( GetMousePosition(), (Rectangle) {j*10 + 200, i*10, 10, 10})) mundo[i][j] = 2;
                    else if ( okMobs && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec( GetMousePosition(), (Rectangle) {j*10 + 200, i*10, 10, 10})) mundo[i][j] = 3;
                    else if ( okAreia && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec( GetMousePosition(), (Rectangle) {j*10 + 200, i*10, 10, 10})) mundo[i][j] = 4;
                    else if ( okConstrucoes && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec( GetMousePosition(), (Rectangle) {j*10 + 200, i*10, 10, 10})) mundo[i][j] = 5;
                }
            }
        }
        if (!editar){
            //desativando botoes caso o modo Editar nao esteja ativo
            okTerra = false;
            okAgua = false;
            okArvore = false;
            okMobs = false;
            okAreia = false;
            okConstrucoes = false;
        }
        if (salvar){
            if ( (fp = fopen("mundo.txt", "w")) == NULL){
                salvar = false;
                break; //checando se houve erro na criacao do arquivo, se sim parar a operacao
            }
            //lendo a matriz mundo, armazenando cada item e jogando no arquivo criado
            for (i=0; i<LINHA; i++){
                for (j=0; j<COLUNA; j++){
                    quadrado = mundo[i][j];
                    fprintf(fp, "%d", quadrado);
                    fprintf(fp, "%c", ' ');
                }
                fprintf(fp, "%s", "\n");
            }
            fclose(fp); //fechando arquivo e salvando alteracoes
            salvar = false;
        }
        //Renderizacao da simulacao
        BeginDrawing();
            ClearBackground(WHITE);//limpando toda a tela para a cor branca
            
            DrawRectangleRec(simulacao, BLACK); //local onde o mundo sera gerado e mostrado
            DrawRectangleRec(abaConfig, DARKGRAY); //local onde as opcoes de simulacao serao mostradas
            //pixelizando a tela de acordo com as informacoes na matriz mundo
            for (i=0; i<LINHA; i++){
                for (j=0; j<COLUNA; j++){
                    if (mundo[i][j] == 0) DrawRectangle(j*10 + 200, i*10, 10, 10, GREEN);
                    else if (mundo[i][j] == 1) DrawRectangle(j*10 + 200, i*10, 10, 10, BLUE);
                    else if (mundo[i][j] == 2) DrawRectangle(j*10 + 200, i*10, 10, 10, DARKGREEN);
                    else if (mundo[i][j] == 3) DrawRectangle(j*10 + 200, i*10, 10, 10, RED);
                    else if (mundo[i][j] == 4) DrawRectangle(j*10 + 200, i*10, 10, 10, GOLD);
                    else if (mundo[i][j] == 5) DrawRectangle(j*10 + 200, i*10, 10, 10, DARKBROWN);
                }
            }
            //renderizando botoes
            DrawRectangleRec(botaoSimular, DARKGREEN);
            DrawText(FormatText("SIMULAR"), 30, 530, 30, BLACK);
            DrawRectangleRec(botaoLimpar, RED);
            DrawText(FormatText("LIMPAR"), 40, 630, 30, BLACK);
            DrawRectangleRec(botaoEditar, YELLOW);
            DrawText(FormatText("EDITAR"), 40, 230, 30, BLACK);
            DrawRectangleRec(botaoSalvar, GREEN);
            DrawText(FormatText("SALVAR"), 40, 130, 30, BLACK);
            if (!okTerra) DrawRectangleRec(botaoTerra, RAYWHITE);
            else DrawRectangleRec(botaoTerra, GREEN);
            if (!okAgua) DrawRectangleRec(botaoAgua, RAYWHITE);
            else DrawRectangleRec(botaoAgua, BLUE);
            if (!okArvore) DrawRectangleRec(botaoArvore, RAYWHITE);
            else DrawRectangleRec(botaoArvore, DARKGREEN);
            if (!okMobs) DrawRectangleRec(botaoMobs, RAYWHITE);
            else DrawRectangleRec(botaoMobs, RED);
            if (!okAreia) DrawRectangleRec(botaoAreia, RAYWHITE);
            else DrawRectangleRec(botaoAreia, GOLD);
            if (!okConstrucoes) DrawRectangleRec(botaoConstrucoes, RAYWHITE);
            else DrawRectangleRec(botaoConstrucoes, DARKBROWN);
             
        EndDrawing(); 
        
    }
    
    CloseWindow();
    
    return 0;
}
