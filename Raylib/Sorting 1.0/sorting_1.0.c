#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define TRUE 1
#define FALSE 0
#define N 1000
/*
    Programa feito para visualizacao grafica dos algoritmos de ordenacao...
    Estao inclusos:
    1- Bubble Sort
    2- Selection Sort
    3- Insertion Sort
    4- Shell Sort
    
    OBS: testar a gravacao da ordenacao em arquivo!!! para entao renderizar passo a passo...
*/
int main(){
    //prototipos das funcoes de geracao e impressao do vetor de elementos
    void preencherVetor(int vetor[N]);
    void imprimirVetor( int vetor[N], int forma, int altura, int largura);
    
    //constantes do programa
    const int largura = 1000;
    const int altura = 600;

    //Variaveis do programa
    int ordenar = FALSE, embaralhado = FALSE, okBubble = FALSE, okSelection = FALSE, okInsertion = FALSE, okShell = FALSE; //flags dos botoes
    int vetor[N]; //vetor responsavel por armazenar os numeros aleatorios de 0 ate N
    int i, j, temp, passo1, passo2, algoritmo = 0; //variaveis do bubbleSort
    int pos, trocas, trocar, menor; //variaveis do selectionSort
    int ponta, passo3, passo4; //variaveis do insertionSort
    int n; //variaveis do shell sort
    
    //inicializando vetor de maneira ordenada
    for(i=0; i<N; i++){
        vetor[i] = i;
    }
    
    //Paineis e botoes do menu de configuracoes
    Rectangle menu = {0, 500, 1000, 100};  //retangulo na posicao (0, 500) com dimensoes de 1000x100
    Rectangle botaoBubble = {10, 505, 40, 40};
    Rectangle botaoSelection = {10, 555, 40, 40};
    Rectangle botaoInsertion = {300, 505, 40, 40};
    Rectangle botaoShell = {300, 555, 40, 40};
    Rectangle Shuffle = {600, 505, 70, 40};
    Rectangle Sort = {600, 555, 70, 40};
    
    //Iniciando tela e FPS
    InitWindow( largura, altura, "Sorting 1.0");
    
    SetTargetFPS(60);
    
    //Loop principal
    while (!WindowShouldClose()){
        //Update do programa
        
        //checando toque para selecao de algoritmo de ordenacao e sua execucao
        if ( !ordenar){
            if ( CheckCollisionPointRec( GetMousePosition(), botaoBubble) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && embaralhado){
                algoritmo = 1; //ativando Bubble Sort
                passo1 = 0; //setando variavel de controle
                passo2 = (N-1); //setando variavel de controle
                okBubble = TRUE; //setando flag
                okSelection = FALSE;
                okInsertion = FALSE;
                okShell = FALSE;
            }
            if ( CheckCollisionPointRec( GetMousePosition(), botaoSelection) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && embaralhado){
                algoritmo = 2; //ativando Bubble Sort
                trocas = 0; //setando variavel de controle
                okSelection = TRUE; //setando flag
                okBubble = FALSE;
                okInsertion = FALSE;
                okShell = FALSE;
            }
            if ( CheckCollisionPointRec( GetMousePosition(), botaoInsertion) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && embaralhado){
                algoritmo = 3; //ativando Bubble Sort
                passo3 = 1; //setando variavel de controle
                passo4 = 0; //setando variavel de controle
                okInsertion = TRUE; //setando flag
                okBubble = FALSE;
                okSelection = FALSE;
                okShell = FALSE;
            }
            if ( CheckCollisionPointRec( GetMousePosition(), botaoShell) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && embaralhado){
                algoritmo = 4; //ativando Bubble Sort
                //inicializando n
                if ( N%2 == 0) n = N/2; //se o numero de elementos for par
                else n = (N/2)+1; //se for impar...
                okShell = TRUE; //setando flag
                okBubble = FALSE;
                okSelection = FALSE;
                okInsertion = FALSE;
            }
            //embaralhando vetor para futura ordenacao
            if ( CheckCollisionPointRec( GetMousePosition(), Shuffle) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ){
                //resetando flags dos botoes
                embaralhado = TRUE;
                okBubble = FALSE;
                okSelection = FALSE;
                okInsertion = FALSE;
                okShell = FALSE;
                algoritmo = 0; //resetando algoritmo
                preencherVetor(vetor); //embaralhando vetor
            }
            //ativando ordenacao se houver algum algoritmo ativo
            if ( CheckCollisionPointRec( GetMousePosition(), Sort) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (okBubble || okSelection || okInsertion || okShell)){
                ordenar = TRUE; //ordenacao pode comecar
            }
        }
        
        //ativando algoritmos, se possivel
        if ( ordenar ){
            if (algoritmo == 1){
                //TESTANDO BUBBLE SORT !!!
                //percorrendo vetor (do primeiro ao ultimo)
                for (i=passo1; i<N; i++){
                    for (j=passo2; j>=i; j--){
                        if ( vetor[i] > vetor[j] ){
                            //trocando valores
                            temp = vetor[i];
                            vetor[i] = vetor[j];
                            vetor[j] = temp;
                        }
                        passo2--; //atualizando contador mais interno
                        break; //saindo do loop interno
                    }
                    if ( j == i) {
                        passo1++; //atualizando contador externo assim que o mais interno foi totalmente percorrido
                        passo2 = (N-1); //resetando contador mais interno
                    }
                    if ( i == (N-1)) {
                        algoritmo = 0; //encerrando a ordenacao nesse algoritmo
                        ordenar = FALSE;
                        okBubble = FALSE;
                        embaralhado = FALSE;
                    }
                    break; //saindo do loop mais externo
                }
            }
            else if ( algoritmo == 2){
                //TESTANDO SELECTION SORT !!!
                //enquanto numero de trocas <= (tam-1)
                while (trocas < (N-1)){

                    menor = vetor[trocas]; //resetando menor para primeiro valor do vetor nao ordenado
                    trocar = 0; //setando flag para troca como FALSE
                    //procurando menor elemento pelo resto do vetor nao-ordenado
                    for (i=(trocas+1); i<N; i++){
                        if ( vetor[i] < menor){
                            menor = vetor[i]; //atualizando menor elemento
                            pos = i; //salvando posicao do menor elemento
                            trocar = 1; //setando flag para troca como TRUE
                        }
                    }
                    //jogando menor valor na posicao inicial do vetor nao-ordenado
                    if (trocar){
                        temp = vetor[trocas];
                        vetor[trocas] = menor;
                        vetor[pos] = temp;
                    }
                    //atualizando numero de trocas (ultima posicao trocada)
                    trocas++;
                    break; //necessario para alternar para o modo de desenho
                }
                if (trocas == (N-1)){
                    algoritmo = 0; //encerrando ordenacao nesse algoritmo
                    ordenar = FALSE;
                    okSelection = FALSE;
                    embaralhado = FALSE;
                }
            }
            else if (algoritmo == 3){
                //TESTANDO INSERTION SORT!!!
                //passando por todo o vetor e comparando a ponta com seus antecessores
                for (i=passo3; i<N; i++){
                    ponta = i;
                    for (j=passo4; j>=0; j--){
                        //trocando ponta com o resto do vetor caso ela seja menor
                        if ( vetor[ponta] < vetor[j]){
                            temp = vetor[ponta];
                            vetor[ponta] = vetor[j];
                            vetor[j] = temp;
                            ponta--; //mantendo registro da posicao do elemento ponta
                        }
                    }
                    if ( j < 0) {
                        passo3++; //atualizando contador externo assim que o mais interno foi totalmente percorrido
                        passo4 = (passo3-1); //resetando contador mais interno
                    }
                    if ( i == (N-1)) {
                        algoritmo = 0; //encerrando a ordenacao nesse algoritmo
                        ordenar = FALSE;
                        okInsertion = FALSE;
                        embaralhado = FALSE;
                    }
                    break; //saindo do loop mais externo
                }
            }
            else if ( algoritmo == 4){
                //TESTANDO SHELL SORT!!!
                //ordenando enquanto houver trocas
                while (n>=1){
                    trocar = 0;
                    //percorrendo todo o vetor
                    for (i=0; i<N; i++){
                        //realizando trocas na range de N, se possivel
                        if ( (i+n) < N && vetor[i] > vetor[i+n]){
                            temp = vetor[i];
                            vetor[i] = vetor[i+n];
                            vetor[i+n] = temp;
                            trocar = 1;
                        }
                    }
                    if (!trocar) n--; //atualizando valor de N caso nao haja mais trocas possiveis
                    break;
                }
                if ( n < 1) {
                    algoritmo = 0;
                    ordenar = FALSE;
                    okShell = FALSE;
                    embaralhado = FALSE;
                }
            }
        }
        
        //Renderizacao do programa
        BeginDrawing();
            ClearBackground(BLACK);
            //desenhando em forma de barras
            imprimirVetor(vetor, 1, largura, altura);
            //desenhando o menu de configuracao, seus botoes e suas opcoes...
            DrawRectangleRec( menu, GRAY );
            
            DrawText(FormatText("Bubble Sort"), botaoBubble.x+50, botaoBubble.y+10, 20, BLACK);
            DrawRectangleRec( botaoBubble, WHITE);
            if ( okBubble ){
                //desenhando efeito de marcacao no botao (X)
                DrawLine( botaoBubble.x, botaoBubble.y, botaoBubble.x+botaoBubble.width, botaoBubble.y+botaoBubble.height, BLACK);
                DrawLine( botaoBubble.x+botaoBubble.width, botaoBubble.y, botaoBubble.x, botaoBubble.y+botaoBubble.height, BLACK);
            }
            
            DrawText(FormatText("Selection Sort"), botaoSelection.x+50, botaoSelection.y+10, 20, BLACK);
            DrawRectangleRec( botaoSelection, WHITE);
            if ( okSelection ){
                //desenhando efeito de marcacao no botao (X)
                DrawLine( botaoSelection.x, botaoSelection.y, botaoSelection.x+botaoSelection.width, botaoSelection.y+botaoSelection.height, BLACK);
                DrawLine( botaoSelection.x+botaoSelection.width, botaoSelection.y, botaoSelection.x, botaoSelection.y+botaoSelection.height, BLACK);
            }
            
            DrawText(FormatText("Insertion Sort"), botaoInsertion.x+50, botaoInsertion.y+10, 20, BLACK);
            DrawRectangleRec( botaoInsertion, WHITE);
            if ( okInsertion ){
                //desenhando efeito de marcacao no botao (X)
                DrawLine( botaoInsertion.x, botaoInsertion.y, botaoInsertion.x+botaoInsertion.width, botaoInsertion.y+botaoInsertion.height, BLACK);
                DrawLine( botaoInsertion.x+botaoInsertion.width, botaoInsertion.y, botaoInsertion.x, botaoInsertion.y+botaoInsertion.height, BLACK);
            }
            
            DrawText(FormatText("Shell Sort"), botaoShell.x+50, botaoShell.y+10, 20, BLACK);
            DrawRectangleRec( botaoShell, WHITE);
            if ( okShell ){
                //desenhando efeito de marcacao no botao (X)
                DrawLine( botaoShell.x, botaoShell.y, botaoShell.x+botaoShell.width, botaoShell.y+botaoShell.height, BLACK);
                DrawLine( botaoShell.x+botaoShell.width, botaoShell.y, botaoShell.x, botaoShell.y+botaoShell.height, BLACK);
            }
            
            DrawRectangleRec( Shuffle, RED);
            DrawRectangleLines( Shuffle.x, Shuffle.y, Shuffle.width, Shuffle.height, BLACK);
            DrawText(FormatText("Shuffle"), Shuffle.x+8, Shuffle.y+12, 15, BLACK);
            
            DrawRectangleRec( Sort, GREEN);
            DrawRectangleLines( Sort.x, Sort.y, Sort.width, Sort.height, BLACK);
            DrawText(FormatText("Sort"), Sort.x+17, Sort.y+14, 15, BLACK);
            
            if ( ordenar ) DrawText(FormatText("Ordenando vetor..."), 770, 550, 15, BLACK);
             
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}

void imprimirVetor( int vetor[N], int forma, int largura, int altura){
    int i, valor, x = (largura/N), y = (500/N);
     
    if ( forma == 1){
        for (i=0; i<N; i++){
            valor = vetor[i];
            //desenhando barras com valor unitario para valores de N > 500
            if ( N > 500) DrawRectangle(i*x, 500-(valor*(0.5)), 1, valor*(0.5), WHITE);
            else DrawRectangle(i*x, 500-(valor*y), x, valor*y, WHITE);
            //desenhando contorno das barras (ate N == 200)
            if ( N <= 200) DrawRectangleLines(i*x, 500-(valor*y), x, valor*y, BLACK);
        }
    }

}

void preencherVetor(int vetor[N]){
    int i, j, valido, alet;
    time_t t; //necessario para gerar numeros realmente aleatorios
    
    srand( (unsigned) time(&t)); //seed para gerar os numeros aleatorios
    
    //resetando vetor para assumir novos valores
    for (i=0; i<N; i++){
        vetor[i] = -1; //valor padrao para indicar que o local esta "vazio"
    }
    //preenchendo vetor com valores aleatorios de 0 ate (N-1)
    for (i=0; i<N; i++){
        valido = TRUE; //setando flag
        alet = ( rand() % N); //gerando numero aleatorio
        //buscando se ja existe esse numero no vetor...
        for (j=0; j<i; j++){
            if ( vetor[j] == alet) valido = FALSE;
        }
        if (valido) vetor[i] = alet;
        else i--; //retornando para a mesma posicao e tentando novamente
    }
}
