#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define LINHAS 15
#define COLUNAS 15
#define TAM 40
#define MEIO (LINHAS+COLUNAS)/4
#define TRUE 1
#define FALSE 0

/*
    DARKGRAY, MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, DARKBROWN,
    GRAY, RED, GOLD, LIME, BLUE, VIOLET, BROWN, LIGHTGRAY, PINK, YELLOW,
    GREEN, SKYBLUE, PURPLE, BEIGE!
    
    Legenda:
    0- vazio ()
    1- energia (---)
    2- nucleo (!)
    3- bloqueio (X)
    4- desvio para esquerda (<)
    5- desvio para direita (>)
    6- incremento de energia (^)
    7- congelamento (#)
    8- comprador (?)
*/

typedef struct Laser{
    int linha; //coordenada y da frente do laser
    int coluna; //coordenada x da frente do laser
    char direcao; //direcao da frente do laser
    int energiaAcumulada; //quantidade de "casas" que o laser pode percorrer
} Laser;

typedef struct Jogador{
    int runas[10]; //colecao de runas do jogador
    int numRunas; //numeros de runas que o jogador tem disponivel
} Jogador;

int main(){
    //constantes do jogo
    const int largura = 830;
    const int altura = 620;
    //variaveis do jogo
    int i, j, alet, valido = FALSE, vitoria = FALSE, derrota = FALSE, okJogar = FALSE, okComprar = FALSE, okLaser = FALSE;
    int efeito, runa, runaUsada, total = 40;
    int tabuleiro[LINHAS][COLUNAS]; //tabuleiro do jogo
    Laser laser = {0, 0, 's', 1}; //informacoes da frente do laser que irao ditar seu movimento
    Jogador jogador = { {3, 4, 5, 6, 7, 0, 0, 0, 0, 0}, 5}; //configuracao inicial do jogador
    //colecao de runas disponiveis ao longo do jogo todo
    int runasTotal[40] = {6, 6, 6, 6, 6, 7, 6, 6, 7, 6, 4, 4, 4, 6, 6, 6, 6, 5, 5, 5, 3, 3, 3, 3, 3, 3, 4, 4, 5, 5, 6, 4, 4, 4, 3, 3, 5, 5, 5, 6};

    //inicializando paineis e botoes do jogo
    Rectangle legenda = {620, 10, 200, 330};
    Rectangle leg0 = {630, 60, 20, 20};
    Rectangle leg1 = {630, 90, 20, 20};
    Rectangle leg2 = {630, 120, 20, 20};
    Rectangle leg3 = {630, 150, 20, 20};
    Rectangle leg4 = {630, 180, 20, 20};
    Rectangle leg5 = {630, 210, 20, 20};
    Rectangle leg6 = {630, 240, 20, 20};
    Rectangle leg7 = {630, 270, 20, 20};
    Rectangle leg8 = {630, 300, 20, 20};
    Rectangle leg9 = {630, 330, 20, 20};
    Rectangle botaoComprar = {660, 350, 120, 50};
    Rectangle botaoJogar = {660, 410, 120, 50};
    Rectangle deck = {620, 470, 200, 140};
    //inicializando locais dos quadrantes do tabuleiro
    Rectangle areaTab[LINHAS][COLUNAS];
    for (i=0; i<LINHAS; i++) {
        for (j=0; j<COLUNAS; j++) {
            areaTab[i][j].x = j*TAM+10;  
            areaTab[i][j].y = i*TAM+10;
            areaTab[i][j].width = TAM;
            areaTab[i][j].height = TAM;      
        }
    }
    //inicializando locais das runas do jogador
    int okRunas[10];
    Rectangle areaRunas[10];
    for (i=0; i<10; i++) {
        //runas da primeira fileira
        if (i < 5) {
            areaRunas[i].x = i*28+630+i*10;
            areaRunas[i].y = 480;
            areaRunas[i].width = 28;
            areaRunas[i].height = 55;
        } else {
        //runas da segunda fileira
            areaRunas[i].x = (i-5)*28+630+(i-5)*10;
            areaRunas[i].y = 545;
            areaRunas[i].width = 28;
            areaRunas[i].height = 55;
        }
        okRunas[i] = FALSE;
    }
    
    //inicializando matriz do tabuleiro com centro e bordas
    for (i=0; i<LINHAS; i++){
        for (j=0; j<COLUNAS; j++){
            //setando meio como objetivo principal, o resto ficara vazio (por enquanto)
            if ( i == MEIO && j == MEIO) tabuleiro[i][j] = 2;
            else tabuleiro[i][j] = 0;
        }
    }
    
    //setando spawn do laser em um dos 4 cantos de maneira aleatoria
    srand(time(NULL)); //setando a seed da randomizacao para o tempo atual
    alet = (rand()%4)+1;
    if (alet == 1) {
        tabuleiro[0][0] = 1;
        laser.linha = 0;
        laser.coluna = 0;
        //setando direcao que o laser vai seguir nesse canto
        alet = (rand()%10)+1;
        if (alet%2 == 0) laser.direcao = 'd'; //direita
        else laser.direcao = 's'; //para baixo
    }
    else if (alet == 2) {
        tabuleiro[0][COLUNAS-1] = 1;
        laser.linha = 0;
        laser.coluna = COLUNAS-1;
        //setando direcao que o laser vai seguir nesse canto
        alet = (rand()%10)+1;
        if (alet%2 == 0) laser.direcao = 'a'; //esquerda
        else laser.direcao = 's'; //para baixo
    }
    else if (alet == 3) {
        tabuleiro[LINHAS-1][0] = 1;
        laser.linha = LINHAS-1;
        laser.coluna = 0;
        //setando direcao que o laser vai seguir nesse canto
        alet = (rand()%10)+1;
        if (alet%2 == 0) laser.direcao = 'd'; //direita
        else laser.direcao = 'w'; //para cima
    }
    else if (alet == 4) {
        tabuleiro[LINHAS-1][COLUNAS-1] = 1;
        laser.linha = LINHAS-1;
        laser.coluna = COLUNAS-1;
        //setando direcao que o laser vai seguir nesse canto
        alet = (rand()%10)+1;
        if (alet%2 == 0) laser.direcao = 'a'; //esquerda
        else laser.direcao = 's'; //para cima
    }
    
    //Iniciando tela e FPS
    InitWindow( largura, altura, "F.L.I.P  1.0");
    
    SetTargetFPS(60);

    //Loop principal
    while (!WindowShouldClose()){
        //Update
        
        //checando se ainda ha runas com o jogador ou para comprar
        if (jogador.numRunas == 0 && total == 0) derrota = TRUE;
        //atualizando situacao do laser
        if ( okLaser ) {
            //verificando direcao de deslocamento e fazendo laser se mover por tantas casas
            for (i=0; i<laser.energiaAcumulada; i++) {
                if (laser.direcao == 'w' && laser.linha-1 >= 0) {
                    laser.linha--; //atualizando coordenadas do laser
                    //guardando antigo valor do quadrante do tabuleiro para onde o laser se deslocou
                    efeito = tabuleiro[laser.linha][laser.coluna];
                    //movendo laser para o novo local
                    tabuleiro[laser.linha][laser.coluna] = 1;
                } else if (laser.direcao == 'a' && laser.coluna-1 >= 0) {
                    laser.coluna--; //atualizando coordenadas do laser
                    //guardando antigo valor do quadrante do tabuleiro para onde o laser se deslocou
                    efeito = tabuleiro[laser.linha][laser.coluna];
                    //movendo laser para o novo local
                    tabuleiro[laser.linha][laser.coluna] = 1;
                } else if (laser.direcao == 's' && laser.linha+1 < LINHAS) {
                    laser.linha++; //atualizando coordenadas do laser
                    //guardando antigo valor do quadrante do tabuleiro para onde o laser se deslocou
                    efeito = tabuleiro[laser.linha][laser.coluna];
                    //movendo laser para o novo local
                    tabuleiro[laser.linha][laser.coluna] = 1;
                } else if (laser.direcao == 'd' && laser.coluna+1 < COLUNAS) {
                    laser.coluna++; //atualizando coordenadas do laser
                    //guardando antigo valor do quadrante do tabuleiro para onde o laser se deslocou
                    efeito = tabuleiro[laser.linha][laser.coluna];
                    //movendo laser para o novo local
                    tabuleiro[laser.linha][laser.coluna] = 1;
                } else {
                    //movimento invalido por alguma limitacao, logo aleatoriamente escolher outra direcao
                    alet = (rand()%4)+1;
                    if (alet == 1) laser.direcao = 'w';
                    else if (alet == 2) laser.direcao = 'a';
                    else if (alet == 3) laser.direcao = 's';
                    else if (alet == 4) laser.direcao = 'd';
                    i--; //resetando contador para o movimento invalido nao contar como deslocamento
                }
                //realizando efeito de acordo com a runa que estava no local que o laser entrou
                if (efeito == 2) {
                    efeito = 0; //resetando efeito
                    vitoria = TRUE; //Jogador alcancou o nucleo de energia!
                    break; //finalizando checagem e partindo para a declaracao de vitoria
                } else if ( efeito == 3) {
                    efeito = 0; //resetando efeito                    
                    break; //efeito BLOCK, logo o laser vai parar de se mover
                } else if (efeito == 4) {
                    efeito = 0; //resetando efeito
                    //efeito DESVIO PARA A ESQUERDA, vai depender da direcao atual sendo rotacionada 90 graus
                    if (laser.direcao == 'w') laser.direcao = 'a';
                    else if (laser.direcao == 'a') laser.direcao = 's';
                    else if (laser.direcao == 's') laser.direcao = 'd';
                    else laser.direcao = 'w';              
                } else if (efeito == 5) {
                    efeito = 0; //resetando efeito
                    //efeito DESVIO PARA A DIREITA, vai depender da direcao atual sendo rotacionada 90 graus
                    if (laser.direcao == 'w') laser.direcao = 'd';
                    else if (laser.direcao == 'a') laser.direcao = 'w';
                    else if (laser.direcao == 's') laser.direcao = 'a';
                    else laser.direcao = 's'; 
                } else if (efeito == 6) {
                    efeito = 0; //resetando efeito
                    //efeito INCREMENTO DE ENERGIA, vai aumentar o contador deste loop
                    laser.energiaAcumulada++;
                } else if (efeito == 7) {
                    efeito = 0; //resetando efeito
                    //efeito CONGELAMENTO, o laser vai parar de se mover E perder toda a energia acumulada
                    laser.energiaAcumulada = -1;
                    break;
                } else if (efeito == 8) {
                    efeito = 0; //resetando efeito
                    //efeito COMPRADOR, o jogador vai receber 1 runa (se houver espaco)
                    if (jogador.numRunas < 10 && total > 0) {
                        total--; //atualizando numero de runas do deck
                        runa = runasTotal[total];
                        runasTotal[total] = 0; //apagando runa comprada do sistema
                        //procurando local vazio para acrescentar a nova runa adquirida
                        for (i=0; i<10; i++) {
                            if (jogador.runas[i] == 0) {
                                jogador.runas[i] = runa;
                                break; //encerrando busca
                            }
                        }
                        jogador.numRunas++; //atualizando numero de runas do jogador
                    }
                }
            }
            okLaser = FALSE;
            //atualizando energiaAcumulada do laser
            if (laser.energiaAcumulada  < 5) laser.energiaAcumulada++;
            else laser.energiaAcumulada = 1; //resetando energia do laser assim que ultrapassar 5
        }
        //checando se o jogador ativou algum dos botoes
        if (CheckCollisionPointRec( GetMousePosition(), botaoComprar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !okJogar && !okComprar) okComprar = TRUE;
        else if (CheckCollisionPointRec( GetMousePosition(), botaoComprar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !okJogar && okComprar) okComprar = FALSE;
        if (CheckCollisionPointRec( GetMousePosition(), botaoJogar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !okComprar && !okJogar) okJogar = TRUE;
        else if (CheckCollisionPointRec( GetMousePosition(), botaoJogar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !okComprar && okJogar) okJogar = FALSE;
        //checando possiveis acoes do jogador ao estar apto a jogar
        if ( okJogar ) {
            //checando se o jogador clicou em alguma runa
            for (i=0; i<10; i++) {
                if ( CheckCollisionPointRec( GetMousePosition(), areaRunas[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && valido == FALSE && jogador.runas[i] != 0) {
                    okRunas[i] = TRUE;
                    runaUsada = i; //guardando posicao da runa selecionada
                    valido = TRUE;
                    break; //encerrando busca
                }
                else if ( CheckCollisionPointRec( GetMousePosition(), areaRunas[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && valido && okRunas[i]) {
                    okRunas[i] = FALSE;
                    runaUsada = -1; //resetando valor de runa usada para nenhuma/invalida
                    valido = FALSE;
                    break; //encerrando busca
                }
            }
            //checando se o jogador clicou em um quadrante do tabuleiro apos clicar em uma runa valida
            for (i=0; i<LINHAS; i++) {
                for (j=0; j<COLUNAS; j++) {
                    if ( CheckCollisionPointRec( GetMousePosition(), areaTab[i][j]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && valido) {
                        //area valida: quadrante vazio (0) ou quadrante de energia (1) que nao seja a frente do laser de energia 
                        if (tabuleiro[i][j] == 0 || (tabuleiro[i][j] == 1 && (i != laser.linha || j != laser.coluna))) {
                            tabuleiro[i][j] = jogador.runas[runaUsada]; //lancando runa no tabuleiro
                            //jogada concluida, atualizando status
                            okRunas[runaUsada] = FALSE; //runa acabou de ser usada
                            valido = FALSE;
                            okJogar = FALSE;
                            okLaser = TRUE;
                            //removendo runa usada do deck do jogador
                            jogador.runas[runaUsada] = 0;
                            jogador.numRunas--; //decrementando numero de runas do jogador
                            runaUsada = -1; //resetando valor de runa usada para nenhuma/invalida
                            break; //encerrando busca
                        }
                    }
                }
            } 
        } 
        //checando possiveis acoes do jogador ao estar apto a comprar
        else if ( okComprar ) {
            //se o jogador puder comprar mais runas e ainda houver runas
            if (jogador.numRunas < 10 && total > 0) {
                total--; //atualizando numero de runas do deck
                runa = runasTotal[total];
                runasTotal[total] = 0; //apagando runa comprada do sistema
                //procurando local vazio para acrescentar a nova runa adquirida
                for (i=0; i<10; i++) {
                    if (jogador.runas[i] == 0) {
                        jogador.runas[i] = runa;
                        break; //encerrando busca
                    }
                }
                jogador.numRunas++; //atualizando numero de runas do jogador  
            }
            okComprar = FALSE; //encerrando compra
            okLaser = TRUE;
        }
        //Draw
        BeginDrawing();
            ClearBackground(BLACK); //limpando toda a tela e setando cor PRETA de fundo
            //imprimindo legenda do tabuleiro
            DrawRectangle(legenda.x, legenda.y, legenda.width, legenda.height, YELLOW);
            DrawRectangleLines(legenda.x, legenda.y, legenda.width, legenda.height, BLACK);
            DrawText(FormatText("LEGENDA"), legenda.x+59, legenda.y+20, 20, BLACK);

            DrawRectangle(leg0.x, leg0.y, leg0.width, leg0.height, BEIGE);
            DrawRectangleLines(leg0.x, leg0.y, leg0.width, leg0.height, BLACK);
            DrawText(FormatText(" 1. Vazio"), leg0.x+40, leg0.y+4, 16, BLACK);
            
            DrawRectangle(leg1.x, leg1.y, leg1.width, leg1.height, SKYBLUE);
            DrawRectangleLines(leg1.x, leg1.y, leg1.width, leg1.height, BLACK);
            DrawText(FormatText(" 2. Energia"), leg1.x+40, leg1.y+4, 16, BLACK);

            DrawRectangle(leg2.x, leg2.y, leg2.width, leg2.height, GREEN);
            DrawRectangleLines(leg2.x, leg2.y, leg2.width, leg2.height, BLACK);
            DrawText(FormatText(" 3. Nucleo"), leg2.x+40, leg2.y+4, 16, BLACK);

            DrawRectangle(leg3.x, leg3.y, leg3.width, leg3.height, BROWN);
            DrawRectangleLines(leg3.x, leg3.y, leg3.width, leg3.height, BLACK);
            DrawText(FormatText(" 4. Bloqueio"), leg3.x+40, leg3.y+4, 16, BLACK);

            DrawRectangle(leg4.x, leg4.y, leg4.width, leg4.height, DARKGREEN);
            DrawRectangleLines(leg4.x, leg4.y, leg4.width, leg4.height, BLACK);
            DrawText(FormatText(" 5. Virar esquerda"), leg4.x+40, leg4.y+4, 16, BLACK);

            DrawRectangle(leg5.x, leg5.y, leg5.width, leg5.height, VIOLET);
            DrawRectangleLines(leg5.x, leg5.y, leg5.width, leg5.height, BLACK);
            DrawText(FormatText(" 6. Virar direita"), leg5.x+40, leg5.y+4, 16, BLACK);

            DrawRectangle(leg6.x, leg6.y, leg6.width, leg6.height, GOLD);
            DrawRectangleLines(leg6.x, leg6.y, leg6.width, leg6.height, BLACK);
            DrawText(FormatText(" 7. Incremento"), leg6.x+40, leg6.y+4, 16, BLACK);

            DrawRectangle(leg7.x, leg7.y, leg7.width, leg7.height, DARKBLUE);
            DrawRectangleLines(leg7.x, leg7.y, leg7.width, leg7.height, BLACK);
            DrawText(FormatText(" 8. Congelamento"), leg7.x+40, leg7.y+4, 16, BLACK);

            DrawRectangle(leg8.x, leg8.y, leg8.width, leg8.height, DARKGRAY);
            DrawRectangleLines(leg8.x, leg8.y, leg8.width, leg8.height, BLACK);
            DrawText(FormatText(" 9. Comprar 1 runa"), leg8.x+40, leg8.y+4, 16, BLACK);

            DrawRectangle(botaoComprar.x, botaoComprar.y, botaoComprar.width, botaoComprar.height, GREEN);
            if ( okComprar )DrawRectangleLines(botaoComprar.x+5, botaoComprar.y+5, botaoComprar.width-10, botaoComprar.height-10, BLACK);
            DrawText(FormatText("COMPRAR"), botaoComprar.x+11, botaoComprar.y+18, 20, BLACK);

            DrawRectangle(botaoJogar.x, botaoJogar.y, botaoJogar.width, botaoJogar.height, RED);
            if ( okJogar ) DrawRectangleLines(botaoJogar.x+5, botaoJogar.y+5, botaoJogar.width-10, botaoJogar.height-10, BLACK);
            DrawText(FormatText("JOGAR"), botaoJogar.x+26, botaoJogar.y+18, 20, BLACK);

            DrawRectangle(deck.x, deck.y, deck.width, deck.height, DARKGRAY);
            DrawRectangleLines(deck.x, deck.y, deck.width, deck.height, BLACK);
            
            if (!vitoria && !derrota) {
                //imprimindo tabuleiro com espacamento de 10 pixels nas bordas
                for (i=0; i<LINHAS; i++){
                    for (j=0; j<COLUNAS; j++){
                        if (tabuleiro[i][j] == 0) DrawRectangle(areaTab[i][j].x, areaTab[i][j].y, TAM, TAM, BEIGE);
                        else if (tabuleiro[i][j] == 1) DrawRectangle(areaTab[i][j].x, areaTab[i][j].y, TAM, TAM, SKYBLUE);
                        else if (tabuleiro[i][j] == 2) DrawRectangle(areaTab[i][j].x, areaTab[i][j].y, TAM, TAM, GREEN);
                        else if (tabuleiro[i][j] == 3) DrawRectangle(areaTab[i][j].x, areaTab[i][j].y, TAM, TAM, BROWN);
                        else if (tabuleiro[i][j] == 4) DrawRectangle(areaTab[i][j].x, areaTab[i][j].y, TAM, TAM, DARKGREEN);
                        else if (tabuleiro[i][j] == 5) DrawRectangle(areaTab[i][j].x, areaTab[i][j].y, TAM, TAM, VIOLET);
                        else if (tabuleiro[i][j] == 6) DrawRectangle(areaTab[i][j].x, areaTab[i][j].y, TAM, TAM, GOLD);
                        else if (tabuleiro[i][j] == 7) DrawRectangle(areaTab[i][j].x, areaTab[i][j].y, TAM, TAM, DARKBLUE);
                        else if (tabuleiro[i][j] == 8) DrawRectangle(areaTab[i][j].x, areaTab[i][j].y, TAM, TAM, DARKGRAY);
                        //imprimindo bordas internas nos retangulos
                        DrawRectangleLines(areaTab[i][j].x, areaTab[i][j].y, TAM, TAM, BLACK);
                        //imprimindo frente do laser com uma cor mais forte para diferenciar
                        if (i == laser.linha && j == laser.coluna) DrawRectangle(areaTab[i][j].x, areaTab[i][j].y, TAM, TAM, BLUE); 
                    }
                }
            } else if (vitoria) {
                DrawText(FormatText("VICTORY!"), 200, 300, 50, GREEN);
            } else if (derrota) DrawText(FormatText("GAME OVER!"), 170, 300, 50, RED);
            //imprimindo deck do jogador
            for (i=0; i<10; i++) {
                //imprimindo runa de acordo com a sua cor/tipo
                if (jogador.runas[i] == 0) DrawRectangle(areaRunas[i].x, areaRunas[i].y, areaRunas[i].width, areaRunas[i].height, RAYWHITE);
                else if (jogador.runas[i] == 3) DrawRectangle(areaRunas[i].x, areaRunas[i].y, areaRunas[i].width, areaRunas[i].height, BROWN);
                else if (jogador.runas[i] == 4) DrawRectangle(areaRunas[i].x, areaRunas[i].y, areaRunas[i].width, areaRunas[i].height, DARKGREEN);
                else if (jogador.runas[i] == 5) DrawRectangle(areaRunas[i].x, areaRunas[i].y, areaRunas[i].width, areaRunas[i].height, VIOLET);
                else if (jogador.runas[i] == 6) DrawRectangle(areaRunas[i].x, areaRunas[i].y, areaRunas[i].width, areaRunas[i].height, GOLD);
                else if (jogador.runas[i] == 7) DrawRectangle(areaRunas[i].x, areaRunas[i].y, areaRunas[i].width, areaRunas[i].height, DARKBLUE);
                //imprimindo bordas das runas independente da cor/tipo
                DrawRectangleLines(areaRunas[i].x, areaRunas[i].y, areaRunas[i].width, areaRunas[i].height, BLACK);
                //imprimindo bordas duplas caso a runa esteja selecionada para jogar
                if (okRunas[i]) DrawRectangleLines(areaRunas[i].x+5, areaRunas[i].y+5, areaRunas[i].width-10, areaRunas[i].height-10, BLACK);
            }  
        EndDrawing();
    }
    
    CloseWindow(); //encerrando jogo

    return 0;
}
