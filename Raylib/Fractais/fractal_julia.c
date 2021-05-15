#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

#define TRUE 1
#define FALSE 0

int main(){
    //constantes do programa
    const int largura = 700; //dimensao do eixo x
    const int altura = 700; //dimensao do eixo y
    const int N = largura*altura; //total de pontos do vetor
    static const float c1 = -0.8;
    static const float c2 = 0.125;
    const int n = 80; //numero de iteracoes no calculo do fractal
    
    //variaveis do programa
    int pontos[N]; //onde ira armazenar apenas 1 ou 0 ( ou seja, se o ponto (i, j) tende ou nao tende ao infinito)
    int i, j, k, index = 0, gerando = TRUE, pertence; //contadores e flag de controle do calculo
    long double x0, y0, x1, y1, distancia; //vao armazenar valores intermediarios no calculo
    
    //Iniciando tela e FPS
    InitWindow( largura, altura, "Fractais 1.0");
    
    SetTargetFPS(60);
    
    //Loop principal
    while (!WindowShouldClose()){
        //Update do programa
        if ( gerando ){
            
            //aplicando algoritmo da geracao dos conjuntos de Julia
            for (i=1; i<=altura; i++){
                for (j=1; j<=largura; j++){
                    x0 = ((double)i/ (double) 200) - 2;
                    y0 = 2 - ( (double) j/ (double) 200);
                    pertence = TRUE;
                    //aplicando pontos na funcao em n iteracoes
                    for (k=0; k<n; k++){
                        x1 = pow(x0, 2) - pow(y0, 2) + c1;
                        y1 = (2*x0*y0) + c2;
                        distancia = pow(x1, 2) + pow(y1, 2);
                        //verificando se o ponto tende ao infinito
                        if ( distancia > 2){
                            pertence = FALSE; //nao esta dentro do fractal
                            break; //encerrando iteracoes sobre o ponto
                        }
                        else{
                            //se o ponto ainda esta dentro do fractal...continuar iteracoes
                            x0 = x1;
                            y0 = y1;
                        }
                    }
                    //se ao final das iteracoes o ponto estiver dentro do fractal...
                    if ( pertence ) pontos[index] = TRUE;
                    else pontos[index] = FALSE;
                    //atualizando posicao de preenchimento no vetor
                    index++;
                }
            }
            
            gerando = FALSE; //finalizando calculo do fractal
        }
        
        //Renderizacao do programa
        BeginDrawing();
            //desenhando fractal apos ter sido gerado...
            if ( !gerando ){
                ClearBackground(GREEN);
                //percorrendo vetor como matriz
                i=0;
                j=0;
                for (k=0; k<N; k++){
                    //se ponto nao tender ao infinito, estiver dentro == TRUE, entao desenhar pixel branco
                    if ( pontos[k] ){
                        DrawRectangle( i, j, 1, 1, WHITE);
                    }
                    //se ponto tender ao infinito, estiver dentro == FALSE, entao desenhar pixel preto 
                    else{
                        DrawRectangle( i, j, 1, 1, BLACK);
                    }
                    //atualizando contadores para manter o comportamento de matriz
                    if ( j == (largura-1)){
                        i++;
                        j = 0;
                    }
                    else j++;
                    
                }
            }
        
        EndDrawing();
    }
    
    CloseWindow(); //finalizando programa
    
    return 0;
}