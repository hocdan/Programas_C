#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "raylib.h"

#define TRUE 1
#define FALSE 0
#define MIN -500 //sempre o menor
#define MAX 500 //sempre o maior
#define PASSO 0.1 //sempre um numero positivo

/*  Programa feito para visualizar graficos de determinadas funcoes...
    Onde:
    1- funcao identidade
    2- funcao quadratica
    3- funcao cubica
    4- funcao exponencial (de base 2)
    5- funcao seno
    6- funcao cosseno
    7- funcao tangente
    8- funcao seno hiperbolico
    9- funcao cosseno hiperbolico
    10- funcao log na base 10
    11- funcao logaritmo natural
    
*/
typedef struct Ponto{
       double x; //coordenada do ponto no eixo x
       double y; //coordenada do ponto no eixo y
}Ponto;

int main(){
    //definindo funcao a ser utilizada
    void converter(int n, char s[]);

    //constantes do programa
    const int largura = 1000;
    const int altura = 700;
    
    //variaveis do programa
    char valor[21], digito[2];
    int tecla, okA = FALSE, okB = FALSE, okC = FALSE, okD = FALSE, okTipo = FALSE, okCalcular = FALSE;
    int okMaisA = FALSE, okMaisB = FALSE, okMaisC = FALSE, okMaisD = FALSE; //flags I
    int okMenosA = FALSE, okMenosB = FALSE, okMenosC = FALSE, okMenosD = FALSE; //flags II
    int tam = (int)( (abs(MIN) + abs(MAX)) / PASSO ); //calculando tamanho do vetor que ira armazenar os pontos
    int tipoFuncao = 1, index, frames = 0;
    double x = 0, y = 0; //vao guardar os dados da funcao f(x) = y
    int a = 0, b = 0, c = 0, d = 0; //coeficientes da funcao f(x)
    Ponto pontos[tam]; //vai guardar os pontos (x, y) gerados pela funcao f(x) = y no intervalo de [MIN, MAX]
    
    //Paineis e botoes do menu de configuracao
    Rectangle menu = {0, 0, 300, altura};
    Rectangle funcaoAtual = {20, 20, 260, 40};
    Rectangle botaoCalcular = {80, 80, 120, 40}; //botao na posicao (80, 80) com dimensoes 120x40
    Rectangle botaoTipoFuncao = {200, 140, 80, 40}; 
    Rectangle botaoA = {200, 200, 80, 40};
    Rectangle botaoB = {200, 260, 80, 40};
    Rectangle botaoC = {200, 320, 80, 40};
    Rectangle botaoD = {200, 380, 80, 40};
    Rectangle botaoMaisA = {180, 200, 10, 10};
    Rectangle botaoMenosA = {180, 230, 10, 10};
    Rectangle botaoMaisB = {180, 260, 10, 10};
    Rectangle botaoMenosB = {180, 290, 10, 10};
    Rectangle botaoMaisC = {180, 320, 10, 10};
    Rectangle botaoMenosC = {180, 360, 10, 10};
    Rectangle botaoMaisD = {180, 380, 10, 10};
    Rectangle botaoMenosD = {180, 410, 10, 10};
    
    //Iniciando tela e FPS
    InitWindow( largura, altura, "Graphical");
    
    SetTargetFPS(60);
    
    //Loop principal
    while (!WindowShouldClose()){
        //Update do programa
        frames++; 
        
        //checando toques no menu de configuracoes
        if ( CheckCollisionPointRec( GetMousePosition(), botaoTipoFuncao) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            strcpy(valor, ""); //resetando valor
            okTipo = TRUE;
            okCalcular = FALSE;
            okA = FALSE;
            okB = FALSE;
            okC = FALSE;
        }
        if ( CheckCollisionPointRec( GetMousePosition(), botaoCalcular) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            okTipo = FALSE;
            okCalcular = TRUE;
            okA = FALSE;
            okB = FALSE;
            okC = FALSE;
        }
        if ( CheckCollisionPointRec( GetMousePosition(), botaoA) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            strcpy(valor, ""); //resetando valor
            okTipo = FALSE;
            okCalcular = FALSE;
            okA = TRUE;
            okB = FALSE;
            okC = FALSE;
        }
        if ( CheckCollisionPointRec( GetMousePosition(), botaoB) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            strcpy(valor, ""); //resetando valor
            okTipo = FALSE;
            okCalcular = FALSE;
            okA = FALSE;
            okB = TRUE;
            okC = FALSE;
        }
        if ( CheckCollisionPointRec( GetMousePosition(), botaoC) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            strcpy(valor, ""); //resetando valor
            okTipo = FALSE;
            okCalcular = FALSE;
            okA = FALSE;
            okB = FALSE;
            okC = TRUE;
        }
        if ( CheckCollisionPointRec( GetMousePosition(), botaoD) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            strcpy(valor, ""); //resetando valor
            okTipo = FALSE;
            okCalcular = FALSE;
            okA = FALSE;
            okB = FALSE;
            okC = FALSE;
            okD = TRUE;
        }
        if ( CheckCollisionPointRec( GetMousePosition(), botaoMaisA) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) okMaisA = TRUE;
        if ( CheckCollisionPointRec( GetMousePosition(), botaoMenosA) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) okMenosA = TRUE;
        if ( CheckCollisionPointRec( GetMousePosition(), botaoMaisB) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) okMaisB = TRUE;
        if ( CheckCollisionPointRec( GetMousePosition(), botaoMenosB) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) okMenosB = TRUE;
        if ( CheckCollisionPointRec( GetMousePosition(), botaoMaisC) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) okMaisC = TRUE;
        if ( CheckCollisionPointRec( GetMousePosition(), botaoMenosC) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) okMenosC = TRUE;
        if ( CheckCollisionPointRec( GetMousePosition(), botaoMaisD) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) okMaisD = TRUE;
        if ( CheckCollisionPointRec( GetMousePosition(), botaoMenosD) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) okMenosD = TRUE;
        
        //opcao Tipo da Funcao escolhida...
        if ( okTipo ){
            //verificando se houve algum input do usuario
            tecla = GetKeyPressed();
            //Verificando se a tecla apertada foi um numero
            if ( tecla >= 48 && tecla <= 57) {
                converter((tecla-48), digito); //convertendo int em string na base decimal
                strcat(valor, digito); //acrescentando digito ao numero de valor
                tipoFuncao = atoi(valor); //convertendo string em long int
            }
        }
        //opcao botao A, B ou C escolhido...
        if ( okA || okB || okC || okD){
            //verificando se houve algum input do usuario
            tecla = GetKeyPressed();
            //Verificando se a tecla apertada foi um numero
            if ( tecla >= 48 && tecla <= 57) {
                converter((tecla-48), digito); //convertendo int em string na base decimal
                strcat(valor, digito); //acrescentando digito ao numero de valor
                if ( okA ) a = atoi(valor); //convertendo string em long int
                else if ( okB ) b = atoi(valor); //convertendo string em long int
                else if ( okC ) c = atoi(valor); //convertendo string em long int
                else if ( okD ) d = atoi(valor); //convertendo string em long int
            }
        }
        //opcao de incremento ou decremento nos coeficientes a, b, c ou d
        if ( okMaisA || okMaisB || okMaisC || okMaisD ||
             okMenosA || okMenosB || okMenosC || okMenosD){
            if ( okMaisA ) {
                a += 1;
                okMaisA = FALSE; //desativando incremento
            }
            else if ( okMaisB ) {
                b += 1;
                okMaisB = FALSE; //desativando incremento
            }
            else if ( okMaisC ) {
                c += 1;
                okMaisC = FALSE; //desativando incremento
            }
            else if ( okMaisD ) {
                d += 1;
                okMaisD = FALSE; //desativando incremento
            }
            else if ( okMenosA) {
                a -= 1;
                okMenosA = FALSE; //desativando decremento
            }
            else if ( okMenosB) {
                b -= 1;
                okMenosB = FALSE; //desativando decremento
            }
            else if ( okMenosC) {
                c -= 1;
                okMenosC = FALSE; //desativando decremento
            }
            else if ( okMenosD) {
                d -= 1;
                okMenosD = FALSE; //desativando decremento
            }
        }           
        
        //opcao Calcular escolhida...
        if ( okCalcular){                                                           
            //percorrendo valores de x e jogando na funcao f(x), gerando assim valores y
            index = 0; //necessario para acompanhar o acesso ao vetor de pontos
            for( x=MIN; x <=MAX; x+=PASSO){
                if ( tipoFuncao == 1) y = (x*a) + b;
                else if ( tipoFuncao == 2) y = a*((x)*(x)) + (x*b) + c;
                else if ( tipoFuncao == 3) y = a*((x)*(x)*(x)) + b*((x)*(x)) + (x*c) + d;
                else if ( tipoFuncao == 4) y = pow(a, x+b) + c;
                else if ( tipoFuncao == 5) y = a * sin(x*b) + c;
                else if ( tipoFuncao == 6) y = a * cos(x*b) + c;
                else if ( tipoFuncao == 7) y = a * tan(x*b) + c;
                else if ( tipoFuncao == 8) y = a * sinh(x*b) + c;
                else if ( tipoFuncao == 9) y = a * cosh(x*b) + c;
                else if ( tipoFuncao == 10) y = a * log10(x*b) + c;
                else if ( tipoFuncao == 11) y = a * log(x*b) + c;
                else break; //parar de calcular pois o tipo da funcao eh invalido!
                //armazenando resultados dos valores de x e y no vetor de pontos
                pontos[index].x = x;
                pontos[index].y = y;
                //atualizando index
                index++;
            }
            //desativando calculo pois tudo ja foi calculado (apenas 1 vez)
            okCalcular = FALSE;
        }
        
        //Draw do programa
        BeginDrawing();
            ClearBackground(BLACK);
       
            //desenhando menu de configuracao
            DrawRectangleRec(menu, BLACK);
            DrawRectangleLines(menu.x, menu.y, menu.width, menu.height, WHITE);
            DrawRectangleRec(funcaoAtual, GRAY); //visor que mostra a funcao atual sendo calculada
            //imprimindo funcao atual 
            if ( tipoFuncao == 1){
                DrawText(FormatText("F(x) = %d x + %d", a, b), funcaoAtual.x+10, funcaoAtual.y+10, 20, WHITE);
            }
            else if ( tipoFuncao == 2){
                DrawText(FormatText("F(x) = %dx² + %dx + %d", a, b, c), funcaoAtual.x+10, funcaoAtual.y+10, 20, WHITE);
            }
            else if ( tipoFuncao == 3){
                DrawText(FormatText("F(x) = %dx³ + %dx² + %dx + %d", a, b, c, d), funcaoAtual.x+10, funcaoAtual.y+10, 20, WHITE);
            }
            else if ( tipoFuncao == 4){
                DrawText(FormatText("F(x) = %d^(x+%d) + %d", a, b, c), funcaoAtual.x+10, funcaoAtual.y+10, 20, WHITE);
            }
            else if ( tipoFuncao == 5){
                DrawText(FormatText("F(x) = %dsin(x*%d) + %d", a, b, c), funcaoAtual.x+10, funcaoAtual.y+10, 20, WHITE);
            }
            else if ( tipoFuncao == 6){
                DrawText(FormatText("F(x) = %dcos(x*%d) + %d", a, b, c), funcaoAtual.x+10, funcaoAtual.y+10, 20, WHITE);
            }
            else if ( tipoFuncao == 7){
                DrawText(FormatText("F(x) = %dtan(x*%d) + %d", a, b, c), funcaoAtual.x+10, funcaoAtual.y+10, 20, WHITE);
            }
            else if ( tipoFuncao == 8){
                DrawText(FormatText("F(x) = %dsinh(x*%d) + %d", a, b, c), funcaoAtual.x+10, funcaoAtual.y+10, 20, WHITE);
            }
            else if ( tipoFuncao == 9){
                DrawText(FormatText("F(x) = %dcosh(x*%d) + %d", a, b, c), funcaoAtual.x+10, funcaoAtual.y+10, 20, WHITE);
            }
            else if ( tipoFuncao == 10){
                DrawText(FormatText("F(x) = %dlog10(x*%d) + %d", a, b, c), funcaoAtual.x+10, funcaoAtual.y+10, 20, WHITE);
            }
            else if ( tipoFuncao == 11){
                DrawText(FormatText("F(x) = %dlog(x*%d) + %d", a, b, c), funcaoAtual.x+10, funcaoAtual.y+10, 20, WHITE);
            }
            DrawRectangleRec(botaoCalcular, WHITE); //botao para iniciar o calculo da funcao selecionada
            DrawText(FormatText("CALCULAR"), botaoCalcular.x+10, botaoCalcular.y+10, 20, BLACK);
            
            DrawText(FormatText("Tipo da funcao: "), 20, 150, 20, WHITE); //texto informativo
            DrawRectangleRec(botaoTipoFuncao, WHITE); //botao para informar o tipo da funcao (numero)
            DrawText(FormatText("%d", tipoFuncao), botaoTipoFuncao.x+10, botaoTipoFuncao.y+10, 20, BLACK); //printando tipo da funcao
            
            DrawText(FormatText("Coeficiente a:"), 20, 210, 20, WHITE); //texto informativo
            DrawRectangleRec(botaoA, WHITE); //botao para informar o coeficiente de f(x)(numero)
            DrawText(FormatText("%d", a), botaoA.x+10, botaoA.y+10, 20, BLACK); //printando coeficiente a atual
            DrawRectangleRec(botaoMaisA, GREEN); //botao para incrementar +1 o coeficiente a
            DrawText(FormatText("+"), botaoMaisA.x+2, botaoMaisA.y-2, 15, BLACK); //sinal de + para sinalizar incremento
            DrawRectangleRec(botaoMenosA, RED); //botao para decrementar -1 o coeficiente a
            DrawText(FormatText("-"), botaoMenosA.x+2, botaoMenosA.y, 15, BLACK); //sinal de - para sinalizar decremento
            
            DrawText(FormatText("Coeficiente b:  "), 20, 270, 20, WHITE); //texto informativo
            DrawRectangleRec(botaoB, WHITE); //botao para informar o coeficiente de f(x)(numero)
            DrawText(FormatText("%d", b), botaoB.x+10, botaoB.y+10, 20, BLACK); //printando coeficiente b atual
            DrawRectangleRec(botaoMaisB, GREEN); //botao para incrementar +1 o coeficiente b
            DrawText(FormatText("+"), botaoMaisB.x+2, botaoMaisB.y-2, 15, BLACK); //sinal de + para sinalizar incremento
            DrawRectangleRec(botaoMenosB, RED); //botao para decrementar -1 o coeficiente b
            DrawText(FormatText("-"), botaoMenosB.x+2, botaoMenosB.y, 15, BLACK); //sinal de - para sinalizar decremento
            
            DrawText(FormatText("Coeficiente c:  "), 20, 330, 20, WHITE); //texto informativo
            DrawRectangleRec(botaoC, WHITE); //botao para informar o coeficiente de f(x)(numero)
            DrawText(FormatText("%d", c), botaoC.x+10, botaoC.y+10, 20, BLACK); //printando coeficiente c atual
            DrawRectangleRec(botaoMaisC, GREEN); //botao para incrementar +1 o coeficiente c
            DrawText(FormatText("+"), botaoMaisC.x+2, botaoMaisC.y-2, 15, BLACK); //sinal de + para sinalizar incremento
            DrawRectangleRec(botaoMenosC, RED); //botao para decrementar -1 o coeficiente c
            DrawText(FormatText("-"), botaoMenosC.x+2, botaoMenosC.y, 15, BLACK); //sinal de - para sinalizar decremento
            
            DrawText(FormatText("Coeficiente d:  "), 20, 390, 20, WHITE); //texto informativo
            DrawRectangleRec(botaoD, WHITE); //botao para informar o coeficiente de f(x)(numero)
            DrawText(FormatText("%d", d), botaoD.x+10, botaoD.y+10, 20, BLACK); //printando coeficiente d atual
            DrawRectangleRec(botaoMaisD, GREEN); //botao para incrementar +1 o coeficiente d
            DrawText(FormatText("+"), botaoMaisD.x+2, botaoMaisD.y-2, 15, BLACK); //sinal de + para sinalizar incremento
            DrawRectangleRec(botaoMenosD, RED); //botao para decrementar -1 o coeficiente d
            DrawText(FormatText("-"), botaoMenosD.x+2, botaoMenosD.y, 15, BLACK); //sinal de - para sinalizar decremento
            
            //desenhando divisorias dos quadrantes
            DrawLine( (largura/2) + 150, 0, (largura/2) + 150, altura, RAYWHITE);
            DrawLine( 300, altura/2, largura, altura/2, RAYWHITE);
            //percorrendo vetor e desenhando os pontos de acordo com suas coordenadas e com raio = 1, na cor branca
            for(index=0; index<tam; index++){
                //modificando pontos para que possam ser mostrados de acordo com os 4 quadrantes
                if ( (pontos[index].x + (largura/2) + 150) > 300 &&
                     (pontos[index].y + (altura/2)) >= 0  &&
                     (pontos[index].y + (altura/2)) <= altura ){ //somente imprimindo pontos dentro dos quadrantes
                    DrawCircle( pontos[index].x + (largura/2) + 150, pontos[index].y + (altura/2), 1, WHITE);
                }
            }
            
            DrawText(FormatText("frames: %d", frames), 10, 600, 20, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}

//funcoes necessarias para converter int em char
void converter(int n, char s[]) {
    //definicao da funcao
    void reverse(char s[]);

    int i, sign;

    if ((sign = n) < 0)  /* record sign */
     n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
     s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
     s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
} 
