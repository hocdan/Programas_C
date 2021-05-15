#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define LINHAS 60
#define COLUNAS 30
#define TRUE 1
#define FALSE 0 
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
*/


//Estrutura responsavel pelas pecas geometricas
typedef struct Forma{
    //tipo da Forma (1 ate 6 tipos diferentes)
    int tipo;
    //rotacao atual da Forma (1 ate 4 rotacoes "diferentes")
    int rotacao;
    //Vetor de blocos que a forma eh composta
    struct Bloco {
        //coordenadas do bloco (x, y)
        int linha;
        int coluna;
    } blocos[4];
}Forma;

int main(){
    //Delcarando funcoes a serem utilizadas
    int soltarPeca(Forma peca, int grade[LINHAS][COLUNAS]);
    void colocarPeca(Forma peca, int grade[LINHAS][COLUNAS]);
    int moverPeca(Forma *peca, int grade[LINHAS][COLUNAS], char direcao);
    void rotacionarPeca(Forma *peca, int grade[LINHAS][COLUNAS]);
    void limparGrade(int grade[LINHAS][COLUNAS], int *pontuacao, int nivel);
    
    //constantes do jogo
    const int largura = 400;
    const int altura = 600;
    
    //Variaveis do jogo
    int i, j, alet, frames = 0, pontuacao = 0, nivel = 1;
    int grade[LINHAS][COLUNAS];
    Forma pecaAtual; //inicializando variavel que ira armazenar a peca geometrica atual no jogo 
    
    //Flags dos jogo (indicam status)
    int liberarPeca = TRUE, jogando = TRUE, rotacionar = FALSE, moverEsq = FALSE, moverDir = FALSE;
    
    //Inicializando grade
    for (i=0; i<LINHAS; i++){
        for (j=0; j<COLUNAS; j++){
            grade[i][j] = 0; //vazio = 0
        }
    }
    
    //Aba lateral do jogo
    Rectangle aba = {300, 0, 100, altura};
    
    //Iniciando tela e FPS
    InitWindow( largura, altura, "tetris 1.0");
    
    SetTargetFPS(60);

    //Loop principal do jogo
    while(!WindowShouldClose()){
        //Update do jogo
        if (jogando){
            frames++; //atualizando frame
            //atualizando nivel atual
            if ( pontuacao >= 500 && pontuacao < 1000) nivel = 2;
            else if ( pontuacao >= 1000 && pontuacao < 1500) nivel = 3;
            else if ( pontuacao >= 1500 && pontuacao < 2000) nivel = 4;
            else if ( pontuacao >= 2000 && pontuacao < 2500) nivel = 5;
            else if ( pontuacao >= 2500) nivel = 6;
            
            //checando por input do usuario no teclado
            if ( IsKeyDown(KEY_R) ) rotacionar = TRUE;
            if ( IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ) moverEsq = TRUE;
            if ( IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ) moverDir = TRUE;
            if ( IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ) moverPeca(&pecaAtual, grade, 's');
            
            //atualizando 3 frames por segundo
            if (frames%20 == 0){
                //verificando se eh possivel liberar peca
                if (liberarPeca){
                    //Limpando blocos eliminados da grade
                    limparGrade(grade, &pontuacao, nivel);
                    //Selecionando tipo de peca a ser liberada (de forma aleatoria)
                    alet = GetRandomValue(1, 6);
                    //inicializando peca escolhida no centro da grade
                    if (alet == 1) {
                        pecaAtual.tipo = 1;
                        pecaAtual.rotacao =  1;
                        pecaAtual.blocos[0].linha = 0;
                        pecaAtual.blocos[0].coluna = 14;
                        pecaAtual.blocos[1].linha = 1;
                        pecaAtual.blocos[1].coluna = 14;
                        pecaAtual.blocos[2].linha = 2;
                        pecaAtual.blocos[2].coluna = 14;
                        pecaAtual.blocos[3].linha = 3;
                        pecaAtual.blocos[3].coluna = 14;
                    }
                    else if (alet == 2) {
                        pecaAtual.tipo = 2;
                        pecaAtual.rotacao = 1;
                        pecaAtual.blocos[0].linha = 0;
                        pecaAtual.blocos[0].coluna = 13;
                        pecaAtual.blocos[1].linha = 0;
                        pecaAtual.blocos[1].coluna = 14;
                        pecaAtual.blocos[2].linha = 1;
                        pecaAtual.blocos[2].coluna = 13;
                        pecaAtual.blocos[3].linha = 1;
                        pecaAtual.blocos[3].coluna = 14;
                    }
                    else if (alet == 3) {
                        pecaAtual.tipo = 3;
                        pecaAtual.rotacao = 1;
                        pecaAtual.blocos[0].linha = 0;
                        pecaAtual.blocos[0].coluna = 13;
                        pecaAtual.blocos[1].linha = 0;
                        pecaAtual.blocos[1].coluna = 14;
                        pecaAtual.blocos[2].linha = 0;
                        pecaAtual.blocos[2].coluna = 15;
                        pecaAtual.blocos[3].linha = 1;
                        pecaAtual.blocos[3].coluna = 14;
                    }
                    else if (alet == 4) {
                        pecaAtual.tipo = 4;
                        pecaAtual.rotacao = 1;
                        pecaAtual.blocos[0].linha = 0;
                        pecaAtual.blocos[0].coluna = 14;
                        pecaAtual.blocos[1].linha = 1;
                        pecaAtual.blocos[1].coluna = 14;
                        pecaAtual.blocos[2].linha = 2;
                        pecaAtual.blocos[2].coluna = 14;
                        pecaAtual.blocos[3].linha = 2;
                        pecaAtual.blocos[3].coluna = 13;
                    }
                    else if (alet == 5) {
                        pecaAtual.tipo = 5;
                        pecaAtual.rotacao = 1;
                        pecaAtual.blocos[0].linha = 0;
                        pecaAtual.blocos[0].coluna = 13;
                        pecaAtual.blocos[1].linha = 0;
                        pecaAtual.blocos[1].coluna = 14;
                        pecaAtual.blocos[2].linha = 1;
                        pecaAtual.blocos[2].coluna = 14;
                        pecaAtual.blocos[3].linha = 1;
                        pecaAtual.blocos[3].coluna = 15;
                    }
                    else if (alet == 6) {
                        pecaAtual.tipo = 6;
                        pecaAtual.rotacao = 1;
                        pecaAtual.blocos[0].linha = 1;
                        pecaAtual.blocos[0].coluna = 13;
                        pecaAtual.blocos[1].linha = 1;
                        pecaAtual.blocos[1].coluna = 14;
                        pecaAtual.blocos[2].linha = 0;
                        pecaAtual.blocos[2].coluna = 14;
                        pecaAtual.blocos[3].linha = 0;
                        pecaAtual.blocos[3].coluna = 15;
                    }
                    //verificando se a peca pode ser inserida na grade sem problemas
                    if ( soltarPeca(pecaAtual, grade) ){
                        colocarPeca(pecaAtual, grade);
                        liberarPeca = FALSE;
                    }
                    else{
                        jogando = FALSE;
                        liberarPeca = FALSE;
                    }
                }
                else{
                    //Movendo peca existente, pois ja foi liberado uma...
                    if (rotacionar){
                        rotacionarPeca( &pecaAtual, grade);
                        rotacionar = FALSE;
                    }
                    if ( moverEsq ) {
                        if (!moverPeca( &pecaAtual, grade, 'a')) liberarPeca = TRUE;
                        moverEsq = FALSE;
                    }
                    else if ( moverDir ) { 
                        if (!moverPeca( &pecaAtual, grade, 'd')) liberarPeca = TRUE;
                        moverDir = FALSE;
                    }
                    //Peca vai descendo naturalmente...
                    if (!moverPeca( &pecaAtual, grade, 's')) liberarPeca = TRUE;
                }
                
            }
        }
        
        //Draw do jogo
        BeginDrawing();
            if (jogando){
                //Limpando janela de fundo
                ClearBackground(WHITE);
                //Desenhando grade do jogo
                for (i=0; i<LINHAS; i++){
                    for (j=0; j<COLUNAS; j++){
                        if ( grade[i][j] == 0) DrawRectangle(j*10, i*10, 10, 10, BLACK);
                        else if ( grade[i][j] == 1) DrawRectangle(j*10, i*10, 10, 10, BLUE);
                        else if ( grade[i][j] == 2) DrawRectangle(j*10, i*10, 10, 10, GREEN);
                        else if ( grade[i][j] == 3) DrawRectangle(j*10, i*10, 10, 10, YELLOW);
                        else if ( grade[i][j] == 4) DrawRectangle(j*10, i*10, 10, 10, PURPLE);
                        else if ( grade[i][j] == 5) DrawRectangle(j*10, i*10, 10, 10, RED);
                        else if ( grade[i][j] == 6) DrawRectangle(j*10, i*10, 10, 10, ORANGE);
                    }
                }
                //Desenhando aba lateral
                DrawRectangleRec(aba, LIGHTGRAY);
                DrawText(FormatText("Nivel: %d", nivel), 310, 10, 10, BLACK);
                DrawText(FormatText("Pontuacao: %d", pontuacao), 310, 30, 10, BLACK);
            }
            else{
                //Desenhando tela de game over e finalizando jogo
                ClearBackground(BLACK);
                DrawText(FormatText("GAME OVER!"), 80, 280, 40, WHITE);
            }
        EndDrawing();
        
        
    }

    //Fechando janela e finalizando jogo
    CloseWindow();
    
    return 0;
}

void limparGrade(int grade[LINHAS][COLUNAS], int *pontuacao, int nivel){
    //Percorrendo matriz de baixo para cima e eliminando linhas totalmente preenchidas (500 pontos) e
    //descendo blocos superiores para preencher o vazio
    int i, j, k, l, eliminar=FALSE;
    for (i=(LINHAS-1); i>=0; i--){
        if (eliminar){
            //se houve eliminacao na linha anterior...entao puxar todos os blocos de cima para baixo
            for (l=i; l>=0; l--){
                for (k=0; k<COLUNAS; k++){
                    //evitando que parte inexistentes da grade sejam acessadas
                    if (l >= 0 && l <= (LINHAS-2)){
                        grade[l+1][k] = grade[l][k]; //copiando bloco para baixo
                        grade[l][k] = 0; //apagando bloco para nao haver repeticao
                    }
                }
            }
        }
        eliminar = TRUE; //setando flag novamente para true, para sinalizar eliminacao
        for (j=0; j<COLUNAS; j++){
            //se houver espaco vazio entao nao podemos eliminar os blocos daquela coluna
            if ( grade[i][j] == 0) eliminar = FALSE;
        }
        //se apos verificar toda a linha nao houver espacos vazios...entao eliminar toda a linha
        if (eliminar){
            for (k=0; k<COLUNAS; k++){
                grade[i][k] = 0;
                *pontuacao += 10 * nivel; //pontos por bloco = produto de 10 pelo nivel atual do jogo
            }
        }
    }
    
}

int soltarPeca(Forma peca, int grade[LINHAS][COLUNAS]){
    //Verificando coordenadas da peca com coordenadas da grade, para ver se ha espaco suficiente
    int i, linha, coluna;
    for (i=0; i<4; i++){    
        linha = peca.blocos[i].linha;
        coluna = peca.blocos[i].coluna;
        if ( grade[linha][coluna] != 0) return FALSE;
    }
    return TRUE;
    
}

void colocarPeca(Forma peca, int grade[LINHAS][COLUNAS]){
    //inserindo peca na grade
    int i, linha, coluna;
    for (i=0; i<4; i++){    
        linha = peca.blocos[i].linha;
        coluna = peca.blocos[i].coluna;
        grade[linha][coluna] = peca.tipo; //preenchendo matriz com o tipo da peca
    }
    
}

int moverPeca(Forma *peca, int grade[LINHAS][COLUNAS], char direcao){
    //Movendo a peca de acordo com a direcao fornecida
    int i, linha, coluna, valido = TRUE;
    //Limpando local antigo da peca
    for (i=0; i<4; i++){
        linha = peca->blocos[i].linha;
        coluna = peca->blocos[i].coluna;
        grade[linha][coluna] = 0; //limpando
    }
    if ( direcao == 'a'){
        for (i=0; i<4; i++){
            linha = peca->blocos[i].linha;
            coluna = peca->blocos[i].coluna;
            //verificando se a movimentacao eh possivel
            if ( (coluna-1) >= 0 && (coluna-1) < COLUNAS){
                //se a nova posicao nao estiver vaga...
                if ( grade[linha][coluna-1] != 0){ 
                    valido = FALSE;
                    break;
                }
            }
            else{
                return valido; //para que a peca nao "morra" no canto esquerdo
            }
        }
        if (valido){
            for (i=0; i<4; i++){
                peca->blocos[i].coluna -= 1; //atualizando posicao coluna do bloco da peca
                linha = peca->blocos[i].linha;
                coluna = peca->blocos[i].coluna;
                grade[linha][coluna] = peca->tipo; //atualizando grade
            }
        }
    }
    else if ( direcao == 'd'){
        for (i=0; i<4; i++){
            linha = peca->blocos[i].linha;
            coluna = peca->blocos[i].coluna;
            //verificando se a movimentacao eh possivel
            if ( (coluna+1) >= 0 && (coluna+1) < COLUNAS){
                //se a nova posicao nao estiver vaga...
                if ( grade[linha][coluna+1] != 0){ 
                    valido = FALSE;
                    break;
                }
            }
            else{
                return valido; //para que a peca nao "morra" no canto direito
            }
        }
        if ( valido){
            for (i=0; i<4; i++){
                peca->blocos[i].coluna += 1; //atualizando posicao coluna do bloco da peca
                linha = peca->blocos[i].linha;
                coluna = peca->blocos[i].coluna;
                grade[linha][coluna] = peca->tipo; //atualizando grade
            }
        }
    }
    else if ( direcao == 's'){
        for (i=0; i<4; i++){
            linha = peca->blocos[i].linha;
            coluna = peca->blocos[i].coluna;
            //verificando se a movimentacao eh possivel
            if ( (linha+1) >= 0 && (linha+1) < LINHAS){
                //se a nova posicao nao estiver vaga...
                if ( grade[linha+1][coluna] != 0){ 
                    valido = FALSE;
                    break;
                }
            }
            else{
                valido = FALSE;
                break;
            }
        }
        if ( valido){
            for (i=0; i<4; i++){
                peca->blocos[i].linha += 1; //atualizando posicao coluna do bloco da peca
                linha = peca->blocos[i].linha;
                coluna = peca->blocos[i].coluna;
                grade[linha][coluna] = peca->tipo; //atualizando grade
            }
        }
    }
    //desfazendo limpeza caso o movimento nao tenha dado certo...
    if (!valido){
        for (i=0; i<4; i++){
            linha = peca->blocos[i].linha;
            coluna = peca->blocos[i].coluna;
            grade[linha][coluna] = peca->tipo; //limpando
        }
    } 
    return valido; //retornando se o movimento foi concluido ou nao...
}

void rotacionarPeca(Forma *peca, int grade[LINHAS][COLUNAS]){
    int i, linha, coluna, valido = TRUE;
    
    //Limpando local antigo da peca
    for (i=0; i<4; i++){
        linha = peca->blocos[i].linha;
        coluna = peca->blocos[i].coluna;
        grade[linha][coluna] = 0; //limpando
    }
    
    //atualizando tipo de rotacao
    if ( peca->rotacao == 4) peca->rotacao = 1; //resetando para rotacao inicial
    else peca->rotacao += 1; //atualizando para nova rotacao
    
    //Verificando o tipo de peca, sua rotacao atual e fazendo as alteracoes necessarias
    //PECA DO TIPO GRAVETO (FEITO)
    if ( peca->tipo == 1){
        //Verificando qual o tipo de rotacao (OK)
        if ( peca->rotacao == 1 || peca->rotacao == 3){
            //verificando se rotacao eh valida, e se sim, alterando matriz
            if ( grade[peca->blocos[0].linha-3][peca->blocos[0].coluna+2] == 0 &&
                 grade[peca->blocos[1].linha-2][peca->blocos[1].coluna+1] == 0 &&
                 grade[peca->blocos[2].linha-1][peca->blocos[2].coluna]   == 0 &&
                 grade[peca->blocos[3].linha][peca->blocos[3].coluna-1]   == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  -= 3;
                peca->blocos[0].coluna += 2;
                peca->blocos[1].linha  -= 2;
                peca->blocos[1].coluna += 1;
                peca->blocos[2].linha  -= 1;
                peca->blocos[3].coluna -= 1;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else{
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha+3][peca->blocos[0].coluna-2] == 0 &&
                 grade[peca->blocos[1].linha+2][peca->blocos[1].coluna-1] == 0 &&
                 grade[peca->blocos[2].linha+1][peca->blocos[2].coluna]   == 0 &&
                 grade[peca->blocos[3].linha][peca->blocos[3].coluna+1]   == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  += 3;
                peca->blocos[0].coluna -= 2;
                peca->blocos[1].linha  += 2;
                peca->blocos[1].coluna -= 1;
                peca->blocos[2].linha  += 1;
                peca->blocos[3].coluna += 1;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
    }
    //PECA DO TIPO CAIXA (FEITO)
    else if ( peca->tipo == 2){
        valido = FALSE; //como a peca do tipo 2 nao muda ao ser rotacionada...deixar do jeito que esta (OK)
    }
    //PECA DO TIPO NAVE (FEITO)
    else if ( peca->tipo == 3){
        if ( peca->rotacao == 1){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha-1][peca->blocos[0].coluna-1]   == 0 &&
                 grade[peca->blocos[1].linha][peca->blocos[1].coluna]       == 0 &&
                 grade[peca->blocos[2].linha+1][peca->blocos[2].coluna+1]   == 0 &&
                 grade[peca->blocos[3].linha+1][peca->blocos[3].coluna-1]   == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  -= 1;
                peca->blocos[0].coluna -= 1;
                peca->blocos[2].linha  += 1;
                peca->blocos[2].coluna += 1;
                peca->blocos[3].linha  += 1;
                peca->blocos[3].coluna -= 1;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else if ( peca->rotacao == 2){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha-1][peca->blocos[0].coluna+1]   == 0 &&
                 grade[peca->blocos[1].linha][peca->blocos[1].coluna]       == 0 &&
                 grade[peca->blocos[2].linha+1][peca->blocos[2].coluna-1]   == 0 &&
                 grade[peca->blocos[3].linha-1][peca->blocos[3].coluna-1]   == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  -= 1;
                peca->blocos[0].coluna += 1;
                peca->blocos[2].linha  += 1;
                peca->blocos[2].coluna -= 1;
                peca->blocos[3].linha  -= 1;
                peca->blocos[3].coluna -= 1;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else if ( peca->rotacao == 3){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha+1][peca->blocos[0].coluna+1]   == 0 &&
                 grade[peca->blocos[1].linha][peca->blocos[1].coluna]       == 0 &&
                 grade[peca->blocos[2].linha-1][peca->blocos[2].coluna-1]   == 0 &&
                 grade[peca->blocos[3].linha-1][peca->blocos[3].coluna+1]   == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  += 1;
                peca->blocos[0].coluna += 1;
                peca->blocos[2].linha  -= 1;
                peca->blocos[2].coluna -= 1;
                peca->blocos[3].linha  -= 1;
                peca->blocos[3].coluna += 1;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else if ( peca->rotacao == 4){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha+1][peca->blocos[0].coluna-1]   == 0 &&
                 grade[peca->blocos[1].linha][peca->blocos[1].coluna]       == 0 &&
                 grade[peca->blocos[2].linha-1][peca->blocos[2].coluna+1]   == 0 &&
                 grade[peca->blocos[3].linha+1][peca->blocos[3].coluna+1]   == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  += 1;
                peca->blocos[0].coluna -= 1;
                peca->blocos[2].linha  -= 1;
                peca->blocos[2].coluna += 1;
                peca->blocos[3].linha  += 1;
                peca->blocos[3].coluna += 1;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
    }
    //PECA DO TIPO PERNA (FEITO)
    else if ( peca->tipo == 4){
        if ( peca->rotacao == 1){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha-1][peca->blocos[0].coluna+1]   == 0 &&
                 grade[peca->blocos[1].linha][peca->blocos[1].coluna]       == 0 &&
                 grade[peca->blocos[2].linha+1][peca->blocos[2].coluna-1]   == 0 &&
                 grade[peca->blocos[3].linha][peca->blocos[3].coluna-2]     == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  -= 1;
                peca->blocos[0].coluna += 1;
                peca->blocos[2].linha  += 1;
                peca->blocos[2].coluna -= 1;
                peca->blocos[3].coluna -= 2;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else if ( peca->rotacao == 2){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha+2][peca->blocos[0].coluna+1]   == 0 &&
                 grade[peca->blocos[1].linha+1][peca->blocos[1].coluna]     == 0 &&
                 grade[peca->blocos[2].linha][peca->blocos[2].coluna-1]     == 0 &&
                 grade[peca->blocos[3].linha-1][peca->blocos[3].coluna]     == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  += 2;
                peca->blocos[0].coluna += 1;
                peca->blocos[1].linha  += 1;
                peca->blocos[2].coluna -= 1;
                peca->blocos[3].linha  -= 1;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else if ( peca->rotacao == 3){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha][peca->blocos[0].coluna-1]     == 0 &&
                 grade[peca->blocos[1].linha-1][peca->blocos[1].coluna]     == 0 &&
                 grade[peca->blocos[2].linha-2][peca->blocos[2].coluna+1]   == 0 &&
                 grade[peca->blocos[3].linha-1][peca->blocos[3].coluna+2]   == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].coluna -= 1;
                peca->blocos[1].linha  -= 1;
                peca->blocos[2].linha  -= 2;
                peca->blocos[2].coluna += 1;
                peca->blocos[3].linha  -= 1;
                peca->blocos[3].coluna += 2;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else if ( peca->rotacao == 4){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha-1][peca->blocos[0].coluna-1]   == 0 &&
                 grade[peca->blocos[1].linha][peca->blocos[1].coluna]       == 0 &&
                 grade[peca->blocos[2].linha+1][peca->blocos[2].coluna+1]   == 0 &&
                 grade[peca->blocos[3].linha+2][peca->blocos[3].coluna]     == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  -= 1;
                peca->blocos[0].coluna -= 1;
                peca->blocos[2].linha  += 1;
                peca->blocos[2].coluna += 1;
                peca->blocos[3].linha  += 2;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
    }
    //PECA DO TIPO COBRA PRA ESQUERDA (FEITO)
    else if ( peca->tipo == 5){
        if ( peca->rotacao == 1){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha-1][peca->blocos[0].coluna-1]   == 0 &&
                 grade[peca->blocos[1].linha][peca->blocos[1].coluna]       == 0 &&
                 grade[peca->blocos[2].linha+1][peca->blocos[2].coluna-1]   == 0 &&
                 grade[peca->blocos[3].linha+2][peca->blocos[3].coluna]     == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  -= 1;
                peca->blocos[0].coluna -= 1;
                peca->blocos[2].linha  += 1;
                peca->blocos[2].coluna -= 1;
                peca->blocos[3].linha  += 2;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else if ( peca->rotacao == 2){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha-1][peca->blocos[0].coluna+1]   == 0 &&
                 grade[peca->blocos[1].linha][peca->blocos[1].coluna]       == 0 &&
                 grade[peca->blocos[2].linha-1][peca->blocos[2].coluna-1]   == 0 &&
                 grade[peca->blocos[3].linha][peca->blocos[3].coluna-2]     == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  -= 1;
                peca->blocos[0].coluna += 1;
                peca->blocos[2].linha  -= 1;
                peca->blocos[2].coluna -= 1;
                peca->blocos[3].coluna -= 2;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else if ( peca->rotacao == 3){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha+2][peca->blocos[0].coluna+1]   == 0 &&
                 grade[peca->blocos[1].linha+1][peca->blocos[1].coluna]     == 0 &&
                 grade[peca->blocos[2].linha][peca->blocos[2].coluna+1]     == 0 &&
                 grade[peca->blocos[3].linha-1][peca->blocos[3].coluna]     == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  += 2; 
                peca->blocos[0].coluna += 1;
                peca->blocos[1].linha  += 1;
                peca->blocos[2].coluna += 1;
                peca->blocos[3].linha  -= 1;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else if ( peca->rotacao == 4){
            //verificando se rotacao eh valida, e se sim, alterando matriz
            if ( grade[peca->blocos[0].linha][peca->blocos[0].coluna-1]   == 0 &&
                 grade[peca->blocos[1].linha-1][peca->blocos[1].coluna]   == 0 &&
                 grade[peca->blocos[2].linha][peca->blocos[2].coluna+1]   == 0 &&
                 grade[peca->blocos[3].linha-1][peca->blocos[3].coluna+2] == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].coluna -= 1;
                peca->blocos[1].linha  -= 1;
                peca->blocos[2].coluna += 1;
                peca->blocos[3].linha  -= 1;
                peca->blocos[3].coluna += 2;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
    }
    //PECA DO TIPO COBRA PRA DIREITA (consertar)
    else if ( peca->tipo == 6){
        if ( peca->rotacao == 1){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha][peca->blocos[0].coluna-2]     == 0 &&
                 grade[peca->blocos[1].linha+1][peca->blocos[1].coluna-1]   == 0 &&
                 grade[peca->blocos[2].linha][peca->blocos[2].coluna]       == 0 &&
                 grade[peca->blocos[3].linha+1][peca->blocos[3].coluna+1]   == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].coluna -= 2;
                peca->blocos[1].linha  += 1;
                peca->blocos[1].coluna -= 1;
                peca->blocos[3].linha  += 1;
                peca->blocos[3].coluna += 1;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else if ( peca->rotacao == 2){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha-2][peca->blocos[0].coluna+1]   == 0 &&
                 grade[peca->blocos[1].linha-1][peca->blocos[1].coluna]     == 0 &&
                 grade[peca->blocos[2].linha][peca->blocos[2].coluna+1]     == 0 &&
                 grade[peca->blocos[3].linha+1][peca->blocos[3].coluna]     == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  -= 2;
                peca->blocos[0].coluna += 1;
                peca->blocos[1].linha  -= 1;
                peca->blocos[2].coluna += 1;
                peca->blocos[3].linha  += 1;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else if ( peca->rotacao == 3){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha+1][peca->blocos[0].coluna+1]   == 0 &&
                 grade[peca->blocos[1].linha][peca->blocos[1].coluna]       == 0 &&
                 grade[peca->blocos[2].linha+1][peca->blocos[2].coluna-1]   == 0 &&
                 grade[peca->blocos[3].linha][peca->blocos[3].coluna-2]     == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  += 1; 
                peca->blocos[0].coluna += 1;
                peca->blocos[2].linha  += 1;
                peca->blocos[2].coluna -= 1;
                peca->blocos[3].coluna -= 2;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
        else if ( peca->rotacao == 4){
            //verificando se rotacao eh valida, e se sim, alterando matriz (OK)
            if ( grade[peca->blocos[0].linha+1][peca->blocos[0].coluna]   == 0 &&
                 grade[peca->blocos[1].linha][peca->blocos[1].coluna+1]   == 0 &&
                 grade[peca->blocos[2].linha-1][peca->blocos[2].coluna]   == 0 &&
                 grade[peca->blocos[3].linha-2][peca->blocos[3].coluna+1] == 0 ){
                //atualizando posicoes dos blocos da peca
                peca->blocos[0].linha  += 1;
                peca->blocos[1].coluna += 1;
                peca->blocos[2].linha  -= 1;
                peca->blocos[3].linha  -= 2;
                peca->blocos[3].coluna += 1;
                //atualizando grade com novas posicoes da peca
                for (i=0; i<4; i++){
                    linha = peca->blocos[i].linha;
                    coluna = peca->blocos[i].coluna;
                    grade[linha][coluna] = peca->tipo;
                }
            }
            else valido = FALSE;
        }
    }
    if (!valido){
        //restaurando rotacao inicial
        if (peca->rotacao == 1) peca->rotacao = 4;
        else peca->rotacao -= 1;
        //restaurando posicoes iniciais
        for (i=0; i<4; i++){
            linha = peca->blocos[i].linha;
            coluna = peca->blocos[i].coluna;
            grade[linha][coluna] = peca->tipo; //limpando
        }
    }
}

