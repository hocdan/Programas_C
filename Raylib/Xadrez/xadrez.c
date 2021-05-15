#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

#define N 8
/*
Legenda do tabuleiro:
0 -> casa vazia
10, 20 -> peao branco e peao preto
11, 21 -> torre branca e torre preta
12, 22 -> cavalo branco e cavalo preto
13, 23 -> bispo branco e bispo preto
14, 24 -> rainha branca e rainha preta
15, 25 -> rei branco e rei preto

OBS: as brancas iniciam (turnos impares), logo as pretas seguem (turnos pares)
*/
//Variaveis globais
const int largura = 500; // tem que ser divisivel por 10
const int altura = 400; // tem que ser divisivel por 10

int main(){
    //Declaracao das funcoes que serao utilizadas
	void moverPeao(int mat[N][N], int l1, int c1, int l2, int c2, int peao);
	void moverTorre(int mat[N][N], int l1, int c1, int l2, int c2, int torre);
	void moverCavalo(int mat[N][N], int l1, int c1, int l2, int c2, int cavalo);
	void moverBispo(int mat[N][N], int l1, int c1, int l2, int c2, int bispo);
	void moverRainha(int mat[N][N], int l1, int c1, int l2, int c2, int rainha);
	void moverRei(int mat[N][N], int l1, int c1, int l2, int c2, int rei);
	void promoverPeao(int mat[N][N], int linha, int coluna, int peao);
	//Inicializacao das pecas no tabuleiro
    int tabuleiro[N][N] = { 21, 22, 23, 25, 24, 23, 22, 21
					  , 20, 20, 20, 20, 20, 20, 20, 20
					  , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 
					  , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 
					  , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 
					  , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 
					  , 10, 10, 10, 10, 10, 10, 10, 10
					  , 11, 12, 13, 14, 15, 13, 12, 11};
	int i, j, frames = 0, turno = 1, achouKb, achouKp, l1, c1, l2, c2;
    int toques = 0; //contador para verificar quantos toques ocorreram
    
    InitWindow(largura, altura, "Xadrez!");
    SetTargetFPS(60);
	
	while (!WindowShouldClose()){
		//Area responsavel pelo update do jogo
        if (frames > 240) break; //fechando o jogo depois de 4 segundos apos o cheque-mate
		//Checando toque e armazenando a jogada...
        for (i=0; i<8; i++){
            for (j=0; j<8; j++){
                Rectangle quadrado = {(j*50)+100, i*50, 50, 50};
                //se mouse esta em cima do quadrado...
                if ( CheckCollisionPointRec(GetMousePosition(), quadrado)){
                    //se botao esquerdo do mouse foi pressionado...
                    if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        toques++;
                        //armazenando coordenadas do toque
                        if (toques == 1){
                            l1 = i;
                            c1 = j;
                        }
                        else if ( toques == 2){
                            l2 = i;
                            c2 = j;
                        }
                    }
                }
            }
        }
		//Verificando quem esta jogando...
		if ( turno%2 != 0 && toques == 2) //turno das brancas
		{
			//verificando se a peca a ser movida eh das brancas
			if ( tabuleiro[l1][c1] != 0 && tabuleiro[l1][c1] != 20 && tabuleiro[l1][c1] != 21 && tabuleiro[l1][c1] != 22 && tabuleiro[l1][c1] != 23 && tabuleiro[l1][c1] != 24 && tabuleiro[l1][c1] != 25)
			{
				if ( tabuleiro[l1][c1] == 10) moverPeao(tabuleiro, l1, c1, l2, c2, 10);
				else if ( tabuleiro[l1][c1] == 11) moverTorre(tabuleiro, l1, c1, l2, c2, 11);
				else if ( tabuleiro[l1][c1] == 12) moverCavalo(tabuleiro, l1, c1, l2, c2, 12);
				else if ( tabuleiro[l1][c1] == 13) moverBispo(tabuleiro, l1, c1, l2, c2, 13);
				else if ( tabuleiro[l1][c1] == 14) moverRainha(tabuleiro, l1, c1, l2, c2, 14);
				else if ( tabuleiro[l1][c1] == 15) moverRei(tabuleiro, l1, c1, l2, c2, 15);
				turno++;
                toques = 0; //resetando contador
			} 
			else {
				DrawText(FormatText("Jogada Invalida!"), 10, altura-15, 10, RED);
				turno++;
                toques = 0; //resetando contador
			}
		}
		else if ( turno%2 == 0 && toques == 2)//turno das pretas
		{
			//verificando se a peca a ser movida eh das pretas
			if ( tabuleiro[l1][c1] != 0 && tabuleiro[l1][c1] != 10 && tabuleiro[l1][c1] != 11 && tabuleiro[l1][c1] != 12 && tabuleiro[l1][c1] != 13 && tabuleiro[l1][c1] != 14 && tabuleiro[l1][c1] != 15)
			{
				if ( tabuleiro[l1][c1] == 20) moverPeao(tabuleiro, l1, c1, l2, c2, 20);
				else if ( tabuleiro[l1][c1] == 21) moverTorre(tabuleiro, l1, c1, l2, c2, 21);
				else if ( tabuleiro[l1][c1] == 22) moverCavalo(tabuleiro, l1, c1, l2, c2, 22);
				else if ( tabuleiro[l1][c1] == 23) moverBispo(tabuleiro, l1, c1, l2, c2, 23);
				else if ( tabuleiro[l1][c1] == 24) moverRainha(tabuleiro, l1, c1, l2, c2, 24);
				else if ( tabuleiro[l1][c1] == 25) moverRei(tabuleiro, l1, c1, l2, c2, 25);
				turno++;
                toques = 0; //resetando contador
			} 
			else {
				DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
				turno++;
                toques = 0; //resetando contador
			}
		}
		//Verificando se algum peao pode ser promovido ou se houve Xeque-Mate!
		achouKb = 0;
		achouKp = 0;
		for (i=0; i<N; i++){
			for (j=0; j<N; j++){
				if (tabuleiro[i][j] == 10 || tabuleiro[i][j] == 20) promoverPeao(tabuleiro, i, j, tabuleiro[i][j]);
				if (tabuleiro[i][j] == 15) achouKb = 1;
				if (tabuleiro[i][j] == 25) achouKp = 1;
			}
		}
        //Area responsavel pelo desenho do jogo
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
            
            //Desenhando vitoria (se houver)
            if (!achouKb){
                DrawText(FormatText("VITORIA DAS PRETAS!!! Parabens :)"), 60, 170, 20, DARKGRAY);
                frames++;
            }
            else if (!achouKp){
                DrawText(FormatText("VITORIA DAS BRANCAS!!! Parabens :) "), 60 , 170, 20, DARKGRAY);
                frames++;
            }
            else{
                //Desenhando informacoes
                DrawRectangle( 0, 0, 100, altura, RAYWHITE); //aba que contem as informacoes
                DrawText(FormatText("Turno: %d", turno), 5, 10, 5, DARKGRAY);
                if ( turno%2 != 0) DrawText(FormatText("BRANCAS!"), 5, 30, 5, DARKGRAY);
                else DrawText(FormatText("PRETAS!"), 5, 30, 5, DARKGRAY);
                DrawText(FormatText("PEAO"), 15, 60, 5, DARKGRAY); //legenda do peao
                DrawCircle( 25, 85, 10, BLACK);
                DrawText(FormatText("TORRE"), 15, 100, 5, DARKGRAY); //legenda da torre
                DrawRectangle( 20, 115, 10, 20, BLACK);
                DrawText(FormatText("CAVALO"), 15, 140, 5, DARKGRAY); //legenda do cavalo
                DrawRectangle( 20, 155, 20, 20, BLACK);
                DrawText(FormatText("BISPO"), 15, 180, 5, DARKGRAY); //legenda do bispo
                DrawTriangle( (Vector2){ 25, 190}, (Vector2){ 20, 210}, (Vector2){ 30, 210}, BLACK);
                DrawText(FormatText("RAINHA"), 15, 220, 5, DARKGRAY); //legenda da rainha
                DrawPoly( (Vector2){ 25, 245}, 5, 10, 0, BLACK);
                DrawText(FormatText("REI"), 15, 260, 5, DARKGRAY); //legenda do rei
                DrawPoly( (Vector2){ 25, 285}, 6, 10, 0, BLACK);
                //Desenhando tabuleiro
                for (i=0; i<8; i++){
                    for (j=0; j<8; j++){
                        //desenhando quadrados intercalados em branco e preto
                        if ((i+j)%2 != 0) DrawRectangle((j*50)+100, i*50, 50, 50, RAYWHITE);
                        else DrawRectangle((j*50)+100, i*50, 50, 50, BLACK);
                       //desenhando pecas do xadrez
                        if ( tabuleiro[i][j] == 10) DrawCircle((j*50)+125, i*50 + 25, 12.5f, BLUE);
                        else if ( tabuleiro[i][j] == 11) DrawRectangle((j*50)+115, i*50 + 12.5f, 20, 25, BLUE);
                        else if ( tabuleiro[i][j] == 12) DrawRectangle((j*50)+112.5f, i*50 + 12.5f, 25, 25, BLUE);
                        else if ( tabuleiro[i][j] == 13) DrawTriangle( (Vector2){(j*50)+125, i*50 + 12.5f}, (Vector2){(j*50)+112.5f, i*50 + 37.5f}, (Vector2){(j*50)+137.5f, i*50 + 37.5f}, BLUE);
                        else if ( tabuleiro[i][j] == 14) DrawPoly( (Vector2){(j*50)+125, i*50 + 25}, 5, 12.5f, 0, BLUE); 
                        else if ( tabuleiro[i][j] == 15) DrawPoly( (Vector2){(j*50)+125, i*50 + 25}, 6, 12.5f, 0, BLUE);
                        else if ( tabuleiro[i][j] == 20) DrawCircle((j*50)+125, i*50 + 25, 12.5f, RED);
                        else if ( tabuleiro[i][j] == 21) DrawRectangle((j*50)+115, i*50 + 12.5f, 20, 25, RED);
                        else if ( tabuleiro[i][j] == 22) DrawRectangle((j*50)+112.5f, i*50 + 12.5f, 25, 25, RED);
                       else if ( tabuleiro[i][j] == 23) DrawTriangle( (Vector2){(j*50)+125, i*50 + 12.5f}, (Vector2){(j*50)+112.5f, i*50 + 37.5f}, (Vector2){(j*50)+137.5f, i*50 + 37.5f}, RED);
                        else if ( tabuleiro[i][j] == 24) DrawPoly( (Vector2){(j*50)+125, i*50 + 25}, 5, 12.5f, 0, RED);
                        else if ( tabuleiro[i][j] == 25) DrawPoly( (Vector2){(j*50)+125, i*50 + 25}, 6, 12.5f, 0, RED);
                    }
                }
            }
            
        EndDrawing();
    }
    
    CloseWindow(); //Encerrando programa... 
    
    return 0;
}

void promoverPeao(int mat[N][N], int linha, int coluna, int peao){
    int alet;
	if ( peao == 10 && linha == 0){
		alet = GetRandomValue(11, 14); //escolhendo leatoriamente uma dessas pecas
        mat[linha][coluna] = alet;
	}
	else if ( peao == 20 && linha == 7){
		alet = GetRandomValue(21, 24);
        mat[linha][coluna] = alet;
	}
}
void moverPeao(int mat[N][N], int l1, int c1, int l2, int c2, int peao){
	int alcance = 1;
	if (peao == 10 && (mat[l2][c2] == 0 || mat[l2][c2] == 20 || mat[l2][c2] == 21 || mat[l2][c2] == 22 || mat[l2][c2] == 23 || mat[l2][c2] == 24 || mat[l2][c2] == 25))
	{
		//checando movimentacao (andar pra frente)
		if ( (l2 == l1 - alcance && c2 == c1) && mat[l2][c2] == 0 ){
			mat[l1][c1] = 0;
			mat[l2][c2] = 10;
		}
		//checando movimentacao (comer para a diagonal frontal esquerda)
		else if ( (l2 == l1 - alcance && c2 == c1 - 1) && mat[l2][c2] != 0){
			mat[l1][c1] = 0;
			mat[l2][c2] = 10;
		}
		//checando movimentacao (comer para a diagonal frontal direita)
		else if ( (l2 == l1 - alcance && c2 == c1 + 1) && mat[l2][c2] != 0){
			mat[l1][c1] = 0;
			mat[l2][c2] = 10;
		}
		else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
	}
	else if (peao == 20 && (mat[l2][c2] == 0 || mat[l2][c2] == 10 || mat[l2][c2] == 11 || mat[l2][c2] == 12 || mat[l2][c2] == 13 || mat[l2][c2] == 14 || mat[l2][c2] == 15))
	{
		//checando movimentacao (andar pra frente)
		if ( (l2 == l1 + alcance && c2 == c1) && mat[l2][c2] == 0 ){
			mat[l1][c1] = 0;
			mat[l2][c2] = 20;
		}
		//checando movimentacao (comer para a diagonal frontal esquerda)
		else if ( (l2 == l1 + alcance && c2 == c1 - 1) && mat[l2][c2] != 0){
			mat[l1][c1] = 0;
			mat[l2][c2] = 20;
		}
		//checando movimentacao (comer para a diagonal frontal direita)
		else if ( (l2 == l1 + alcance && c2 == c1 + 1) && mat[l2][c2] != 0){
			mat[l1][c1] = 0;
			mat[l2][c2] = 20;
		}
		else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
	}
	else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
}

void moverTorre(int mat[N][N], int l1, int c1, int l2, int c2, int torre){
	int valido = 1, i; //verdadeiro
	//checando se a movimentacao eh valida...
	if ( l1 == l2){
		//buscando por obstaculos para todo o lado esquerdo ate o alvo
		if ( c1 > c2){
			for (i=c1-1; i>c2; i--){
				if ( mat[l1][i] != 0) valido = 0; //falso
			}
		}
		//buscando por obstaculos para todo o lado direito ate o alvo
		else if ( c1 < c2){
			for (i=c1+1; i<c2; i++){
				if ( mat[l1][i] != 0) valido = 0; //falso
			}
		}
		else{
			valido = 0; //falso
			DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
		}
	}
	else if ( c1 == c2){
		//buscando por obstaculos por toda a direcao de cima
		if ( l1 > l2){
			for (i=l1-1; i>l2; i--){
				if ( mat[i][c1] != 0) valido = 0; //falso
			}
		}
		else if ( l1 < l2){
			for (i=l1+1; i<l2; i++){
				if ( mat[i][c1] != 0) valido = 0; //falso
			}
		}
		else{
			valido = 0; //falso
			DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
		}
	}
	else{
		valido = 0; //falso
		DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
	}
	//Caso a movimentacao seja valida, verificar o alvo
	if (valido){
		if (torre == 11 && (mat[l2][c2] == 0 || mat[l2][c2] == 20 || mat[l2][c2] == 21 || mat[l2][c2] == 22 || mat[l2][c2] == 23 || mat[l2][c2] == 24 || mat[l2][c2] == 25))
		{
			mat[l1][c1] = 0;
			mat[l2][c2] = 11;
		}
		else if (torre == 21 && (mat[l2][c2] == 0 || mat[l2][c2] == 10 || mat[l2][c2] == 11 || mat[l2][c2] == 12 || mat[l2][c2] == 13 || mat[l2][c2] == 14 || mat[l2][c2] == 15))
		{
			mat[l1][c1] = 0;
			mat[l2][c2] = 21;
		}
		else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
	}
	else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
}

void moverCavalo(int mat[N][N], int l1, int c1, int l2, int c2, int cavalo){
	int valido = 0; //falso
	//verificando se eh um cavalo e de qual cor
	if (cavalo == 12 && (mat[l2][c2] == 0 || mat[l2][c2] == 20 || mat[l2][c2] == 21 || mat[l2][c2] == 22 || mat[l2][c2] == 23 || mat[l2][c2] == 24 || mat[l2][c2] == 25)){ 
		//verificando se o movimento eh valido
		if ( l2 == l1 - 2 && c2 == c1 - 1) valido = 1;
		else if ( l2 == l1 - 2 && c2 == c1 + 1) valido = 1;
		else if ( l2 == l1 + 2 && c2 == c1 - 1) valido = 1;
		else if ( l2 == l1 + 2 && c2 == c1 + 1) valido = 1;
		else if ( c2 == c1 - 2 && l2 == l1 - 1) valido = 1;
		else if ( c2 == c1 - 2 && l2 == l1 + 1) valido = 1;
		else if ( c2 == c1 + 2 && l2 == l1 - 1) valido = 1;
		else if ( c2 == c1 + 2 && l2 == l1 + 1) valido = 1;
		else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
	}
	else if (cavalo == 22 && (mat[l2][c2] == 0 || mat[l2][c2] == 10 || mat[l2][c2] == 11 || mat[l2][c2] == 12 || mat[l2][c2] == 13 || mat[l2][c2] == 14 || mat[l2][c2] == 15)){ 
		//verificando se o movimento eh valido
		if ( l2 == l1 - 2 && c2 == c1 - 1) valido = 1;
		else if ( l2 == l1 - 2 && c2 == c1 + 1) valido = 1;
		else if ( l2 == l1 + 2 && c2 == c1 - 1) valido = 1;
		else if ( l2 == l1 + 2 && c2 == c1 + 1) valido = 1;
		else if ( c2 == c1 - 2 && l2 == l1 - 1) valido = 1;
		else if ( c2 == c1 - 2 && l2 == l1 + 1) valido = 1;
		else if ( c2 == c1 + 2 && l2 == l1 - 1) valido = 1;
		else if ( c2 == c1 + 2 && l2 == l1 + 1) valido = 1;
		else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
		
	}
	else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
	//realizando a jogada, se for valida
	if (valido){
		mat[l1][c1] = 0;
		mat[l2][c2] = cavalo;
	}	
}

void moverBispo(int mat[N][N], int l1, int c1, int l2, int c2, int bispo){
	int valido = 1; //verdadeiro
	int deltaL= fabs(l2-l1), deltaC = fabs(c2-c1), i, j; //variacoes do movimento do bispo
	//verificando se o movimento eh valido
	if ( deltaL == deltaC){
		//verificando a cor e se a peca eh um bispo
		if (bispo == 13 && (mat[l2][c2] == 0 || mat[l2][c2] == 20 || mat[l2][c2] == 21 || mat[l2][c2] == 22 || mat[l2][c2] == 23 || mat[l2][c2] == 24 || mat[l2][c2] == 25)){
			//verificando se ha obstaculos ate o alvo
			if ( l1 > l2 && c1 > c2){
				j = c1 - 1; //j acompanha variacao nas colunas
				for(i=l1-1; i>l2; i--){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j--; //atualizando a variacao nas colunas
				}
			}
			else if ( l1 > l2 && c1 < c2){
				j = c1 + 1; //j acompanha variacao nas colunas
				for(i=l1-1; i>l2; i--){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j++; //atualizando a variacao nas colunas
				}
			}
			else if ( l1 < l2 && c1 > c2){
				j = c1 - 1; //j acompanha variacao nas colunas
				for(i=l1+1; i<l2; i++){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j--; //atualizando a variacao nas colunas
				}
			}
			else if ( l1 < l2 && c1 < c2){
				j = c1 + 1; //j acompanha variacao nas colunas
				for(i=l1+1; i<l2; i++){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j++; //atualizando a variacao nas colunas
				}
			}
			else{
				valido = 0;
				DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
			}
		}
		else if (bispo == 23 && (mat[l2][c2] == 0 || mat[l2][c2] == 10 || mat[l2][c2] == 11 || mat[l2][c2] == 12 || mat[l2][c2] == 13 || mat[l2][c2] == 14 || mat[l2][c2] == 15)){
			//verificando se ha obstaculos ate o alvo
			if ( l1 > l2 && c1 > c2){
				j = c1 - 1; //j acompanha variacao nas colunas
				for(i=l1-1; i>l2; i--){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j--; //atualizando a variacao nas colunas
				}
			}
			else if ( l1 > l2 && c1 < c2){
				j = c1 + 1; //j acompanha variacao nas colunas
				for(i=l1-1; i>l2; i--){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j++; //atualizando a variacao nas colunas
				}
			}
			else if ( l1 < l2 && c1 > c2){
				j = c1 - 1; //j acompanha variacao nas colunas
				for(i=l1+1; i<l2; i++){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j--; //atualizando a variacao nas colunas
				}
			}
			else if ( l1 < l2 && c1 < c2){
				j = c1 + 1; //j acompanha variacao nas colunas
				for(i=l1+1; i<l2; i++){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j++; //atualizando a variacao nas colunas
				}
			}
			else{
				valido = 0;
				DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
			}
		}
		else{
			valido = 0;
			DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
		}
	}
	else{
		valido = 0;
		DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
	}
	if (valido){
		mat[l1][c1] = 0;
		mat[l2][c2] = bispo;
	}
	else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
}

void moverRainha(int mat[N][N], int l1, int c1, int l2, int c2, int rainha){
	//---> verificando movimento nas diagonais (movimento bispo)
	int valido = 1; //verdadeiro
	int deltaL= fabs(l2-l1), deltaC = fabs(c2-c1), i, j; //variacoes do movimento do bispo
	//verificando se o movimento eh valido
	if ( deltaL == deltaC){
		//verificando a cor e se a peca eh um bispo
		if (rainha == 14 && (mat[l2][c2] == 0 || mat[l2][c2] == 20 || mat[l2][c2] == 21 || mat[l2][c2] == 22 || mat[l2][c2] == 23 || mat[l2][c2] == 24 || mat[l2][c2] == 25)){
			//verificando se ha obstaculos ate o alvo
			if ( l1 > l2 && c1 > c2){
				j = c1 - 1; //j acompanha variacao nas colunas
				for(i=l1-1; i>l2; i--){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j--; //atualizando a variacao nas colunas
				}
			}
			else if ( l1 > l2 && c1 < c2){
				j = c1 + 1; //j acompanha variacao nas colunas
				for(i=l1-1; i>l2; i--){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j++; //atualizando a variacao nas colunas
				}
			}
			else if ( l1 < l2 && c1 > c2){
				j = c1 - 1; //j acompanha variacao nas colunas
				for(i=l1+1; i<l2; i++){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j--; //atualizando a variacao nas colunas
				}
			}
			else if ( l1 < l2 && c1 < c2){
				j = c1 + 1; //j acompanha variacao nas colunas
				for(i=l1+1; i<l2; i++){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j++; //atualizando a variacao nas colunas
				}
			}
			else valido = 0;
		}
		else if (rainha == 24 && (mat[l2][c2] == 0 || mat[l2][c2] == 10 || mat[l2][c2] == 11 || mat[l2][c2] == 12 || mat[l2][c2] == 13 || mat[l2][c2] == 14 || mat[l2][c2] == 15)){
			//verificando se ha obstaculos ate o alvo
			if ( l1 > l2 && c1 > c2){
				j = c1 - 1; //j acompanha variacao nas colunas
				for(i=l1-1; i>l2; i--){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j--; //atualizando a variacao nas colunas
				}
			}
			else if ( l1 > l2 && c1 < c2){
				j = c1 + 1; //j acompanha variacao nas colunas
				for(i=l1-1; i>l2; i--){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j++; //atualizando a variacao nas colunas
				}
			}
			else if ( l1 < l2 && c1 > c2){
				j = c1 - 1; //j acompanha variacao nas colunas
				for(i=l1+1; i<l2; i++){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j--; //atualizando a variacao nas colunas
				}
			}
			else if ( l1 < l2 && c1 < c2){
				j = c1 + 1; //j acompanha variacao nas colunas
				for(i=l1+1; i<l2; i++){ //i acompanha variacao nas linhas
					if ( mat[i][j] != 0) valido = 0; //falso
					j++; //atualizando a variacao nas colunas
				}
			}
			else valido = 0;
		}
		else valido = 0;
	}
	else //---> verificando movimentos nas laterais (torre)
	{
		//checando se a movimentacao eh valida...
		if ( l1 == l2){
			//buscando por obstaculos para todo o lado esquerdo ate o alvo
			if ( c1 > c2){
				for (i=c1-1; i>c2; i--){
					if ( mat[l1][i] != 0) valido = 0; //falso
				}
			}
			//buscando por obstaculos para todo o lado direito ate o alvo
			else if ( c1 < c2){
				for (i=c1+1; i<c2; i++){
					if ( mat[l1][i] != 0) valido = 0; //falso
				}
			}
			else valido = 0; //falso
		}
		else if ( c1 == c2){
			//buscando por obstaculos por toda a direcao de cima
			if ( l1 > l2){
				for (i=l1-1; i>l2; i--){
					if ( mat[i][c1] != 0) valido = 0; //falso
				}
			}
			else if ( l1 < l2){
				for (i=l1+1; i<l2; i++){
					if ( mat[i][c1] != 0) valido = 0; //falso
				}
			}
			else valido = 0; //falso
		}
		else valido = 0; //falso
	}
	//Caso a movimentacao seja valida, verificar o alvo
	if (valido){
		if (rainha == 14 && (mat[l2][c2] == 0 || mat[l2][c2] == 20 || mat[l2][c2] == 21 || mat[l2][c2] == 22 || mat[l2][c2] == 23 || mat[l2][c2] == 24 || mat[l2][c2] == 25))
		{
			mat[l1][c1] = 0;
			mat[l2][c2] = rainha;
		}
		else if (rainha == 24 && (mat[l2][c2] == 0 || mat[l2][c2] == 10 || mat[l2][c2] == 11 || mat[l2][c2] == 12 || mat[l2][c2] == 13 || mat[l2][c2] == 14 || mat[l2][c2] == 15))
		{
			mat[l1][c1] = 0;
			mat[l2][c2] = rainha;
		}
		else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
	}
	else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
}

void moverRei(int mat[N][N], int l1, int c1, int l2, int c2, int rei){
	int alcance = 1, valido = 0;
	if (rei == 15 && (mat[l2][c2] == 0 || mat[l2][c2] == 20 || mat[l2][c2] == 21 || mat[l2][c2] == 22 || mat[l2][c2] == 23 || mat[l2][c2] == 24 || mat[l2][c2] == 25))
	{
		if ( l1 == l2 + alcance && c1 == c2) valido = 1; //mover para a frente
		else if ( l1 == l2 + alcance && c1 == c2 + alcance) valido = 1; //mover para a diagonal frontal esquerda
		else if ( l1 == l2 + alcance && c1 == c2 - alcance) valido = 1; //mover para a diagonal frontal direita
		else if ( l1 == l2 && c1 == c2 + alcance) valido = 1; //mover para o lado esquerdo
		else if ( l1 == l2 && c1 == c2 - alcance) valido = 1; //mover para o lado direito
		else if ( l1 == l2 - alcance && c1 == c2) valido = 1; //mover para atras
		else if ( l1 == l2 - alcance && c1 == c2 + alcance) valido = 1; //mover para a diagonal traseira esquerda
		else if ( l1 == l2 - alcance && c1 == c2 - alcance) valido = 1; //mover para a diagonal traseira direita
		else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
	}
	else if (rei == 25 && (mat[l2][c2] == 0 || mat[l2][c2] == 10 || mat[l2][c2] == 11 || mat[l2][c2] == 12 || mat[l2][c2] == 13 || mat[l2][c2] == 14 || mat[l2][c2] == 15))
	{
		if ( l1 == l2 + alcance && c1 == c2) valido = 1; //mover para a frente
		else if ( l1 == l2 + alcance && c1 == c2 + alcance) valido = 1; //mover para a diagonal frontal esquerda
		else if ( l1 == l2 + alcance && c1 == c2 - alcance) valido = 1; //mover para a diagonal frontal direita
		else if ( l1 == l2 && c1 == c2 + alcance) valido = 1; //mover para o lado esquerdo
		else if ( l1 == l2 && c1 == c2 - alcance) valido = 1; //mover para o lado direito
		else if ( l1 == l2 - alcance && c1 == c2) valido = 1; //mover para atras
		else if ( l1 == l2 - alcance && c1 == c2 + alcance) valido = 1; //mover para a diagonal traseira esquerda
		else if ( l1 == l2 - alcance && c1 == c2 - alcance) valido = 1; //mover para a diagonal traseira direita
		else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
	}
	else DrawText(FormatText("Jogada Invalida!"), 10, altura-10, 10, RED);
	if (valido){
		mat[l1][c1] = 0;
		mat[l2][c2] = rei;
	}
}
