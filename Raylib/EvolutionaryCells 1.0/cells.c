#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#define LINHA 60
#define COLUNA 120

/*
    Legenda da matriz:
    0 - vazio
    1 - alimento
    2 - celula
*/

typedef struct Cell{
    //atributos responsaveis pela sobrevivencia da celula
    int vida; //quanto dano a celula aguenta receber, se chegar a 0 a celula morrera
    int energia; //reserva necessaria para a celula se sustentar (reproduzir e locomover), recarrega ao se alimentar
    int velocidade; //o quanto a celula pode se mover por segundo
    int visao; //o quao longe a celula pode observar no ambiente
    //atributos necessarios para localizacao na matriz
    int linha;
    int coluna;
    
} Cell;

int main(void){
    //Prototipos das funcoes a serem usadas
    void limparVetor(int grade[LINHA][COLUNA], struct Cell *celulas, int x, int numCelulas);
    void moverCelula(int grade[LINHA][COLUNA], struct Cell *celulas, int x);
    int reproduzir(int grade[LINHA][COLUNA], struct Cell *celulas, int x, int numCelulas, int geracao);
    
    //constantes do programa
    const int largura = 1200;
    const int altura = 700;
    
    //variaveis do programa
    int i, j, alet, frames = 0;
    int numCelulas = 0, geracao = 1;
    int grade[LINHA][COLUNA];
    struct Cell *celulas; //declarando vetor dinamico que ira armazenar as celulas
    
    //inicializando matriz com valor padrao (0 - vazio)
    for (i=0; i<LINHA; i++){
        for (j=0; j<COLUNA; j++){
            alet = GetRandomValue(0, 99);
            if ( alet >= 0 && alet < 10) grade[i][j] = 1; //10% de chance de gerar alimento
            else grade[i][j] = 0;
        }
    }
    
    //janelas da simulacao
    Rectangle simulacao = {0, 100, largura, 600};
    Rectangle menu = {0, 0, largura, 100};
    
    //iniciando a janela da simulacao
    InitWindow(largura, altura, "Evolucionary Cells 1.0");
    SetTargetFPS(60); // setando o FPS da aplicacao
    
    //Loop principal do jogo
    while (!WindowShouldClose()){
        //Area responsavel pelo update da simulacao(atualizar variaveis a cada segundo):
        if (frames%60 == 0){
            //inicializando o vetor de celulas ou realocando caso necessario
            if ( numCelulas == 0 && frames ==0){
                numCelulas++;
                celulas = malloc(numCelulas*sizeof(struct Cell));
                //setando celula-mae com atributos base
                celulas[0].vida = GetRandomValue(40, 60); //valor base entre 10 e 20
                celulas[0].energia = GetRandomValue(50, 100); //valor base entre 10 e 100
                celulas[0].velocidade = GetRandomValue(1, 3); //valor base entre 1 e 3
                celulas[0].visao = GetRandomValue(1, 3); //valor base entre 1 e 3
                celulas[0].linha = GetRandomValue(0, 59); //valor base entre 0 e 59
                celulas[0].coluna = GetRandomValue(0, 119); //valor base entre 0 e 119
                //inserindo celula nova na grade
            }
            else if (numCelulas > 0){
                for (i=0; i<numCelulas; i++){
                    if (celulas[i].vida <= 0){ //morrer
                        limparVetor( grade, celulas, i, numCelulas);
                        numCelulas--; //atualizando numero de celulas
                        if (numCelulas > 0) celulas = (struct Cell*)realloc(celulas, sizeof(struct Cell)*numCelulas); //ajustando tamanho do vetor
                        break;
                    }
                    //
                    else if (celulas[i].energia >= 50){ //reproduzir
                        numCelulas += 2; //atualizando numero de celulas para acomodar as novas celulas
                        celulas = (struct Cell*)realloc(celulas, sizeof(struct Cell)*numCelulas); //realocando vetor
                        if (!reproduzir( grade, celulas, i, numCelulas, geracao)){
                            numCelulas -= 2;
                            celulas = (struct Cell*)realloc(celulas, sizeof(struct Cell)*numCelulas); //realocando vetor
                        }
                        if ( i == (numCelulas-1)) geracao++; //atualizando geracao a cada nova reproducao do mais novo
                        celulas[i].energia -= 50;
                        break;
                    }
                    //
                    else if (celulas[i].energia <= 0){
                        celulas[i].vida -= 2; //perdendo vida pois a celula ja nao tem energia
                        grade[celulas[i].linha][celulas[i].coluna] = 2; //jogando celula na grade
                        moverCelula(grade, celulas, i);
                    }
                    else{ //mover
                        grade[celulas[i].linha][celulas[i].coluna] = 2; //jogando celula na grade
                        moverCelula(grade, celulas, i);
                    }
                }
            }
        }
        frames++;
        
        //Area responsavel pela rederizacao da simulacao:
        BeginDrawing();
            ClearBackground(RAYWHITE);
            //renderizando janelas de fundo
            DrawRectangleRec( simulacao, WHITE);
            DrawRectangleLines( simulacao.x, simulacao.y, simulacao.width, simulacao.height, GREEN);
            DrawRectangleRec( menu, DARKGRAY);
            DrawRectangleLines( menu.x, menu.y, menu.width, menu.height, GREEN);
            //renderizando matriz na area de simulacao
            for (i=0; i<LINHA; i++){
                for (j=0; j<COLUNA; j++){
                    //renderizando quadrados com linhas
                    if (grade[i][j] == 0) DrawRectangle( j*10, i*10 + 100, 10, 10, BLACK);
                    else if (grade[i][j] == 1) DrawRectangle( j*10, i*10 + 100, 10, 10, GREEN);
                    else if (grade[i][j] == 2) DrawRectangle( j*10, i*10 + 100, 10, 10, RED);
                    DrawRectangleLines( j*10, i*10 + 100, 10, 10, GREEN);
                }
            }
            //exibindo informacoes sobre a grade
            DrawText(FormatText("Frames: %d", frames), 10, 10, 15, GREEN);
            DrawText(FormatText("Geracao atual: %d", geracao), 10, 30, 15, GREEN);
            DrawText(FormatText("Celulas: %d", numCelulas), 10, 50, 15, GREEN);
            if (numCelulas > 0) DrawText(FormatText("( Vida: %d, Energia: %d, Velocidade: %d, Visao: %d, Linha: %d, Coluna: %d", celulas[numCelulas-1].vida, celulas[numCelulas-1].energia, celulas[numCelulas-1].velocidade, celulas[numCelulas-1].visao, celulas[numCelulas-1].linha, celulas[0].coluna), 200, 10, 15, GREEN);
            
        EndDrawing();
    }
    
    free(celulas); //desalocando vetor de celulas
    
    //Finalizando programa
    CloseWindow(); //fechando a janela e o OpenGL
    
    return 0;
}

int reproduzir(int grade[LINHA][COLUNA], struct Cell *celulas, int x, int numCelulas, int geracao){
    int n = numCelulas, mutacao = geracao;
    int i, j, linha = celulas[x].linha, coluna = celulas[x].coluna, l1= 0, c1 = 0, l2 = 0, c2 = 0;
    int okC1 = 0, okC2 = 0;
    //Verificando se o entorno da celula esta livre de outras celulas
    for(i=(linha-1); i<=(linha+1); i++){
        for (j=(coluna-1); j<=(coluna+1); j++){
            if (  (i >= 0 && i < LINHA) && (j >= 0 && j < COLUNA) && grade[i][j] != 2){
                if (!okC1){
                    l1 = i;
                    c1 = j;
                    okC1 = 1; //celula-filha 1 esta pronta
                }
                else if (!okC2){
                    l2 = i;
                    c2 = j;
                    okC2 = 1; //celula-filha 2 esta pronta
                }
            }
        }
    }
    //Se ambas as celulas-filhas estao prontas...entao realizar reproducao
    if ( okC1 && okC2){
        //celula-filha 1
        celulas[n-2].vida = GetRandomValue(40-mutacao, 60+mutacao);
        celulas[n-2].energia = GetRandomValue( 50-mutacao, 100+mutacao);
        celulas[n-2].velocidade = GetRandomValue( 1, 3+mutacao);
        celulas[n-2].visao = GetRandomValue( 1, 3+mutacao);
        celulas[n-2].linha = l1;
        celulas[n-2].coluna = c1;
        grade[l1][c1] = 2;
        //celula-filha 2
        celulas[n-1].vida = GetRandomValue(40-mutacao, 60+mutacao);
        celulas[n-1].energia = GetRandomValue( 50-mutacao, 100+mutacao);
        celulas[n-1].velocidade = GetRandomValue( 1, 3+mutacao);
        celulas[n-1].visao = GetRandomValue( 1, 3+mutacao);
        celulas[n-1].linha = l2;
        celulas[n-1].coluna = c2;
        grade[l2][c2] = 2;
        return 1; //se a reproducao ocorreu com sucesso
    }
    return 0; //se a reproducao nao ocorreu
}

void moverCelula(int grade[LINHA][COLUNA], struct Cell *celulas, int x){
    int alet, l = celulas[x].linha, c = celulas[x].coluna, alcance = celulas[x].velocidade;
    
    //Atualizando localizacao da celula
    grade[l][c] = 0;
    //aleatorizando a movimentacao
    alet = GetRandomValue(1, 8); 
    //celula perde energia proporcionalmente ao tanto de velocidade e visao
    celulas[x].energia -= celulas[x].velocidade;
    //Verificando possiveis posicoes na matriz
    if ( l-alcance >= 0 && c - alcance >= 0 && grade[l-alcance][c-alcance] != 2 && alet == 1) {
        if ( grade[l-alcance][c-alcance] == 1) celulas[x].energia += 20; //celula se alimentando
        grade[l-alcance][c-alcance] = 2; //atualizando nova localizacao
        celulas[x].linha = l-alcance;
        celulas[x].coluna = c-alcance;
    }
    else if ( l-alcance >= 0 && grade[l-alcance][c] != 2 && alet == 2) {
        if ( grade[l-alcance][c] == 1) celulas[x].energia += 20; //celula se alimentando
        grade[l-alcance][c] = 2; //atualizando nova localizacao
        celulas[x].linha = l-alcance;
        celulas[x].coluna = c;
    }
    else if ( l-alcance >= 0 && c + alcance < COLUNA && grade[l-alcance][c+alcance] != 2 && alet == 3) {
        if ( grade[l-alcance][c+alcance] == 1) celulas[x].energia += 20; //celula se alimentando
        grade[l-alcance][c+alcance] = 2; //atualizando nova localizacao
        celulas[x].linha = l-alcance;
        celulas[x].coluna = c+alcance;
    }
    else if ( c + alcance < COLUNA && grade[l][c+alcance] != 2 && alet == 4) {
        if ( grade[l][c+alcance] == 1) celulas[x].energia += 20; //celula se alimentando
        grade[l][c+alcance] = 2; //atualizando nova localizacao
        celulas[x].linha = l;
        celulas[x].coluna = c+alcance;
    }
    else if ( l+alcance < LINHA && c+alcance < COLUNA && grade[l+alcance][c+alcance] != 2 && alet == 5) {
        if ( grade[l+alcance][c+alcance] == 1) celulas[x].energia += 20; //celula se alimentando
        grade[l+alcance][c+alcance] = 2; //atualizando nova localizacao
        celulas[x].linha = l+alcance;
        celulas[x].coluna = c+alcance;
    }
    else if ( l+alcance < LINHA && grade[l+alcance][c] != 2 && alet == 6) {
        if ( grade[l+alcance][c] == 1) celulas[x].energia += 20; //celula se alimentando
        grade[l+alcance][c] = 2; //atualizando nova localizacao
        celulas[x].linha = l+alcance;
        celulas[x].coluna = c;
    }
    else if ( l+alcance < LINHA && c - alcance >= 0 && grade[l+alcance][c-alcance] != 2 && alet == 7) {
        if ( grade[l+alcance][c-alcance] == 1) celulas[x].energia += 20; //celula se alimentando
        grade[l+alcance][c-alcance] = 2; //atualizando nova localizacao
        celulas[x].linha = l+alcance;
        celulas[x].coluna = c-alcance;
    }
    else if ( c - alcance >= 0 && grade[l][c-alcance] != 2 && alet == 8) {
        if ( grade[l][c-alcance] == 1) celulas[x].energia += 20; //celula se alimentando
        grade[l][c-alcance] = 2; //atualizando nova localizacao
        celulas[x].linha = l;
        celulas[x].coluna = c-alcance;
    }
    else{
        grade[l][c] = 2; //atualizando nova localizacao (ficou no mesmo lugar)
        celulas[x].energia += (celulas[x].velocidade/2); //recuperando parte da energia por nao se movimentar
    }
    
}

void limparVetor(int grade[LINHA][COLUNA], struct Cell *celulas, int x, int numCelulas){    
    int i;
    int alterar = 0;
    //Excluindo celula morta da matriz
    grade[celulas[x].linha][celulas[x].coluna] = 0;
    //Excluindo celula morta do vetor de celulas
    for(i=0; i<(numCelulas-1); i++){
        if ( (numCelulas-1) == 0) break; //nao precisa substituir
        else if ( i == x){
            alterar = 1;
        }
        if (alterar) { 
            celulas[i].vida = celulas[i+1].vida;
            celulas[i].energia = celulas[i+1].energia;
            celulas[i].velocidade = celulas[i+1].velocidade;
            celulas[i].visao = celulas[i+1].visao;
            celulas[i].linha = celulas[i+1].linha;
            celulas[i].coluna = celulas[i+1].coluna;
        }
    }
}
