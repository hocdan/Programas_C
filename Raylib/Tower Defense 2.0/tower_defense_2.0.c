#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#define LINHA 70
#define COLUNA 70
#define NUM_GRUPOS 4
#define TAM 20
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
    0- terra
    1- agua 
    2- arvore
    3- mobs 
    4- caminho dos mobs
    5- construcoes
    6- torre
*/

typedef struct Anjo{
    char nome[21];
    char direcao;
    float armadura;
    float vida;
    int linha;
    int coluna;
    int gold;
    bool status;
} Anjo;

typedef struct Torre{
    char alvo[21];
    float dano;
    int nivel;
    int range;
    int linha;
    int coluna;
} Torre;

int main(){
    //Definicoes das funcoes a serem usadas no jogo
    void limparVetor(int mundo[LINHA][COLUNA], struct Anjo inimigo[NUM_GRUPOS][TAM], int linha, int coluna, int *tam);
    void moverInimigo( int mundo[LINHA][COLUNA], struct Anjo inimigo[NUM_GRUPOS][TAM], int i, int j, float *vidaBase);
    void addTorre(struct Torre *defesas, int n, int l, int c);
    void setarAlvo(int mundo[LINHA][COLUNA], struct Anjo inimigo[NUM_GRUPOS][TAM], int tam1, int tam2, int tam3, int tam4, struct Torre *defesas, int x);
    void atacarAlvo(int mundo[LINHA][COLUNA], struct Anjo inimigo[NUM_GRUPOS][TAM], int tam1, int tam2, int tam3, int tam4, struct Torre *defesas, int x);
    
    //Constantes do jogo
    const int largura = 1000;
    const int altura = 700;
    //Variaveis do jogador
    const char nomeJogador[21] = "Jogador Numero 1";
    int goldJogador = 100;     
    //Variaveis do jogo
    int i, j, tam = 0, repetir, numTorres = 0, frames = 0, turno = 0;
    int tam1 = TAM, tam2 = TAM, tam3 = TAM, tam4 = TAM; //tamanho dos vetores de inimigos (padrao = 20)
    int taxaL = 2, taxaM = 1, taxaT = 1; //taxas que regulam o nascimento e velocidade dos inimigos e velocidade das torres
    float vidaBase = 100; //vida da base, chegando a zero...GAME OVER
    char stringVazia[21] = ""; //string usada para comparacoes
    int mundo[LINHA][COLUNA];
    bool okComprarTorre = false;
    
    //Inicializando vetor de torres
    struct Torre *defesas;
    
    //inicializando vetor de inimigos
    struct Anjo inimigos[NUM_GRUPOS][TAM];
    for (i=0; i<NUM_GRUPOS; i++){
        for (j=0; j<TAM; j++){
            //convertendo int em string 
            char id[11];
            printf( id, "%d", j);
            //Inicializando atributos especificos de acordo com o local de spawn
            if (i == 0){
                strcpy( inimigos[i][j].nome, "Anjo N");
                strcat( inimigos[i][j].nome, id); //concatenando id com o nome Anjo
                inimigos[i][j].direcao = 's';
                inimigos[i][j].armadura = 0;
                inimigos[i][j].vida = 15;
                inimigos[i][j].linha = 0;
                inimigos[i][j].coluna = 34;
                inimigos[i][j].gold = 10;
                inimigos[i][j].status = false;
            }
            else if (i == 1){
                strcpy( inimigos[i][j].nome, "Anjo W");
                strcat( inimigos[i][j].nome, id); //concatenando id com o nome Anjo
                inimigos[i][j].direcao = 'd';
                inimigos[i][j].armadura = 10;
                inimigos[i][j].vida = 20;
                inimigos[i][j].linha = 34;
                inimigos[i][j].coluna = 0;
                inimigos[i][j].gold = 20;
                inimigos[i][j].status = false;
            }
            else if (i == 2){
                strcpy( inimigos[i][j].nome, "Anjo S");
                strcat( inimigos[i][j].nome, id); //concatenando id com o nome Anjo
                inimigos[i][j].direcao = 'w';
                inimigos[i][j].armadura = 15;
                inimigos[i][j].vida = 25;
                inimigos[i][j].linha = 69;
                inimigos[i][j].coluna = 34;
                inimigos[i][j].gold = 30;
                inimigos[i][j].status = false;
            }
            else if ( i == 3){
                strcpy( inimigos[i][j].nome, "Anjo E");
                strcat( inimigos[i][j].nome, id); //concatenando id com o nome Anjo
                inimigos[i][j].direcao = 'a';
                inimigos[i][j].armadura = 20;
                inimigos[i][j].vida = 30;
                inimigos[i][j].linha = 34;
                inimigos[i][j].coluna = 69;
                inimigos[i][j].gold = 40;
                inimigos[i][j].status = false;
            }
        }
    }
    
    //Jogando o arquivo do mundo na matriz
    FILE *fp;
    if ( (fp = fopen("mundo.txt", "r")) == NULL) exit(1);
    
    for (i=0; i<LINHA; i++){
        for (j=0; j<COLUNA; j++){
            if ( j == (COLUNA-1)) fscanf( fp, "%d\n", &mundo[i][j]);
            else fscanf(fp, "%d", &mundo[i][j]);
        }
    }
    
    fclose(fp);
    
    //janelas do jogo
    Rectangle abaMenu= {0, 0, 300, altura};
    Rectangle abaJogo = {300, 0, 700, altura};
    Rectangle abaPerfil = {10, 10, 280, 280};
    Rectangle comprarTorre = {10, 300, 80, 80};
    
    //Iniciando tela e FPS
    InitWindow( largura, altura, "Tower Defense");
    
    SetTargetFPS(60);
    
    //Loop principal
    while ( !WindowShouldClose()){
        
        //Update do jogo
        
        //checando toque nos botoes do menu
        if ( CheckCollisionPointRec( GetMousePosition(), comprarTorre) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if (goldJogador >= 50) okComprarTorre = true;
        }
        //verificando compra de torre
        if (okComprarTorre){
            //percorrendo matriz e vendo se o usuario selecionou algum local para a torre
            for (i=0; i<LINHA; i++){
                for (j=0; j<COLUNA; j++){
                    if ( IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec( GetMousePosition(), (Rectangle) {j*10 + 300, i*10, 10, 10}) && mundo[i][j] != 4 && mundo[i][j] != 6) {
                        okComprarTorre = false;
                        goldJogador -= 50; //valor da torre
                        //chamando funcoes de criar e adicionar torres de acordo com a situacao
                        if ( numTorres == 0){
                            //Alocando vetor de defesas apos a primeira compra
                            defesas = malloc(1*sizeof(struct Torre));
                            strcpy(defesas[0].alvo, "");
                            defesas[0].dano = 10;
                            defesas[0].nivel = 1;
                            defesas[0].range = 5;
                            defesas[0].linha = i;
                            defesas[0].coluna = j;
                            numTorres++; //atualizando
                        }
                        else{
                            numTorres++; //atualizando
                            //Realocando vetor de defesas de acordo com o numero de torres existentes apos a compra
                            defesas = (struct Torre*)realloc(defesas, sizeof(struct Torre)*numTorres);
                            strcpy(defesas[numTorres-1].alvo, "");
                            defesas[numTorres-1].dano = 10;
                            defesas[numTorres-1].nivel = 1;
                            defesas[numTorres-1].range = 5;
                            defesas[numTorres-1].linha = i;
                            defesas[numTorres-1].coluna = j;
                        }
                        mundo[i][j] = 6;
                        break; //evitando que hajam compras multiplas por acaso
                    }
                }
            }
        }
        
        frames++;
        if ( frames%20 == 0) {
            turno++; //turno sendo atualizado a cada 1/3 de segundo
            //Liberando inimigos do grupo 1 (NORTE) no inicio do jogo
            if (turno%taxaL == 0 && turno <= 20){
                for (i=0; i<tam1; i++){
                    if ( inimigos[0][i].status == false){
                        mundo[inimigos[0][i].linha][inimigos[0][i].coluna] = 3; //jogando inimigo na matriz mundo
                        inimigos[0][i].status = true;
                        break; //encerrando laco pois um inimigo ja foi liberado
                    }
                }
            }
            //Loberando inimigos do grupo 2 (OESTE) a partir do turno 20
            if (turno >= 20 && turno%taxaL == 0 && turno <= 40){
                for (i=0; i<tam2; i++){
                    if ( inimigos[1][i].status == false){
                        mundo[inimigos[1][i].linha][inimigos[1][i].coluna] = 3; //jogando inimigo na matriz mundo
                        inimigos[1][i].status = true;
                        break; //encerrando laco pois um inimigo ja foi liberado
                    }
                }
            }
            //Loberando inimigos do grupo 3 (SUL) a aprtir do turno 40
            if (turno >= 40 && turno%taxaL == 0 && turno <= 60){
                for (i=0; i<tam3; i++){
                    if ( inimigos[2][i].status == false){
                        mundo[inimigos[2][i].linha][inimigos[2][i].coluna] = 3; //jogando inimigo na matriz mundo
                        inimigos[2][i].status = true;
                        break; //encerrando laco pois um inimigo ja foi liberado
                    }
                }
            }
            //Loberando inimigos do grupo 4 (LESTE) a partir do turno 60
            if (turno >= 60 && turno%taxaL == 0 && turno <= 80){
                for (i=0; i<tam; i++){
                    if ( inimigos[3][i].status == false){
                        mundo[inimigos[3][i].linha][inimigos[3][i].coluna] = 3; //jogando inimigo na matriz mundo
                        inimigos[3][i].status = true;
                        break; //encerrando laco pois um inimigo ja foi liberado
                    }
                }
            }
            //Movendo inimigos a cada x segundos de acordo com a taxaM (taxa de movimento)
            if (turno%taxaM == 0){
                for (i=0; i<NUM_GRUPOS; i++){
                    //adequando busca de acordo com o grupo (1, 2, 3 ou 4)
                    if (i==0) tam = tam1;
                    else if (i==1) tam = tam2;
                    else if (i==2) tam = tam3;
                    else if (i==3) tam = tam4;
                    while (1){
                        repetir = 0; //flag usada para percorrer o vetor de inimigos enquanto houver necessidade
                        for (j=0; j<tam; j++){
                            //Verificando se algum inimigo morreu
                            if ( inimigos[i][j].vida <= 0){
                                mundo[inimigos[i][j].linha][inimigos[i][j].coluna] = 4; //apagando inimigo do mapa
                                if (i==0) {
                                    limparVetor(mundo, inimigos, i, j, &tam1);
                                    goldJogador += inimigos[i][j].gold;
                                }
                                if (i==1) {
                                    limparVetor(mundo, inimigos, i, j, &tam2);
                                    goldJogador += inimigos[i][j].gold;
                                }
                                if (i==2) {
                                    limparVetor(mundo, inimigos, i, j, &tam3);
                                    goldJogador += inimigos[i][j].gold;
                                }
                                if (i==3) {
                                    limparVetor(mundo, inimigos, i, j, &tam4);
                                    goldJogador += inimigos[i][j].gold;
                                }
                                repetir = 1;
                                break;
                            }
                            //Movendo os inimigos vivos
                            if ( inimigos[i][j].status == true) moverInimigo(mundo, inimigos, i, j, &vidaBase);
                        }
                        //verficando se o laco deve continuar...
                        if (!repetir) break;
                    }
                }
            }
            //Analisando se ha inimigos no alcance das torres, e se houver, travar no alvo e atacar
        if (turno%taxaT == 0 && numTorres >= 1 && (tam1 > 0 || tam2 > 0 || tam3 > 0 || tam4 > 0)){
                for (i=0; i<numTorres; i++){
                    //Verificando se algum inimigo esta na mira da torre (se ela ja nao tiver um alvo na mira)
                    if ( strcmp(defesas[i].alvo, stringVazia) == 0) setarAlvo( mundo, inimigos, tam1, tam2, tam3, tam4, defesas, i);
                    else atacarAlvo( mundo, inimigos, tam1, tam2, tam3, tam4, defesas, i);
                }
            }
        }
        
        //Renderizacao do jogo
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            DrawRectangleRec( abaJogo, BLACK);
            DrawRectangleRec( abaMenu, GRAY);
            
            //pixelizando a tela de acordo com as informacoes na matriz mundo
            for (i=0; i<LINHA; i++){
                for (j=0; j<COLUNA; j++){
                    if (mundo[i][j] == 0) DrawRectangle(j*10 + 300, i*10, 10, 10, GREEN);
                    else if (mundo[i][j] == 1) DrawRectangle(j*10 + 300, i*10, 10, 10, BLUE);
                    else if (mundo[i][j] == 2) DrawRectangle(j*10 + 300, i*10, 10, 10, DARKGREEN);
                    else if (mundo[i][j] == 3) DrawRectangle(j*10 + 300, i*10, 10, 10, RED);
                    else if (mundo[i][j] == 4) DrawRectangle(j*10 + 300, i*10, 10, 10, GOLD);
                    else if (mundo[i][j] == 5) DrawRectangle(j*10 + 300, i*10, 10, 10, DARKBROWN);
                    else if (mundo[i][j] == 6) DrawRectangle(j*10 + 300, i*10, 10, 10, VIOLET);
                }
            }
            //Desenhando botoes e informacoes na aba Menu
            DrawRectangleRec( abaPerfil, BLACK); // area onde as informacoes do jogador irao aparecer
            DrawText(FormatText("TOWER DEFENSE 2.0"), 35, 15, 22, ORANGE);
            DrawText(FormatText("Turno: %d", turno), 20, 50, 15, ORANGE);
            DrawText(FormatText("Nome: %s", nomeJogador), 20, 70, 15, ORANGE);
            DrawText(FormatText("Gold: %d", goldJogador), 20, 90, 15, ORANGE);
            DrawText(FormatText("Torres: %d", numTorres), 20, 110, 15, ORANGE); 
            DrawText(FormatText("Inimigos vivos: %d", (tam1+tam2+tam3+tam4)), 20, 130, 15, ORANGE);
            DrawText(FormatText("Integridade da base: %d / 100", (int)vidaBase), 20, 150, 15, ORANGE);
            DrawRectangleRec( comprarTorre, VIOLET); //botao para realizar compras de Torres
            if (okComprarTorre) DrawRectangleLines( comprarTorre.x, comprarTorre.y, comprarTorre.width, comprarTorre.height, BLACK);
            
        EndDrawing();
        
    }
    free(defesas); //limpando vetor alocado dinamicamente
    
    CloseWindow(); //encerrando jogo
    
    return 0;
}

void atacarAlvo(int mundo[LINHA][COLUNA], struct Anjo inimigo[NUM_GRUPOS][TAM], int tam1, int tam2, int tam3, int tam4, struct Torre *defesas, int x){
    int i, j, tam, range = defesas[x].range;
    int lAlvo, cAlvo, l = defesas[x].linha, c = defesas[x].coluna;
    bool noAlcance = false;
    //Procurando alvo e verificando se ainda esta dentro da range da torre
    for (i=0; i<NUM_GRUPOS; i++){
        //adequando busca de acordo com o grupo
        if (i==0) tam = tam1;
        else if (i==1) tam = tam2;
        else if (i==2) tam = tam3;
        else if (i==3) tam = tam4;
        //buscando no vetor do grupo i
        for (j=0; j<tam; j++){
            lAlvo = inimigo[i][j].linha;
            cAlvo = inimigo[i][j].coluna;
            if ( (strcmp(defesas[x].alvo, inimigo[i][j].nome) == 0) && (lAlvo >= (l-range) && lAlvo <= (l+range)) && (cAlvo >= (c-range) && cAlvo <= (c+range))){
                noAlcance = true;
                if ( inimigo[i][j].armadura <= 0) inimigo[i][j].vida -= defesas[x].dano;
                else inimigo[i][j].armadura -= defesas[x].dano;
                break; //finalizando busca e ataque por este turno
            }
        }
    }
    //Caso o alvo esteja fora de alcance ou morto...atualizar alvo para nulo
    if (!noAlcance || inimigo[i][j].vida <= 0) strcpy(defesas[x].alvo, "");
}

void setarAlvo(int mundo[LINHA][COLUNA], struct Anjo inimigo[NUM_GRUPOS][TAM], int tam1, int tam2, int tam3, int tam4, struct Torre *defesas, int x){
    int i, j, tam, linhaAlvo, colunaAlvo;
    int l = defesas[x].linha, c = defesas[x].coluna;
    bool achou = false;
    //Procurando inimigos dentro da range da torre
    for (i=1; i <= defesas[x].range; i++){
        if ( (l-i) >= 0 && (l+i) < LINHA && (c-i) >= 0 && (c+i) < COLUNA){
            if (mundo[l-i][c-i] == 3){
                linhaAlvo = l-i;
                colunaAlvo = c-i;
                achou = true;
                break;
            }
            else if (mundo[l-i][c] == 3){
                linhaAlvo = l-i;
                colunaAlvo = c;
                achou = true;
                break;
            }
            else if (mundo[l-i][c+i] == 3){
                linhaAlvo = l-i;
                colunaAlvo = c+i;
                achou = true;
                break;
            }
            else if (mundo[l][c-i] == 3){
                linhaAlvo = l;
                colunaAlvo = c-i;
                achou = true;
                break;
            }
            else if (mundo[l][c+i] == 3){
                linhaAlvo = l;
                colunaAlvo = c+i;
                achou = true;
                break;
            }
            else if (mundo[l+i][c-i] == 3){
                linhaAlvo = l+i;
                colunaAlvo = c-i;
                achou = true;
                break;
            }
            else if (mundo[l+i][c] == 3){
                linhaAlvo = l+i;
                colunaAlvo = c;
                achou = true;
                break;
            }
            else if (mundo[l+i][c+i] == 3){
                linhaAlvo = l+i;
                colunaAlvo = c+i;
                achou = true;
                break;
            }
        }
    }
    //Procurando inimigo com as coordenadas encontradas pela torre e setando-o como alvo
    if (achou){
        for (i=0; i<NUM_GRUPOS; i++){
            //adequando busca de acordo com o grupo
            if (i==0) tam = tam1;
            else if (i==1) tam = tam2;
            else if (i==2) tam = tam3;
            else if (i==3) tam = tam4;
            //buscando no vetor do grupo i
            for (j=0; j<tam; j++){
                if ( inimigo[i][j].linha == linhaAlvo && inimigo[i][j].coluna == colunaAlvo){
                    strcpy( defesas[x].alvo, inimigo[i][j].nome);
                    break;
                }
            }
        }
    }
}

void limparVetor(int mundo[LINHA][COLUNA], struct Anjo inimigo[NUM_GRUPOS][TAM], int linha, int coluna, int *tam){    
    int i;
    int alterar = 0;
    //Excluindo inimigo morto do vetor de inimigos
    for(i=0; i<(*tam-1); i++){
        if ( i == coluna){
            alterar = 1;
        }
        if (alterar) {
            strcpy(inimigo[linha][i].nome, inimigo[linha][i+1].nome); //sobrescrevendo nome
            inimigo[linha][i].direcao = inimigo[linha][i+1].direcao;
            inimigo[linha][i].armadura = inimigo[linha][i+1].armadura;
            inimigo[linha][i].vida = inimigo[linha][i+1].vida;
            inimigo[linha][i].linha = inimigo[linha][i+1].linha;
            inimigo[linha][i].coluna = inimigo[linha][i+1].coluna;
            inimigo[linha][i].gold = inimigo[linha][i+1].gold;
            inimigo[linha][i].status = inimigo[linha][i+1].status; 
            
        }
    }
    *tam -= 1; //atualizando tamanho do vetor para que os inimigos mortos nao facam mais parte do jogo
}

void moverInimigo( int mundo[LINHA][COLUNA], struct Anjo inimigo[NUM_GRUPOS][TAM], int i, int j, float *vidaBase){
    int linha = inimigo[i][j].linha;
    int coluna = inimigo[i][j].coluna;
    //Apagando local antigo do inimigo
    mundo[linha][coluna] = 4;
    //Movendo posicao do inimigo de acordo com sua direcao
    if ( mundo[linha-1][coluna] == 4 && inimigo[i][j].direcao != 's'){
        inimigo[i][j].linha = linha-1; //alterando atributo 
        mundo[inimigo[i][j].linha][inimigo[i][j].coluna] = 3; //atualizando localizacao do inimigo no mundo
        inimigo[i][j].direcao = 'w'; //atualizando direcao do inimigo
    }
    else if ( mundo[linha][coluna-1] == 4 && inimigo[i][j].direcao != 'd'){
        inimigo[i][j].coluna = coluna-1;
        mundo[inimigo[i][j].linha][inimigo[i][j].coluna] = 3;
        inimigo[i][j].direcao = 'a';
    }
    else if ( mundo[linha+1][coluna] == 4 && inimigo[i][j].direcao != 'w'){
        inimigo[i][j].linha = linha+1;
        mundo[inimigo[i][j].linha][inimigo[i][j].coluna] = 3;
        inimigo[i][j].direcao = 's';
    }
    else if ( mundo[linha][coluna+1] == 4 && inimigo[i][j].direcao != 'a'){
        inimigo[i][j].coluna = coluna+1;
        mundo[inimigo[i][j].linha][inimigo[i][j].coluna] = 3;
        inimigo[i][j].direcao = 'd';
    }
    else{
        //Auto-explosao do anjo ao chegar na base...
        inimigo[i][j].vida = 0;
        *vidaBase -= 2.5;
    }
    
}
